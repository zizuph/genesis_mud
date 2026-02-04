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
create_room(){
   
   add_npc(PATH + "pilgrim", 1);

   set_short("Clearing");
   set_long("A small clearing in the garden. A row of holly bushes\n" +
      "ring the area, their berries glistening in the light.\n" +
      "A pile of rocks stand here, like a cairn, upon which is\n" +
      "a silver star.\n");
 
     set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","rows","here"}), 
                   3 );

 
   add_item(({"star", "silver star"}), "The star is very silvery!\n");
   add_item(({"cairn", "rocks", "pile"}),
	    "The rocks support the weight of the silver star.\n");
   add_item(({"garden","sacred garden","ground", "forest"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"clearing"}), "It is a gap in the forest that has "+
      "been intentionally cleared.\n");	  
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage",
	  "holly", "holly bushes"}),
      "Kept in perfect condition by the vigilant gardeners.\n");
   add_item(({"berries", "red berries", "white berries"}), 
      "White and red berries add some pops of color to the mostly "+
      "green garden.\n");	 
	  
   add_exit(PATH + "garden2", "west", 0);
   
   reset_room();
}
