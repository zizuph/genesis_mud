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
    string str = one_of_list(({"ermine", "mink", "chincilla", "fox",
	             "wolf", "seal", "leopard", "pahloor", "panther", 
                 "lynx", "sable" }));
	
    set_name("chair");
    set_adj(str);
    add_adj(({"sling", "cross", "hammock"}));
    set_short("fur-draped sling chair");
    set_long("This is an ancient chair made with four beautifully carved " 
     +"wooden legs that curve upward in the shape of an S. The back and "
     +"seat of the chair have sturdy animal hide slung between them, "
	 +"with "+ str +" furs draped over for extra softness and comfort. "
     +"Sitting in this is like being cradled in a hammock.\n");

    set_seat_names(({"chair", "sling", "hammock"}));

    set_seat_id("_sling_chair_e");
   
//    set_visible(1);     //  can be seen in a room when no one is sitting in it.
    set_max_seat(1);    //  only 1 person in this chair.
    set_shift_seat(1);  //  no dumping lap-sitter if seated person stands. 
    set_allow_kinky(1); //  Lets someone sit in a seated person's lap.
    set_portable(1);    //  can be carried around
    add_prop(OBJ_I_WEIGHT, 5000); 
    add_prop(OBJ_I_VOLUME, 5000); 
}
