/*
 * Written by Nuf
 * /d/Genesis/new/start/dwarf/dm/npc_ctrl.c
 * NPC's cloned for the mountain will end up here if they 
 * get stuck some place.
 */

#pragma strict_types

inherit "/std/room";

#include "mountain.h"

/* Prototypes */

/* Defines */

public void 
create_room()
{
    set_short("NPC control room for the dwarven mountain");
    set_long("NPC control room for the dwarven mountain.\n");
    add_exit(MOUNTAIN + "L0_shaft18x12.c", "mortal");
}

public void
reset_room()
{
    ::reset_room();
}