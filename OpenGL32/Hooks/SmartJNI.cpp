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

#include "SmartPlugin.hpp"

unsigned int Texture = 0;
SMARTInfo* SmartGlobal = nullptr;
bool SmartDebugEnabled = false;
bool SmartOpenGLEnabled = true;

void SMARTButtonPressed(int ID, bool State)
{
    switch(ID)
    {
        case 100:
            if (State)
            {
                SmartGlobal->setCapture(false);
                SmartOpenGLEnabled = true;
            }
            else
            {
                SmartGlobal->setCapture(true);
                SmartOpenGLEnabled = false;
            }
            break;

        case 101:
            SmartDebugEnabled = State ? false : true;
            break;

    }
}

extern "C" void SMARTPluginInit(SMARTInfo* ptr, bool* ReplaceButtons, int* ButtonCount, char*** ButtonText, int** ButtonIDs, _SMARTButtonPressed* ButtonCallback)
{
    SmartGlobal = ptr;
    if (ptr)
    {
        *ReplaceButtons = true;
        char** ButtonTexts = new char*[2];
        ButtonTexts[0] = const_cast<char*>("Disable OpenGL_Enable OpenGL");
        ButtonTexts[1] = const_cast<char*>("Enable Debug_Disable Debug");

        int* IDs = new int[2];
        IDs[0] = 100;
        IDs[1] = 101;

        *ButtonCount = 2;
        *ButtonText = ButtonTexts;
        *ButtonIDs = IDs;
        *ButtonCallback = &SMARTButtonPressed;
    }
}

void BltSmartBuffer()
{
    if (SmartGlobal != nullptr)
    {
        if (Texture == 0)
        {
            Texture = LoadTexture(SmartGlobal->dbg, SmartGlobal->width, SmartGlobal->height, GL_TEXTURE_RECTANGLE);
        }
        else
        {
            std::vector<std::uint8_t> Pixels(SmartGlobal->width * SmartGlobal->height * 4);
            void* P = Pixels.data();
            FlipImageBytes(SmartGlobal->dbg, P, SmartGlobal->width, SmartGlobal->height);
            glEnable(GL_TEXTURE_RECTANGLE);
            glBindTexture(GL_TEXTURE_RECTANGLE, Texture);
            glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, SmartGlobal->width, SmartGlobal->height, GL_BGRA, GL_UNSIGNED_BYTE, Pixels.data());
            glDisable(GL_TEXTURE_RECTANGLE);
        }

        std::uint8_t* Ptr = (std::uint8_t*)SmartGlobal->dbg;
        for (int I = 0; I < SmartGlobal->height; ++I)
        {
            for (int J = 0; J < SmartGlobal->width; ++J)
            {
                std::uint8_t B = *(Ptr++);
                std::uint8_t G = *(Ptr++);
                std::uint8_t R = *(Ptr++);
                *(Ptr++) = (B == 0 && G == 0 && R == 0) ? 0 : 0xFF;
            }
        }

        DrawTexture(GL_TEXTURE_RECTANGLE, Texture, 0, 0, SmartGlobal->width, SmartGlobal->height, SmartGlobal->width, SmartGlobal->height);
    }
}
