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

#ifndef MATHEX_HPP_INCLUDED
#define MATHEX_HPP_INCLUDED

#include <array>
#include <cstring>

//template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
template<typename T>
class Vector3D
{
	private:
	    static_assert(std::is_arithmetic<T>::value, "Argument T must be of arithmetic type.");
    public:
		T X, Y, Z;

		Vector3D();
		Vector3D(T X, T Y, T Z);

		Vector3D& operator ()(T X, T Y, T Z);

        bool operator == (const Vector3D& V) const;

        bool operator != (const Vector3D& V) const;

        Vector3D& operator = (const Vector3D& V);

        Vector3D& operator += (const int& W);

        Vector3D& operator += (const Vector3D& V);

        Vector3D& operator -= (const int& W);

        Vector3D& operator -= (const Vector3D& V);

        Vector3D& operator *= (const int& W);

        T operator *= (const Vector3D& V);

        Vector3D& operator /= (const int& W);

        Vector3D& operator ^= (const Vector3D& V);

        T Dot(const Vector3D& V);

        Vector3D& Cross(const Vector3D& V);

        T Magnitude() const;

        T AngleRad(const Vector3D& V);

        T AngleDeg(const Vector3D& V);

        Vector3D& Normalize();

        Vector3D operator + (const int& W);

        Vector3D operator + (const Vector3D& V);

        Vector3D operator - (const int& W);

        Vector3D operator - (const Vector3D& V);

        Vector3D operator * (const int& W);

        T operator * (const Vector3D& V);

        Vector3D operator ^ (const Vector3D& V);

        Vector3D operator / (const int& W);
};

template<typename T>
Vector3D<T>::Vector3D() : X(0), Y(0), Z(0) {}

template<typename T>
Vector3D<T>::Vector3D(T X, T Y, T Z) : X(X), Y(Y), Z(Z) {}

template<typename T>
Vector3D<T>& Vector3D<T>::operator ()(T X, T Y, T Z)
{
    if (this->X != X && this->Y != Y && this->Z != Z)
    {
        this->X = X;
        this->Y = Y;
        this->Z = Z;
    }
    return *this;
}

template<typename T>
bool Vector3D<T>::operator == (const Vector3D<T>& V) const
{
    return ((X == V.X) && (Y == V.Y) && (Z == V.Z));
}

template<typename T>
bool Vector3D<T>::operator != (const Vector3D<T>& V) const
{
    return ((X != V.X) && (Y != V.Y) && (Z != V.Z));
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator = (const Vector3D<T>& V)
{
    if (this != &V)
    {
        X = V.X;
        Y = V.Y;
        Z = V.Z;
    }
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator += (const int& W)
{
    if (W > 0)
    {
        X += W;
        Y += W;
        Z += W;
    }
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator += (const Vector3D<T>& V)
{
    X += V.X; Y += V.Y; Z += V.Z;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator -= (const int& W)
{
    X -= W; Y -= W; Z -= W;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator -= (const Vector3D<T>& V)
{
    X -= V.X; Y -= V.Y; Z -= V.Z;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator *= (const int& W)
{
    X *= W; Y *= W; Z *= W;
    return *this;
}

template<typename T>
T Vector3D<T>::operator *= (const Vector3D<T>& V)
{
    return ((X * V.X) + (Y * V.Y) + (Z * V.Z));
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator /= (const int& W)
{
    if (W != 0)
    {
        X /= W;
        Y /= W;
        Z /= W;
    }
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator ^= (const Vector3D<T>& V)
{
    X = (Y * V.Z) - (Z * V.Y);
    Y = (Z * V.X) - (X * V.Z);
    Z = (X * V.Y) - (Y * V.X);
    return *this;
}

template<typename T>
T Vector3D<T>::Dot(const Vector3D<T>& V)
{
    return Vector3D(*this) *= V;
}

template<typename T>
Vector3D<T>& Vector3D<T>::Cross(const Vector3D& V)
{
    return Vector3D(*this) ^= V;
}

template<typename T>
T Vector3D<T>::Magnitude() const
{
    return sqrtd((X * X) + (Y * Y) + (Z * Z));
}

template<typename T>
T Vector3D<T>::AngleRad(const Vector3D<T>& V)
{
    T I = Magnitude();
    T J = V.Magnitude();
    return T((I == 0.0 || J == 0.0) ? 0.0 : acosd(Dot(V) / (I * J)));
}

template<typename T>
T Vector3D<T>::AngleDeg(const Vector3D& V)
{
    return T((AngleRad(V) * (180 / 3.1415926535897932384626433832795))); //PI = 4 * atan(1);
}

template<typename T>
Vector3D<T>& Vector3D<T>::Normalize()
{
    T Size = this->Magnitude();
    if (Size != 0)
    {
        X /= Size;
        Y /= Size;
        Z /= Size;
    }
    return *this;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator + (const int& W)
{
    return Vector3D(*this) += W;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator + (const Vector3D<T>& V)
{
    return Vector3D(*this) += V;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator - (const int& W)
{
    return Vector3D(*this) -= W;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator - (const Vector3D<T>& V)
{
    return Vector3D(*this) -= V;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator * (const int& W)
{
    return Vector3D(*this) *= W;
}

template<typename T>
T Vector3D<T>::operator * (const Vector3D<T>& V)
{
    return (*this *= V);
}

template<typename T>
Vector3D<T> Vector3D<T>::operator ^ (const Vector3D<T>& V)
{
    return Vector3D(*this) ^= V;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator / (const int& W)
{
    return Vector3D(*this) /= W;
}



template<typename T>
class Array
{
    private:
        int Width, Height;
        const std::vector<T> Data;

    public:
        Array(int Width, int Height);
        Array(T* Data, int Width, int Height);
        Array(T** Data, int Width, int Height);

        inline int size() {return Width * Height;}
        inline int size() const {return Width * Height;}

        inline int width() {return Width;}
        inline int width() const {return Width;}

        inline int height() {return Height;}
        inline int height() const {return Height;}

        inline T* operator [](int Index) {return const_cast<T*>(Data.data()) + Height * Index;}
        inline const T* operator [](int Index) const {return Data.data() + Height * Index;}
};

template<typename T>
Array<T>::Array(int Width, int Height) : Width(Width), Height(Height), Data(Width * Height, 0) {}

template<typename T>
Array<T>::Array(T* Data, int Width, int Height) : Width(Width), Height(Height), Data(Width * Height, 0) {std::copy(Data, Data + Width * Height, const_cast<T*>(this->Data.data()));}

template<typename T>
Array<T>::Array(T** Data, int Width, int Height) : Width(Width), Height(Height), Data(Width * Height, 0) {std::copy(Data[0], Data[0] + Width * Height, const_cast<T*>(this->Data.data()));}

#endif // MATHEX_HPP_INCLUDED
