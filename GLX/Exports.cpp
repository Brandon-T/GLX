#include "Exports.hpp"

HINSTANCE hInstance = nullptr;
std::unique_ptr<SharedMemory> SharedImageData;
std::unique_ptr<SharedMemory> SharedHookData;
std::string SharedImageName = "Local\\GLXImage_";
std::string SharedHookName = "Local\\GLXHooks_";
std::string ReplyEventName = "GLXReply_";
std::string RequestEventName = "GLXRequest_";

char* Exports[] = {
    (char*)"GLXSetup", (char*)"Function GLXSetup(ProcessID: Integer): Boolean;",
    (char*)"GLXImagePointer", (char*)"Function GLXImagePointer: Pointer;",
    (char*)"GLXDebugPointer", (char*)"Function GLXDebugPointer: Pointer;",
    (char*)"GLXMapHooks", (char*)"Function GLXMapHooks(ProcessID: Integer): Boolean;",
    (char*)"GLXViewPort", (char*)"Procedure GLXViewPort(var X1, Y1, X2, Y2: Integer);",
    (char*)"GLXTextures", (char*)"Function GLXTextures(var Size: Cardinal): Pointer;",
    (char*)"GLXModels", (char*)"Function GLXModels(var Size: Cardinal): Pointer;",
    (char*)"GLXFonts", (char*)"Function GLXFonts(var Size: Cardinal): Pointer;",
    (char*)"GLXMatrices", (char*)"Function GLXMatrices: Pointer;",
    (char*)"GLXMap", (char*)"Function GLXMap(var Width, Height: Integer; var X, Y: array[0..3] of Single): Pointer;",
    (char*)"GLXMapCoords", (char*)"Procedure GLXMapCoords(var X, Y: array[0..3] of single);",
    (char*)"GLXDebug", (char*)"Procedure GLXDebug(Mode, HudID: Cardinal; X1, Y1, X2, Y2: Integer);",
    (char*)"GLXSetColourCapture", (char*)"Procedure GLXSetColourCapture(Enable: Boolean);"
};

extern "C" bool __declspec(dllexport) GLXSetup(int ProcessID)
{
    return (CreateSharedMemory(ProcessID) || OpenSharedMemory(ProcessID));
}

extern "C" bool __declspec(dllexport) GLXMapHooks(int ProcessID)
{
    return MapHooks(ProcessID);
}

extern "C" void* __declspec(dllexport) GLXImagePointer()
{
    return SharedImageData ? SharedImageData->GetDataPointer() : nullptr;
}

extern "C" void* __declspec(dllexport) GLXDebugPointer()
{
    return SharedImageData ? reinterpret_cast<std::uint8_t*>(SharedImageData->GetDataPointer()) + SharedImageSize : nullptr;
}

extern "C" void __declspec(dllexport) GLXViewPort(int &X1, int &Y1, int &X2, int &Y2)
{
    X1 = X2 = Y1 = Y2 = 0;
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_ViewPort);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        X1 = ReadPointer<int>(Data);
        Y1 = ReadPointer<int>(Data);
        X2 = ReadPointer<int>(Data);
        Y2 = ReadPointer<int>(Data);
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
}

extern "C" Texture* __declspec(dllexport) GLXTextures(std::uint32_t &Size)
{
    Size = 0;
    LoT.clear();
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Textures);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        DeSerialize D(Data, SharedHookSize);
        D >> LoT;
        SharedHookData->SetEventSignal(ReplyEventName, false);
        Size = LoT.size();
        return LoT.data();
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

extern "C" Model* __declspec(dllexport) GLXModels(std::uint32_t &Size)
{
    Size = 0;
    LoM.clear();
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Models);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        DeSerialize D(Data, SharedHookSize);
        D >> LoM;
        SharedHookData->SetEventSignal(ReplyEventName, false);
        Size = LoM.size();
        return LoM.data();
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

extern "C" Font* __declspec(dllexport) GLXFonts(std::uint32_t &Size)
{
    Size = 0;
    LoF.clear();
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Fonts);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        DeSerialize D(Data, SharedHookSize);
        D >> LoF;
        SharedHookData->SetEventSignal(ReplyEventName, false);
        Size = LoF.size();
        return LoF.data();
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

extern "C" Matrices* GLXMatrices()
{
    std::memset(&matrices.ModelView[0], 0, matrices.ModelView.size() * sizeof(float));
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Matrices);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        DeSerialize D(Data, SharedHookSize);
        D >> matrices;
        SharedHookData->SetEventSignal(ReplyEventName, false);
        return &matrices;
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

extern "C" std::uint8_t* GLXMap(int &Width, int &Height, float X[4], float Y[4])
{
    map.Pixels.clear();
    std::memset(&map, 0, (sizeof(float) * 8) + (sizeof(int) * 3));
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Map);
    WritePointer(Data, Width);
    WritePointer(Data, Height);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        DeSerialize D(Data, SharedHookSize);
        D >> map;
        SharedHookData->SetEventSignal(ReplyEventName, false);
        Width = map.Width;
        Height = map.Height;
        std::memcpy(&X[0], &map.X[0], sizeof(float) * 4);
        std::memcpy(&Y[0], &map.Y[0], sizeof(float) * 4);
        return map.Pixels.data();
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

extern "C" void GLXMapCoords(float X[4], float Y[4])
{
    std::memset(X, 0, sizeof(float) * 4);
    std::memset(Y, 0, sizeof(float) * 4);
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_MapCoords);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true) == WAIT_OBJECT_0)
    {
        for (int I = 0; I < 4; ++I)
        {
            X[I] = ReadPointer<float>(Data);
            Y[I] = ReadPointer<float>(Data);
        }
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
}

extern "C" void GLXDebug(std::uint32_t Mode, std::uint32_t HudID, int X1, int Y1, int X2, int Y2)
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Debug);
    WritePointer(Data, Mode);
    WritePointer(Data, HudID);
    WritePointer(Data, X1);
    WritePointer(Data, Y1);
    WritePointer(Data, X2);
    WritePointer(Data, Y2);
    SharedHookData->SetEventSignal(RequestEventName, true);
    SharedHookData->OpenSingleEvent(ReplyEventName, true, true);
    SharedHookData->SetEventSignal(ReplyEventName, false);
}

void GLXSetColourCapture(bool Enabled)
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_ColourBuffer);
    WritePointer(Data, Enabled ? 1 : 0);
    SharedHookData->SetEventSignal(RequestEventName, true);
    SharedHookData->OpenSingleEvent(ReplyEventName, true, true);
    SharedHookData->SetEventSignal(ReplyEventName, false);
}

                                                    /** Internal API **/

extern "C" int __declspec(dllexport) GetPluginABIVersion()
{
    return 2;
}

extern "C" int __declspec(dllexport) GetFunctionCount()
{
    return ExportCount;
}

extern "C" int __declspec(dllexport) GetFunctionInfo(int Index, void* &Address, char* &Definition)
{
    if (Index < ExportCount)
    {
        Address = reinterpret_cast<void*>(GetProcAddress(hInstance, Exports[Index * 2]));
		#ifdef _MSC_VER
		#pragma warning(disable: 4996)
		strcpy(Definition, Exports[Index * 2 + 1]);
        //strcpy_s(Definition, Exports[Index * 2 + 1]);
		#else
		strcpy(Definition, Exports[Index * 2 + 1]);
		#endif
        return Index;
    }
    return -1;
}

void GetDesktopResolution(int &width, int &height)
{
    #if defined _WIN32 || defined _WIN64
    RECT desktop = {0};
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    width = desktop.right;
    height = desktop.bottom;
    #endif
}

bool CreateSharedMemory(int ProcessID)
{
    int Width = 0, Height = 0;
    GetDesktopResolution(Width, Height);
    SharedImageData.reset(new SharedMemory(SharedImageName + std::to_string(ProcessID)));
    return SharedImageData->MapMemory(Width || Height == 0 ? TotalImageSize : Width * Height * 4 * 2);
}

bool OpenSharedMemory(int ProcessID)
{
    int Width = 0, Height = 0;
    GetDesktopResolution(Width, Height);
    SharedImageData.reset(new SharedMemory(SharedImageName + std::to_string(ProcessID)));
    return SharedImageData->OpenMemoryMap(Width || Height == 0 ? SharedImageSize : Width * Height * 4 * 2);
}

bool MapHooks(int ProcessID)
{
    ReplyEventName = "GLXReply_" + std::to_string(ProcessID);
    RequestEventName = "GLXRequest_" + std::to_string(ProcessID);
    SharedHookData.reset(new SharedMemory(SharedHookName + std::to_string(ProcessID)));
    SharedHookData->DeleteAllEvents();
    SharedHookData->CreateNewEvent(nullptr, true, false, RequestEventName);
    return SharedHookData->MapMemory(SharedHookSize) || SharedHookData->OpenMemoryMap(SharedHookSize);
}

bool UnMapSharedMemory()
{
    SharedImageData.reset(nullptr);
    SharedHookData.reset(nullptr);
    return true;
}
