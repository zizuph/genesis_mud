// file name: marsh15
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
set_short("Grey Marsh");
marsh_long(randmarsh[random(sizeof(randmarsh))]);

am("20","north");
am("10","south");
am("14","west");
am("16","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
