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

#ifndef BUFFERHOOK_HPP_INCLUDED
#define BUFFERHOOK_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include "Exports.hpp"
#include "Math.hpp"

class Buffer
{
    private:
        bool VertexCapture = true;
        unsigned char* Ptr = 0;

        std::vector<std::uint8_t> VBOData;
        std::vector<std::uint8_t> IBOData;

    public:
        std::vector<std::vector<Vector3D<float>>> Vertices;
        GLuint VBO = 0, IBO = 0, CoordsPerVertex = 0, Stride = 0;
        void Bind(GLenum target, GLuint ID);
        void BufferData(GLenum Target, GLint Size, const void* Ptr, GLenum type);
        void EnableClientState(GLenum cap);
        void VertexPointer(GLint  size, GLenum  type, GLsizei  stride, const GLvoid *  pointer);
        void DrawElements(GLenum  mode,  GLsizei  count,  GLenum  type,  const GLvoid*  indices);
};

/*
struct Buffer
{
    std::uint32_t ID, Checksum;
    std::uint32_t Target, Usage;
    std::vector<std::uint8_t> Data;
    static std::vector<Buffer> Buffers;
    void LogBindBuffer(std::uint32_t target, std::uint32_t Buffer);
    void LogBufferData(std::uint32_t target, std::ptrdiff_t size, const void* data, std::uint32_t usage);
    void LogBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data);
};
*/

#endif // BUFFERHOOK_HPP_INCLUDED
