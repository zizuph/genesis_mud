// file name: marsh25
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" You hear the "
         +"faint sounds of water in the vicinity.");

am("30","north");
am("22","south");
AE(PATH+"shore11","west",0,3);
am("26","east");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
