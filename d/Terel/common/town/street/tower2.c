inherit "/std/room";

#include <stdproperties.h>
void
create_room()
{
    set_short("Inside a tower");
    set_long("The top floor of the tower is empty " +
        "except for some debris that has fallen in from " +
        "the hole in the roof high above. It is very dark "+
        "here, and the walls look charred, covered as they "+
        "are by soot or something similar.\n");
    
    add_item(({ "debris", "small debris", "fragments", "remains",
                "fragmented remains", "fragmented blocks", "leaves",
                "twigs", "paper", "bits of paper",
                "small bits of paper" }),
        "Leaves, twigs, small bits of paper, and the fragmented " +
        "remains of a pair of stone blocks from the roof lie on " +
        "the floor below a hole in the roof above.\n");

    add_item(({ "hole", "hole in roof", "openings" }),
        "Several stone blocks have fallen away, leaving a hole in " +
        "the roof of the tower, and some openings in the floor.\n");

    add_item(({"floor"}), "The floor has been damaged by stones "+
        "falling from the collapsing of the roof. You will need "+
		"to be careful not to fall through to the bottom of the "+
        "tower.\n");
		
    add_item(({ "stairs", "stairway", "staircase" }),
        "A long stairway follows the wall of the tower, spiraling " +
        "down to the tower floor.\n");
		
    add_item(({"wall", "walls", "tower", "stone", "soot"}), 
        "The walls of the tower are black with something like soot.\n");

   add_prop(ROOM_S_DARK_LONG, "It is dark here, and dank. Feeling around, "+
      "you think you might be able to make your way down. You feel a "+
      "faint breeze from the hole in the roof high overhead.\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    
    add_exit("tower1", "down");
}
