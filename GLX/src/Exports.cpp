/**  © 2013, Brandon T. All Rights Reserved.
  *
  *  This file is part of the GLX Library.
  *  GLX is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  GLX is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with GLX.  If not, see <http://www.gnu.org/licenses/>.
  */

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
    (char*)"GLXViewPort", (char*)"Function GLXViewPort(var X1, Y1, X2, Y2: Integer): Boolean;",
    (char*)"GLXTextures", (char*)"Function GLXTextures(var Size: Cardinal): Pointer;",
    (char*)"GLXModels", (char*)"Function GLXModels(var Size: Cardinal): Pointer;",
    (char*)"GLXFonts", (char*)"Function GLXFonts(var Size: Cardinal): Pointer;",
    (char*)"GLXMatrices", (char*)"Function GLXMatrices: Pointer;",
    (char*)"GLXMap", (char*)"Function GLXMap(var Width, Height: Integer; var X, Y: array[0..3] of Single): Pointer;",
    (char*)"GLXMapCoords", (char*)"Function GLXMapCoords(var X, Y: array[0..3] of single): Boolean;",
    (char*)"GLXDebug", (char*)"Function GLXDebug(Mode, TextureID, ColourID, FullColourID: Cardinal; Tolerance, X1, Y1, X2, Y2: Integer): Boolean;",
    (char*)"GLXSetColourCapture", (char*)"Function GLXSetColourCapture(Enable: Boolean): Boolean;",
    (char*)"GLXSetFontCapture", (char*)"Function GLXSetFontCapture(Enable: Boolean): Boolean;",
    (char*)"GLXSaveTexture", (char*)"Function GLXSaveTextures: Boolean;",
    (char*)"GLXUTF8ToUTF16", (char*)"Function GLXUTF8ToUTF16(UTF8, UTF16: Pointer): Integer;",
    (char*)"GLXUTF16ToUTF8", (char*)"Function GLXUTF16ToUTF8(UTF16, UTF8: Pointer): Integer;"
};

bool GLXSetup(int ProcessID)
{
    return (CreateSharedMemory(ProcessID) || OpenSharedMemory(ProcessID));
}

bool GLXMapHooks(int ProcessID)
{
    return MapHooks(ProcessID);
}

void* GLXImagePointer()
{
    return SharedImageData ? SharedImageData->GetDataPointer() : nullptr;
}

void* GLXDebugPointer()
{
    return SharedImageData ? reinterpret_cast<std::uint8_t*>(SharedImageData->GetDataPointer()) + SharedImageSize : nullptr;
}

bool GLXViewPort(int &X1, int &Y1, int &X2, int &Y2)
{
    bool result = false;
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_ViewPort);
    WritePointer(Data, X1);
    WritePointer(Data, Y1);
    WritePointer(Data, X2);
    WritePointer(Data, Y2);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
    {
        X1 = ReadPointer<int>(Data);
        Y1 = ReadPointer<int>(Data);
        X2 = ReadPointer<int>(Data);
        Y2 = ReadPointer<int>(Data);
        result = true;
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return result;
}

Texture* GLXTextures(std::uint32_t &Size)
{
    Size = 0;
    LoT.clear();
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Textures);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
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

Model* GLXModels(std::uint32_t &Size)
{
    Size = 0;
    LoM.clear();
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Models);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
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

Font* GLXFonts(std::uint32_t &Size)
{
    Size = 0;
    LoF.clear();
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Fonts);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
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

Matrices* GLXMatrices()
{
    std::memset(&matrices.ModelView[0], 0, matrices.ModelView.size() * sizeof(float));
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Matrices);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
    {
        DeSerialize D(Data, SharedHookSize);
        D >> matrices;
        SharedHookData->SetEventSignal(ReplyEventName, false);
        return &matrices;
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

std::uint8_t* GLXMap(int &Width, int &Height, float X[4], float Y[4])
{
    map.Pixels.clear();
    std::memset(&map.X[0], 0, (sizeof(float) * 8) + (sizeof(int) * 3));
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Map);

    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
    {
        bool Rendered = ReadPointer<bool>(Data);
        for (int I = 0; I < 4; ++I)
        {
            X[I] = ReadPointer<float>(Data);
            Y[I] = ReadPointer<float>(Data);
        }

        if (Rendered)
        {
            DeSerialize D(Data, SharedHookSize);
            D >> map;
            SharedHookData->SetEventSignal(ReplyEventName, false);
            return map.Pixels.data();
        }
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return nullptr;
}

bool GLXMapCoords(float X[4], float Y[4])
{
    bool result = false;
    std::memset(X, 0, sizeof(float) * 4);
    std::memset(Y, 0, sizeof(float) * 4);
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_MapCoords);
    SharedHookData->SetEventSignal(RequestEventName, true);
    if (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0)
    {
        for (int I = 0; I < 4; ++I)
        {
            X[I] = ReadPointer<float>(Data);
            Y[I] = ReadPointer<float>(Data);
        }
        result = true;
    }
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return result;
}

bool GLXDebug(std::uint32_t Mode, std::uint32_t TextureID, std::uint32_t ColourID, std::uint32_t FullColourID, int Tolerance, int X1, int Y1, int X2, int Y2)
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_Debug);
    WritePointer(Data, Mode);
    WritePointer(Data, TextureID);
    WritePointer(Data, ColourID);
    WritePointer(Data, FullColourID);
    WritePointer(Data, Tolerance);
    WritePointer(Data, X1);
    WritePointer(Data, Y1);
    WritePointer(Data, X2);
    WritePointer(Data, Y2);
    SharedHookData->SetEventSignal(RequestEventName, true);
    bool result = (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0);
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return result;
}

bool GLXSetFontCapture(bool Enabled)
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_FontsEnable);
    WritePointer(Data, Enabled ? 1 : 0);
    SharedHookData->SetEventSignal(RequestEventName, true);
    SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT);
    SharedHookData->SetEventSignal(ReplyEventName, false);

    SharedHookData->SetEventSignal(RequestEventName, true);
    bool result = (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0);
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return result;
}

bool GLXSetColourCapture(bool Enabled)
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_ColourBuffer);
    WritePointer(Data, Enabled ? 1 : 0);
    SharedHookData->SetEventSignal(RequestEventName, true);
    SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT);
    SharedHookData->SetEventSignal(ReplyEventName, false);

    SharedHookData->SetEventSignal(RequestEventName, true);
    bool result = (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0);
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return result;
}

bool GLXSaveTextures()
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    WritePointer(Data, GLX_SaveTexture);
    SharedHookData->SetEventSignal(RequestEventName, true);
    bool result = (SharedHookData->OpenSingleEvent(ReplyEventName, true, true, EVENT_ALL_ACCESS, EVENT_TIMEOUT) == WAIT_OBJECT_0);
    SharedHookData->SetEventSignal(ReplyEventName, false);
    return result;
}

int GLXUTF8ToUTF16(char* utf8, wchar_t* utf16)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    if (utf16 != NULL)
    {
        MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16, len);
    }
    return len;
}

int GLXUTF16ToUTF8(wchar_t* utf16, char* utf8)
{
    int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, 0, 0);
    if (utf8 != NULL)
    {
        WideCharToMultiByte(CP_UTF8, 0, utf16, -1, utf8, len, 0, 0);
    }
    return len;
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
