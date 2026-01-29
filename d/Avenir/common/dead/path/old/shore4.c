// file name: shore4
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
set_long("The stone path turns from the east to the "
        +"northwest here. To the west and south, the "
        +"great Sunless Sea spreads out, its dark waves "
        +"languidly rolling into the shorline. A grey "
        +"and dismal marsh lies to the north.\n");

add_prop(ROOM_I_LIGHT,1);

add_sea();
add_ground();
add_cobble();

AE(DEAD+"shore3","east",0,1);
AE(DEAD+"shore5","northwest",0,1);
AE(DEAD+"marsh4","north",0,2);

}
