// Ledge path 1 (/d/Avenir/common/ledge/ledge1.c)
// creator(s): Ilyian
// last update:  
// purpose:
//
// note: this is where the ledge area meets the port cavern area
// bug(s):
// to-do:

inherit "/d/Avenir/common/ledge/std_ledge";
#include "ledge.h"

void
create_room()
{
   AE(PORT+"port1", "west",0);
   AE(LEDGE+"ledge2", "south", 0, 0);

   SHORT("On the steep path");
   make_the_room("  To the west is a stormy cavern port. Mist flows "
      +"everywhere here, rolling off of the edge to the east. The "
       +"path ends to the north, where a majestic waterfall flows "
       +"out of a floodgate, sending spray everywhere and falling "
      +"hundreds of meters to the great sea below. The wind here "
       +"is intense.\n");


    AI(({"ledge","cliff","dropoff","view"}),"Merely looking " 
      +"over the dropoff gives "
      +"you a terrifying sense of vertigo. The cliff falls hundreds "
      +"of meters down to a great sea in which appear to be islands. "
      +"The entire great cavern is lit by strange phosphorescent veins "
      +"that run through the ceiling. A narrow path has been carved "
      +"out along the cliff, winding steeply downwards to "
      +"the southern part of the cavern.\n"); 
    AI(({"sea","ocean"}),"The great underground sea stretches out "
      +"thousands "
      +"of meters beneath you, making for a breathtaking sight. "
      +"Throughout the sea are islands of various sizes, and you can "
      +"even make out a ship or two travelling across the waters. The "
      +"light from above does not penetrate the sea, making it a heavy "
      +"shade of black.\n");
    AI(({"island","islands"}),"There are a number of islands of various "
      +"shapes and sizes far beneath you in the sea. From this height "
      +"you can make out few details, but one larger island in the "
      +"centre seems to contain a city, while others appear to be "
      +"green with forests and vegetation.\n");
    AI(({"ceiling","rocks","cave","cavern","Sybarus"}),
       "Spreading out to "
      +"the east you can see the enormous cavern "
      +"ceiling that stretches over all of the land. It seems to be "
      +"criss-crossed by veins of some substance that sheds a dazzling "
      +"white light. The veins seem more prominent on the eastern "
      +"reaches of the ceiling, many leagues away.\n");



     AI(({"waterfall","water"}),"The waterfall that comes out of the "
       +"floodgate to the north is truly beautiful. The power of it "
       +"creates a frightening noise, and droplets of water are "
       +"scattered everywhere, making you wet as you stand looking "
       +"at it.\n");

     AI(("port"),"To the west is a large, man made cavern that seems to "
       +"have been made into a sort of ship's port. The cavern is stormy "
       +"and you can feel the strong winds here, blowing mist and water "
       +"everywhere. A ledge circles around the port on its north "
       +"and south side.\n");


}

