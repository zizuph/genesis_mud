#include "defs.h";

inherit TELBERIN_STREET;

void
create_telberin_street()
{

    set_short("Narrow walkway in Telberin");
    set_em_long("You are standing on a narrow walkway in Telberin that "+
        "is situated between two of the famous gardens. The fragrances "+
        "from the gardens are sweet and linger in the air here. You can "+
        "continue northeast to the Royal Circle or continue southwest to "+
        "the Ri Circle.\n");

    add_item(({"ri circle"}),
        "The Ri Circle is the main road that runs through all four quarters of "+
        "Telberin. It is made from cobblestones and you can reach the many shops "+
        "that are open.\n");

    add_item(({"rose garden","rose bud", "rose buds", "roses"}),
        "You spy a few rose buds peeping through the hedge of the rose "+
        "garden. The sweet scent of roses delightfully fills your senses.\n");

    add_item(({"fruit", "fruits", "fruit garden"}),
        "You can see the tops of tall trees bursting above the tall hedges "+
        "that surround the lovely fruit garden. You can also see many "+
        "different size, shapes and colors of fruit hanging from their "+
        "limbs.\n");

    add_item(({"royal circle"}),
        "Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bares the same name.\n");

    add_item(({"circle"}),
        "Did you want to examine the Royal Circle or the Ri Circle?\n");

    add_item(({"garden", "gardens"}),
        "You are between two of Telberin’s famous gardens. The sweet fragrances "+
        "linger softly in the air filling you with anticipation.\n");

    add_item(({"fragrance", "fragrances"}),
        "The sweet fragrance of roses and fruit lingers around you here.\n");


    add_exit("tel08_08", "northeast");
    add_exit("tel06_06", "southwest");
}