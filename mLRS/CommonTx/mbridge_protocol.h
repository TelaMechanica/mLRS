//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// M Bridge Protocol
//********************************************************
#ifndef MBRIDGE_PROTOCOL_H
#define MMBRIDGE_PROTOCOL_H
#pragma once

#include <inttypes.h>


#ifndef PACKED
  #define MBRDIGE_PACKED(__Declaration__)  __Declaration__ __attribute__((packed)) // that's for __GNUC__
#else
  #define MBRDIGE_PACKED  PACKED
#endif


#define MBRIDGE_STX1                        'O'
#define MBRIDGE_STX2                        'W'

#define MBRIDGE_RX_SERIAL_PAYLOAD_LEN_MAX   17 // up to 17 bytes payload when received from transmitter

#define MBRIDGE_TX_SERIAL_PAYLOAD_LEN_MAX   16 // up to 16 bytes payload when send to transmitter
#define MBRIDGE_TX_SERIAL_PAYLOAD_LEN_LIM   11 // only up to 11 bytes if a channel or command packet was received

#define MBRIDGE_CHANNELPACKET_SIZE          22 // 22 bytes payload, only received from transmitter

#define MBRIDGE_RX_COMMAND_PAYLOAD_LEN      22 // 22 bytes payload when received from transmitter
#define MBRIDGE_RX_COMMAND_FRAME_LEN        23 // cmd byte + payload

#define MBRIDGE_TX_COMMAND_PAYLOAD_LEN      12 // 12 bytes payload when send to transmitter
#define MBRIDGE_TX_COMMAND_FRAME_LEN        13 // cmd byte + payload


typedef enum {
  MBRIDGE_SERIALPACKET_STX    = 0x00,
  MBRIDGE_CHANNELPACKET_STX   = 0xFF,
  MBRIDGE_COMMANDPACKET_STX   = 0xA0, // 0b101x
  MBRIDGE_COMMANDPACKET_MASK  = 0xE0, // 0b111x
} MBRIDGE_PACKET_STX_ENUM;


typedef enum {
  MBRIDGE_TYPE_NONE = 0,
  MBRIDGE_TYPE_SERIALPACKET,
  MBRIDGE_TYPE_CHANNELPACKET,
  MBRIDGE_TYPE_COMMANDPACKET,
} MBRIDGE_TYPE_ENUM;;


typedef enum {
  MBRIDGE_TX_CMD_LINK_STATS = 0x02,
} MBRIDGE_TX_CMD_ENUM;


// do not confuse with sbus, it is similar to sbus packet format, but not sbus values
typedef union {
  uint8_t c[MBRIDGE_CHANNELPACKET_SIZE]; // 154 + 20 + 2 = 176 bits = 22 bytes
  MBRDIGE_PACKED(
  struct {
      uint16_t ch0  : 11; // 14 channels a 11 bits per channel = 154 bits, 0 .. 1024 .. 2047
      uint16_t ch1  : 11;
      uint16_t ch2  : 11;
      uint16_t ch3  : 11;
      uint16_t ch4  : 11;
      uint16_t ch5  : 11;
      uint16_t ch6  : 11;
      uint16_t ch7  : 11;
      uint16_t ch8  : 11;
      uint16_t ch9  : 11;
      uint16_t ch10 : 11;
      uint16_t ch11 : 11;
      uint16_t ch12 : 11;
      uint16_t ch13 : 11;
      uint16_t ch14 : 10; // 2 channels a 10 bits per channel = 20 bits, 0 .. 512 .. 1023
      uint16_t ch15 : 10;
      uint16_t ch16 : 1; // 2 channels a 1 bits per channel = 2 bits, 0..1
      uint16_t ch17 : 1;
  });
} tMBridgeChannelBuffer;


MBRDIGE_PACKED(
typedef struct
{
  int8_t rssi;
  uint8_t LQ;
  int8_t snr; // invalid = INT8_MAX
  int8_t rssi2; // in case of 2nd antenna, invalid = INT8_MAX

  int8_t receiver_rssi;
  uint8_t receiver_LQ;
  int8_t receiver_snr; // invalid = INT8_MAX
  int8_t receiver_rssi2; // in case of 2nd antenna, invalid = INT8_MAX

  uint8_t ant_no : 1; // 0: antenna 1, 1: antenna 2
  uint8_t receiver_ant_no : 1; // 0: antenna 1, 1: antenna 2
  uint8_t spare_bits : 6;

  uint8_t LQ_received_ma;
  uint8_t LQ_received;
  uint8_t LQ_valid_received;
}) tMBridgeLinkStats;



#endif // MBRIDGE_PROTOCOL_H
