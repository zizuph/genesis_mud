// /d/Avenir/common/outpost/obj/seats/chair.c
// Lilith, Jan 2022
//     Uses the seating lib developed by Lucius and Zielia
//     A common chair for use where seats are wanted.

#include "/d/Avenir/common/city/zigg/zigg.h"
inherit (ZIG_LIB + "seating");

#include "/sys/stdproperties.h"

public void
create_seating(void)
{
    set_name("chair");
    add_adj(({"bentwood", "sturdy", "bamboo"}));
    set_short("sturdy bentwood chair");
    set_long("It's a sturdy chair made of bamboo. The back and arms are "+
    "poles bent into arches, and the seat is woven of peeled bamboo.\n");

    set_seat_names(({"chair", "bentwood chair", "bamboo chair"}));

    // Need a random # because two seats in a room can't have the same seat id.
    set_seat_id("_bentwood_chair" +random(100));
   
    set_visible(1);     //  can be seen in a room when no one is sitting in it.
    set_max_seat(1);    //  only 1 person in this chair.
    set_shift_seat(1);  //  no dumping lap-sitter if seated person stands. 
    set_allow_kinky(1); //  Lets someone sit in a seated person's lap.
    set_portable(1);    //  can be carried around
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6500);
}
