/*
* Copyright (c) 2012, Alexander I. Mykyta
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
* \addtogroup MOD_FIFO FIFO Datapipe
* \brief FIFO Datapipe Buffer
* \author Alex Mykyta
*
* This module creates a generic First-in First-out buffer.
*
* <b> Compilers Supported: </b>
*    - Any C89 compatible or newer
*
* \{
**/

/**
* \file
* \brief Include file for \ref MOD_FIFO "FIFO Datapipe"
* \author Alex Mykyta
**/

#ifndef __FIFO_H__
#define __FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <result.h>

//==================================================================================================
// Struct Typedefs
//==================================================================================================

// FIFO object
    typedef struct
    {
        uint8_t *bufptr;    // pointer to the buffer array
        size_t bufsize;    // size of buffer
        size_t rdidx;    // points to next address to be read
        size_t wridx;    // points to next address to be written
#if(FIFO_LOG_MAX_USAGE == 1)
        size_t max;
#endif
    } FIFO_t;

//==================================================================================================
// Function Prototypes
//==================================================================================================
    /**
    * \brief Initializes a new FIFO Datapipe
    * \param [in] bufptr Pointer to the buffer to be used as storage for the FIFO
    * \param [in] bufsize Size of the buffer in bytes
    * \param [in] fifo Pointer to an empty #FIFO_t object
    * \param [out] fifo Initialized FIFO object
    * \return Nothing
    **/
    void fifo_init(FIFO_t *fifo, void *bufptr, size_t bufsize);

    /**
    * \brief Write data into the FIFO buffer
    * \param [in] fifo Pointer to the #FIFO_t object
    * \param [in] src Pointer to the data to be stored
    * \param [in] size Number of bytes to be written to the FIFO
    * \retval RES_OK
    * \retval RES_FULL Not enough space in FIFO for requested write operation
    **/
    RES_t fifo_write(FIFO_t *fifo, void *src, size_t size);

    /**
    * \brief Read data from the FIFO buffer
    * \param [in] fifo Pointer to the #FIFO_t object
    * \param [out] dst Destination of the data to be read. A \c NULL pointer discards the data.
    * \param [in] size Number of bytes to be read from the FIFO
    * \retval RES_OK
    * \retval RES_PARAMERR Not enough bytes written in FIFO for requested read operation
    **/
    RES_t fifo_read(FIFO_t *fifo, void *dst, size_t size);

    /**
    * \brief Read data from the FIFO buffer without advancing the read pointer
    * \param [in] fifo Pointer to the #FIFO_t object
    * \param [out] dst Destination of the data to be read.
    * \param [in] size Number of bytes to be read from the FIFO
    * \retval RES_OK
    * \retval RES_PARAMERR Not enough bytes written in FIFO for requested read operation
    **/
    RES_t fifo_peek(FIFO_t *fifo, void *dst, size_t size);

    /**
    * \brief Empties the FIFO
    * \param [in] fifo Pointer to the #FIFO_t object
    * \return Nothing
    **/
    void fifo_clear(FIFO_t *fifo);

    /**
    * \brief Get the number of bytes available for read in the FIFO
    * \param [in] fifo Pointer to the #FIFO_t object
    * \return Number of bytes
    **/
    size_t fifo_rdcount(FIFO_t *fifo); // Returns the number of bytes currently stored in the FIFO

    /**
    * \brief Get the number of bytes that can be written to the FIFO
    * \param [in] fifo Pointer to the #FIFO_t object
    * \return Number of bytes
    **/
    size_t fifo_wrcount(FIFO_t *fifo); // Returns the number of bytes free in the FIFO


#ifdef __cplusplus
}
#endif

#endif
///\}
