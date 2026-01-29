#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    
    set_em_long("You are on the Ri Circle in the mercantile quarter. The "+
        "light gently cascades softly along the street. The most delicate "+
        "fragrances of ripened fruit that makes its way from the fruit garden "+
        "to here.\n");

    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_item(({"people"}),
        "There are a few people mingling here visiting with each other about "+
        "many different topics.\n");


    add_exit("tel08_04", "southeast");
    add_exit("tel06_06", "northwest");
    add_exit("mercantile/armoury/armoury", "southwest");
}
