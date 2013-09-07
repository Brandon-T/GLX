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

#include "Communication.hpp"

DebugGraphics Debugger;
bool Initialized = false;
bool ColourBufferEnabled = true;
std::unique_ptr<SharedMemory> SharedImageData;
std::unique_ptr<SharedMemory> SharedHookData;
const char* SharedImageName = "Local\\GLXImage_";
const char* SharedHookName = "Local\\GLXHooks_";
std::string ReplyEventName = "GLXReply_";
std::string RequestEventName = "GLXRequest_";

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
    SharedHookData->CreateNewEvent(nullptr, true, false, ReplyEventName);
    return SharedHookData->MapMemory(SharedHookSize) || SharedHookData->OpenMemoryMap(SharedHookSize);
}

bool UnMapSharedMemory()
{
    SharedHookData->DeleteAllEvents();
    SharedImageData.reset(nullptr);
    SharedHookData.reset(nullptr);
    return true;
}

void ProcessRequests()
{
    char* Data = static_cast<char*>(SharedHookData->GetDataPointer());
    switch (SharedHookData->OpenSingleEvent(RequestEventName, true, true, EVENT_ALL_ACCESS, 0))
    {
        case WAIT_OBJECT_0:
        {
            switch(ReadPointer<int>(Data))
            {
                case GLX_ViewPort:
                {
                    GLint ViewPort[4];
                    glGetIntegerv(GL_VIEWPORT, ViewPort);
                    WritePointer(Data, ViewPort[0]);
                    WritePointer(Data, ViewPort[1]);
                    WritePointer(Data, ViewPort[2]);
                    WritePointer(Data, ViewPort[3]);
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_Textures:
                {
                    Serialize S(Data, SharedHookSize);
                    S << Texture::Textures;
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_Models:
                {
                    Serialize S(Data, SharedHookSize);
                    S << Model::Models;
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_Fonts:
                {
                    Serialize S(Data, SharedHookSize);
                    S << Font::RenderedFonts;
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_Matrices:
                {
                    Serialize S(Data, SharedHookSize);
                    S << InfoLogger.matrices;
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_Map:
                {
                    InfoLogger.map.width = ReadPointer<int>(Data);
                    InfoLogger.map.height = ReadPointer<int>(Data);
                    Serialize S(Data, SharedHookSize);
                    S << InfoLogger.map;
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_MapCoords:
                {
                    for (int I = 0; I < 4; ++I)
                    {
                        WritePointer(Data, InfoLogger.map.X[I]);
                        WritePointer(Data, InfoLogger.map.Y[I]);
                    }
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_Debug:
                {
                    Debugger.SetMode(ReadPointer<std::uint32_t>(Data));
                    Debugger.SetTexture(ReadPointer<std::uint32_t>(Data));
                    int X1 = ReadPointer<int>(Data);
                    int Y1 = ReadPointer<int>(Data);
                    int X2 = ReadPointer<int>(Data);
                    int Y2 = ReadPointer<int>(Data);
                    Debugger.SetArea(X1, Y1, X2, Y2);
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_ColourBuffer:
                {
                    ColourBufferEnabled = ReadPointer<int>(Data);
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                case GLX_SaveTexture:
                {
                    std::uint32_t TextureID = ReadPointer<std::uint32_t>(Data);
                    std::uint32_t TextureType = ReadPointer<std::uint32_t>(Data);
                    InfoLogger.Save(TextureID, TextureType);
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    SharedHookData->SetEventSignal(ReplyEventName, true);
                }
                break;

                default:
                    SharedHookData->SetEventSignal(RequestEventName, false);
                    break;
            }
        }
        break;

        default:
            SharedHookData->SetEventSignal(RequestEventName, false);
            break;
    }
}
