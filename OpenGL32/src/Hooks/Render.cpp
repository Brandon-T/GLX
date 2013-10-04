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

#include "Render.hpp"

Render::Render(HDC DC, int FontSize) : Base(glGenLists(96))
{
    HFONT Font = CreateFont(-MulDiv(FontSize, GetDeviceCaps(DC, LOGPIXELSY), 72), 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Arial");
    HFONT OldFont = static_cast<HFONT>(SelectObject(DC, Font));
    wglUseFontBitmaps(DC, 32, 96, Base);
    wglUseFontBitmaps(DC, 32, 96, Base);
    SelectObject(DC, OldFont);
    DeleteObject(Font);
}

Render::~Render()
{
    /**Causes RS to print a stack trace.. Might as well let the OS clean it up automatically then..**/
    /**Todo investigate why**/
    //glDeleteLists(this->Base, 96);
}

void Render::EnableDrawing()
{
    if (!this->DrawingEnabled)
    {
        this->GLTexture2D = glIsEnabled(GL_TEXTURE_2D);
        this->GLRectangleTexture = glIsEnabled(GL_TEXTURE_RECTANGLE);
        this->PointSmooth = glIsEnabled(GL_POINT_SMOOTH);
        glGetFloatv(GL_POINT_SIZE, &this->PointSize);

        glDisable(GL_TEXTURE_RECTANGLE);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        glPushMatrix();
        glLoadIdentity();
        this->DrawingEnabled = true;
    }
}

void Render::DisableDrawing()
{
    if (this->DrawingEnabled)
    {
        glPopMatrix();
        if (this->GLTexture2D) glEnable(GL_TEXTURE_2D);
        if (this->GLRectangleTexture) glEnable(GL_TEXTURE_RECTANGLE);
        if (!this->PointSmooth) glDisable(GL_POINT_SMOOTH);
        this->DrawingEnabled = false;
    }
}

void Render::EnableTransparency()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::DisableTransparency()
{
    glDisable(GL_BLEND);
}

void Render::OrthoProjection(int Width, int Height)
{
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, Width, Height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

std::uint32_t Render::LoadTexture(GLenum Target, void* Buffer, int width, int height) const
{
    GLuint ID = 0;
    glGenTextures(1, &ID);
    glBindTexture(Target, ID);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    glTexImage2D(Target, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, Buffer);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexParameteri(Target, GL_TEXTURE_WRAP_S, Target == GL_TEXTURE_2D ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(Target, GL_TEXTURE_WRAP_T, Target == GL_TEXTURE_2D ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return ID;
}

void Render::DrawLine(float X1, float Y1, float X2, float Y2) const
{
    glBegin(GL_LINES);
        glVertex2f(X1, Y1);
        glVertex2f(X2, Y2);
    glEnd();
    glFlush();
}

void Render::DrawRect(float X1, float Y1, float X2, float Y2, bool Fill) const
{
    glBegin(Fill ? GL_POLYGON : GL_LINE_LOOP);
      glVertex2f(X1, Y1);
      glVertex2f(X1, Y2);
      glVertex2f(X2, Y2);
      glVertex2f(X2, Y1);
    glEnd();
    glFlush();
}

void Render::DrawPoint(float X, float Y, float Z, float Radius) const
{
    glRasterPos2f(X, Y);
    glPointSize(Radius);
    glBegin(GL_POINTS);
        glVertex3f(X, Y, Z);
    glEnd();
    glPointSize(this->PointSize);
    glFlush();
}

void Render::DrawCircle(float CenterX, float CenterY, float Radius, int Rotations) const
{
	float Theta = 2 * 3.1415926535897932384626433832795 / float(Rotations);
	float Cos = cosf(Theta);
	float Sine = sinf(Theta);
	float X = Radius, Y = 0, Temp = 0;

	glBegin(GL_LINE_LOOP);
        for(int I = 0; I < Rotations; ++I)
        {
            glVertex2f(X + CenterX, Y + CenterY);
            Temp = X;
            X = Cos * X - Sine * Y;
            Y = Sine * Temp + Cos * Y;
        }
	glEnd();
	glFlush();
}

void Render::DrawTexture(std::uint32_t Target, std::uint32_t ID, float X1, float Y1, float X2, float Y2, int Width, int Height) const
{
    if (Width == 1 && Height == 1 && Target == GL_TEXTURE_RECTANGLE)
    {
        Width = X2 - X1;
        Height = Y2 - Y1;
    }
    else
    {
        Width = Target == GL_TEXTURE_RECTANGLE ? Width : 1;
        Height = Target == GL_TEXTURE_RECTANGLE ? Height : 1;
    }

    glEnable(Target);
    glBindTexture(Target, ID);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
        glTexCoord2f(0, Height);
        glVertex2f(X1, Y1);
        glTexCoord2f(0, 0);
        glVertex2f(X1, Y2);
        glTexCoord2f(Width, 0);
        glVertex2f(X2, Y2);
        glTexCoord2f(Width, Height);
        glVertex2f(X2, Y1);
    glEnd();
    glDisable(Target);
}
