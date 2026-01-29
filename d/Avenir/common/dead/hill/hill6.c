// file name: hill6
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
hill_long("You are near the top of the hill, and upwards "
         +"to the east you can make out some sort of "
         +"standing stones at the apex. The hill continues "
         +"along to the north and south, and drops steeply "
         +"to the west.");

AI(({"stone","stones","standing stones"}),"You really cannot "
         +"make out any details from this angle.\n");

ahup(HILL+"cairn","east");
AE(HILL+"hill8","north",0,1);
AE(HILL+"hill4","south",0,1);
ahdown(HILL+"hill5","west");

reset_room();
}

reset_room()
 {
    hill_reset();
 }
