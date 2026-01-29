
#include "/d/Avenir/common/city/zigg/zigg.h"
inherit (ZIG_LIB + "seating");

#include "/sys/stdproperties.h"

public void
create_seating(void)
{	
    set_name("chair");
    add_name("north_throne");
    add_adj(({"north","throne-like", "high-backed", "wood", "wooden"}));
    set_short("north chair");
    set_long("It is a high-backed chair made of carved ebony and "+
    "cushioned with tufted azure satin. The padding on chair arms "+
	"is thick and would make the chair comfortable for long periods "+
	"of sitting. The seat of the chair is only wide enough for "+
    "one person. The type of person who would chose this seat over "+
    "others isn't the type to share very well. It is at the north "+
    "end of the table.\n"); 

    set_seat_id("_north_chair");
    set_seat_names(({"north chair", "throne", "chair"}));
   
    set_max_seat(1);    //  only 1 person in this chair.
    set_shift_seat(1);  //  no dumping lap-sitter if seated person stands. 
    set_allow_kinky(1); //  Lets someone sit in a seated person's lap.
    add_prop(OBJ_I_WEIGHT, 30000); // ~65 pounds
    add_prop(OBJ_I_VOLUME, 65000); 
}
