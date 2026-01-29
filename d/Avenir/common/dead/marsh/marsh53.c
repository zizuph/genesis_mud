// file name: marsh53
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the north and "
    +"east you can make out a narrow path running along the "
    +"shore of the island.");

AE(PATH+"shore23","north",0,3);
AE(PATH+"shore24","east",0,3);
am("49","south");
am("52","west");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
