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

#include "Math.hpp"

const char Math::Base36Chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool Math::EncodeBase36(std::uint32_t Value, std::string &Result)
{
    if (Value < 0) return false;

    std::vector<char> Data;
    while (Value != 0)
    {
        Data.push_back(Base36Chars[Value % 36]);
        Value /= 36;
    }

    Result = std::string(Data.begin(), Data.end());
    return true;
}

std::uint32_t Math::DecodeBase36(std::string Value)
{
    std::uint32_t Result = 0;

    auto IndexOf = [&](char const & c)
    {
        const int Size = sizeof(Base36Chars) / sizeof(char);
        char const* Found = std::find(&Base36Chars[0], &Base36Chars[Size], c);
        return Found == &Base36Chars[Size] ? -1 : Found - Base36Chars;
    };

    for (std::size_t I = 0, Pos = 0; I < Value.size(); ++I, ++Pos)
    {
        Result += IndexOf(Value[I]) * std::pow(36, Pos);
    }

    return Result;
}

void Math::Transpose(float Data[16])
{
    for (int I = 1; I < 4; ++I)
    {
        for (int J = 0; J < I; ++J)
        {
            std::swap(Data[I * 4 + J], Data[J * 4 + I]);
        }
    }
}

void Math::Transpose(float Data[4][4])
{
    for (int I = 0; I < 4; ++I)
    {
        for (int J = 0; J < I; ++J)
        {
            std::swap(Data[I][J], Data[J][I]);
        }
    }
}

Vector3D<double> Math::GetEulerAngles(float ModelView[16], bool RowMajor)
{
    if (RowMajor)
    {
        double X = std::atan2(ModelView[6], ModelView[10])  * (180 / Math::PI);
        double Y = std::atan2(-ModelView[8], std::sqrt(std::pow(ModelView[0], 2) + std::pow(ModelView[1], 2)))  * (180 / Math::PI);
        double Z = std::atan2(ModelView[1], ModelView[0]) * (180 / Math::PI);
        return {X < 0 ? 360 - X : X, Y < 0 ? 360 - Y : Y, Z < 0 ? 360 - Z : Z};
    }
    else
    {
        double X = std::atan2(ModelView[9], ModelView[10])  * (180 / Math::PI);
        double Y = std::atan2(-ModelView[8], std::sqrt(std::pow(ModelView[0], 2) + std::pow(ModelView[4], 2)))  * (180 / Math::PI);
        double Z = std::atan2(ModelView[4], ModelView[0]) * (180 / Math::PI);
        return {X < 0 ? 360 - X : X, Y < 0 ? 360 - Y : Y, Z < 0 ? 360 - Z : Z};
    }
}

Vector3D<double> Math::GetEulerAngles(float ModelView[4][4], bool RowMajor)
{
    if (RowMajor)
    {
        double X = std::atan2(ModelView[1][2], ModelView[2][2])  * (180 / Math::PI);
        double Y = std::atan2(-ModelView[0][2], std::sqrt(std::pow(ModelView[0][0], 2) + std::pow(ModelView[0][1], 2)))  * (180 / Math::PI);
        double Z = std::atan2(ModelView[0][1], ModelView[0][0]) * (180 / Math::PI);
        return {X < 0 ? 360 - X : X, Y < 0 ? 360 - Y : Y, Z < 0 ? 360 - Z : Z};
    }
    else
    {
        double X = std::atan2(ModelView[2][1], ModelView[2][2])  * (180 / Math::PI);
        double Y = std::atan2(-ModelView[2][0], std::sqrt(std::pow(ModelView[0][0], 2) + std::pow(ModelView[1][0], 2)))  * (180 / Math::PI);
        double Z = std::atan2(ModelView[1][0], ModelView[0][0]) * (180 / Math::PI);
        return {X < 0 ? 360 - X : X, Y < 0 ? 360 - Y : Y, Z < 0 ? 360 - Z : Z};
    }
}

Vector3D<double> Math::GetTranslation(float ModelView[16], bool RowMajor)
{
    return RowMajor ? Vector3D<double>{ModelView[12], ModelView[13], ModelView[14]} : Vector3D<double>{ModelView[3], ModelView[7], ModelView[11]};
}

Vector3D<double> Math::GetTranslation(float ModelView[4][4], bool RowMajor)
{
    return RowMajor ? Vector3D<double>{ModelView[3][0], ModelView[3][1], ModelView[3][2]} : Vector3D<double>{ModelView[0][3], ModelView[1][3], ModelView[2][3]};
}

double Math::CalculateAngle(double Size, double Distance)
{
    double Rad = 2.0 * std::atan2(Size / 2.0, Distance);
    return (180.0 * Rad) / 3.1415926535897932384626433832795;
}

void Math::PointOfView(double ObjectX, double ObjectY, double ObjectZ, double Roll, double Pitch, double Heading)
{
    glRotated(Roll, 0.0, 0.0, 1.0);
    glRotated(Pitch, 0.0, 1.0, 0.0);
    glRotated(Heading, 1.0, 0.0, 0.0);
    glTranslated(-ObjectX, -ObjectY, -ObjectZ);
}

void Math::PolarView(double Distance, double Twist, double Elevation, double Azimuth)
{
    glTranslated(0.0, 0.0, -Distance);
    glRotated(-Twist, 0.0, 0.0, 1.0);
    glRotated(-Elevation, 1.0, 0.0, 0.0);
    glRotated(Azimuth, 0.0, 0.0, 1.0);
}

bool Math::WorldToScreen(float &X, float &Y, Vector3D<float> World)
{
    int ViewPort[4];
    double Screen[3];
    double ModelViewMatrix[16];
    double ProjectionMatrix[16];

    glGetIntegerv(GL_VIEWPORT, ViewPort);
    glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

    if(gluProject(World.X, World.Y, World.Z, ModelViewMatrix, ProjectionMatrix, ViewPort, &Screen[0], &Screen[1], &Screen[2]))
    {
        X = static_cast<float>(Screen[0]);
        Y = static_cast<float>(ViewPort[3] - Screen[1]);
        return true;
    }
    return false;
}

bool Math::WorldToScreen(float &X, float &Y, Vector3D<float> World, int* ViewPort, double* ModelViewMatrix, double* ProjectionMatrix)
{
    double Screen[3];
    if(gluProject(World.X, World.Y, World.Z, ModelViewMatrix, ProjectionMatrix, ViewPort, &Screen[0], &Screen[1], &Screen[2]))
    {
        X = static_cast<float>(Screen[0]);
        Y = static_cast<float>(ViewPort[3] - Screen[1]);
        return true;
    }
    return false;
}

bool Math::ScreenToWorld(float X, float Y, Vector3D<float> &World)
{
    float Z = 0;
    int ViewPort[4];
    double Screen[3];
    double ModelViewMatrix[16];
    double ProjectionMatrix[16];

    glGetIntegerv(GL_VIEWPORT, ViewPort);
    glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

    glReadPixels(static_cast<int>(X), static_cast<int>(ViewPort[3] - Y - 1), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Z);
    if (gluUnProject(X, ViewPort[3] - Y - 1, Z, ModelViewMatrix, ProjectionMatrix, ViewPort, &Screen[0], &Screen[1], &Screen[3]))
    {
        World.X = static_cast<float>(Screen[0]);
        World.Y = static_cast<float>(Screen[1]);
        World.Z = static_cast<float>(Screen[2]);
        return true;
    }
    return false;
}

bool Math::ScreenToWorld(float X, float Y, Vector3D<float> &World, int* ViewPort, double* ModelViewMatrix, double* ProjectionMatrix)
{
    float Z = 0;
    double Screen[3];
    glReadPixels(static_cast<int>(X), static_cast<int>(ViewPort[3] - Y - 1), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Z);
    if (gluUnProject(X, ViewPort[3] - Y - 1, Z, ModelViewMatrix, ProjectionMatrix, ViewPort, &Screen[0], &Screen[1], &Screen[3]))
    {
        World.X = static_cast<float>(Screen[0]);
        World.Y = static_cast<float>(Screen[1]);
        World.Z = static_cast<float>(Screen[2]);
        return true;
    }
    return false;
}

std::uint32_t Math::ColourCheckSum(const void* Data, std::uint32_t &MeanColour, std::size_t Width, std::size_t Height, uint32_t BitsPerPixel)
{
    std::uint32_t CheckSum = 0;
    int R = 0, G = 0, B = 0, K = 0;

    const std::uint8_t* BuffPos = static_cast<const std::uint8_t*>(Data);

    for (std::size_t I = Height < 12 ? 1 : 12; I < Height; ++I)
    {
        for (std::size_t J = 0; J < Width; ++J, ++K)
        {
            R += *(BuffPos++);
            G += *(BuffPos++);
            B += *(BuffPos++);
            CheckSum += (BitsPerPixel > 24 ? * (BuffPos++) : 0xFF);
        }

        if(BitsPerPixel == 24)
            BuffPos += (-Width * 3) & 3;
    }

    MeanColour = (K != 0 ? RGB(R / K, G / K, B / K) : RGB(R, G, B));

    return CheckSum;
}

std::uint32_t Math::LazyCheckSum(std::uint32_t* Data, std::size_t Size)
{
    if(!Data) return 0;
    std::uint32_t Temp = 0, Sum = *Data;

    for(std::size_t I = 1; I < (Size / 4); ++I)
    {
        Temp = Data[I];
        Temp = static_cast<std::uint32_t>(Sum >> 29) + Temp;
        Temp = static_cast<std::uint32_t>(Sum >> 17) + Temp;
        Sum = static_cast<std::uint32_t>(Sum << 3) ^ Temp;
    }
    return Sum;
}

std::uint32_t Math::CRC32CheckSum(void* Data, std::size_t Size, std::uint32_t InitialValue)
{
    static const std::uint32_t LookUpTable[256] =
    {
        0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
        0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
        0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
        0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
        0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
        0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
        0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
        0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
        0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
        0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
        0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
        0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
        0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
        0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
        0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
        0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
        0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
        0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
        0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
        0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
        0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
        0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
        0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
        0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
        0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
        0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
        0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
        0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
        0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
        0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
        0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
        0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
        0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
        0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
        0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
        0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
        0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
        0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
        0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
        0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
        0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
        0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
        0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
        0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
        0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
        0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
        0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
        0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
        0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
        0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
        0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
        0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
        0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
        0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
        0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
        0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
        0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
        0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
        0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
        0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
        0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
        0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
        0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
        0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
    };

    std::uint32_t CRC = ~InitialValue;
    std::uint8_t* Pointer = static_cast<std::uint8_t*>(Data);

    for(std::size_t I = 0; I < Size; ++I)
    {
        CRC = LookUpTable[(CRC ^ *Pointer++) & 0xFF] ^ (CRC >> 8);
    }

    return ~CRC;
}
