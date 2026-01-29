/* Re Albi's pasture IV
 * Coded by Marisol (05/01/98)
 * Modified by Marisol (08/05/98) to be used in the village of 
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#pragma strict_types

#include "defs.h"

inherit OV_PASTURES;

#include <stdproperties.h>

void
create_emerald_pasture()
{
    set_em_long("@@special_long@@The pasture is small and rugged with "+
       	"some outcrops spread here and there.  Sheep and their lambs "+
       	"graze and jump happily in the green turf uncaring of any "+
       	"danger. A tall shepherd stand aloof near an outcrop, singing "+
       	"softly to himself. Sheep's bleats fill the air together with "+
       	"distance music of a shepherd's pipe. The air here is wholesome "+
       	"and with a very very slight tang of salty sea mingled with "+
       	"forest scents. In the distance, you can see the mountains "+
        "and valleys rolling down south to the sea.\n");

    add_item("outcrops",
       	"These rocks seem to have been pushed up from the center "+
       	"of the earth, breaking forth in the pasture. They look "+
       	"like nice places for the shepherd to rest and watch the "+
       	"flock.\n");

    /*
    add_item("shepherd",
        "A young shepherd stand still watching the sheep and lambs "+
        "grazing the pastures. Now and then he would sing for himself "+
        "a nice shepherd song.\n");
    */

    add_exit("pastures01", "east");
    add_exit("pastures03", "north");
    add_exit("pastures02", "northeast");
}                              

                                                    
string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you follow the hilly contour of the pasture, you can "+
            "see the dark bulk of the castle. ";
    }

    filename = file_name(last_room);

    if (filename == (OVEJUNO_DIR + "pastures01"))
    {
        return "As you follow the hilly contour of the pasture, you can "+
            "see the dark bulk of the castle. ";
    }

    if (filename == (OVEJUNO_DIR + "pastures03"))
    {
        return "As you climb down the hilly contour of the pasture, you "+
            "can see the dark bulk of the castle. ";
    }

    if (filename == (OVEJUNO_DIR + "pastures02"))
    {
        return "As you climb down the hilly contour of the pasture, you "+
            "can see the dark bulk of the castle. ";
    }

    return "As you climb down the hilly contour of the pasture, you "+
        "can see the dark bulk of the castle. ";
}


