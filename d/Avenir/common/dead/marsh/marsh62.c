// file name: marsh62
// creator(s): Ilyian (28 August, 1995)
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

am("64","north");
am("59","south");
am("61","west");
am("63","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
