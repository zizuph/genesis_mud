// file name: hill3
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
hill_long("The hillside continues to the north and "
         +"south, and rises sharply to the east. The "
         +"marsh lies to the west.");

ahup(HILL+"hill4","east");
AE(HILL+"hill5","north",0,1);
AE(HILL+"hill2","south",0,1);
ahdown(MARSH+"marsh42","west");

reset_room();
}

reset_room()
 {
    hill_reset();
 }
