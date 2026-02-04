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
   
   set_short("Copse");
   set_long("This small copse of aspen and birch stands in striking\n" +
      "difference to the evergreen garden. The white trunks of the\n" +
      "trees, their light green leaves contrast the rest of the garden\n" +
      "very well. A lane leads north from here and a large building\n" +
      "can be seen through the trees to the south.\n");

    add_item(({"building", "gothic building", "shining building",
	    "minarets", "large building", "south"}),
        "A large gothic building with spiral minarets rises up in "+
        "the south. It must be the famed home of the Minstrels.\n");	  
   add_item(({"garden","sacred garden"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage",
	  "briars", "aspen", "birch", "evergreens"}),
      "Kept in perfect condition by the vigilant gardeners.\n");
    add_item(({"ground", "leaves", "moss"}), "The ground is soft with "+
      "moss and leaves.\n");
    add_item(({"trees","tree","small tree","small trees", "copse", "aspen",
      "birch", "trunks", "white trunks", "copse"}),
      "Aspen and birch trees have grown up toward the edge of the lane.\n");
    add_item(({"lane", "north"}), "The lane leads north into the sacred "+
        "garden that is south of Calathin.\n");
	
     set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","trunks","here"}), 
                   3 );	
		
   add_exit(PATH + "lane4", "north", 0);
   add_exit(PATH + "glade", "northeast", 0);
   add_exit(PATH + "copse1", "south", 0);

    reset_room();   
}
