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
    land      = "Eriador";   /*Name of land   */
    roomtype  = 3;             /*dining room*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "Judging by the size of the room, quite a few " +
        "gatherings are held here. Wonderful smells drift from " +
        "the kitchen nearby.";

    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
 
    add_exit(HOUSES_DIR + "hobbit02d", "south");
    add_exit(HOUSES_DIR + "hobbit02b", "west");
   
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
