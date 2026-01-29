#include "defs.h";

inherit TELBERIN_SAVENUE;

void
create_south_avenue()
{

    set_short("South Avenue and Ri Circle");
    set_em_long("You are standing at the wonderful South Avenue and Ri Circle. "+
        "The South Avenue leads north through two of Telberin’s famous gardens. "+
        "The long expanse of South Avenue draws your attention and you look down "+
        "its length to see the great buildings of the Royal Circle.\n");


    add_item(({"garden", "gardens"}),
        "If you travel north you will pass between two of Telberin’s "+
        "famous gardens.\n");


    add_exit("tel11_04", "east");
    add_exit("tel09_04", "west");
    add_exit("tel10_05", "north");
    add_exit("tel10_03", "south");
}