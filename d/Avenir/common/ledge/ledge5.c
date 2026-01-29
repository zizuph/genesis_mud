
// Ledge path 5 (/d/Avenir/common/ledge/ledge5.c)
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
     AE(LEDGE+"ledge4", "north", 0, 6);
     AE(LEDGE+"ledge6", "southeast", 0, 0);

   SHORT("On the steep path");
   make_the_room("  The path turns from north to southeast, following "
      +"the curve of the western wall of the cavern. Far down to the "
      +"south you can see that the path ends in a tunnel that enters "
      +"the southern cavern wall. From the north you can make out a "
      +"bright glow that falls onto the path from a vein that snakes "
      +"up the wall.\n");

   AI(({"glow","light","vein"}),"The light that falls on the path is "
      +"of dazzling brightness, but you cannot make out any features "
      +"of the vein from here.\n");

   AI(("tunnel"),"The tunnel enters into darkness to the south. You can "
      +"make out no features from here.\n");


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

