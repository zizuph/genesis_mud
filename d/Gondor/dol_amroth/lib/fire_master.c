/* -*- Mode: C -*-
 *
 * fire_master.c
 *
 * By Skippern 20(c)02
 *
 * Controling the fires from the fireplaces and the smoke in the chimneys.
 */
inherit "/std/room";

#include "../defs.h"

#define ROOF      (DOL_HILLS + "m-11/roof.c")
#define NORTH     (DOL_HILLS + "m-11/hall2.c")
#define SOUTH     (DOL_HILLS + "m-11/hall4.c")
#define TIME      15.0

/* Global variables */
public int        Smoke_N, Smoke_S;

/* Prototypes */
void self_extinguish(string arg);


void
create_room()
{
    set_short("fire master");
    set_long("Are you nuts? You are sitting in the middle of the fire in a " +
	     "fireplace. Get out of here!!!!\n");
}

public void 
fire_north() 
{ 
    Smoke_N = 1; 
    tell_room(ROOF, "A puff of smoke comes out of the north chimney.\n", 0, 0);
    NORTH->start_noise();
    set_alarm(TIME, 0.0, &self_extinguish("north"));
}

public void 
fire_south() 
{ 
    Smoke_S = 1; 
    tell_room(ROOF, "A puff of smoke comes out of the south chimney.\n", 0, 0);
    SOUTH->start_noise();
    set_alarm(TIME, 0.0, &self_extinguish("south"));
}

public void 
extinguish_north() 
{ 
    Smoke_N = 0; 
    tell_room(ROOF, "The smoke dies out from the north chimney.\n", 0, 0);
    NORTH->stop_noise();
}

public void 
extinguish_south() 
{
    Smoke_S = 0; 
    tell_room(ROOF, "The smoke dies out from the south chimney.\n", 0, 0);
    SOUTH->stop_noise();
}

public int query_smoke_n() { return Smoke_N; }
public int query_smoke_s() { return Smoke_S; }

void
self_extinguish(string arg)
{
    if (arg == "north" && Smoke_S == 1)
    {
        tell_room(SOUTH, "The fire starts to flicker and dies out.\n", 0, 0);
	extinguish_south();
        return;
    }
    else if (arg == "south" && Smoke_N == 1)
    {
        tell_room(NORTH, "The fire starts to flicker and dies out.\n", 0, 0);
	extinguish_north();
        return;
    }
}


