/* Re Albi's pasture I
 * Coded by Marisol (04/22/98)
 * Copyright (c) Marisol Ramos 1998 */
/* Modified by Marisol (07/21/98) to be used in the village of
 * Ovejuno in Emerald. */

#pragma strict_types
#include "defs.h"
#include "/d/Emerald/sys/macros.h"
#define EWE OV_VILLAGE_NPC + "female_sheep"
#define LAMB OV_VILLAGE_NPC + "lamb"
inherit OV_PASTURES;
#include <stdproperties.h>

object ewe;
object lamb;

void
reset_room()
{
 if(!objectp(ewe))
 {
  ewe=clone_object(EWE);
  ewe->move(TO);
 }

 if(!objectp(LAMB))
 {
  lamb=clone_object(LAMB);
  lamb->move(TO);
 }

}


void
create_emerald_pasture()

{

    set_em_long("@@special_long@@The pasture here is small and rugged. "+
       "Sheep and their lambs graze and jump happily in the green "+
       "turf uncaring of any danger. Their bleats fill the air together "+
       "with the sweet music of a shepherd pipe. The view here is "+
        "breathtaking.");

   
    reset_room();
    
    add_exit("village_OV/village_ov15", "southeast");
    add_exit("pastures02.c", "north");
    add_exit("pastures03.c", "northwest");
    add_exit("pastures04.c", "west");

}
                                                       
string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you climb the ascending hills of the Cayeyi "+
        "mountains, you enter the communal pasture. ";
    }

    filename = file_name(last_room);

    if (filename == (OV_DIR_VIL + "village_ov15"))
    {
    return "As you climb the ascending hills of the Cayeyi "+
    "mountains, you enter the communal pasture. ";
    }

    if (filename == ("pasture/pastures02"))
    {
    return "As you climb down the hilly contour of the pasture, you "+
    "can see the outskirts of the village. ";
    }

    return "As you climb down the hilly contour of the pasture, you "+
    "can see the outskirts of the village. ";

    if (filename == ("pasture/pastures03"))
    {
    return "As you climb down the hilly contour of the pasture, you "+
    "can see the outskirts of the village. ";

    }

    return "As you climb down the hilly contour of the pasture, you "+
    "can see the outskirts of the village. ";

    if (filename == (OV_PATH + "pasture/pastures04"))
    {
    return "As you follow the hilly contour of the pasture, you can "+
    "see the outskirts of the village. ";
    }

    return "As you follow the hilly contour of the pasture, you can "+
    "see the outskirts of the village. ";

}

