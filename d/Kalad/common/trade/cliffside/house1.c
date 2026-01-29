inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Abandoned House");
set_long("This house is abandoned and filthy dirty.\n");
add_exit(TRADE(cliffside/cliffside6),"north");
add_prop(ROOM_NO_TIME_DESC,1);
}
