// file name: marsh31
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

am("36","north");
am("26","south");
am("30","west");
am("32","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
