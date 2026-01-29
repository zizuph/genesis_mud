// file name: marsh39
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" A steep hill "
     +"ascends to the east.");

add_hill();

AE(HILL+"hill2","east",0,5);
am("42","north");
am("36","south");
am("38","west");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
