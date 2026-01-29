// file name: shore3
// creator(s): Ilyian (12 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "dead.h"

create_room()
{
set_short("Shore Path");
set_long("The cobbles path continues along the shore "
        +"of the lake here to the west and northeast. "
        +"To the north the edge of the walkway drops off "
        +"into a dark and murky swamp, over which lies a "
        +"shroud of fog.\n");

add_prop(ROOM_I_LIGHT,1);

add_sea();
add_ground();
add_cobble();

AE(DEAD+"shore2","northeast",0,1);
AE(DEAD+"shore4","west",0,1);
AE(DEAD+"marsh3","north",0,2);

}
