inherit "/d/Gondor/rohan/plains/plain";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain()
{
    set_geo("open");
    set_wet("damp");
    set_grass("high dark green");
    set_land("the Westfold");
    set_where("northwestern");
    set_special(2);
    set_river_name("Deeping Stream");;
    set_rhard(10);
    set_rwhere("north");
    add_exit("NotOpen/l04","north",drown);
/*
    add_exit("NotOpen/l04","north",crossing);
*/
    add_exit("k05","east",0,5);
    add_exit("j04","south",0,5);
    add_exit("k03","west",0,5);

    set_npc_number(2 + random(5));
    set_npc_file(NPC_DIR + "rabbit");
    reset_room();
    set_drink_from( ({"stream","river","deeping stream"}) );
}
