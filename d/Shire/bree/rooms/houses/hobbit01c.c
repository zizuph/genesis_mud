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
    roomtype  = 4;             /*kitchen*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/

    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"pots", "pans", "pots and pans"}),
        "The pots and pans are battered looking from all their use. " +
        "Some have one or two handles and others have lids. Most of " +
        "them are all sizes but generally round or oval shaped.\n");
    add_item(({"lids"}),
        "The lids are batter like the pots and pans they fit. They " +
        "are metal and are slightly domed.\n");
    add_item(({"range", "cooking range"}),
        "This is a a larger stove with pots and pans simmering on " +
        "its surface.\n");
    add_item(({"soot"}),
        "This is black powder that is around the edges of the stove " +
        "and range.\n");

    add_exit(HOUSES_DIR + "hobbit01b", "north");
   
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
