// file name: hill9
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
hill_long("the hill reaches its apex to the west, where you "
         +"can just make out some sort of standing stones. Passage "
         +"north is blocked by a sheer cliff face that drops "
         +"straight down to the swamp below.");

AI(({"cliff","dropoff"}),"The hill ends abruptly to the "
         +"north, droping straight down to the swampy "
         +"ground below.\n");

ahup(HILL+"cairn","west");
AE(HILL+"hill10","south",0,1);
ahdown(HILL+"hill14","east");

reset_room();
}

reset_room()
 {
    hill_reset();
 }
