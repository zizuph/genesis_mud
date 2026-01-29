// file name: marsh51
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the north "
    +"you can make out the shoreline of the island.");

AE(PATH+"shore21","north",0,3);
am("47","south");
am("50","west");
am("52","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
