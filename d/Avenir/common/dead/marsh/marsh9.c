// file name: marsh9
// creator(s): Ilyian (21 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
set_short("Grey Marsh");
marsh_long("The ground underfoot is wet and clings to your feet.");

am("10","east");
am("8","west");
am("14","north");
am("6","south");
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
