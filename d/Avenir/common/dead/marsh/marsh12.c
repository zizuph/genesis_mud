// file name: marsh12
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" To the east "
          +"can be seen a narrow cobbled path.");

am("17","north");
am("1","south");
am("11","west");
AE(PATH+"path3","east",0,3);
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
    set_searched(0);
 }
