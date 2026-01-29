// /d/Avenir/common/outpost/obj/seats/stool.c
// Lilith, Jan 2022
// uses the seating lib developed by Lucius and Zielia
//
//     A common stool for use where seats are wanted.

#include "/d/Avenir/common/city/zigg/zigg.h"
inherit (ZIG_LIB + "seating");
#include "/sys/stdproperties.h"

public void
create_seating(void)
{

    set_name("stool");
    add_adj(({"wooden"}));
    set_short("wooden stool");
    set_long("It's a simple stool made of pine from the Silver Forest. "+
    "A large trefoil has been carved into the round seat.\n");

    set_seat_names(({"chair","bamboo chair"}));

    // Need a random # because two seats in a room can't have the same seat id.
    set_seat_id("_simple_chair" +random(100));
	
    set_visible(1);     //  can be seen in a room when no one is sitting in it.
    set_portable(1);
    set_max_seat(1);
    set_lay_num(0);
    set_shift_seat(1);
    set_allow_kinky(1);
	
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 3500);
	
    add_item(({"seat", "round seat", "trefoil", "large trefoil"}),
    "A large trefoil, symbol of Sybarus, has been carved into the round "+
    "seat of the stool.\n");
}
