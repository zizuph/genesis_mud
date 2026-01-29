// file name: shore1
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
set_long("You are walking along a narrow cobbled path in very "
        +"bad repair. To the south is the rocky shoreline of the "
        +"island, against which dark waves are lapping. The path "
        +"follows along thw shore to the west, and to the "
        +"east is a crossroads. North lies a mist-covered "
        +"marsh.\n");

add_prop(ROOM_I_LIGHT,1);

add_sea();
add_ground();
add_cobble();

AE(DEAD+"cross","east",0,1);
AE(DEAD+"shore2","west",0,1);
AE(DEAD+"marsh1","north",0,2);

}
