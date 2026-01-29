// file name: marsh37
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
      +"west you can make out a path running along the "
      +"shoreline.");

AE(PATH+"shore14","west",0,3);
am("40","north");
am("34","south");
am("38","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
