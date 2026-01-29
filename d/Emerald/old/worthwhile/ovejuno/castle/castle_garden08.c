/*The Manor's Garden VIII
*Coded by Marisol (9/4/97) 
 * Modified by Marisol (07/27/98) to be used in the village of Ovejuno
 * in Emerald
*Copyright (c) Marisol Ramos 1997
*/

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
    
    add_exit("castle_garden13", "east");
    add_exit("castle_garden11", "south");

    reset_room();
}
                                  
void
reset_room()
{
/*
    if(!present("g_insectoid"))
    {
        setuid();
        seteuid(getuid());
        clone_object(GARDEN_NPC_DIR + "g_insectoid")->move(this_object());
        clone_object(GARDEN_NPC_DIR + "g_insectoid")->move(this_object());
    }
*/
}
