/*
 *  /d/Emerald/north_shore/outpost/outpost_outside_room.c
 *
 *  This is the base file for outdoor rooms in the outpost area.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#include "defs.h"

inherit OUTPOST_ROOM;
inherit "/d/Emerald/lib/room_tell";

void
create_outpost_outside_room()
{
    set_short("Outpost room");
    set_em_long("Outside the outpost.\n");
}

nomask void
create_outpost_room()
{
    set_tell_time(180);
    add_tell("Birds chirp in the distance.\n");
    add_tell("The sound of a woodpecker echoes in the distance.\n");
    add_tell("A slight breeze blows in from the lake.\n");
    create_outpost_outside_room();

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells();
}
