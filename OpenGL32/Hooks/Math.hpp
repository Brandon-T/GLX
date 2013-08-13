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

#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdint>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "MathEx.hpp"

class Math
{
    private:
        static const char Base36Chars[];

    public:
        static constexpr double PI = 3.1415926535897932384626433832795;
        bool EncodeBase36(std::uint32_t Value, std::string &Result);

        std::uint32_t DecodeBase36(std::string Value);

        void Transpose(float Data[16]);

        void Transpose(float Data[4][4]);

        Vector3D<double> GetEulerAngles(float ModelView[16], bool RowMajor = true);

        Vector3D<double> GetEulerAngles(float ModelView[4][4], bool RowMajor = true);

        Vector3D<double> GetTranslation(float ModelView[16], bool RowMajor = true);

        Vector3D<double> GetTranslation(float ModelView[4][4], bool RowMajor = true);

        double CalculateAngle(double Size, double Distance);

        void PointOfView(double ObjectX, double ObjectY, double ObjectZ, double Roll, double Pitch, double Heading);

        void PolarView(double Distance, double Twist, double Elevation, double Azimuth);

        bool WorldToScreen(float &X, float &Y, Vector3D<float> World);

        bool WorldToScreen(float &X, float &Y, Vector3D<float> World, int* ViewPort, double* ModelViewMatrix, double* ProjectionMatrix);

        bool ScreenToWorld(float X, float Y, Vector3D<float> &World);

        bool ScreenToWorld(float X, float Y, Vector3D<float> &World, int* ViewPort, double* ModelViewMatrix, double* ProjectionMatrix);

        std::uint32_t ColourCheckSum(const void* Data, std::uint32_t &MeanColour, size_t Width, size_t Height, uint32_t BitsPerPixel = 32);

        std::uint32_t LazyCheckSum(std::uint32_t* BufferData, size_t Size);

        std::uint32_t CRC32CheckSum(void* Data, size_t Size, std::uint32_t InitialValue = 0xFFFFFFFF);
};

#endif // MATH_HPP_INCLUDED
