#include "zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"grey","marble","heavy","uncut",}));
    set_short("grey marble bench");
    set_long("A large, flat slab of uncut marble rests upon two smaller "+
    "blocks of the same grey marble, forming a natural looking bench "+
    "to sit and listen to the birds that's also long enough to lie on.\n");

    set_seat_names("bench");

    set_seat_id("__zigg_garden_bench");

    set_max_seat(3);
    set_lay_num(3);

    set_shift_seat(1);
    set_allow_kinky(1);
}
