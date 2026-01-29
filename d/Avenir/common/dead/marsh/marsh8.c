// file name: marsh8
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
marsh_long("The mist parts to the west, revealing a rough stone "
          +"path along the shore.");

am("9","east");
AE(PATH+"shore7","west",0,3);
am("13","north");
am("5","south");
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
