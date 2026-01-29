/*
 * local.h
 *
 * Local defines for the new Kurinost camp
 *
 * Copyright (C): Kellon, October 2011
 *
*/
// F I L E   D E F I N I T I O N S
#include "../local.h"

// O T H E R   D E F I N I T I O N S

// ROCKY SHORE
#define MOUNT_FATIGUE   (15 - (TP->resolve_task(TASK_ROUTINE, \
                            ({ TS_CON, SS_CLIMB })) ? 5 : 0))
#define SETCAPERAVAIL   random(11) + 10
#define SETCAPERRESET   random(6) + 5
#define SETPEARAVAIL    random(5) + 8
#define SETPEARRESET    random(5) + 4
#define SETVEGETATION   random(3)

// DRACONIAN CAMP
#define DCAMP_MUDDYPIT      0
#define DCAMP_BROKENPATH    1
#define DCAMP_TENTCAMP      2

#define TILEEONE            1
#define TILEETWO            2
#define TILEETHREE          4
#define TILEEFOUR           8
#define TILEEFIVE           16
#define TILEESIX            32
#define TILEESEVEN          64
#define TILEEEIGHT          128


