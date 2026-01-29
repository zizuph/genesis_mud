#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"


public void
create_plain() 
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("south");
    set_special(5);
    add_exit("d13","north", 0, 6);
    add_exit("c14","east",  0, 6);
    add_exit(ROH_DIR + "road/er6","south",   0, 3);
    add_exit(ROH_DIR + "road/er5","west",    0, 3);
    
    set_npc_file(NPC_DIR + "deer");
    set_npc_number(1);

    reset_room();
}
