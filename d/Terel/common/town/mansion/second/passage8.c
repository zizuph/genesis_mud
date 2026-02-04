
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define SOUTH_EXIT  	"One of Dust's Rooms?"
#define NORTH_EXIT     	MANSION + "second/passage7.c"

create_room()
{
    set_short("Dark Passage");
    set_long(BS(
    	"The twisty little passage has become very narrow here.\n"));
    	
    add_exit(NORTH_EXIT, "north", 0);
    add_exit(SOUTH_EXIT, "south",  "@@no_go");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    
    add_item(({"floor", "boards", "floorboards"}),
        "The floor boards are buried deep below vast quantities of dust.\n");

    add_item(({"dust", "thick dust"}), "@@dusty_floor");

    add_cmd_item(({"dust", "thick dust"}), ({"clean", "wipe"}),
        "There is so much dust, you quickly give up hope.\n");

    add_item(({"footprint", "footprints"}), "@@footprint");

    add_item(({"passage", "tiny passage", "passages", "passageway"}),
        "The passageway is very dark and narrow.\n");
}

no_go()
{
    write("The passage is so dark you decide not to go that way!\n");
    return 1;
}

dusty_floor()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
            + (TP->query_skill(SS_LOC_SENSE)) > (random(250) + 50)) {
        return "The dust is very thick here.  You can just about make " +
               "out some footprints.\n";
        }
    return "The dust is very thick here.  You can feel your feet " +
           "sinking into the thickness.\n";
}

footprint()
{
    return "You recognise the footprints as your own.\n";
}
