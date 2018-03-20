// -*- Mode: C; c-basic-offset: 8; -*-
//
// Copyright (c) 2012 Andrew Tridgell, All Rights Reserved
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  o Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  o Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//


/// return the next packet to be sent
///
/// @param max_xmit		maximum bytes that can be sent
/// @param buf			buffer to put bytes in
///
/// @return			number of bytes to send
extern uint8_t packet_get_next(register uint8_t max_xmit, __xdata uint8_t *buf);

/// return true if the last packet was a resend
///
/// @return			true is a resend
extern bool packet_is_resend(void);

/// return true if the last packet was a injected packet
///
/// @return			true is injected
extern bool packet_is_injected(void);

/// determine if a received packet is a duplicate
///
/// @return			true if this is a duplicate
extern bool packet_is_duplicate(uint8_t len, __xdata uint8_t *buf, bool is_resend);

/// force the last packet to be re-sent. Used when packet transmit has
/// failed
extern void packet_force_resend(void);

/// set the maximum size of a packet
///
extern void packet_set_max_xmit(uint8_t max);

/// set the serial rate in bytes/s
///
/// @param  speed		serial speed bytes/s
///
extern void packet_set_serial_speed(uint16_t speed);

/// inject a packet to be sent when possible
/// @param buf			buffer to send
/// @param len			number of bytes
///			
extern void packet_inject(__xdata uint8_t *buf, __pdata uint8_t len);

// mavlink 1.0 and 2.0 markers
#define MAVLINK10_STX 254
#define MAVLINK20_STX 253

#define PPRZLINK_1 // TODO: add as a flag to makefile

#if defined PPRZLINK_1 || defined PPRZLINK_2 || defined PPRZLINK_GEC

#define PPRZ_GCS_ID 0
#define PPRZ_TELEMETRY_ID 1

#ifdef PPRZLINK_1
  #define PPRZ_STX  0x99
  #define PPRZ_RSSI_ID 39
  #define PPRZ_RSSI_LENGTH 11
  #define PPRZ_PONG_ID 3
  #define PPRZ_PONG_LENGTH 6 // 1 stx + 2 len + 3 sender id + 4 msg id + 5 chksm A + 6 chksm B
  #define PPRZ_LENGTH_IDX 1 // offset from the start of the buffer
  #define PPRZ_SENDER_ID_IDX 2 // offset from the start of the buffer
  #define PPRZ_MSG_ID_IDX 3 // offset from the start of the buffer
#endif // PPRZLINK 1.0

// pprzlink markers
#ifdef PPRZLINK_2
  #define PPRZ_STX  0x99
  #define PPRZ_RSSI_ID 39
  #define PPRZ_RSSI_LENGTH 13 // we have two extra bytes
  #define PPRZ_PONG_ID 3
  #define PPRZ_PONG_LENGTH 8 // 1 stx + 2 len + 3 sender id + 4 dest id + 5 class id + 6 msg id + 7 chksm A + 8 chksm B
  #define PPRZ_LENGTH_IDX 1 // offset from the start of the buffer
  #define PPRZ_SENDER_ID_IDX 2 // offset from the start of the buffer
  #define PPRZ_MSG_ID_IDX 5 // offset from the start of the buffer
#endif // PPRZLINK 2.0

#ifdef PPRZLINK_1_GEC
  // Currently for Pprzlink 1.0 only
  // we have an extra crypto byte at the beginning
  #define PPRZ_STX  0x99
  #define PPRZ_RSSI_ID 39
  #define PPRZ_RSSI_LENGTH 12 // 5 bytes payload + 7 bytes overhead
  #define PPRZ_PONG_LENGTH 27 // encrypted PONG length
  #define PPRZ_LENGTH_IDX 1 // offset from the start of the buffer
  #define PPRZ_CRYPTO_BYTE_IDX 2 // offset from the start of the buffer
  #define PPRZ_SENDER_ID_IDX 7 // offset from the start of the buffer
  #define PPRZ_CRYPTO_BYTE_PLAINTEXT 0xaa // plaintext value
  #define PPRZ_CRYPTO_BYTE_ENCRYPTED 0x55 // encrypted message
  #define PPRZ_MSG_ID_IDX 8 // offset from the start of the buffer
#endif // PPRZLINK 1.0 encrypted

#else
#error "Please define Pprzlink version (PPRZLINK_1, PPRZLINK_2, PPRZLINK_GEC)"
#endif
