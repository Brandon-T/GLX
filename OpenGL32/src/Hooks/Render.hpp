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

#ifndef RENDER_HPP_INCLUDED
#define RENDER_HPP_INCLUDED

#include <GL/gl.h>
#include <GL/glext.h>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>
#include "System.hpp"

class Render
{
    private:
        std::uint32_t Base;
        bool DrawingEnabled;

        float PointSize;
        bool PointSmooth;
        bool GLTexture2D;
        bool GLRectangleTexture;

    public:
        Render(HDC DC, int FontSize);
        ~Render();

        void EnableDrawing();
        void DisableDrawing();
        void EnableTransparency();
        void DisableTransparency();
        void OrthoProjection(int Width, int Height);

        std::uint32_t LoadTexture(GLenum Target, void* Buffer, int width, int height) const;
        void DrawLine(float X1, float Y1, float X2, float Y2) const;
        void DrawRect(float X1, float Y1, float X2, float Y2, bool Fill = true) const;
        void DrawPoint(float X, float Y, float Z, float Radius) const;
        void DrawCircle(float CenterX, float CenterY, float Radius, int Rotations = 360) const;
        void DrawTexture(std::uint32_t Target, std::uint32_t ID, float X1, float Y1, float X2, float Y2, int Width = 1, int Height = 1) const;

        template<typename... Args>
        void Print(float X, float Y, const char* Text, Args... args);

        template<typename... Args>
        void Print(float X, float Y, float R, float G, float B, const char* Text, Args... args);
};

template<typename... Args>
void Render::Print(float X, float Y, const char* Text, Args... args)
{
    this->Print(X, Y, 1, 1, 1, Text, std::forward(args)...);
}

template<typename... Args>
void Render::Print(float X, float Y, float R, float G, float B, const char* Text, Args... args)
{
    using namespace std;
    std::size_t Position = 0;
    std::string Container(Text);
    std::vector<std::string> Arguments;
    std::initializer_list<int> {(Arguments.push_back(to_string(args)), 0)...};

    for (auto it = Arguments.begin(); it != Arguments.end(); ++it)
    {
        if ((Position = Container.find("%")) != std::string::npos)
        {
            Container.replace(Position, 1, *it);
        }
    }

    glColor3f(R, G, B);
    glRasterPos2f(X, Y);
    glPushAttrib(GL_LIST_BIT);
    glListBase(this->Base - 32);
    glCallLists(Container.size(), GL_UNSIGNED_BYTE, Container.data());
    glPopAttrib();
    glFlush();
}

#endif // RENDER_HPP_INCLUDED
