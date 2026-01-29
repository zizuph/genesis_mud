#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
enter_inv(object ob, object from)
{
    object sword;
    string origin_alignment;

    ::enter_inv(ob, from);

    while (sword = present("light_sword", ob))
    {
	write("Your sword of light suddenly fades and then starts emitting " +
	    "darkness!\n");
	say(QCTNAME(ob) + "'s sword of light suddenly fades and then starts " +
	    "emitting darkness!\n");
	origin_alignment = sword->query_prop(OBJ_S_ORIGIN_ALIGNMENT);
	sword->remove_object();
	sword = clone_object(WEAPON("sword_of_darkness"));
	sword->move(ob);
	sword->add_prop(OBJ_S_ORIGIN_ALIGNMENT, origin_alignment);
    }
}

void
create_room()
{
    set_short("The room of darkness");
    set_long(
	"This is a small trapezoidal-shaped room whose north and south walls " +
	"slope away to the east.  " +
	"The darkness in this room is very heavy, and your light source does " +
	"little good.  " +
	"You can make out no other details in the dimness.  " +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(ROOM("dark_stairs"), "west", 0);
    add_exit(ROOM("dark_silent"), "east", 0);
    add_exit(ROOM("dark_bronze"), "north", 0);
    call_out("reset_room", 1);
}