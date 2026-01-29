// file name: marsh43
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" From the north "
     +"and the west you can hear the gentle lapping of water.");

AE(PATH+"shore16","west",0,3);
AE(PATH+"shore17","north",0,3);
am("41","south");
am("44","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
