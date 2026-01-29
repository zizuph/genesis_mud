// file name: marsh56
// creator(s): Ilyian (28 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

create_room()
{
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the west "
   +"you can barely make out a narrow road.");

am("59","north");
am("55","south");
am("57","east");
AE(PATH+"path4","west",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
