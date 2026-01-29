/*
 * Hobbit burrow in Frogmorton
 * By Finwe, September 1998
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
   
    areaname  = "Frogmorton";  /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 5;            /*Type of room in the smial*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "A large bed, at least by hobbit standards, " +
        "sits against a wall. A dresser sits in a corner with " +
        "a some cupboards on another wall.";
 
    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood and swept clean.\n");
 
    add_exit(FROG_DIR + "smial01b", "north");
   
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
