#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"dark","stone","heavy","basalt","basaltic"}));
    set_short("dark basalt bench");
    set_long("This bench is made of a slab of basalt that "+
    "is balanced atop two smaller blocks. It is fairly deep, "+
	"and wide enough for two. It could double as a spot "+
    "to nap, if one wanted.\n");

    set_seat_names(({"bench", "basalt bench"}));

    set_seat_id("_basalt_bench");

    set_max_seat(2);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
