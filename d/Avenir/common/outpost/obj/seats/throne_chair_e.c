// /d/Avenir/common/outpost/obj/seats/throne_chair.c
// Lilith, Jan 2022
//     Uses the seating lib developed by Lucius and Zielia
//     A common chair for use where seats are wanted.

#include "/d/Avenir/common/city/zigg/zigg.h"
inherit (ZIG_LIB + "seating");

#include "/sys/stdproperties.h"


public void
create_seating(void)
{
    string str = one_of_list(({"black", "red", "purple"}));
	
    set_name("throne");
    add_name("chair");
    set_adj(str);
    add_adj(({"ebony", "throne-like"}));
    set_short("ebony throne-like chair");
    set_long("It is a high-backed chair made of carved ebony and "+
    "cushioned with tufted "+ str +" leather. The padding on chair arms "+
	"is thick and would make the chair comfortable for long periods "+
	"of sitting. The seat of the chair is only wide enough for "+
    "one person. The type of person who would chose this seat over "+
    "others isn't the type to share very well.\n"); 

    set_seat_names(({"throne"}));
	
    // Need a random # because two seats in a room can't have the same seat id.
    set_seat_id(random(100)+"e_throne_chair");
   
    set_visible(1);     //  can be seen in a room when no one is sitting in it.
    set_max_seat(1);    //  only 1 person in this chair.
    set_shift_seat(1);  //  no dumping lap-sitter if seated person stands. 
    set_allow_kinky(1); //  Lets someone sit in a seated person's lap.
    add_prop(OBJ_I_WEIGHT, 30000); // ~65 pounds
    add_prop(OBJ_I_VOLUME, 65000); 
}
