#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    
    set_em_long("You find this section of Ri Circle in the mercantile "+
        "quarter to be quiet although there are many people hurrying "+
        "about here. The scent of the fruit garden infiltrates the air "+
        "in a most alluring way leaving you with the desire to taste the "+
        "ripened fruit.\n");


    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_item(({"people"}),
        "It is surprisingly quiet here despite the flow of traffic of "+
        "people that move through here.\n");


    add_exit("tel10_04", "east");
    add_exit("tel08_04", "west");
}