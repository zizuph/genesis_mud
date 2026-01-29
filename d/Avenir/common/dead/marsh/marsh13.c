// file name: marsh13
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
set_short("Grey Marsh");
marsh_long(randmarsh[random(sizeof(randmarsh))]+" From the west "
          +"you can hear water laping against a shore.");

am("18","north");
am("8","south");
AE(PATH+"shore8","west",0,3);
am("14","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
    set_searched(0);
 }
