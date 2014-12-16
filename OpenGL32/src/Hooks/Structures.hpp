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

#ifndef STRUCTURES_HPP_INCLUDED
#define STRUCTURES_HPP_INCLUDED

#include <cmath>
#include <cstdint>
#include <vector>
#include <GL/gl.h>
#include <GL/glext.h>
#include <map>
#include <cstring>
#include <fstream>
#include <tuple>
#include "Math.hpp"
#include "MathEx.hpp"
#include "Serialization.hpp"
#include "Graphics.hpp"

struct Matrices
{
    private:
        bool Logged;

    public:
        std::array<float, 16> ModelView;

        void LogMatrix();
        inline void Reset() {this->Logged = false;}
};

struct Map
{
    private:
        bool MapBound = false, stored = false;
        int VertexCount = 0;
        std::uint32_t MapCount = 0, TextureID = 0, Target = 0, PossibleID = 0;

    public:
        float X[4], Y[4];
        bool Rendered = false;
        std::uint32_t MapID = 0;
        int Width = 0, Height = 0;
        int width = 512, height = 512;
        std::vector<std::uint8_t> Pixels;

        void Store();
        void LogBindTexture(std::uint32_t target, std::uint32_t texture);
        void Log2DImageTexture(std::uint32_t target, int width, int height, const void* pixels);
        void LogPixelStore(std::uint32_t flag, std::uint32_t size);
        void LogVertices(float x, float y);
        inline void Reset() {Width = Height = VertexCount = TextureID = MapBound = 0;}
};

struct ModelBuffer
{
    Math math;
    std::uint32_t ID, Target, Usage;
    std::ptrdiff_t Size;
    std::uint32_t Checksum;
    static ModelBuffer CurrentBuffer;
    static std::vector<ModelBuffer> Buffers;
    void LogBindBuffer(std::uint32_t target, std::uint32_t Buffer);
    void LogBufferData(std::uint32_t target, std::ptrdiff_t size, const void* data, std::uint32_t usage);
    void LogBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data);
};

struct Model
{
    private:
        Math math;
        bool IsRendering;
        ModelBuffer Info;

    public:
        int X, Y;
        std::uint32_t ID;
        std::uint32_t Stride;
        std::uint32_t Triangles;
        static std::vector<Model> Models;

        void LogBindBuffer(std::uint32_t target, std::uint32_t Buffer);
        void LogBufferData(std::uint32_t target, std::ptrdiff_t size, const void* data, std::uint32_t usage);
        void LogBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data);
        void LogDrawElements(std::uint32_t mode, int count, std::uint32_t type, const void* indices);
        void LogPopMatrix();
        void LogVertexPointer(int size, std::uint32_t type, int stride, const void* pointer);
};

struct Texture
{
    private:
        Math math;
        bool Depth, Found;
        std::uint32_t ActiveTexture = 0;
        std::uint32_t ActiveTextureCount = 0;
        static std::uint32_t ActiveTextures[3];

    public:
        int X, Y, Count;
        int VX[4], VY[4];
        int Width, Height;
        std::uint32_t Target, ID, BaseID, ColourID, FullColourID;
        static std::vector<Texture> Textures;
        static std::multimap<std::uint32_t, std::tuple<std::uint32_t, std::uint32_t, std::uint32_t>> IDMap;

        void LogBindTexture(std::uint32_t target, std::uint32_t texture);
        void LogVertices(int X, int Y);
        void LogActiveTexture(std::uint32_t texture);
        void Log2DImageTexture(std::uint32_t Target, const void* Pixels, std::size_t Width, std::size_t Height);
};

struct Font
{
    private:
        int Count = 0;
        int VertexCount = 0;
        bool Found = false;
        bool Rendering = false, LastFont = false;

    public:
        std::uint32_t TextureID = 0;
        std::uint32_t ID = 0;
        std::uint32_t Colour;
        int X, Y;
        char Letter;
        bool Shadow;
        float Translate[3];
        int VX[4], VY[4];
        static std::vector<Font> Fonts;
        static std::vector<Font> RenderedFonts;

        void LogBindTexture(std::uint32_t texture);
        void LogGenList(std::uint32_t Range);
        void LogCallList(std::uint32_t List);
        void LogVertices(int x, int y);
        void LogGenTextures(std::size_t n, std::uint32_t* textures);
        void LogColour(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha);
        void LogEndList();
        void LogNewList(std::uint32_t List, std::uint32_t Mode);
        void LogTranslate(float x, float y, float z);
};

class Logger
{
    public:
        Map map;
        Font font;
        Model model;
        Texture texture;
        Matrices matrices;

        void Reset();
        void Save(std::uint32_t TextureID, std::uint32_t TextureType = GL_TEXTURE_2D);
};

extern Logger InfoLogger;
Serialize& operator << (Serialize& Destination, const Model &Source);
Serialize& operator << (Serialize& Destination, const Texture &Source);
Serialize& operator << (Serialize& Destination, const Font &Source);
Serialize& operator << (Serialize& Destination, const Map &Source);
Serialize& operator << (Serialize& Destination, const Matrices &Source);
DeSerialize& operator >> (DeSerialize& Source, Model &Destination);
DeSerialize& operator >> (DeSerialize& Source, Texture &Destination);
DeSerialize& operator >> (DeSerialize& Source, Font &Destination);
DeSerialize& operator >> (DeSerialize& Source, Map &Destination);
DeSerialize& operator >> (DeSerialize& Source, Matrices &Destination);

#endif // STRUCTURES_HPP_INCLUDED
