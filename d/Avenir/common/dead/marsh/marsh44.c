// file name: marsh44
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the "
     +"east, a large hill rises out of the swamp.");

add_hill();

AE(HILL+"hill5","east",0,5);
am("45","north");
am("42","south");
am("43","west");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
