inherit "/d/Shire/eastroad/village/whit/whitstreet";
#include "/d/Shire/common/defs.h"
#include <macros.h>

void
create_street()
{
   set_short("Whitfurrows village road");
   set_long("This is a road that connects the Great East Road "+
      "to the north with the small hobbit village of Whitfurrows " +
      "to the south.  The village can be seen in the distance, made " +
      "up of a number of houses and burrows, with some smials " +
      "built into the hill to the south of the village.\n");
   
   add_exit("/d/Shire/eastroad/village/whit/whitroad2","south");
   add_exit(ER_DIR + "er21","north",0,1);
   
   
   add_prop(ROOM_I_INSIDE,0);
   
}
