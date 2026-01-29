// file name: hill13
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
hill_long("To the west and north, a stone path leads up the "
         +"hillside. The hills drops sharply to the east down "
         +"to the marsh below.");

ahup(HILL+"hill11","north");
ahdown(MARSH+"marsh68","east");
AE(PATH+"path9","west",0,3);
AE(PATH+"path8","south",0,3);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
