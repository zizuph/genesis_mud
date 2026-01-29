

/*The Manor's Garden II
 * Coded by Marisol (7/31/97)
 * The bee file is from Gondor domain 
 * the same as the weak_sting poison, 
 * Coded by Gnadnar. The rest is coded by me.
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
        "birds that seem to talk to each other in a secret "+
        "language. The breeze brings the sweet music of water "+
        "falling down a fountain. The smell of roses is strong here, "+
        "overwhelming your senses.\n");


    add_roses();

    add_exit("castle_garden04", "north");
    add_exit("castle_garden01", "east");

    reset_room();
}

void
reset_room()
{
/*
    if (!present("g_bee"))
    {
    	setuid();
    	seteuid(getuid());
    	clone_object(GARDEN_NPC_DIR + "g_bee")->move(this_object());
    	clone_object(GARDEN_NPC_DIR + "g_bee")->move(this_object());
    }
*/
}
