#include "defs.h";

inherit TELBERIN_ROYAL_MERC;

void
create_telberin_royal_merc()
{

    set_em_long("This is a small intersection on the Royal Circle in the "+
        "mercantile quarter. The street is very busy with many citizens "+
        "moving through the city. The aromas here caress your senses "+
        "lovingly with sweet roses and ripened fruit, which stem from "+
        "the gardens. The direction of the rose garden is to the northwest "+
        "and the fruit garden is southeast. To the southwest is a narrow "+
        "walkway as it stretches between two gardens leading to the Ri Circle.\n");


    add_item(({"rose garden","rose bud", "rose buds", "roses"}),
        "You spy a few rose buds peeping through the hedge of the rose "+
        "garden. The sweet scent of roses delightfully fills your senses. "+
        "You can reach the entrance by heading northwest.\n");

    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs. You can reach the entrance by heading southeast.\n");

    add_item(({"garden", "gardens"}),
        "The entrance to the rose garden is to the northwest and the fruit "+
        "garden is to the southeast.\n");



    add_exit("tel09_07", "southeast");
    add_exit("tel07_09", "northwest");
    add_exit("tel07_07", "southwest");
}