/*
    Entrance to Porcia's rooms, leading to one (or several) logical riddles
    Dust 921016
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define PORDIR "/d/Terel/common/town/mansion/porcia/"



void
create_room()
{
    set_short("mysterious tunnel");
    set_long(break_string("You find yourself in a very mysterious, old " +
	"tunnel. The tunnel connects a room to the south with a room to " +
	"the north. You feel a bit unsafe to continue your way to the " +
	"north, maybe you better go back south... you can feel the cobwebs " +
	"hanging from the ceiling on your neck.\n",70));
    add_item(({"web", "webs", "cobwebs", "cobweb"}), break_string(
        "From the size of the cobwebs you realise that the creatures " +
        "who made them must be quite big.\n",70));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(PORDIR + "entrance", "south", 0);
    add_exit(DUSTDIR + "door_room", "north", 0);
}

