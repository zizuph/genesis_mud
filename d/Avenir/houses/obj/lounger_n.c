#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("lounger");
	add_name(({"chair", "chaise", "lounge"}));
    add_adj(({"lounge","rope", "mesh", "wood", "wooden","north","pool"}));
    set_short("lounge chair");
    set_long("This is a long chair designed for lounging by the pool. "+ 
	"It is made of a wooden frame with ropes lashed between, forming a "+
    "mesh net that supports a person while enabling water to drain away. "+
    "It is narrow, so it will fit only one person, but it looks very "+
    "comfortable. This lounger is located north of the other one.\n");

    set_seat_names(({"lounge", "lounger", "north lounger", "pool chair"}));
    set_seat_id("_north_lounger");

    add_item(({"rope", "mesh", "web", "net"}), "Ropes have been lashed to "+
    "the wooden frame of the lounger, forming a mesh-like net that is "+
    "comfortable to recline in.\n");
	
    set_max_seat(1);
    set_lay_num(1);

    set_shift_seat(1);
    set_allow_kinky(1);
}
