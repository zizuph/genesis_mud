// file name: hill11
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
hill_long("The hill rises sharply to the north to its apex, "
         +"and to the west is a path leading up the hillside.");

ahup(PATH+"entry","north");
AE(HILL+"hill13","south",0,1);
ahdown(HILL+"hill12","east");
AE(PATH+"path10","west",0,3);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
