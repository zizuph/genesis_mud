// file name: hill15
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
hill_long("The hillside ends abruptly to the east with a "
         +"sheer cliff that drops down into the black sea.");

AI(({"sea","ocean","water"}),"The great dark sea spreads out "
   +"to the east as far as you can see. Its gentle waves lap "
   +"softly against the side of the cliff.\n");

ahup(HILL+"hill10","west");
ahup(HILL+"hill14","north");
ahdown(MARSH+"marsh70","south");

reset_room();
}

reset_room()
 {
    hill_reset();
 }
