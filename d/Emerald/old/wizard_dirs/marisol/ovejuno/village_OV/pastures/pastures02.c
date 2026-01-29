/* Re Albi's pasture II
 * Coded by Marisol (04/22/98)
 * Modified by Marisol (08/05/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

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
if(!objectp(lamb))
 {
   lamb=clone_object(LAMB);
   lamb->move(TO);
 }
}

void
create_emerald_pasture()
{

    set_em_long("@@special_long@@The pasture is lush and green and "+
        "scattered in the grass, there are wildflowers. Sheep and "+
        "lambs graze and frolic in the green turf uncaring of any "+
        "danger. Their bleats fill the air together with the "+
        "sweet music of a shepherd's pipe. In the distance, you can "+
        "enjoy a great view of the mountains and valleys rolling "+
        "down south to the sea. A small trail wound down to the "+
        "southeast to a stone fountain.");

    add_item("outcrops",
       "These rocks seem to have been pushed up from the center "+
       "of the earth, breaking forth in the pasture. They look "+
       "like nice places for the shepherd to rest and watch the "+
       "flock.\n");

    add_item("shepherd",
       "A young boy is seated in the distance playing a pipe. He "+
       "seems to be one of the village shepherd.\n");

    reset_room();

    add_exit("pastures01.c", "south");
    add_exit("pastures03.c", "west");
    add_exit("pastures04.c", "southwest");
    add_exit("../ov_fountain.c", "southeast");

}
                                                     
string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "The pasture rises steeply over the hills and some "+
       "rocky outcrops spread here and there. ";
    }

    filename = file_name(last_room);

    if (filename == ("pasture/pastures01"))
    {

    return "The pasture rises steeply over the hills and some "+
    "rocky outcrops spread here and there. ";
    }

    if (filename == ("pasture/pastures03"))
    {
    return "As you follow the hilly contour of the pasture, you can "+
    "see the outskirts of the village. ";
    }

    return "As you follow the hilly contour of the pasture, you can "+
    "see the outskirts of the village. ";

    if (filename == ("pasture/pastures04"))
    {
    return "The pasture rises steeply over the hills and some "+
    "rocky outcrops spread here and there. ";
    }

    return "The pasture rises steeply over the hills and some "+
    "rocky outcrops spread here and there. ";

    if (filename == (OV_DIR_VIL + "ov_fountain"))
    {
    return "As you climb the ascending hills of the Cayeyi "+
    "mountains, you enter the communal pasture. ";
    }

    return "As you climb the ascending hills of the Cayeyi "+
    "mountains, you enter the communal pasture. ";

}


