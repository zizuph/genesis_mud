// file name: hill12
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
hill_long("The hill drops down towards the swamp to the "
         +"east and south, and rises sharply to the west.");

ahup(HILL+"hill11","west");
ahdown(MARSH+"marsh70","east");
ahdown(MARSH+"marsh68","south");
AE(HILL+"hill10","north",0,1);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
