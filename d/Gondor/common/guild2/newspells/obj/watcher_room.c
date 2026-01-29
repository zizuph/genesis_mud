/*
 *	/d/Gondor/common/guild2/newspells/obj/watcher_room.c
 *
 *	Dummy room for Morgul spell ???
 */
#pragma strict_types

inherit "/std/room.c";

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_long("A dummy room for the watcher.\n");
    set_short("dummy room");
}

