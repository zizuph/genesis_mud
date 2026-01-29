#include "defs.h";

inherit TELBERIN_RI;

void
create_telberin_ri()
{

    
    set_em_long("This is a small intersection on the Ri Circle in mercantile "+
        "quarter. The street is filled with many pedestrians as they travel "+
        "to and from a few shops. The aromas here are of lovely sweet roses "+
        "and ripened fruit, which stem from the gardens. To the northeast and "+
        "is a narrow walkway it stretches between two gardens leading to the "+
        "Royal Circle.\n");

    add_item(({"garden", "gardens"}),
        "If you travel northeast you will pass between two of Telberin’s "+
        "famous gardens.\n");

    add_item(({"royal circle"}),
        "You can reach the Royal Circle by traveling northeast.\n");

    add_item(({"rose garden","rose bud", "rose buds", "roses"}),
        "You spy a few rose buds peeping through the hedge of the rose "+
        "garden. The sweet scent of roses delightfully fills your senses.\n");

    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_item(({"intersection", "small intersection"}),
        "This is a small but very busy intersection on the Ri Circle. Many "+
        "travel here heading to the many shops and to the northeast along a "+
        "narrow walkway to the Royal Circle.\n");

    add_item(({"pedestrians", "pedestrian", "people"}),
        "There are many pedestrians traveling here of many different races.\n");


    add_exit("tel07_05", "southeast");
    add_exit("tel05_07", "northwest");
    add_exit("tel07_07", "northeast");
    add_exit("shop", "southwest");
}
