#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bed");
    add_adj(({"big","large","luxurious"}));
    set_short("big luxurious bed");
    set_long("Now this is a bed! It is so big four people could "+
    "probably sleep in it. Ivory silk sheets drape a goosedown "+
    "mattress that rests on a platform of white onyx.\n");

    set_seat_names(({"bed", "big bed", "large bed", "luxurious bed"}));
    set_seat_id("_v1_bed");
	
    add_item(({"sheets", "silk sheets", "ivory silk sheets" }),
	   "The sheets are smooth and heavy and very luxurious.\n");
    add_item(({"mattress", "goosedown", "goosedown mattress"}),
        "This is the thickest mattress you have ever seen. It "+
		"beckons to you to lay on the bed.\n");
    add_item(({"platform" }), "A platform made of white onyx "+
        "acts as the base on which the mattress rests.\n");
		
    set_max_seat(4);
    set_lay_num(4);

    set_shift_seat(1);
    set_allow_kinky(1);
}
