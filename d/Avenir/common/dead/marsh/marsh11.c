// file name: marsh11
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

am("16","north");
am("2","south");
am("10","west");
am("12","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
    set_searched(0);
 }
