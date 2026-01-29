// file name: shore6
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
set_long("The cobbled path turns from the southeast "
        +"to the north here, running along the "
        +"shoreline to the east against which dark "
        +"waves slowly break. A dank marsh lies to the "
        +"east, nearly obscured by thick shrouds of "
        +"mist and fog.\n");

add_prop(ROOM_I_LIGHT,1);

add_sea();
add_ground();
add_cobble();

AE(DEAD+"shore7","north",0,1);
AE(DEAD+"shore5","southeast",0,1);
AE(DEAD+"marsh","east",0,2);

}
