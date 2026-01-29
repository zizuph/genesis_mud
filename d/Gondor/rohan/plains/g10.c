inherit "/d/Gondor/rohan/plains/plain";

#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_plain() 
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("northwest");
    set_special(5);
    set_river_name("Snowbourn");;
    set_rhard(20);
    set_rwhere("north");
    add_exit("h10","north",crossing);
    add_exit("g11","east",0,5);
    add_exit(ROH_DIR + "road/er2","south",0,2);
    add_exit(ROH_DIR + "road/er1","west",0,2);
    add_exit("willows","northeast",0,5);
    set_extraline("To the northeast you can see the willow thickets where "
      + "the Snowbourn joins the Entwash. ");
    add_item(({"thicket","willow","willows","willow thickets"}), BSN(
        "These willows are growing at the joining of the Snowbourn with the Entwash."));
    set_drink_from(({"entwash","river","stream"}));
    set_npc_number(2 + random(4));
    set_npc_file(NPC_DIR + "rabbit");
    reset_room();
}
