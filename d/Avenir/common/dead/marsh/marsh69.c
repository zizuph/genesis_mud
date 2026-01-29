// file name: marsh69
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
marsh_long(randmarsh[random(sizeof(randmarsh))]+" The marsh "
   +"ends abruptly to the east, where a steep dropoff "
   +"ends in the sea below.");

AI(({"dropoff","cliff"}),"It falls quite steeply down into "
   +"the murky sea below. Fog from the marsh slowly rolls "
   +"over the edge.\n");
AI(({"sea","ocean","water"}),"The great dark sea spreads out "
   +"to the east as far as you can see. Its gentle waves lap "
   +"softly against the side of the cliff.\n");


am("70","north");
am("67","south");
am("68","west");

reset_room();
}

reset_room()
 {
    set_searched(0);   marsh_reset();
 }
