/* -*- C++ -*- */
// $Id$

/* Provides a virtual communcations layer for the drwho program. */

#ifndef _COMM_MANAGER_H
#define _COMM_MANAGER_H

#include "ace/OS.h"
#include "global.h"

class Comm_Manager
{
protected:
  char		recv_packet[UDP_PACKET_SIZE];
  char		send_packet[UDP_PACKET_SIZE];
  sockaddr_in	sin;
  int		sokfd;

  virtual int	mux (char *packet, int &packet_length)   = 0;
  virtual int	demux (char *packet, int &packet_length) = 0;
  virtual int	open (short port_number)		 = 0;
  virtual int	receive (int timeout = 0)		 = 0;
  virtual int	send (void)                              = 0;
};
#endif _COMM_MANAGER_H
