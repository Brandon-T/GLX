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

#ifndef EXPORTS_HPP_INCLUDED
#define EXPORTS_HPP_INCLUDED

#include <cstring>
#include <vector>
#include <memory>
#include "Platform.hpp"
#include "Structures.hpp"
#include "SharedMemory.hpp"

#define ExportCount         18
#define SharedImageSize     8294400     //Highest Resolution Support: 1920 x 1080 x sizeof(RGBA)
#define TotalImageSize      (SharedImageSize * 2)  //Image + DebugImage
#define SharedHookSize      5000000

extern char* Exports[];
extern HINSTANCE hInstance;
extern unsigned long int EVENT_TIMEOUT;

extern std::string SharedImageName;
extern std::string SharedHookName;
extern std::unique_ptr<SharedMemory> SharedImageData;
extern std::unique_ptr<SharedMemory> SharedHookData;

extern "C" int __declspec(dllexport) GetPluginABIVersion();
extern "C" int __declspec(dllexport) GetFunctionCount();
extern "C" int __declspec(dllexport) GetFunctionInfo(int Index, void* &Address, char* &Definition);

extern "C" bool __declspec(dllexport) GLXSetup(int ProcessID);
extern "C" bool __declspec(dllexport) GLXMapHooks(int ProcessID);
extern "C" void* __declspec(dllexport) GLXImagePointer();
extern "C" void* __declspec(dllexport) GLXDebugPointer();
extern "C" bool __declspec(dllexport) GLXViewPort(int &X1, int &Y1, int &X2, int &Y2);
extern "C" Texture* __declspec(dllexport) GLXTextures(std::uint32_t &Size);
extern "C" Model* __declspec(dllexport) GLXModels(std::uint32_t &Size);
extern "C" Font* __declspec(dllexport) GLXFonts(std::uint32_t &Size);
extern "C" Matrices* __declspec(dllexport) GLXMatrices();
extern "C" std::uint8_t* __declspec(dllexport) GLXMap(int &Width, int &Height, float X[4], float Y[4]);
extern "C" bool __declspec(dllexport) GLXMapCoords(float X[4], float Y[4]);
extern "C" bool __declspec(dllexport) GLXDebug(std::uint32_t Mode, std::uint32_t TextureID, std::uint32_t ColourID, std::uint32_t FullColourID, int Tolerance, int X1, int Y1, int X2, int Y2);
extern "C" bool __declspec(dllexport) GLXSetFontCapture(bool Enabled);
extern "C" bool __declspec(dllexport) GLXSetColourCapture(bool Enabled);
extern "C" bool __declspec(dllexport) GLXSaveTextures();
extern "C" int __declspec(dllexport) GLXUTF8ToUTF16(char* utf8, wchar_t* utf16);
extern "C" int __declspec(dllexport) GLXUTF16ToUTF8(wchar_t* utf16, char* utf8);
extern "C" void __declspec(dllexport) GLXSetTimeout(unsigned long int timeout);

extern void GetDesktopResolution(int &width, int &height);
extern bool CreateSharedMemory(int ProcessID);
extern bool OpenSharedMemory(int ProcessID);
extern bool MapHooks(int ProcessID);
extern bool UnMapSharedMemory();

#endif // EXPORTS_HPP_INCLUDED
