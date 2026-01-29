// file name: river1.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 242 */


create_room()
{
set_short("Near the river");
set_long("You find yourself standing on a narrow strip"
        +" of sandy shore on the east bank of a swiftly moving river. High"
        +" cliffs rise above you for many hundreds of feet, coming down to"
        +" meet the water on all sides. The calls of wildlife"
        +" fill your ears from some distance away, and the foam of the"
        +" river splashes up at you as it rushes past. You may"
        +" follow this piece of dry land southward for a bit, or enter"
        +" a passage leading back into the mountainside, to the northeast."
        +"\n");

add_prop(ROOM_I_LIGHT,1); IN

AE(PK+"fall2","northeast",0);
AE(PK+"river2","south",0);

add_item(({"passage","passageway","tunnel"}), "A fair-sized"
        +" passageway leads into darkness, going off to the northeast"
        +" from here.\n");

}
