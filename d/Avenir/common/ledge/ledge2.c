
// Ledge path 2 (/d/Avenir/common/ledge/ledge2.c)
// creator(s): Ilyian
// last update:  
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/ledge/std_ledge";
#include "ledge.h"

void
create_room()
{
     AE(LEDGE+"ledge1", "north", 0, 6);
     AE(LEDGE+"ledge3", "southeast", 0);
 

   SHORT("On the steep path");
   make_the_room("  The path seems to end up to the north, from where "
       +"you can hear the noise of intense winds and the roar of "
       +"a waterfall. To the east is a sheer dropoff, looking out "
       +"over the vast cavern. Your footing is slippery due to the "
       +"white mist that rolls down from above.\n");


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


}

