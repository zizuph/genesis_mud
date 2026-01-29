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
    roomtype  = 10;             /*Pantry*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "Wonderful smells drift about the room.";

    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
 
    add_exit(HOUSES_DIR + "hobbit02c", "north");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
/*
    object duster;

        if (!present("_shire_duster_",TO))
    {
        duster = clone_object("/d/Shire/scav_hunt/duster");
        duster->add_prop(OBJ_I_HIDE, 10 + random(10));
        duster->move(TO);
    }
*/
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(MAIDEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}
