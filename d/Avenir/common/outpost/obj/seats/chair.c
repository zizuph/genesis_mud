// /d/Avenir/common/outpost/obj/seats/chair.c
// Lilith, Jan 2022
// uses the seating lib developed by Lucius and Zielia
//     A common chair for use where seats are wanted.

#include "/d/Avenir/common/city/zigg/zigg.h"
inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("chair");
    add_adj(({"simple", "bamboo"}));
    set_short("simple bamboo chair");
    set_long("It's a simple chair made of cut lengths of bamboo. "+
        "The seat it made of a half-dozen sections of bamboo "+
        "lashed together with rope.\n");

    set_seat_names(({"chair","bamboo chair"}));

    // Need a random # because two seats in a room can't have the same seat id.
    set_seat_id("_simple_chair" +random(100));
	
    set_visible(1);     //  can be seen in a room when no one is sitting in it.
    set_portable(1);
    set_max_seat(1);
    set_lay_num(0);
    set_shift_seat(1);
    set_allow_kinky(1);
	
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6500);
}
