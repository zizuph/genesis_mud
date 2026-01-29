/* File: /d/Shire/common/eastroad/eroad.26.c */

#define ROOM_NUMBER 26
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"


create_eastroad()
{
   
   set_short("Great Eastroad");
   set_long(
      "You are now standing on the Last Bridge, east of the Trollshaws. \n"+
      "The river floats underneath the bridge, southwards beyond the \n"+
      "horizon. The forest to the east looks darker and fiercer \n"+
      "here then further west. The road continues southeastwards, into the \n"+
      "forest, and northwest to Bree. \n");
   
   add_item(({"bridge"}),
      "The bridge is made of stone. It's very old, but still strong\n"+
      "after so many years. It is a magnificent piece of art standing here.\n"
   );
   add_item(({"forest","shaws","trollshaws"}),
      "To your east you spot the forest. You can see it's dark in there, but you \n"+
      "don't know what's hiding in there. Looks quite dangerous and scary from here.\n"
   );
   add_item(({"water","river"}),
      "The river looks dark and loomy as you look down into it. The tide seems \n"+
      "dangerous enough from here, so you wouldn't want to try swim in it. \n"
   );
   
   add_exit(TROLLSH_DIR + "rivend1", "southeast", 0);
   add_exit(TEMP_DIR + "eroad.25", "northwest", 0);
   
}


