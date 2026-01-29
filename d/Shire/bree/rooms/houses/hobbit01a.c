/*
 * Hobbit hole in Bree
 * By Finwe, June 2002
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "defs.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit;
 
void
create_room()
{
   
    areaname  = "Bree";  /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 2;             /*parlor*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "Large chairs are scattered around the room.";
    add_item(({"chairs", "large chairs"}),
        "They are over-stuffed chairs, and decorated with " +
        "bright colours and patterns. The chairs are scattered " +
        "about the room and look inviting.\n");
 
    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"painting", "paintings", "portrait", 
            "portraits"}),
        "The paintings are portaits of the hobbits who live " +
        "here. The hobbits in the paintings look well off and " +
        "very jolly.\n");
    add_item(({"round window", "circular window", "window"}),
        "The window is large and look out into Bree. They are " +
        "round with bright curtains on either side of it.\n");
 
    add_exit(HOUSES_DIR + "hobbit01b", "east");
    add_exit(HOUSES_DIR + "hobbit01", "southwest");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(MAIDEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
