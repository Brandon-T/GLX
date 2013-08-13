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

#include "Debugger.hpp"

void DebugGraphics::SetMode(std::uint32_t Mode)
{
    this->Mode = Mode;
}

void DebugGraphics::SetRenderer(Render* Renderer)
{
    this->Renderer = Renderer;
}

void DebugGraphics::SetArea(int X1, int Y1, int X2, int Y2)
{
    this->Filters[this->Mode > 0 ? this->Mode - 1 : 0] = {X1, Y1, X2, Y2};
}

void DebugGraphics::SetTexture(std::uint32_t ID)
{
    this->HudID = ID;
}

void DebugGraphics::Draw()
{
    if (this->Mode == 1)
    {
        for (auto it = Texture::Textures.begin(); it != Texture::Textures.end(); ++it)
        {
            if ((it->X >= Filters[0].X1 && it->Y >= Filters[0].Y1 && it->X <= Filters[0].X2 && it->Y <= Filters[0].Y2) && it->BaseID != 0)
            {
                Renderer->Print(it->X, it->Y, 0.0f, 1.0f, 0.0f, "%", it->BaseID);
            }
        }
    }
    else if (this->Mode == 2)
    {
        for (auto it = Model::Models.begin(); it != Model::Models.end(); ++it)
        {
            if ((it->X >= Filters[1].X1 && it->Y >= Filters[1].Y1 && it->X <= Filters[1].X2 && it->Y <= Filters[1].Y2) && it->ID != 0)
            {
                Renderer->Print(it->X, it->Y, 0.0f, 1.0f, 0.0f, "%", it->ID);
            }
        }
    }
    else if (this->Mode == 3)
    {
        //auto HangingLetter = [](const char &C){return (C == 'f' ||  C == 'g' || C == 'j' || C == 'p' || C == 'q' || C == 'y' || C == '[' || C == ']' || C == '_' || C == '.');};
        for (auto it = Font::RenderedFonts.begin(); it != Font::RenderedFonts.end(); ++it)
        {
            if ((it->X >= Filters[2].X1 && it->Y >= Filters[2].Y1 && it->X <= Filters[2].X2 && it->Y <= Filters[2].Y2))
            {
                if ((it != Font::RenderedFonts.end() - 1) && (it->X - (it + 1)->X == 1))
                    ++it;
                Renderer->Print(it->Translate[0] + it->VX[0], it->Y + 3, 0.0f, 1.0f, 0.0f, "%", it->Letter);
            }
        }
    }
    else if (this->Mode == 4)
    {
        int HudX = 4, HudY = 75;
        int TextX = 10, TextY = 90, TextLn = 10;
        auto it = std::find_if(Texture::Textures.begin(), Texture::Textures.end(), [&](const Texture &T) {return T.BaseID == this->HudID;});

        if (it != Texture::Textures.end())
        {
            glEnable(it->Target);
            glBindTexture(it->Target, it->ID);
            glGetTexLevelParameteriv(it->Target, 0, GL_TEXTURE_WIDTH, &it->Width);
            glGetTexLevelParameteriv(it->Target, 0, GL_TEXTURE_HEIGHT, &it->Height);
            glDisable(it->Target);

            int MaxWidth = 200;
            int MaxHeight = ((TextLn * 10) + it->Height) + 160;
            glColor4f(0.25f, 0.25f, 0.25f, 0.75f);
            Renderer->DrawRect(HudX, HudY, MaxWidth, MaxHeight);

            glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
            Renderer->DrawRect(HudX, HudY, MaxWidth, MaxHeight, false);
            Renderer->Print(70, TextY, 1.0f, 1.0f, 1.0f, "GLX v3.0");

            glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
            TextY += (TextLn - 2);
            Renderer->DrawLine(HudX, TextY, MaxWidth, TextY);

            GLint ViewPort[4];
            glGetIntegerv(GL_VIEWPORT, ViewPort);
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "ViewPort: [%, %, %, %]", ViewPort[0], ViewPort[1], ViewPort[2], ViewPort[3]);
            Renderer->Print(TextX, TextY += (TextLn * 2) , 0.0f, 1.0f, 0.0f, "Target:  %", it->Target == GL_TEXTURE_2D ? "TEXTURE-2D" : "TEXTURE-RECTANGLE");
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "GenID:    %", it->ID);
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "BaseID:   %", it->BaseID);
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "ColourID: %", it->ColourID);
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "Location: (%, %)", it->X, it->Y);
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "Width:    %", it->Width);
            Renderer->Print(TextX, TextY += TextLn, 0.0f, 1.0f, 0.0f, "Height:   %", it->Height);
            Renderer->Print(TextX, TextY += (TextLn * 2), 0.0f, 1.0f, 0.0f, "Image:");

            glPushMatrix();
            glColor4f(1, 1, 1, 1);
            glTranslated((MaxWidth - it->Width) / 2, TextY += TextLn, 0);
            DrawTexture(it->Target, it->ID, 0, 0, it->Width, it->Height, it->Width, it->Height);
            glPopMatrix();
            glFlush();
        }
    }
}
