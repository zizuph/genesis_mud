// file name: marsh5
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
marsh_long("You can hear the faint lapping of water against a shore.");

am("6","east");
AE(PATH+"shore6","west",0,3);
am("8","north");
AE(PATH+"shore5","south",0,3);
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
