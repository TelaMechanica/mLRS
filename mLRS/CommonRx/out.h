//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// OUT
//********************************************************
#ifndef OUT_H
#define OUT_H
#pragma once


#include <inttypes.h>
#include "..\Common\common_types.h"
#include "..\Common\frame_types.h"


//-------------------------------------------------------
// Generic Out Class
//-------------------------------------------------------

typedef enum {
  OUT_CONFIG_SBUS = 0,
  OUT_CONFIG_CRSF,
} OUT_CONFIG_ENUM;


typedef struct
{
  int8_t receiver_rssi1;
  int8_t receiver_rssi2;
  uint8_t receiver_LQ;
  int8_t receiver_snr;
  uint8_t receiver_antenna;
  uint8_t receiver_transmit_antenna;
  uint8_t receiver_power;
  int8_t transmitter_rssi;
  uint8_t transmitter_LQ;
  int8_t transmitter_snr;
  uint8_t transmitter_antenna;
  uint8_t transmitter_transmit_antenna;
} tOutLinkStats;


class OutBase
{
  public:
    void Init(void);

    void Configure(uint8_t new_config);

    void Do(uint16_t tnow_us);

    void SendRcData(tRcData* rc, bool frame_lost = false, bool failsafe = false);
    void SendLinkStatistics(tOutLinkStats* stats);
    void SendLinkStatisticsDisconnected(void);

    void SetChannelOrder(uint8_t new_channel_order);

  private:
    void send_sbus_rcdata(tRcData* rc, bool frame_lost, bool failsafe);
    void send_crsf_rcdata(tRcData* rc);
    void send_crsf_linkstatistics(tOutLinkStats* stats);
    void do_crsf(uint16_t tnow_us);

    void putbuf(uint8_t* buf, uint16_t len);

    virtual void putc(char c);
    virtual bool config_sbus(bool enable_flag) { return false; }
    virtual bool config_crsf(bool enable_flag) { return false; }

    uint8_t config;
    uint8_t channel_order;
    uint8_t channel_map[4];
    bool initialized;

    bool link_stats_available;
    bool link_stats_set_tstart;
    uint16_t link_stats_tstart_us;
    tOutLinkStats link_stats;
};


#endif // OUT_H
