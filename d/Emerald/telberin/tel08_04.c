#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    
    set_em_long("You are on the Ri Circle in the mercantile quarter. It "+
        "is quite a lovely area with the aromas from the fruit garden "+
        "lingering here and the beautiful hedges from thus garden glistening "+
        "with dew in the soft light.\n");

    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_item(({"hedge", "hedges"}),
        "The tall hedge surrounds the fruit garden. It is bursting with many "+
        "different colors of green. It produces a wonderful sight to behold "+
        "with the dew glistening in the light on its leaves.\n");

    add_item(({"dew"}),
        "The gentle dew glistens on the leaves with such beauty and tranquility "+
        "that it adds to the peaceful surroundings.\n");


    add_exit("tel09_04", "east");
    add_exit("tel07_05", "northwest");
}