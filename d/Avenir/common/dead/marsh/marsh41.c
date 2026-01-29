// file name: marsh41
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

am("43","north");
am("38","south");
am("40","west");
am("42","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
