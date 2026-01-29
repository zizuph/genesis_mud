// file name: marsh7
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
marsh_long("A faint moaning can be heard in the distance.");

am("2","east");
am("6","west");
am("10","north");
am("3","south");
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
