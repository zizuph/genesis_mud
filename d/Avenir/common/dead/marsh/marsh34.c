// file name: marsh34
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The sound "
          +"of water is near.");

AE(PATH+"shore13","west",0,3);
am("37","north");
am("29","south");
am("35","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
