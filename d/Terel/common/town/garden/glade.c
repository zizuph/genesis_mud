// modified by Lilith, Mar 2022:  updated desc and added items.
 
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#define PATH "/d/Terel/common/town/garden/"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";


void
reset_room()
{
    set_searched(0);
}

void
create_room()
{
   add_npc("/d/Terel/common/town/garden/elf", 2);
   set_short("Glade");
   set_long(
      "This is a small glade in the sacred forest. There are\n"+ 
      "large rocks piled here in the center of the space. They\n"+
	  "are covered in ivy and moss. The warm sun shines down\n"+ 
      "onto the rocks, warming them.\n");
	  
   add_exit("/d/Terel/common/town/garden/garden5", "northeast", 0);
   add_exit("/d/Terel/common/town/garden/lane5", "southwest", 0);
   add_exit("/d/Terel/common/town/garden/grove2", "north", 0);
   add_exit("/d/Terel/common/town/garden/arbor_shrine", "southeast", 0);
   
        set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","rows","here"}), 
                   3 );

   add_item(({"garden","sacred garden","ground"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", "forest", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage",
      "moss", "ivy"}),
      "Kept in perfect condition by the vigilant gardeners.\n");
   add_item(({"berries", "red berries", "white berries"}), 
      "White and red berries add some pops of color to the mostly "+
      "green garden.\n");	  
   add_item(({"stones", "pile", "rocks"}),
      "The stones are very large and look like they have been here "+
      "for a long time.\n");    

   reset_room();
   
}
