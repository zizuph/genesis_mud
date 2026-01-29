/* Castle_room2_01-Stairs.
 * Coded by Marisol (09/22/98)
 * Copyright (c) Marisol Ramos 1998
 */


#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV;


void
create_castle_room()
{
    set_short("A staircase to the first floor");
    set_em_long("A staircase goes down to the first floor. This "+
        "room is as tasteful as the rest of the residence. "+
        "Paintings and tapestries hang on the walls and the "+
        "light of torches illuminate this place.\n");

    add_item("staircase",
        "The staircase is made with a dark wooden handrail that rise "+
        "to the second floor. An ornate newel pole end with a "+
        "big wooden pineapple. Slender balusters connect to the long "+
        "banister, making it easy to climb the stairs without losing "+
        "your balance. The riser of the steps are not too high and "+
        "the tread where your footsteps fall are of a nice soft felt.\n");

    add_item("handrail",
        "A dark polished wooden handrail goes down to the first floor. "+
        "The handrail is wide enough to fit easily in your hand and "+
        "the surface of the wood looks nice and smooth.\n");

    add_item("newel pole",
        "This is just a wooden pole made from the same wood than the "+
        "rest of the staircase. The wood is smooth and it shines with "+
        "the reflecting light of the torches.\n");

    add_item("wooden pinapple",
        "This is a piece of wood carved like a big pineapple but "+
        "without the top leaves. Lines crisscross all over the "+
        "wooden surface, creating little diamonds like the ones "+
        "seen in the real fruit.\n");

    add_item(({"balusters", "banister"}),
        "The slender poles, also known as balusters, look delicate "+
        "but sturdy. They can easily carry the weight of the "+
        "handrail. The whole structure of balusters and handrail is "+
        "known as the banister. This banister is not only pretty "+
        "but functional, it will carry easily the weight of any "+
        "individual using the handrail to climb the steps.\n");

    add_item(({"riser", "tread"}),
        "The riser of the wooden steps are the right height, not too "+
        "high but not to low, they are just perfect for your feet. "+
        "A felt tread covers the surface of the steps making easy to "+
        "climb the steps without fear of sliping from its surface.\n");

    add_exit("castle2_02", "west");
    add_exit("castle1_10", "down");
}                        
