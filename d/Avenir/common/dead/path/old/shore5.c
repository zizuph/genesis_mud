// file name: shore5
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
set_long("The path is straight here, running from the "
        +"northwest to the southeast. Rough cobblestone "
        +"underfoot threaten to trip you up, and the "
        +"foul stench of the marsh that lies north and "
        +"east is nearly overwhelming. Black water extends "
        +"as far as you can see to the west and south.\n");

add_prop(ROOM_I_LIGHT,1);

add_sea();
add_ground();
add_cobble();

AE(DEAD+"shore6","northwest",0,1);
AE(DEAD+"shore4","southeast",0,1);
AE(DEAD+"marsh4","east",0,2);
AE(DEAD+"marsh5","north",0,2);

}
