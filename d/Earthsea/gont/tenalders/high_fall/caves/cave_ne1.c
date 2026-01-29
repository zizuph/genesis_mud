/*
*  coded by Amelia 7/26/97
*
*/

inherit "/std/room";

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
inherit ROOM_TELL;



void
create_room()
{

    set_short("Limestone cave");
    set_short("Tunnel hallway.");
    set_long(BS("The tunnel levels off here. Deep under the "+
	"earth, you feel the pressure of tons of solid rock above "+
	"and around you.\n", 70));

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_tell("Moisture drips down the walls.\n");

    add_exit(CAVES+"cave7.c", "southwest");
    reset_room();
    set_tell_time(120);

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
}
