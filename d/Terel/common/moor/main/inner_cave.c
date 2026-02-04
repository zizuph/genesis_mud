/*
 * Lilith Dec 2021: updated cloning of npc
 */

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include "../local.h"


void
reset_room()
{
    if (present("vercus", TO))
        tell_room(TO, "A dark being arises from bitter slumber "+
            "in the depths of the pit.\n");
    
}

public void
create_room()
{
    set_short("Cavernous Pit");
    set_long("A shallow cavernous pit, filled with darkness.\n");
    add_prop(ROOM_S_DARK_LONG, "A shallow pit, a bowl of "+
	    "seemingly endless darkness.\n");
    add_item("pit", "It is dark and cavernous.\n");

    add_exit("cave", "out", 0);
    add_prop(ROOM_I_LIGHT, -6);
	add_npc(MOBDIR+"warlock", 1);
    set_alarm(3.0, -1.0, reset_room);
}

