#include "zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"cast iron","iron","black","scrolling","elaborate",}));
    set_short("cast iron bench");
    set_long("A scrolling cast iron frame with elaborate black curls "+
    "holds together glossy cherry wood boards to form a lovely bench "+
    "for passersby to sit and enjoy a moment of solitude or perhaps "+
    "a romantic rendezvous in the garden.\n");

    set_seat_names("bench");

    set_seat_id("__zigg_garden_bench");

    set_max_seat(2);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
