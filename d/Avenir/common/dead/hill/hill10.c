// file name: hill10
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
hill_long("The hillside climbs steeply to the west, "
         +"where it reaches the highest point.");

ahup(PATH+"entry","west");
AE(HILL+"hill9","north",0,1);
AE(HILL+"hill12","south",0,1);
ahdown(HILL+"hill15","east");

reset_room();
}

reset_room()
 {
    hill_reset();
 }
