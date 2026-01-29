/*The Manor's Garden XII
*Coded by Marisol (9/8/97) 
*Modified by Marisol (07/27/98) to be used in the village of Ovejuno
*in Emerald.
*The midge npc is Gondor code. The rest is mine.
*Copyright (c) Marisol Ramos 1997
*/

#include "../defs.h"
inherit CASTLE_GARDEN;

void
create_emerald_garden()
{
    set_em_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. This section is "+
        "different from the rest of the garden. Here, citrus trees "+
        "are full of orange and yellow fruits. Some of the fruits "+
        "are overripe and have fallen to the ground. Little midges "+
        "flies over the fruits and the air reeks with the "+ 
        "acidic smell of rotten fruits.\n");

    add_item("plants",
        "Here there are two different trees, one with orange  "+
        "fruits and another with yellow ones. The ground is "+
        "covered with rotten fruits, so the air has an "+
        "unsavory smell. It seems that noone has been here "+
        "in ages to collect the fruits of the trees.\n");

    add_item(({"orange fruit", "yellow fruit", "trees"}),
        "There are Orange and Lemon trees. They are common in the warm "+
        "coast of Emerald. The fruits are over-riped and some "+
        "of them are in the ground. The oranges are broken in pieces and "+
        "the lemons are grey-yellow and covered with a sticky juice. "+
        "Midges are flying over the rotten fruits.\n");

    add_exit("castle_garden09", "north");
    add_exit("castle_garden07", "south");

    reset_room();

}                                                                    
void
reset_room()
{
/*
    if (!present("midge"));
    {
        setuid();
        seteuid(getuid());
        clone_object("/d/Gondor/common/npc/midge")->move(this_object());
    }
*/
}
