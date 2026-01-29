// file name: marsh10
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
marsh_long("Silence hangs over the area.");

am("11","east");
am("9","west");
am("15","north");
am("7","south");
reset_room();
}

reset_room()
{
    set_searched(0);   marsh_reset();
}
