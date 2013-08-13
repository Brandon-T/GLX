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


typedef struct
{
    std::array<float, 16> ModelView;
} Matrices;

typedef struct
{
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
    int X, Y;
    int X1, Y1, X2, Y2;
} Texture;

typedef struct
{
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
