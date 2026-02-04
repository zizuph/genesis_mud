
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define NORTH_EXIT  MANSION + "rooms/bstairs_top"
#define WEST_EXIT   MANSION + "second/passage3.c"
#define SOUTH_EXIT  MANSION + "second/passage.c"

create_room()
{
    set_short("Dark Passage");
    set_long(BS(
    	"The twisty dusty little passage splits into two here.  A tiny " +
    	"passage twists away to the west, while the rest " +
           "of the passageway continues both north and south.\n"));

    add_exit(SOUTH_EXIT, "south", 0);
    add_exit(NORTH_EXIT, "north",  0);
    add_exit(WEST_EXIT,  "west",  0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
    
    add_item(({"floor", "boards", "floorboards"}),
        "The floor boards are buried deep below vast quantities of dust.\n");

    add_item(({"dust", "thick dust"}), "@@dusty_floor");

    add_cmd_item(({"dust", "thick dust"}), ({"clean", "wipe"}),
        "There is so much dust, you quickly give up hope.\n");

    add_item(({"footprint", "footprints"}), "@@footprint");

    add_item(({"passage", "tiny passage", "passages", "passageway"}),
        "The three passageways are very dark and narrow.\n");
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
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
            + (TP->query_skill(SS_LOC_SENSE)) > (random(250) + 50)) {
        return "The footprints lead to the south and to the east.\n";
	    }
    return "You recognise the footprints as your own.\n";
}
        
    
