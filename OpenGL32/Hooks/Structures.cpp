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

#include "Structures.hpp"

std::vector<Texture> Texture::Textures;
std::uint32_t Texture::ActiveTextures[3];
std::multimap<std::uint32_t, std::tuple<std::uint32_t, std::uint32_t, std::uint32_t>> Texture::IDMap;
std::vector<Font> Font::Fonts;
std::vector<Font> Font::RenderedFonts;
std::vector<Model> Model::Models;
std::vector<ModelBuffer> ModelBuffer::Buffers;
ModelBuffer ModelBuffer::CurrentBuffer;

void Matrices::LogMatrix()
{
    int StackDepth = 0;
    glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &StackDepth);
    if (StackDepth == 1 && !Logged)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, &ModelView[0]);
        static constexpr std::array<float, 16> Identity = {{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};

        if (ModelView != Identity)
        {
            Logged = true;
        }
        else
        {
            std::memset(&ModelView[0], 0, ModelView.size() * sizeof(float));
        }
    }
}

void Map::LogBindTexture(std::uint32_t target, GLuint texture)
{
    TextureID = texture;
    MapBound = (MapID != 0 && texture == MapID);
    glGetTexLevelParameteriv(target, 0, GL_TEXTURE_WIDTH, &Width);
    glGetTexLevelParameteriv(target, 0, GL_TEXTURE_WIDTH, &Height);

    if (MapCount && Width == width && Height == height && (++MapCount == 8))
    {
        MapCount = 0;
        Pixels.clear();
        Pixels.resize(Width * Height * 4);
        glGetTexImage(target, 0, GL_BGRA, GL_UNSIGNED_BYTE, Pixels.data());
    }
}

void Map::Log2DImageTexture(std::uint32_t target, int width, int height)
{
    if (width == this->width && height == this->height)
    {
        ++MapCount;
        MapID = TextureID;
    }
}

void Map::LogVertices(float x, float y)
{
    if (MapBound && (++VertexCount < 5))
    {
        X[VertexCount - 1] = x;
        Y[VertexCount - 1] = y;
    }

    if (VertexCount > 4)
    {
        VertexCount = 0;
    }
}

void ModelBuffer::LogBindBuffer(std::uint32_t target, std::uint32_t Buffer)
{
    CurrentBuffer.ID = this->ID = Buffer;
    CurrentBuffer.Target = this->Target = target;
}

void ModelBuffer::LogBufferData(std::uint32_t target, std::ptrdiff_t size, const void* data, std::uint32_t usage)
{
    if (data && size)
    {
        CurrentBuffer.Size = this->Size = size;
        CurrentBuffer.Usage = this->Usage = usage;
        CurrentBuffer.Checksum = this->Checksum = math.LazyCheckSum(reinterpret_cast<std::uint32_t*>(const_cast<void*>(data)), size);

        auto it = std::find_if(ModelBuffer::Buffers.begin(), ModelBuffer::Buffers.end(), [&](const ModelBuffer &MB) {
            return MB.Checksum == this->Checksum;
        });

        if (it == ModelBuffer::Buffers.end())
        {
            ModelBuffer::Buffers.push_back(*this);
        }
        else
        {
            it->Checksum = this->Checksum;
        }
    }
}

void ModelBuffer::LogBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data)
{
    if (data && size)
    {
        CurrentBuffer.Size = this->Size = size;
        CurrentBuffer.Checksum = this->Checksum = math.LazyCheckSum(reinterpret_cast<std::uint32_t*>(const_cast<void*>(data)), size);
        auto it = std::find_if(ModelBuffer::Buffers.begin(), ModelBuffer::Buffers.end(), [&](const ModelBuffer &MB){
            return MB.Checksum == this->Checksum;
        });

        if (it == ModelBuffer::Buffers.end())
        {
            ModelBuffer::Buffers.push_back(*this);
        }
        else
        {
            it->Checksum = this->Checksum;
        }
    }
}

void Model::LogBindBuffer(std::uint32_t target, std::uint32_t Buffer)
{
    Info.LogBindBuffer(target, Buffer);
}

void Model::LogBufferData(std::uint32_t target, std::ptrdiff_t size, const void* data, std::uint32_t usage)
{
    Info.LogBufferData(target, size, data, usage);
}

void Model::LogBufferSubData(std::uint32_t target, std::ptrdiff_t offset, std::ptrdiff_t size, const void* data)
{
    Info.LogBufferSubData(target, offset, size, data);
}

void Model::LogDrawElements(std::uint32_t mode, int count, std::uint32_t type, const void* indices)
{
    if (this->IsRendering)
    {
        Model* ModelPtr = &Model::Models.back();
        ModelPtr->ID = 0;

        for (auto it = Info.Buffers.end(); it != Info.Buffers.begin(); --it)
        {
            if (it->ID == Info.CurrentBuffer.ID)
            {
                ModelPtr->ID = it->Checksum;
                ModelPtr->Triangles = it->Size / this->Stride;
                break;
            }
        }
    }
}

void Model::LogPopMatrix()
{
    if (this->IsRendering)
    {
        float X = 0, Y = 0;
        int ViewPort[4];
        double ModelViewMatrix[16];
        double ProjectionMatrix[16];
        glGetIntegerv(GL_VIEWPORT, ViewPort);
        glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
        glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

        Model* ModelPtr = &Model::Models.back();
        if (math.WorldToScreen(X, Y, {0, 0, 0}))
        {
            ModelPtr->X = X;
            ModelPtr->Y = Y;
        }
    }
    this->IsRendering = false;
}

void Model::LogVertexPointer(int size, std::uint32_t type, int stride, const void* pointer)
{
    this->IsRendering = true;
    this->Stride = stride;
    Model::Models.push_back(*this);
}


void Texture::LogBindTexture(std::uint32_t target, std::uint32_t texture)
{
    this->Found = false;
    this->Target = target;
    this->ActiveTextureCount = 0;
    if (target == GL_TEXTURE_RECTANGLE || target == GL_TEXTURE_2D)
    {
        this->ID = texture;
        auto it = IDMap.find(texture);
        this->Found = false;

        if (it != IDMap.end())
        {
            this->Found = true;
            this->BaseID = std::get<0>(it->second);
            this->ColourID = std::get<1>(it->second);
            this->ClippedID = std::get<2>(it->second);
        }
    }
}

void Texture::LogVertices(int X, int Y)
{
    if (this->Found && (++Count < 5))
    {
        this->VX[Count - 1] = X;
        this->VY[Count - 1] = Y;
    }

    if (this->Found && Count == 4)
    {
        if (ActiveTexture != GL_TEXTURE0)
        {
            ActiveTexture = 0;
            this->ID = Texture::ActiveTextures[0];
            this->BaseID = Texture::ActiveTextures[1];
            this->ColourID = Texture::ActiveTextures[2];
        }
        this->X = (this->VX[0] + this->VX[2]) / 2;
        this->Y = (this->VY[0] + this->VY[2]) / 2;
        Textures.push_back(*this);
        this->Count = 0;
    }
}

void Texture::LogActiveTexture(std::uint32_t texture)
{
    this->ActiveTexture = texture;
    if ((++this->ActiveTextureCount == 1) && (texture != GL_TEXTURE0))
    {
        Texture::ActiveTextures[0] = this->ID;
        Texture::ActiveTextures[1] = this->BaseID;
        Texture::ActiveTextures[2] = this->ColourID;
    }
}

void Texture::Log2DImageTexture(std::uint32_t Target, const void* Pixels, std::size_t Width, std::size_t Height)
{
    if (!Pixels) return;
    if (Target == GL_TEXTURE_RECTANGLE || Target == GL_TEXTURE_2D)
    {
        auto it = Texture::IDMap.find(this->ID);
        if (it == Texture::IDMap.end())
        {
            this->BaseID = math.ColourCheckSum(Pixels, this->ColourID, this->ClippedID, Width, Height);
            if (this->BaseID != 0)
            {
                Texture::IDMap.insert(std::make_pair(this->ID, std::make_tuple(this->BaseID, this->ColourID, this->ClippedID)));
            }
        }
        else
        {
            it->second = std::make_tuple(this->BaseID, this->ColourID, this->ClippedID);
        }
    }
}


void Font::LogBindTexture(std::uint32_t texture)
{
    this->TextureID = texture;
}

void Font::LogGenList(std::uint32_t Range)
{
    if (Range == 256)
    {
        this->Count = 0;
        this->Found = true;
    }
}

void Font::LogCallList(std::uint32_t List)
{
    auto it = std::find_if(Fonts.begin(), Fonts.end(), [List](const Font &Value)
    {
        return List == Value.ID;
    });

    if (it != Fonts.end())
    {
        this->ID = List;
        this->Rendering = true;

        for (int I = 0; I < 4; ++I)
        {
            this->VX[I] = it->VX[I];
            this->VY[I] = it->VY[I];
        }

        this->X = std::round((this->Translate[0] + it->VX[0] + this->Translate[0] + it->VX[2]) / 2);
        this->Y = std::round((this->Translate[1] + it->VY[0] + this->Translate[1] + it->VY[2]) / 2);

        this->Letter = (it->Letter - 32);
        this->RenderedFonts.push_back(*this);
    }
}

void Font::LogGenTextures(std::size_t n, std::uint32_t* textures)
{
    this->Rendering = false;
}

void Font::LogVertices(int x, int y)
{
    if (this->Found && (++VertexCount < 5))
    {
        this->VX[VertexCount - 1] = x;
        this->VY[VertexCount - 1] = y;
    }
}

void Font::LogColour(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
{
    this->Colour = RGB(red, green, blue);
    if (!this->Colour)
    {
        this->Shadow = true;
        this->Rendering = false;
    }
    else
    {
        this->Shadow = false;
        this->Rendering = true;
    }
}

void Font::LogEndList()
{
    if (this->Found)
    {
        this->VertexCount = 0;
        this->LastFont = false;
        if (!this->Fonts.size())
            this->Letter = 32;
        else
            this->Letter = (!this->Fonts.back().LastFont) ? this->Fonts.back().Letter + 1 : 32;

        if (++this->Count >= 255)
        {
            this->Count = 0;
            this->LastFont = true;
            this->Found = false;
        }
        this->Fonts.push_back(*this);
    }
}

void Font::LogNewList(std::uint32_t List, std::uint32_t Mode)
{
    if (this->Found)
        this->ID = List;
}

void Font::LogTranslate(float x, float y, float z)
{
    this->Translate[0] = x;
    this->Translate[1] = y;
    this->Translate[2] = z;
}

void Logger::Reset()
{
    Texture::Textures.clear();
    Font::RenderedFonts.clear();
    Model::Models.clear();
    matrices.Reset();
    map.Reset();

    ModelBuffer::Buffers.shrink_to_fit();
    Texture::Textures.shrink_to_fit();
    Font::RenderedFonts.shrink_to_fit();
    Model::Models.shrink_to_fit();
}

void Logger::Save(std::uint32_t TextureID, std::uint32_t TextureType)
{
    #if defined _WIN32 || defined _WIN64
    CreateDirectory("Images/", nullptr);
    #else
    mkdir("Images/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif


    std::int32_t Width = 0;
    std::int32_t Height = 0;
    std::uint16_t BitsPerPixel = 32;
    bool GLTexture2D = glIsEnabled(GL_TEXTURE_2D);
    bool GLRectangleTexture = glIsEnabled(GL_TEXTURE_RECTANGLE);

    glEnable(TextureType);
    glBindTexture(TextureType, TextureID);
    glGetTexLevelParameteriv(TextureType, 0, GL_TEXTURE_WIDTH, &Width);
    glGetTexLevelParameteriv(TextureType, 0, GL_TEXTURE_HEIGHT, &Height);
    std::vector<std::uint8_t> ImageData(((Width * BitsPerPixel + 31) / 32) * 4 * Height);
    glGetTexImage(TextureType, 0, GL_BGRA, GL_UNSIGNED_BYTE, ImageData.data());
    if (!GLTexture2D) glDisable(GL_TEXTURE_2D);
    if (!GLRectangleTexture) glDisable(GL_TEXTURE_RECTANGLE);

    std::vector<std::uint8_t> PngBuffer(ImageData.size());
    for(std::int32_t I = 0; I < Height; ++I)
    {
        for(std::int32_t J = 0; J < Width; ++J)
        {
            std::size_t OldPos = (Height - I - 1) * (Width * 4) + 4 * J;
            std::size_t NewPos = I * (Width * 4) + 4 * J;
            PngBuffer[NewPos + 0] = ImageData[OldPos + 2];
            PngBuffer[NewPos + 1] = ImageData[OldPos + 1];
            PngBuffer[NewPos + 2] = ImageData[OldPos + 0];
            PngBuffer[NewPos + 3] = ImageData[OldPos + 3];
        }
    }

    std::vector<std::uint8_t> ImageBuffer;
    lodepng::encode(ImageBuffer, PngBuffer, Width, Height);
    lodepng::save_file(ImageBuffer, ("Images/" + std::to_string(TextureID) + ".png").c_str());
}



Logger InfoLogger;
std::vector<Texture> LoT;
std::vector<Model> LoM;
std::vector<Font> LoF;

Serialize& operator << (Serialize& Destination, const Model &Source)
{
    return Destination << Source.ID
    << Source.Triangles
    << Source.X
    << Source.Y;
}

Serialize& operator << (Serialize& Destination, const Texture &Source)
{
    return Destination << Source.BaseID
    << Source.ColourID
    << Source.ClippedID
    << Source.X
    << Source.Y
    << Source.VX[0]
    << Source.VY[0]
    << Source.VX[2]
    << Source.VY[2];
}

Serialize& operator << (Serialize& Destination, const Font &Source)
{
    return Destination << Source.TextureID
    << Source.Colour
    << Source.X
    << Source.Y
    << Source.Letter
    << Source.Translate[0]
    << Source.Translate[1]
    << Source.Translate[2]
    << Source.VX[0]
    << Source.VY[0]
    << Source.VX[2]
    << Source.VY[2];
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
    >> Destination.Triangles
    >> Destination.X
    >> Destination.Y;
}

DeSerialize& operator >> (DeSerialize& Source, Texture &Destination)
{
    return Source >> Destination.ID
    >> Destination.ColourID
    >> Destination.ClippedID
    >> Destination.X
    >> Destination.Y
    >> Destination.VX[0]
    >> Destination.VY[0]
    >> Destination.VX[2]
    >> Destination.VY[2];
}

DeSerialize& operator >> (DeSerialize& Source, Font &Destination)
{
    return Source >> Destination.TextureID
    >> Destination.Colour
    >> Destination.X
    >> Destination.Y
    >> Destination.Letter
    >> Destination.Translate[0]
    >> Destination.Translate[1]
    >> Destination.Translate[2]
    >> Destination.VX[0]
    >> Destination.VY[0]
    >> Destination.VX[2]
    >> Destination.VY[2];
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
