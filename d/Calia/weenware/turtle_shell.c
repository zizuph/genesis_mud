// OBJECT:  turtle shell

    /* Calia Domain

    HISTORY

    [2002-09-26] Created by Uhclem.

    PURPOSE

    This object was created to be an item on the annual Halloween scavenger
    hunt; it has no other purpose.  It is deployed by the spurious "sea
    turtles" which appear on the beaches of Calia around Halloween.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("shell");
    set_adj(({"tiny", "turtle"}));
    set_short("tiny turtle shell");

    set_long("Dark green on the top and light green on the bottom," +
        " this shell looks as if it belongs to a tiny sea" +
        " turtle, but there's no sign of its occupant.\n");

    add_item(({"top", "top of shell", "shell top"}),
        "The top of the shell is dark green and has the typical" +
        " appearance of a sea turtle shell, only in miniature.\n");

    add_item(({"bottom", "bottom of shell", "shell bottom"}),
        "You can just barely make out some words" +
        " inscribed on the bottom of the shell:" +
        " TURTLE COSTUME, SIZE XXXXXXS.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 75);
    add_prop(OBJ_I_VALUE, 0);

}
