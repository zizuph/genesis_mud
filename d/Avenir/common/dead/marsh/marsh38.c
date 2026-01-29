// file name: marsh38
// creator(s): Ilyian (24 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
marsh_long(randmarsh[random(sizeof(randmarsh))]);

am("41","north");
am("35","south");
am("37","west");
am("39","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
