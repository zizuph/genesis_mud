#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("couch");
    add_adj(({"emerald","plush","satin", "east", "eastern"}));
    set_short("emerald satin couch");
    set_long("This plush couch stretches along the eastern wall. "+
	"It is long and wide enough that it "+
    "could double as a bed for napping on. The cushions are made "+
    "of emerald-green satin, which contrasts nicely with the milky "+
    "onyx walls.\n");

    set_seat_names(({"couch", "east couch", "emerald couch"}));
    set_seat_id("_emerald_couch");
	
    add_item(({"emerald cushions", "emerald satin cushions", 
	"emerald satin", "satin", "satin cushions"}), 
	"They are plump and soft and very luxurious.\n");

    set_max_seat(3);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
