#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    
    set_em_long("You are on the Ri Circle in the mercantile quarter. The "+
        "light caresses the street beautifully and the soft sound of people "+
        "walking along this street is warm and inviting. The sweet fragrances "+
        "from the rose garden linger here and you can just make out a rose "+
        "bud or two as you look at the tall hedge that surrounds it.\n");

    add_item(({"rose garden","rose bud", "rose buds", "roses"}),
        "You spy a few rose buds peeping through the hedge of the rose "+
        "garden. The sweet scent of roses delightfully fills your senses.\n");

    add_item(({"people"}),
        "You see a few elven people walking along the street quietly.\n");

    add_exit("tel06_06", "southeast");
    add_exit("tel04_08", "northwest");
}