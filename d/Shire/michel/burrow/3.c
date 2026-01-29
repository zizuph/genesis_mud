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
 
object hobbit;
 
void
create_room()
{
   
    areaname  = "Michel Delving"; /*Name of village*/
    land      = "the Shire";      /*Name of land   */
    roomtype  = 1;                /*Type of room in the smial*/
    areatype  = "town";           /*Type of village*/
    smialsize = "large";          /*Size of the house*/
 
   
    extraline = "This entryhall seems to be the center of " +
        "activity in this smial.  The kitchen is southeast, a " +
        "pantry south, a bedroom southwest, and north seems to " +
        "be a dining room.";
   
    add_exit(MICH_DIR + "gamroad3","out",0,1);
    add_exit(MICH_DIR + "burrow/3d","south",0,1);
    add_exit(MICH_DIR + "burrow/3b","north",0,1);
    add_exit(MICH_DIR + "burrow/3f","southwest",0,1);
    add_exit(MICH_DIR + "burrow/3c","southeast",0,1);
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(TWEENS);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
