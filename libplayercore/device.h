/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2000  
 *     Brian Gerkey, Kasper Stoy, Richard Vaughan, & Andrew Howard
 *                      
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */
/********************************************************************
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 ********************************************************************/

/*
 * $Id: device.h 9120 2013-01-07 00:18:52Z jpgr87 $
 *
 * A device is a driver/interface pair.
 */

#ifndef _DEVICE_H
#define _DEVICE_H

#if defined (WIN32)
  #if defined (PLAYER_STATIC)
    #define PLAYERCORE_EXPORT
  #elif defined (playercore_EXPORTS)
    #define PLAYERCORE_EXPORT    __declspec (dllexport)
  #else
    #define PLAYERCORE_EXPORT    __declspec (dllimport)
  #endif
#else
  #define PLAYERCORE_EXPORT
#endif

#include <libplayerinterface/player.h>
#include <libplayercore/message.h>

#define LOCALHOST_ADDR 16777343

// Forward declarations
class Driver;

/// @brief Encapsulates a device (i.e., a driver bound to an interface)
///
/// A device describes an instantiated driver/interface
/// combination.  Drivers may support more than one interface,
/// and hence appear more than once in the device table.
class PLAYERCORE_EXPORT Device
{
  public:
    /// @brief Constructor
    ///
    /// @param addr : Device address
    /// @param driver : Pointer to the underlying driver
    Device(player_devaddr_t addr, Driver *driver);

    /// @brief Destructor
    ~Device();

    /// @brief Subscribe the given queue to this device.
    ///
    /// @returns 0 on success, non-zero otherwise.
    int Subscribe(QueuePointer &sub_queue);

    /// @brief Unsubscribe the given queue from this device.
    ///
    /// @returns 0 on success, non-zero otherwise.
    int Unsubscribe(QueuePointer &sub_queue);

    /// @brief Send a message to this device.
    ///
    /// This method is the basic way of sending a message to a device.  The
    /// header will be assembled and the message will get pushed on to the 
    /// underlying driver's InQueue.
    ///
    /// @param resp_queue : Where to push any reply (e.g., your InQueue)
    /// @param type : Message type
    /// @param subtype : Message subtype
    /// @param src : Message payload
    /// @param deprecated: Used to be the length of the message this is now calculated
    /// @param timestamp : If non-NULL, the timestamp to attach to the
    /// message; otherwise, the current time is filled in.
    void PutMsg(QueuePointer &resp_queue,
                uint8_t type, 
                uint8_t subtype,
                void* src, 
                size_t deprecated,
                double* timestamp);

    /// @brief Send a message to this device (short form)
    ///
    /// This form of PutMsg is useful if you already have the message
    /// header assembled (e.g., when you're forwarding a message).
    /// 
    /// @param resp_queue Where to push any reply
    /// @param hdr The message header.
    /// @param src The message body (its size is stored in hdr->size).
    /// @param copy If copy is false then the message will be claimed by the device
    void PutMsg(QueuePointer &resp_queue,
                player_msghdr_t* hdr,
                void* src,
                bool copy=true);

    /// @brief Make a request of another device.
    ///
    /// This method send a request message to a device
    /// and waits for the reply.
    ///
    /// @param resp_queue : Where to push the reply (e.g., your InQueue)
    /// @param type : Message type (usually PLAYER_MSGTYPE_REQ).
    /// @param subtype : Message subtype (interface-specific)
    /// @param src : Message body
    /// @param deprecated: Used to be the length of the message this is now calculated
    /// @param timestamp : If non-NULL, the timestamp to attach to the
    /// request; otherwise, the current time is filled in.
    /// @param threaded : True if the caller is executing in its own
    ///                   thread, false otherwise
    /// 
    /// @note It is is crucial that @p threaded be set correctly.  If you
    ///       call this method from within Setup() or Shutdown(), or if
    ///       your driver does not run in its own thread, then @p 
    ///       threaded must be false.  Deadlocks will otherwise result.
    ///
    /// @returns A pointer to the reply message.  The caller is responsible
    ///          for deleting this pointer.
    Message* Request(QueuePointer &resp_queue,
                     uint8_t type,
                     uint8_t subtype,
                     void* src,
                     size_t deprecated,
                     double* timestamp,
                     bool threaded = true);
                     
    /// @brief Make a request of another device with a timeout.
    ///
    /// This method send a request message to a device
    /// and waits for the reply. If a timeout occurs it returns NULL.
    ///
    /// Note that any driver calling this here a timeout is not going to be a bad error also
    /// needs to add into its process messages somethig to handle the ACKs if they are recieved
    /// after the timeout. As such I would recomment that this is only called with a timeout not
    /// 0 if a timeout occurring is an indicaion of a system ailure (and a stall is unacceptable)
    ///
    /// @param resp_queue : Where to push the reply (e.g., your InQueue)
    /// @param type : Message type (usually PLAYER_MSGTYPE_REQ).
    /// @param subtype : Message subtype (interface-specific)
    /// @param src : Message body
    /// @param timeout: How long to wait for a response, if zero will never timeout
    /// @param timestamp : If non-NULL, the timestamp to attach to the
    /// request; otherwise, the current time is filled in.
    /// @param threaded : True if the caller is executing in its own
    ///                   thread, false otherwise
    /// 
    /// @note It is is crucial that @p threaded be set correctly.  If you
    ///       call this method from within Setup() or Shutdown(), or if
    ///       your driver does not run in its own thread, then @p 
    ///       threaded must be false.  Deadlocks will otherwise result.
    ///
    /// @returns A pointer to the reply message.  The caller is responsible
    ///          for deleting this pointer. Will return NULL on a failure
    Message* TimedRequest(QueuePointer &resp_queue,
                     uint8_t type,
                     uint8_t subtype,
                     void* src,
                     double timeout = 0,
                     double* timestamp = NULL,
                     bool threaded = true);
                     

    /// @brief Compare two addresses
    ///
    /// This static method returns true if all 4 components of the two
    /// addresses match exactly.  It's useful in Driver::ProcessMessage
    /// when you're deciding how to handle a message.
    static bool MatchDeviceAddress(player_devaddr_t addr1,
                                   player_devaddr_t addr2)
    {
      // On some machines, looking up "localhost" gives you
      // "127.0.0.1", which packs into a 32-bit int as 16777343.  On other
      // machines, it gives you "0.0.0.0", which packs as 0.  In order to
      // be able to do things like play back logfiles made on any machine,
      // we'll treat these two addresses as identical.
      return(((addr1.host == addr2.host) ||
              ((addr1.host == 0) && (addr2.host == LOCALHOST_ADDR)) ||
              ((addr1.host == LOCALHOST_ADDR) && (addr2.host == 0))) &&
             (addr1.robot == addr2.robot) &&
             (addr1.interf == addr2.interf) &&
             (addr1.index == addr2.index));
    }

    /// Next entry in the device table (this is a linked-list)
    Device* next;

    /// Address for this device
    player_devaddr_t addr;

    /// The string name for the underlying driver
    char drivername[PLAYER_MAX_DRIVER_STRING_LEN];

    
    /// Pointer to the underlying driver's queue
    QueuePointer InQueue;

    /// Linked list of subscribed queues
    QueuePointer* queues;

    /// Length of @p queues
    size_t len_queues;

    /// Pointer to the underlying driver
    Driver* driver;

  private:
    /** @brief Mutex used to lock access, via Lock() and Unlock(), to
    device internals, like the list of subscribed queues. */
    pthread_mutex_t accessMutex;
    /** @brief Lock access to driver internals. */
    void Lock(void); 
    /** @brief Unlock access to driver internals. */
    void Unlock(void);
  
    
};

#endif
