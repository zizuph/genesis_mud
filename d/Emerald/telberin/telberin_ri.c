#include "defs.h"

inherit TELBERIN_STREET;

public void
create_telberin_ri()
{
}

nomask void
create_telberin_street()
{
    
    config_street_room("mercantile", "the Ri Circle");
    set_em_long("Ri Circle is the main road that runs through all four quarters "+
        "of Telberin.\n");

    add_item(({"ri circle", "circle"}),
        "The Ri Circle is the main road that runs through all four quarters of "+
        "Telberin. It is made from cobblestones and you can reach the many shops "+
        "that are open.\n");

    add_item(({"garden", "gardens"}),
        "The entrances for the famous gardens of Telberin are located on the Royal "+
        "Circle.\n");
    
create_telberin_ri();
}
