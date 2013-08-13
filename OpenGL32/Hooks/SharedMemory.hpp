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

#ifndef SHAREDMEMORY_HPP_INCLUDED
#define SHAREDMEMORY_HPP_INCLUDED

#if defined _WIN32 || defined _WIN64
    #include <windows.h>
#else
    #include <sys/types.h>
    #include <sys/mman.h>
    #include <dlfcn.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

#include <tchar.h>
#include <iostream>
#include <map>

/** @file SharedMemory.cpp */

/** @brief A class for mapping
 */
class SharedMemory
{
    private:
        void* FromFile;
        void* hFileMap;
        void* pData;
        std::string MapName;
        std::size_t Size;
        bool Debug;
        std::map<std::string, void*> Events;

    public:
        /** @brief SharedMemory Constructor: Constructs a new SharedMemory object with the specified map name.
         *
         * @param MapName   The unique map name to identify the shared memory region.
         *
         */
        SharedMemory(std::string MapName);


        /** @brief SharedMemory Constructor: Constructs a new SharedMemory object with the specified map name and size.
         *
         * @param MapName   The unique map name to identify the shared memory region.
         * @param Size      The size of the memory region to map.
         *
         */
        SharedMemory(std::string MapName, std::size_t Size);


        /** @brief SharedMemory Destructor: Destroys the SharedMemory object and un-maps the shared memory region.
         *
         *
         */
        ~SharedMemory();

        /** @brief Copy Constructor: Copies/Clones a SharedMemory object.
         *
         * @param Shm The SharedMemory object to copy.
         *
         */
        SharedMemory(const SharedMemory& Shm) = delete;


        /** @brief Move Constructor: Moves a SharedMemory object.
         *
         * @param Shm The SharedMemory object to move.
         *
         */
        SharedMemory(SharedMemory && Shm) = delete;


        /** @brief Copy assignment operator.
         *
         * @param Shm The SharedMemory object to copy.
         * @return A pointer to this instance containing a copy of the specified object.
         *
         */
        SharedMemory& operator = (const SharedMemory& Shm) = delete;


        /** @brief Move assignment operator.
         *
         * @param Shm The SharedMemory object to move.
         * @return A pointer to this instance containing the moved object.
         *
         */
        SharedMemory& operator = (SharedMemory && Shm) = delete;

        /** @brief Retrieves a pointer to the mapped memory region.
         *
         * @return A pointer to the shared/mapped memory region; nullptr is returned if memory was not mapped successfully.
         *
         */
        void* GetDataPointer();


        /** @brief Opens the shared memory region with the given size.
         *
         * @param Size      Size of the memory region to map.
         * @return          A boolean indication whether the memory region was opened and mapped successfully.
         *
         */
        bool OpenMemoryMap(std::size_t Size);


        /** @brief Creates and maps a shared memory region with the given size.
         *
         * @param Size      Size of the memory region to map.
         * @return          A boolean indicating whether the memory region was created and mapped successfully.
         *
         */
        bool MapMemory(std::size_t Size);

        /** @brief Un-maps and closes the shared memory region.
         *
         * @return A boolean indicating whether or not the memory region was unmapped and closed successfully.
         *
         */
        bool ReleaseMemory();

        /** @brief Creates a new Event for synchronous communication between processes.
         *
         * @param lpEventAttributes         The security attributes to apply to the new event; usually nullptr.
         * @param bManualReset              A boolean indication whether the user should manually reset the events.
         * @param bInitialState             A boolean indicating whether the initial state of the event is signaled.
         * @param EventName                 A unique name for which to identify this event.
         * @return                          A boolean indicating whether the event was created successfully.
         *
         */
        bool CreateNewEvent(LPSECURITY_ATTRIBUTES lpEventAttributes, bool bManualReset, bool bInitialState, std::string EventName);

        /** @brief Opens the specified event with the specified access flags.
         *
         * @param EventName                 The unique-name of the event to open.
         * @param InheritHandle             A boolean indicating whether or not to inherit the event's handle.
         * @param SaveHandle                A boolean indicating whether or not to stored the event's handle. Default = false.
         * @param dwDesiredAccess           The specified access flags to use when opening the event. Default = EVENT_ALL_ACCESS.
         * @param dwMilliseconds            Specifies how long to wait for the event. A timeout flag in milliseconds. Default = INFINITE.
         * @return                          An integer indicating whether or not the event was opened successfully. WAIT_FAILED is returned upon failure.
         *
         */
        std::uint32_t OpenSingleEvent(std::string EventName, bool InheritHandle, bool SaveHandle = false, std::uint32_t dwDesiredAccess = EVENT_ALL_ACCESS, std::uint32_t dwMilliseconds = INFINITE);

        /** @brief  Sets the signal of the event.
         *
         * @param EventName                 The unique-name of the event whose signals to change.
         * @param Signaled                  A boolean indicating whether the event's signal should be on or off.
         * @return                          A boolean indicating whether the state of the event was successfully set.
         *
         */
        bool SetEventSignal(std::string EventName, bool Signaled);

        /** @brief Destroyed the specified event.
         *
         * @param EventName                 The unqiue-name of the event to destroy.
         * @return                          A boolean indicating whether or not the event was found and destroyed successfully.
         *
         */
        bool DeleteSingleEvent(std::string EventName);

        /** @brief Deletes all events allocated within this SharedMemory object.
         *
         * @return A boolean indicating whether all events were destroyed successfully.
         *
         */
        bool DeleteAllEvents();

        /** @brief Sets Debugging on.
         *
         * @param On        If debugging is on, states of events and mapped regions are printed to the standard output stream.
         *
         */
        void SetDebug(bool On);
};

#endif // SHAREDMEMORY_HPP_INCLUDED
