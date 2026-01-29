// file name: hill7
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
hill_long("The hillside drops down into the marsh to the "
         +"north and west, and rises upwards to the "
         +"east.");

ahup(HILL+"hill8","east");
AE(HILL+"hill5","south",0,1);
ahdown(MARSH+"marsh45","west");
ahdown(MARSH+"marsh46","north");

reset_room();
}

reset_room()
 {
    hill_reset();
 }
