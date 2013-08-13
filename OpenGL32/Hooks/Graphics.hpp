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

#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED

#include <GL/gl.h>
#include <GL/glext.h>
#include <iostream>
#include <cstring>
#include <vector>

void FlipImageBytes(void* In, void* &Out, int width, int height, uint32_t Bpp = 32);
void EnableDrawing(bool &GLTexture2D, bool &GLRectangleTexture, bool &PointSmooth, float &PointSize);
void DisableDrawing(bool GLTexture2D, bool GLRectangleTexture, bool PointSmooth, float PointSize);
GLuint LoadTexture(void* Buffer, int width, int height, GLenum Target);
void DrawTexture(std::uint32_t Target, std::uint32_t ID, float X1, float Y1, float X2, float Y2, int Width, int Height);
void BltMappedBuffer(void* buffer, int width, int height);

#endif // GRAPHICS_HPP_INCLUDED
