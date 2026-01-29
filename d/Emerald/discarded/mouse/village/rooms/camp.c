/* room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h> 
inherit "/d/Gondor/open/HERBS/herbsearch";
#include "../../mouse.h"

int searched;  

void create_room()  {
     set_short("Under the bridge");
     set_long("   You stumble down the steep path and discover an encampment "+
          "of sorts underneath the bridge. Several coarse looking vagabonds "+
          "have set up camp under the protection of the bridge above. They "+
          "are sitting on logs arranged in a circle around a blazing fire, "+
          "over which an animal is roasting upon a spit. The vagabonds "+
          "seem eager for their dinner to cook, and look none too pleased "+
          "about your untimely arrival. As you look away toward the nearby "+
          "creek, you notice a bit of fur that must be the discarded "+
          "skin of tonight's main course tossed away on the stream bank.\n");
     add_item(({"fur","skin"}),"As you look more closely at the skin, you "+
          "realize it is the soft, liver-brown fur of a spaniel! "+
          "You turn away and puke in the creek.\n");
     add_exit(ROOT+"village/rooms/V17","up");

     set_up_herbs(({ROOT+"herbs/yarrow",
                    ROOT+"herbs/elecampane",
                    ROOT+"herbs/aconite"}), 
                    ({"ditch"}));
     places = ({"ditch"});
     reset_room();            

}

  
void reset_room()  {
     int i;
     if(!present("vagabond"))
     for(i=0;i<5;i++)
         clone_object(ROOT+"village/mons/vagabond.c")->move(TO);
     this_object()->set_searched(0);   
}

