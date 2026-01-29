// file name: hill1
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
hill_long("To the east you can see a path running up the "
         +"hill. The slope drops down into the marsh to the "
         +"south and west, and rises steeply to the north.");

ahup(HILL+"hill2","north");
ahdown(MARSH+"marsh36","west");
ahdown(MARSH+"marsh32","south");
AE(PATH+"path9","east",0,3);

reset_room();
}

reset_room()
 {
    hill_reset();
 }
