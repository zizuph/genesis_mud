// file name: marsh55
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" A cobbled "
   +"road can be seen to the west, and to the east, a path "
   +"runs along the shoreline.");

am("56","north");
am("54","south");
AE(PATH+"shore28","east",0,3);
AE(PATH+"path3","west",0,3);

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
