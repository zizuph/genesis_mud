// file name: marsh27
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

am("32","north");
am("24","south");
am("26","west");
am("28","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
