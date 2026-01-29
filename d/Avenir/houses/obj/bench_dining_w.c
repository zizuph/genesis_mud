#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"dining","kesoit","west"}));
    set_short("kesoit dining bench");
    set_long("This is a bench made of kesoit wood. It has an "+
        "emerald green cushion on top. It looks like it can "+
        "seat three people.\n");

    set_seat_names(({"bench", "dining bench", "west bench"}));

    set_seat_id("_west_bench");

    set_max_seat(3);
    set_allow_kinky(1);
}
