// file name: shore2
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
set_long("The cobbled path turns from east to southwest here, "
        +"following along the contours of the island. A silence "
        +"hangs in the air, and your footfalls seem to be "
        +"muffled by the fog that lies over the marsh to "
        +"the north.\n");

add_prop(ROOM_I_LIGHT,1);

add_sea();
add_ground();
add_cobble();

AE(DEAD+"shore1","east",0,1);
AE(DEAD+"shore3","southwest",0,1);
AE(DEAD+"marsh2","north",0,2);

}
