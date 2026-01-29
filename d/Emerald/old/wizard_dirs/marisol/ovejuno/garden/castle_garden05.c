/*The Manor's Garden V
 * Coded by Marisol (8/13/97)
 * Copyright (c) Marisol Ramos 1997*/
/* Modified by Marisol (07/24/98) to be used in the village of
 * Ovejuno in Emerald.*/

#pragma strict_types

#include "defs.h"
inherit CASTLE_GARDEN;

void
create_emerald_garden()
{

    set_long("An old and ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendron surrounds the garden, making it "+
        "impossible to see outside the enclosure. Exotic flowers from "+
        "all over Emerald are represented in this garden. White and "+
        "porcelain pink sparkle over the green grass. The flowers are "+
        "located on both sides of the overgrown path that winds inside "+
        "the garden. There are sounds of something walking in between "+
        "the plants.\n");


    add_item("plants",
        "Two different exotic plants from the wilderness of Emerald "+
        "cover the ground. Bright white flower shine like moonlight "+
        "and look like goose down, contrasting with brilliant pink "+
        "ones that look like porcelain roses.\n");

    add_item(({"white plants", "white flowers"}),
        "This is the rare orchid, Lady of the Night! This plant is "+
        "usually found near a humid area like rivers or ponds. "+
        "Right now its perfume is really faint but during the night "+              
        "its sweet scent permeate the air to attract moths to pollinate "+
        "it. Its petals are narrow, and its lip are heart-shaped.\n");

    add_item(({"pink plants", "pink flowers"}),
        "This is a Torch Ginger or better known Porcelain Rose! "+
        "This tropical plant is widely cultivated for its roots "+
        "or like in this case for its flowers. This particular  "+
        "sample is appreciated for its beatiful coloration, "+
        "soft and bright pink petals, that look like real "+
        "porcelain.\n");


    add_exit("castle_garden07", "north");
    add_exit("castle_garden03", "south");

    reset_room();

}

void
reset_room()
{
    if(!present("g_sparkfly"))
    {
     setuid();
     seteuid(getuid());
     clone_object(CASTLE_GARDEN_NPC + "g_sparkfly")->move(this_object());
     clone_object(CASTLE_GARDEN_NPC + "g_sparkfly")->move(this_object());
    }
}

