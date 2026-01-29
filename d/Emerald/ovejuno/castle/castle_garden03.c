

/*The Manor's Garden III
 * Coded by Marisol (7/31/97)
 * The bee npc and the weak sting poison is Gondor code.
 * Coded by Gnadnar. The rest is mine.
 * Copyright (c) Marisol Ramos 1997 */
/* Modified by Marisol (07/23/98) to be used in the village of
 * Ovejuno in Emerald.*/

#pragma strict_types

#include "../defs.h"
inherit CASTLE_GARDEN;
 
void
create_emerald_garden()
{
    set_em_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. A great variety "+
        "of ornamental plants run wild in this forgotten place. "+
        "The only sounds that can be heard are from insects and "+
        "bird that seem to talk to each other in a secret "+
        "language. The breeze brings the sweet music of water "+
        "falling down a fountain. The smell of roses is strong here, "+
        "overwhelming your senses.\n");

    add_roses();

    add_exit("castle_garden05", "north");
    add_exit("castle_garden01", "west");

    reset_room();

}

void
reset_room()
{
/*
    if(!present("g_bee"));
    {
        setuid();
        seteuid(getuid());
        clone_object(GARDEN_NPC_DIR + "g_bee")->move(this_object());
    }
*/
}
