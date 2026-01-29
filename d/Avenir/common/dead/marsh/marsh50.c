// file name: marsh50
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The mist thins "
   +"out a bit to the north and west.");

AE(PATH+"shore20","north",0,3);
AE(PATH+"shore19","west",0,3);
am("46","south");
am("51","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
