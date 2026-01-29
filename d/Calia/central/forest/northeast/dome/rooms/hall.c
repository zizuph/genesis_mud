// ROOM:  Dome - entry hall
//        DOME_ROOMS + hall
    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        This is the showpiece of the pleasure dome, and as 
        such the greatest masterpieces of art are displayed
        here.

        AREA HISTORY
        Starting as something of a trophy room, this hall
        has expanded into a near art museum. Everyone has
        the best of their artistic work displayed here,
        even the cooks!

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome entry hall");

    set_long("This great hall runs along the center of the " +
        "dome and is lined with numerous side passages. " +
        "Paintings and ornate tapestries line its walls. " +
        "Colorful carpets and rugs cover the floor. Trophies " +
        "are arrange artistically as well as proudly.\n");

    /* ITEMS */

    add_item(({"paintings", "tapestries", "ornate tapestries"}),
        "There are twelve paintings and six tapestries on the " +
        "walls here, depicting great feats of heroism. All " +
        "of them are very finely done and rather valuable " +
        "looking.\n");

    /* EXITS */

    add_exit("bath", "north", 0, 05);
    add_exit("entrance", "west", 0, 05);
    add_exit("kitchen", "south", 0, 05);
    add_exit("common", "east", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
