#include "Structures.hpp"

Map map;
Matrices matrices;
std::vector<Texture> LoT;
std::vector<Model> LoM;
std::vector<Font> LoF;

Serialize& operator << (Serialize& Destination, const Model &Source)
{
    return Destination << Source.ID
    << Source.TriangleCount
    << Source.X
    << Source.Y;
}

Serialize& operator << (Serialize& Destination, const Texture &Source)
{
    return Destination << Source.ID
    << Source.ColourID
    << Source.X
    << Source.Y
    << Source.X1
    << Source.Y1
    << Source.X2
    << Source.Y2;
}

Serialize& operator << (Serialize& Destination, const Font &Source)
{
    return Destination << Source.Colour
    << Source.X
    << Source.Y
    << Source.Letter
    << Source.Translate[0]
    << Source.Translate[1]
    << Source.Translate[2]
    << Source.X1
    << Source.Y1
    << Source.X2
    << Source.Y2;
}

Serialize& operator << (Serialize& Destination, const Map &Source)
{
    return Destination << Source.Width
    << Source.Height
    << Source.MapID
    << Source.X[0]
    << Source.Y[0]
    << Source.X[1]
    << Source.Y[1]
    << Source.X[2]
    << Source.Y[2]
    << Source.X[3]
    << Source.Y[3]
    << Source.Pixels;
}

Serialize& operator << (Serialize& Destination, const Matrices &Source)
{
    return Destination << Source.ModelView;
}

DeSerialize& operator >> (DeSerialize& Source, Model &Destination)
{
    return Source >> Destination.ID
    >> Destination.TriangleCount
    >> Destination.X
    >> Destination.Y;
}

DeSerialize& operator >> (DeSerialize& Source, Texture &Destination)
{
    return Source >> Destination.ID
    >> Destination.ColourID
    >> Destination.X
    >> Destination.Y
    >> Destination.X1
    >> Destination.Y1
    >> Destination.X2
    >> Destination.Y2;
}

DeSerialize& operator >> (DeSerialize& Source, Font &Destination)
{
    return Source >> Destination.Colour
    >> Destination.X
    >> Destination.Y
    >> Destination.Letter
    >> Destination.Translate[0]
    >> Destination.Translate[1]
    >> Destination.Translate[2]
    >> Destination.X1
    >> Destination.Y1
    >> Destination.X2
    >> Destination.Y2;
}

DeSerialize& operator >> (DeSerialize& Source, Map &Destination)
{
    return Source >> Destination.Width
    >> Destination.Height
    >> Destination.MapID
    >> Destination.X[0]
    >> Destination.Y[0]
    >> Destination.X[1]
    >> Destination.Y[1]
    >> Destination.X[2]
    >> Destination.Y[2]
    >> Destination.X[3]
    >> Destination.Y[3]
    >> Destination.Pixels;
}

DeSerialize& operator >> (DeSerialize& Source, Matrices &Destination)
{
    return Source >> Destination.ModelView;
}
