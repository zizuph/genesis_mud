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
#define MOUNT_FATIGUE   (10 - (TP->resolve_task(TASK_ROUTINE, \
                            ({ TS_CON, SS_CLIMB })) ? 7 : 2))
#define SETCAPERAVAIL   random(11) + 5
#define SETCAPERRESET   random(6) + 5
#define SETPEARAVAIL    random(5) + 4
#define SETPEARRESET    random(5) + 4
#define SETVEGETATION   (!random(3) ? 1 : 0)
#define NESTCHANCE      (!random(4) ? 0 : 1)
#define AMBER  "/d/Genesis/gems/obj/amber"
#define CORAL  "/d/Genesis/gems/obj/coral"

// DRACONIAN CAMP
#define MUD_FATIGUE     5

#define TILE_ONE            1
#define TILE_TWO            2
#define TILE_THREE          4
#define TILE_FOUR           8
#define TILE_FIVE           16
#define TILE_SIX            32
#define TILE_COMPLETE_SET   63

#define DCAMP_MUDDYPIT      1
#define DCAMP_BROKENPATH    2
#define DCAMP_TENTCAMP      3
