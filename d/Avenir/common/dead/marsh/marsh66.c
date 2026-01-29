// file name: marsh66
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the "
   +"west a narrow cobbled path can be seen.");

am("68","north");
am("64","south");
am("67","east");
AE(PATH+"path8","west",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
