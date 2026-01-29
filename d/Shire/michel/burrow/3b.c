/*
 * Hobbit burrow in Michel Delving
 * Updated by Finwe, September 1997
 * Updates include adding the hobbitmaker
 */
 
#pragma strict_types
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "local.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit1, hobbit2;
 
void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 2;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
   
    extraline = "This parlor has small wooden chairs around all " +
        "the walls and a fireplace in the center, which lets the " +
        "heat distribute evenly and provides more light than a " +
        "fireplace in the wall.";
 
    add_item(({"chairs","chair","small wooden chairs"}),
        "The small wooden chairs are not in good condition, " +
        "but they look comfortable all the same.\n");
 
    add_item(({"fireplace","center","fire place","chimney"}),
        "The central position of the fireplace in this room allows " +
        "all an equal chance at being warmed and the light is " +
        "much brighter than if the fireplace were in a corner. " +
        "The chimney leading up through the roof is somewhat " +
        "distracting to conversations, however.\n");
   
    add_exit(MICH_DIR + "burrow/3","south",0,1);
    add_exit(MICH_DIR + "burrow/3a","west",0,1);
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit1)
    {
        hobbit1 = clone_object(HOBBITMAKER);
        hobbit1->set_type(ELDER);
        hobbit1->set_power(100);
        hobbit1->move(TO);
    }
    if (!hobbit2)
    {
        hobbit2 = clone_object(HOBBITMAKER);
        hobbit2->set_type(CITIZEN);
        hobbit2->set_power(100);
        hobbit2->move(TO);
    }
}        
