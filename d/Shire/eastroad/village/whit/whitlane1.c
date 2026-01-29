inherit "/d/Shire/eastroad/village/whit/whitstreet";
#include "/d/Shire/common/defs.h"
#include <macros.h>


void
create_street()
{
   set_short("Whitfurrows village lane");
   set_long("This is a small lane that runs off the road to the east, " +
      "that passes through the village of Whitfurrows.  There are "  +
      "a number of houses surrounding the lane, as well as a few " +
      "small shops.\n");
   
   add_item(({"shop","shops"}),"There are a couple of shops in this " +
      "lane, although only the shop to the north seems open at the  " +
      "moment.  This shop has a sign out the front that you could " +
      "examine.\n");
   
   add_item("sign","The sign says: Folger's Bakery\n");
   
   add_exit("/d/Shire/eastroad/village/whit/whitbaker","north");
   add_exit("/d/Shire/eastroad/village/whit/whithouse2","south");
   add_exit("/d/Shire/eastroad/village/whit/whithouse1","west");
   add_exit("/d/Shire/eastroad/village/whit/whitroad2","east");
   
   add_prop(ROOM_I_INSIDE,0);
   
}
