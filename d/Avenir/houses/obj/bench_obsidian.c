#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("bench");
    add_adj(({"black","stone","glassy", "glass-like","heavy","obsidian"}));
    set_short("black stone bench");
    set_long("A black stone bench carved from a block of glass-like obsidian. "+
    "Its edges are all thick and rounded. It is fairly deep, and wide enough "+
    "for two.\n");

    set_seat_names(({"bench", "black bench", "obsidian bench"}));

    set_seat_id("_obsidian_bench");

    set_max_seat(2);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
