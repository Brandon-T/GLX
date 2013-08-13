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

#ifndef _SMART_PLUGIN
#define _SMART_PLUGIN

#include "Graphics.hpp"

typedef void (*_SMARTGetMousePos)(int &x, int &y);
typedef void (*_SMARTSetCapture)(bool enabled);
typedef void (*_SMARTButtonPressed)(int id, bool state);

typedef struct
{
    int version;
    void *img, *dbg;
    int width, height;
    _SMARTGetMousePos getMousePos;
    _SMARTSetCapture setCapture;
} SMARTInfo;



typedef void (*_SMARTPluginInit)(SMARTInfo* ptr, bool* ReplaceButtons, int* ButtonCount, char*** ButtonText, int** ButtonIDs, _SMARTButtonPressed* ButtonCallback);

extern SMARTInfo* SmartGlobal;
extern bool SmartDebugEnabled;
extern bool SmartOpenGLEnabled;
void BltSmartBuffer();


#endif
