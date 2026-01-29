inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

public void
create_plain()
{
    set_geo("rocky");
    set_wet("high");
    set_grass("long dark green");
    set_land("the Westfold");
    set_where("south");
    set_special(5);
    add_exit("j06", "north", 0, 5);
    add_exit("i07", "east",  0, 5);
    add_exit(ROH_DIR + "road/wr2",   "south", 0, 2);
    add_exit(ROH_DIR + "road/wr3",   "west",  0, 2);

    set_npc_number(1 + random(3));
    set_npc_file(NPC_DIR + "wolf");
    reset_room();
}
