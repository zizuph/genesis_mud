// file name: hill5
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
hill_long("The hillside falls sharply to the west, "
         +"descending down into the mire. The ground "
         +"remains level to the north and south, and rises "
         +"again to the east towards the top.");

ahup(HILL+"hill6","east");
ahdown(MARSH+"marsh44","west");
AE(HILL+"hill7","north",0,1);
AE(HILL+"hill3","south",0,1);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
