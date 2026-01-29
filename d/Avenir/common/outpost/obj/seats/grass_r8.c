#include "zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name(({"grass","patch"}));
    add_adj(({"thick","green","dark","luxurious",}));
    set_short("thick patch of grass");
    set_long("The grass is thick and luxurious with long dark green blades "+
    "that bend readily but spring back quickly, making them a perfect "+
    "cushion to sit or lie on without poking too much.\n");

    set_seat_names(({"grass","patch"}));

    set_seat_id("__zigg_garden_grass");

    set_max_seat(7);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
