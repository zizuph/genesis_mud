// file name: marsh40
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
     +"north and the west, a path runs along the "
     +"edge of the island.");

AE(PATH+"shore15","west",0,3);
AE(PATH+"shore16","north",0,3);
am("37","south");
am("41","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
