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

#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include <memory>
#include "Structures.hpp"
#include "SharedMemory.hpp"
#include "Debugger.hpp"

#define SharedImageSize     8294400     //Highest Resolution Support: 1920 x 1080 x sizeof(RGBA)
#define TotalImageSize      (SharedImageSize * 2)  //Image + DebugImage
#define SharedHookSize      5000000

#define GLX_ViewPort        1
#define GLX_Textures        2
#define GLX_Models          3
#define GLX_Fonts           4
#define GLX_Matrices        5
#define GLX_Map             6
#define GLX_MapCoords       7
#define GLX_Debug           8
#define GLX_ColourBuffer    9


extern bool Initialized;
extern Logger InfoLogger;
extern DebugGraphics Debugger;
extern const char* SharedImageName;
extern const char* SharedHookName;
extern std::unique_ptr<SharedMemory> SharedImageData;
extern std::unique_ptr<SharedMemory> SharedHookData;

template <typename T>
T ReadPointer(char*& Pointer)
{
    T Result = *(reinterpret_cast<T*>(Pointer));
    Pointer += sizeof(T);
    return Result;
}

template <typename T>
void WritePointer(char*& Pointer, const T& Value)
{
    *(reinterpret_cast<T*>(Pointer)) = Value;
    Pointer += sizeof(T);
}

extern bool ColourBufferEnabled;
extern void GetDesktopResolution(int &width, int &height);
extern bool CreateSharedMemory(int ProcessID);
extern bool OpenSharedMemory(int ProcessID);
extern bool MapHooks(int ProcessID);
extern bool UnMapSharedMemory();
extern void ProcessRequests();

#endif // COMMUNICATION_H_INCLUDED
