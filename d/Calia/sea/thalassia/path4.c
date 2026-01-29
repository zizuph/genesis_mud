
/* 	Path To Thalassia 

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Before the bridge");
    set_long("The road you have been following continues "+
        "to the north from here onto a towering bridge. "+
        "To the west and east of you lie tall towers. You "+
        "get the feeling that you are being watched from "+
        "high atop of these towers. To the south you see "+
        "a large object between two buildings.\n");

    add_item(({"road","path"}),"The road you have "+
        "been following continues to the north from "+
        "here and then onto a bridge, while south it "+
        "runs between two walls and appears to curve "+
        "to the southeast in the distance.\n");
    add_item(({"towering bridge","bridge"}),"A bridge "+
        "to the north of you seems to lead into a different "+
        "section of the city. Crowning the bridge is a large "+
        "lookout tower, presumably to keep an eye on "+
        "anyone attempting to cross it.\n");
    add_item(({"tower","tall tower","towers",
        "tall towers","lookout tower",}),"These towers "+
        "stretch up into the far reaches of the water above "+
        "you. You can't make it out from here but you swear that "+
        "someone is watching you from the top of the "+
        "towers.\n");
    add_item(({"object","large object"}),"It appears to be some "+
        "type of monument or statue from here but details are "+
        "hard to make out through the water. You will have to "+
        "swim south to survey it properly.\n");

    add_swim_exit(THALM+"brguard_s_1_1","north",0,1);
    add_swim_exit(THAL+"guard_nw_1_1","west",0,1);
    add_swim_exit(THAL+"guard_ne_1_2","east",0,1);
    add_swim_exit(THAL+"obelisk","south",0,1);
}
