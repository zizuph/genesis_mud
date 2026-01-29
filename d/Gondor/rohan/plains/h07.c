inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

void
create_plain()
{
    set_geo("rocky");
    set_wet("high");
    set_grass("thick dark green");
    set_land("the Westfold");
    set_where("south");
    set_special(5);
    set_river_name("Snowbourn");;
    set_rwhere("southwest");

    add_exit("i07","north",0,5);
    add_exit("h08","east",0,5);
    add_exit(ROH_DIR + "road/wr1","south",0,2);
    add_exit(ROH_DIR + "road/wr2","west",0,2);

    add_item(({"stream","river","snowbourn"}), BSN(
        "The Snowbourn runs down swiftly into the plain, and at the "
      + "foot of the hills turns in wide bend, flowing away to the east "
      + "to feed the Entwash far off in its reed-choked beds."));

    set_npc_number(3 + random(3));
    set_npc_file(NPC_DIR + "rabbit");
    reset_room();
    set_drink_from( ({"stream","river","snowbourn"}) );
}
