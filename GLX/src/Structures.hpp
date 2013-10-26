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

#include <array>
#include "Serialization.hpp"

#define GLX_ViewPort        1
#define GLX_Textures        2
#define GLX_Models          3
#define GLX_Fonts           4
#define GLX_Matrices        5
#define GLX_Map             6
#define GLX_MapCoords       7
#define GLX_Debug           8
#define GLX_ColourBuffer    9
#define GLX_SaveTexture     10
#define GLX_FontsEnable     11


typedef struct
{
    std::array<float, 16> ModelView;
} Matrices;

typedef struct
{
    bool Rendered;
    float X[4], Y[4];
    int Width, Height;
    std::uint32_t MapID;
    std::vector<std::uint8_t> Pixels;
} Map;

typedef struct
{
    std::uint32_t ID;
    std::uint32_t TriangleCount;
    int X, Y;
} Model;

typedef struct
{
    std::uint32_t ID;
    std::uint32_t ColourID;
    std::uint32_t FullColourID;
    int X, Y;
    int X1, Y1, X2, Y2;
} Texture;

typedef struct
{
    std::uint32_t TextureID;
    std::uint32_t Colour;
    int X, Y;
    char Letter;
    bool Shadow;
    float Translate[3];
    int X1, Y1, X2, Y2;
} Font;

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

extern Map map;
extern Matrices matrices;
extern std::vector<Texture> LoT;
extern std::vector<Model> LoM;
extern std::vector<Font> LoF;

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
