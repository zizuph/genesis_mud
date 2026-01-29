#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"green","marble","heavy","uncut",}));
    set_short("green marble bench");
    set_long("This is is simple bench made from a slab of green marble "+
    "resting atop a smaller one. The marble is dark green, with pale "+
    "veins running in waves through it.\n");

    set_seat_names(({"bench", "marble bench"}));

    set_seat_id("__zigg_garden_bench");

    set_max_seat(3);
    set_lay_num(3);

    set_shift_seat(1);
    set_allow_kinky(1);
}
