#include "zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"sturdy","wooden"}));
    set_short("sturdy wooden bench");
    set_long("It's a sturdy wooden bench placed "+
    "within the garden for sitting upon.\n");

    set_seat_names("bench");

    set_seat_id("__zigg_garden_bench");

    set_max_seat(3);
    set_lay_num(3);

    set_shift_seat(1);
    set_allow_kinky(1);
}
