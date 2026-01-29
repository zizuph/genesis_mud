// file name: bldg.c
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

create_room()
{
set_short("Grey stone building");
set_long("You have entered a small hut built"
        +" entirely of dull grey stone. Because of where it rests,"
        +" in the shade of the high stone walls encircling the"
        +" courtyard outside and facing away from the dim light"
        +" source of the cavern, no light enters this room."
        +" It is entirely empty, and featureless, being "
        +" perfectly square in shape, yet you feel that somehow"
        +" it might someday hold more, at the proper time.  For now,"
        +" however, it is of no consequence.\n");

AE(PK+"court_s","north",0);

        add_prop(ROOM_I_LIGHT,0);
        IN_IN

add_item(({"walls","wall","stone","stones","grey","grey stone",
        "grey stones","room","hut","building"}), "This"
        +" small, square hut consists of only one room, and"
        +" is built entirely of squared-off blocks of dark, dull"
        +" grey stone. It has only one apparent exit.\n");
add_item(("floor"),"The floor is smooth and dusty, made from slowly "
        +"decaying stone.\n");
add_item(("ceiling"),"The ceiling is of dark wood, extending above "
        +"you into shadowy gloom.\n");


}
