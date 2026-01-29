inherit "/d/Shire/eastroad/village/whit/whitstreet";
#include "/d/Shire/common/defs.h"
#include <macros.h>

void
create_street()
{
   set_short("Whitfurrows village road");
   set_long("You are standing in the middle of the village of "+
      "Whitfurrows, a charming little place that lies south "+
      "of the Great East Road.  Small houses and burrows line "+
      "the street, while bustling shops can be found in the "+
      "cluttered lanes that wind off to the east and to the "+
      "west.  To the south, a small hill rises up, with a couple "+
      "of large smials dug deep into it.  Delicious odours of "+
      "baked bread and simmering stews drift through the air, "+
      "from the cooking pots of hungry hobbits, and there is a "+
      "general air of happiness and merriment about the place.\n");
   
   
   add_exit("/d/Shire/eastroad/village/whit/whitroad2","north");
   add_exit("/d/Shire/eastroad/village/whit/whitlane5","south");
// add_exit("/d/Shire/eastroad/village/whit/whitlane4","east");
   
   add_prop(ROOM_I_INSIDE,0);
   
}
