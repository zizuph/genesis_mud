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
    roomtype  = 5;             /*master bedroom*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "This large room is comfortable looking. A large " +
        "bed sits under the large circular window against the west " +
        "wall. Some paintings are scattered across the walls.";

    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"painting", "paintings", "portrait", 
            "portraits"}),
        "The paintings are portaits of the hobbits who live " +
        "here and their family. The hobbits look jolly and happy.\n");
    add_item(({"round window", "circular window", "window"}),
        "The window is large and look out into Bree. They are " +
        "round with bright curtains on either side of it.\n");
 
    add_exit(HOUSES_DIR + "hobbit01", "northeast");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(CITIZEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
