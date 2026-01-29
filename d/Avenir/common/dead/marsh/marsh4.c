// file name: marsh4
// creator(s): Ilyian (21 August, 1995)
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
marsh_long("To the south and west you think you can hear the "
          +"sound of water.");

am("3","east");
AE(PATH+"shore5","west",0,3);
am("6","north");
AE(PATH+"shore4","south",0,3);
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
