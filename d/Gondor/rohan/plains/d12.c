inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

public void
create_plain() 
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("central");
    set_special(5);
    add_exit("e12","north",0,5);
    add_exit("d13","east",0,5);
    add_exit(ROH_DIR + "road/er5","south",0,2);
    add_exit(ROH_DIR + "road/er4","west",0,2);

    set_npc_file(NPC_DIR + "wolf");
    set_npc_number(1 + random(3));
    reset_room();
}
