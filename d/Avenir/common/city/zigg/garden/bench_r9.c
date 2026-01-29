#include "zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"black","stone","glossy","heavy",}));
    set_short("black stone bench");
    set_long("A black stone bench carved of the same glossy black stone "+
    "of the ziggurat stands in front of a lovely backdrop of pale flowers. "+
    "The bench is simply carved with no ornamentation. It is an elegantly "+
    "functional place for someone to lie and rest or sit and appreciate "+
    "the flowers and their heady aromas.\n");

    set_seat_names("bench");

    set_seat_id("__zigg_garden_bench");

    set_max_seat(3);
    set_lay_num(3);

    set_shift_seat(1);
    set_allow_kinky(1);
}
