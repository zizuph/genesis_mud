// file name: hill8
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
hill_long("The slope falls very steeply down into the "
         +"marsh to the north, and more gently to the "
         +"west. The hillside continues south, but east "
         +"is a steep cliff that drops straight down to "
         +"the swamp.");

AI(({"cliff","dropoff"}),"The hill ends abruptly to the "
         +"east, droping straight down to the swampy "
         +"ground below.\n");

ahdown(MARSH+"marsh47","north");
ahdown(HILL+"hill7","west");
AE(HILL+"hill6","south",0,1);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
