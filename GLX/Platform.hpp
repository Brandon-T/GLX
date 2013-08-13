#ifndef PLATFORM_HPP_INCLUDED
#define PLATFORM_HPP_INCLUDED

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <string>
#include <cstdint>
#include <stdexcept>

/** @file Platform.cpp */

/** @brief A class for loading Dynamic/Shared Libraries and importing their functions.
 */
class Library
{
    private:
        void* Module;

    public:
        /** @brief Library Constructor: Constructs a new Library Object.
         *
         * @param[in] Library A string specifying the path to the library to load.
         *
         */
        Library(std::string Library);

        /** @brief Library Destructor: Destroys the Library Object and unloads the internal loaded library specified during construction.
         *
         */
        ~Library();

        /** @brief Retrieves a function's address from the loaded library and casts it to the specified function pointer.
         *
         * @param[in] FunctionName  The name of the function whose address to retrieve.
         * @return    The function pointer to which address is casted.
         *
         */
        template<typename T>
        T FunctionAddress(std::string FunctionName);

        /** @brief Retrieves a function address from the loaded library and casts it to the specified function pointer.
         *
         * @param[out] FunctionDefinition  The function pointer that will receive the address of the specified function.
         * @param[in] FunctionName         The name of the function whose address to retrieve.
         * @return                         A boolean indication whether or not the address was retrieved successfully.
         *
         */
        template<typename T>
        bool FunctionAddress(T &FunctionDefinition, std::string FunctionName);


        /** @brief Calls a function pointer with the specified arguments.
         *
         * @param Function  A pointer to the function to be called.
         * @param args      The arguments to pass to the specified function pointer.
         * @return          The return value specified by the function pointer.
         *
         */
        template<typename T, typename ...Args>
        auto CallFunction(void* Function, Args... args) -> decltype(reinterpret_cast<T>(Function)(args...));
};

template<typename T>
T Library::FunctionAddress(std::string FunctionName)
{
    #if defined _WIN32 || defined _WIN64
    T Result = reinterpret_cast<T>(GetProcAddress(static_cast<HMODULE>(this->Module), FunctionName.c_str()));
    return Result ? Result : throw std::runtime_error(FunctionName);
    #else
    T Result = reinterpret_cast<T>(dlsym(this->Module, FunctionName.c_str()));
    return Result ? Result : throw std::runtime_error(FunctionName);
    #endif
}

template<typename T>
bool Library::FunctionAddress(T &FunctionDefinition, std::string FunctionName)
{
    return (FunctionDefinition = this->FunctionAddress<T>(FunctionName));
}

template<typename T, typename ...Args>
auto Library::CallFunction(void* Function, Args... args) -> decltype(reinterpret_cast<T>(Function)(args...))
{
    return reinterpret_cast<T>(Function)(args...);
}

#endif // PLATFORM_HPP_INCLUDED
