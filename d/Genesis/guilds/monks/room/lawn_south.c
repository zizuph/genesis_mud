/*
 * File:    lawn_south.c
 * Creator: Cirion, 1998.12.04
 * Purpose: Area outside the monastery
 */
#pragma strict_types

// since this is a guild room, save the binary of the file
// to facilitate quick loading after reboots
#pragma save_binary

#include "defs.h"

#define NUM_STEEDS      (4 + random(3))

inherit ROOMBASE;

object  *steeds = ({});

void reset_room();

void
create_room ()
{
    set_short("south lawn");
    set_long("Spreading away to the south past the edge of the plateau is "
        + "a vertiginous panorama of the valley below. The cold wind is "
        + "little but a breeze here, blocked by the low stone wall of "
        + "the monastery to the north. The grass is thick and high "
        + "here, untended and breathing with verdant life.\n");
    add_item(({"monastery","building"}),
        "Its ancient stones rise high overhead.\n");
    add_item(({"cliff","drop","down"}),
        "The sheer edge of the cliff drops down to a dark "
        + "forest below.\n");
    add_item(({"stone","stones"}),
        "The monastery is formed of enormous blocks of dark "
        + "grey stone.\n");
    add_item(({"grass","lawn","blades"}),
        "The grass here is high and untended.\n");

    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_west2", "northwest");
    add_exit("lawn_east2", "northeast");

    reset_room();
}


void
reset_room()
{
    object  horse;

    // note that horses only reset in this room if they are dead,
    // not if they are not present. It is intended that players
    // return their horses once thet are done.
    steeds -= ({ 0 }); // get rid of dead horses
    while(sizeof(steeds) < NUM_STEEDS)
        steeds += ({ m_clone_here("horse") });
}

