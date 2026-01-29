// /d/Avenir/common/outpost/obj/seats/wingback_chair.c
// Lilith, Jan 2022
//     Uses the seating lib developed by Lucius and Zielia
//     A common chair for use where seats are wanted.

#include "/d/Avenir/common/city/zigg/zigg.h"
inherit (ZIG_LIB + "seating");

#include "/sys/stdproperties.h"


public void
create_seating(void)
{
    string str = one_of_list(({
                 "purple", "mauve", "violet", "lilac", "royal purple", 
                 "yellow", "goldenrod", "pale yellow", "citrine",
				 "chocolate brown", "fawn", "tan", "brown" }));
	
    set_name("chair");
    set_adj(str);
    add_adj(({"wingback", "satin"}));
    set_short("satin wingback chair");
    set_long("This is a big wingback chair upholstered in "+ str +" satin. "+
    "The back is high and wide, and the arms are thickly padded. "+
	"While meant to seat one person, it is just large enough for "+
    "two to cozy up in.\n");

    set_seat_names(({"chair", "wingback chair"}));

    // Need a random # because two seats in a room can't have the same seat id.
    set_seat_id("_wingback_chair" +random(100));
   
    set_visible(1);     //  can be seen in a room when no one is sitting in it.
    set_max_seat(2);    //  only 1 person in this chair.
    set_shift_seat(1);  //  no dumping lap-sitter if seated person stands. 
    set_allow_kinky(1); //  Lets someone sit in a seated person's lap.
    add_prop(OBJ_I_WEIGHT, 60000); 
    add_prop(OBJ_I_VOLUME, 65000); 
}
