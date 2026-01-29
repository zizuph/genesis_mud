// file name: marsh2
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
marsh_long("Ominous silence hangs over the area.");

am("1","east");
am("7","west");
am("11","north");
AE(PATH+"shore2","south",0,3);
reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
}
