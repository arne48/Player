/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) Andrew Howard 2003
 *
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
 */
/***************************************************************************
 * Desc: Test program for the Player C client
 * Author: Andrew Howard
 * Date: 23 May 2002
 # CVS: $Id: test.h 9120 2013-01-07 00:18:52Z jpgr87 $
 **************************************************************************/

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "playerc.h"

// Message macros
#define TEST(msg) (1 ? printf(msg " ... "), fflush(stdout) : 0)
#define TEST1(msg, a) (1 ? printf(msg " ... ", a), fflush(stdout) : 0)
#define PASS() (1 ? printf("pass\n"), fflush(stdout) : 0)
#define FAIL() (1 ? printf("\033[41mfail\033[0m\n%s\n", playerc_error_str()), fflush(stdout) : 0)

// Basic test for proxies
extern int test_aio(playerc_client_t *client, int index);
extern int test_blobfinder(playerc_client_t *client, int index);
extern int test_camera(playerc_client_t *client, int index);
extern int test_dio(playerc_client_t *client, int index);
extern int test_graphics2d(playerc_client_t *client, int index);
extern int test_graphics3d(playerc_client_t *client, int index);
extern int test_gripper(playerc_client_t *client, int index);
extern int test_imu(playerc_client_t *client, int index);
extern int test_laser(playerc_client_t *client, int index);
extern int test_log(playerc_client_t *client, int index);
extern int test_map(playerc_client_t *client, int index);
extern int test_position2d(playerc_client_t *client, int index);
extern int test_position3d(playerc_client_t *client, int index);
extern int test_power(playerc_client_t *client, int index);
extern int test_ptz(playerc_client_t *client, int index);
extern int test_rfid(playerc_client_t *client, int index);
extern int test_simulation(playerc_client_t *client, int index);
extern int test_sonar(playerc_client_t *client, int index);
extern int test_speech(playerc_client_t *client, int index);
extern int test_wsn(playerc_client_t *client, int index);
extern int test_coopobject(playerc_client_t *client, int index);


#if 0
// Basic test for BPS device.i
extern int test_bps(playerc_client_t *client, int index);

// Basic broadcast test
extern int test_broadcast(playerc_client_t *client, int index);

// Basic test for GPS device.i
extern int test_gps(playerc_client_t *client, int index);

// Basic localization test
extern int test_localize(playerc_client_t *client, int index);

// Basic test for the LBD (laser beacon detector) device.
// REMOVE? int test_lbd(playerc_client_t *client, int index);

// Basic localization test
int test_localize(playerc_client_t *client, int index);

// Basic test for truth device.
extern int test_truth(playerc_client_t *client, int index);

// Basic vision test.
extern int test_vision(playerc_client_t *client, int index);

// Basic comms device test
extern int test_comms(playerc_client_t *client, int index);

// Basic test for the laser beacon device.
extern int test_fiducial(playerc_client_t *client, int index);

// Basic test for wifi device.
extern int test_wifi(playerc_client_t *client, int index);
#endif



#endif // TEST_H
