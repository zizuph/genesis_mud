inherit "/d/Shire/eastroad/village/whit/whitstreet";
#include "/d/Shire/common/defs.h"
#include <macros.h>


create_street()
{
   set_short("Whitfurrows village lane");
   set_long("The street has dwindled into a small lane, that "+
      "leads up to the gentle rolling hill to the south.  This "+
      "is obviously the rich part of the village, and a couple "+
      "of paths wind off the lane through pretty flower "+
      "gardens to smials.  The largest smial has a sign out "+
      "the front, and the door of this smial is wide open, "+
      "inviting you to enter.  The lane is very clean, and the "+
      "area presents an idyllic picture, with smoke drifting "+
      "skywards from ovens, and bees humming softly as "+
      "they fly between the flowers.\n");
   add_cmd_item ("sign","read","The sign reads Whitfurrows School\n");
   add_item(({"flower","flowers"}),"There are a large number of "+
      "different flowers in the thriving flower gardens outside "+
      "the smials of the richer hobbits of Whitfurrows.  Amongst "+
      "the flowers, you can make out petunias and daffodils, "+
      "as well as daisies and other colourful delights.\n");
   
    add_item("school", "It is just south of here so it is hard to tell "+
        "anything from outside of it.\n");

    add_item("garden", "The garden is filled with flowers, "+
        "but you dare not pick any of them.\n");

    add_item("smial", "The smial is just south of here, and the school "+
        "is placed there.\n");
   add_exit("/d/Shire/eastroad/village/whit/whitroad3","north");
   add_exit("/d/Shire/eastroad/village/whit/whitschool","south");
   
   add_prop(ROOM_I_INSIDE,0);
   
   
}
