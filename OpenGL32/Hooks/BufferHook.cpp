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

#include "BufferHook.hpp"
#include <fstream>

void Buffer::Bind(GLenum Target, GLuint ID)
{
    if (ID != 0)
    {
        if (GL_ARRAY_BUFFER == Target)
            VBO = ID;
        else if (GL_ELEMENT_ARRAY_BUFFER == Target)
            IBO = ID;
    }
}

void Buffer::BufferData(GLenum Target, GLint Size, const void* Ptr, GLenum type)
{
    if (GL_ARRAY_BUFFER == Target && type == GL_STATIC_DRAW && VBO) //A vertex buffer was created. Copy its data.
    {
        VBOData.resize(Size);
        memcpy(VBOData.data(), Ptr, Size);
        //File << "VBO: " << VBO << "\n";
        VBO = 0;
    }
    else if (GL_ELEMENT_ARRAY_BUFFER == Target && type == GL_STATIC_DRAW && IBO) //Index buffer created. Copy its data.
    {
        IBOData.resize(Size);
        memcpy(IBOData.data(), Ptr, Size);
        //File << "IBO: " << IBO << "\n";
        IBO = 0;
    }
}

void Buffer::EnableClientState(GLenum cap) //Vertex array enabled.
{
    if (cap == GL_VERTEX_ARRAY)
        VertexCapture = true;
}

void Buffer::VertexPointer(GLint size, GLenum  type, GLsizei  stride, const GLvoid*  pointer) //Get the stride and buffer offset.
{
    //if (VertexCapture)
    {
        Stride = stride;
        CoordsPerVertex = size;
        //File << "VBOPtr: " << (std::size_t)Ptr << "\n";
        //File << "Stride: " << Stride << "\n";
        //File << "Offset: " << (std::size_t)pointer << "\n";
    }
}

void Buffer::DrawElements(GLenum  mode,  GLsizei  count,  GLenum  type,  const GLvoid*  indices) //Print all the indicies being drawn.
{
    Ptr = VBOData.data();
    std::vector<Vector3D<float>> Foo;
    for (std::size_t J = 0; J < VBOData.size() / Stride; ++J, Ptr += Stride)
    {
        float X = *(reinterpret_cast<float*>(Ptr) + 0);
        float Y = *(reinterpret_cast<float*>(Ptr) + 1);
        float Z = *(reinterpret_cast<float*>(Ptr) + 2);
        Foo.push_back({X, Y, Z});
        //File << X << ", " << Y << ", " << Z << "\n";
    }
    Vertices.push_back(Foo);
    VBO = 0;
    //File << "\n";
}





/*
void Buffer::LogBindBuffer(std::uint32_t target, std::uint32_t Buffer)
{
    if (Buffer != 0)
    {
        this->ID = Buffer;
        this->Target = target;
    }
}

void Buffer::LogBufferData(std::uint32_t target, std::ptrdiff_t size, const void* data, std::uint32_t usage)
{
    if (data && size)
    {
        this->Usage = usage;
        this->Data.resize(size);
        std::memcpy(this->Data.data(), data, size);
        Buffer::Buffers.push_back(*this);
    }
}

void Buffer::LogBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data)
{
    if (data && size)
    {
        auto it = std::find_if(Buffer::Buffers.begin(), Buffer::Buffers.end(), [&](const Buffer &buffer){return buffer.ID == ID;});
        if (it != Buffer::Buffers.end())
        {
            std::memcpy(it->Data.data() + offset, data, size);
        }
    }
}*/
