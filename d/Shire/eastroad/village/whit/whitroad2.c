inherit "/d/Shire/eastroad/village/whit/whitstreet";
#include "/d/Shire/common/defs.h"
#include <macros.h>


void
create_street()
{
   
   set_short("Whitfurrows village road");
   set_long("You are walking along a road that meanders "+
      "through the middle of the small hobbit village of "+
      "Whitfurrows, famous for its messenger service and "+
      "the Training Academy.  A number of houses and small "+
      "burrows line the main road, and lanes wander off to "+
      "the east and to the west, where many of the inhabitants "+
      "of Whitfurrows live.  To the north, the road through "+
      "Whitfurrows joins up with the Great East Road, while "+
      "to the south lies the rest of the village.\n");
   
   
   add_exit("/d/Shire/eastroad/village/whit/whitroad1","north");
   add_exit("/d/Shire/eastroad/village/whit/whitroad3","south");
   add_exit("/d/Shire/eastroad/village/whit/whitlane1","west");
   
   add_prop(ROOM_I_INSIDE,0);
   
}
