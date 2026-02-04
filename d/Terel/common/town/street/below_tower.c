inherit "/std/room";

#include <language.h>
#include <filter_funs.h>
#include <language.h>
#include <stdproperties.h>

void
create_room()
{
    set_short("Underground floor of the tower");
    set_long("Like the rest of the tower, this area gives no " +
        "indication of its intended purpose. The walls are charred "+
        "black, as is the floor and the ceiling, as if something "+
        "malevolent once burned here.\n");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is as deep as "+
       "the silence. There is nothing to see.\n");	
	
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -6);

    add_exit("tower1", "up");

    add_item(({"wall", "walls", "soot", "charred walls", "floor", "ceiling"}),
        "Everything is stained with an oily-black substance that "+
        "makes you feel queasy just looking at it. The stones appear "+
        "to have taken a lot of damage.\n");
    add_item(({"stones", "stone", "damage", "mortar"}),
        "The stones that the walls and floor were built from seem "+
        "to be crumbling. You can see where the mortar between the "+
        "stones has cracked and is falling away, causing some stones "+
        "to be loose.\n");
    add_item(({"loose stones", "loose stone", "foundation stones"}), 
        "Sure enough, some of the stones have become loose with "+
        "the loss of the mortar. You wonder how stable this tower "+
        "is, if these foundation stones aren't solid.\n");
    add_cmd_item(({"loose stones", "loose stone", "foundation stones"}),
        ({"move", "push", "wiggle", "remove", "pull"}), 
		"It moves, that's for sure, but not much. Which is good news, "+
        "considering you're in the basemen with an entire tower just "+
        "biding its time before it falls in on your head.\n");
}

