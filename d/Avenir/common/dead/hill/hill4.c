// file name: hill4
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
hill_long("The hill climbs to its apex to the east, and "
         +"falls sharply to the west. South is a path that "
         +"runs along the hillside.");

ahup(PATH+"entry","east");
AE(HILL+"hill6","north",0,1);
ahdown(HILL+"hill3","west");
AE(PATH+"path10","south",0,3);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
