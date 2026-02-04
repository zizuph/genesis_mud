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
   
   set_short("Evergreen Garden");
   set_long("A garden of magnificent greenery. Tall hollies with\n" +
      "red and white berries, various firs and pines, spruce, cedar\n" +
      "and redwood trees adorn the area. Smaller juniper, hemlock\n" +
      "myrtle, candleberry, box and yews fill the lower area and\n" +
      "form hedges. The grounds are covered with mosses and shrubs\n" +
      "of vibrant color. Ornamental stones and white rocks have been\n" +
      "placed below the trees and around the foliage.\n");


     set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","rows","here"}), 
                   3 );

   add_item(({"garden","sacred garden","ground"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage"}),
      "Kept in perfect condition by the vigilant gardeners.\n");
   add_item(({"berries", "red berries", "white berries"}), 
      "White and red berries add some pops of color to the mostly "+
      "green garden.\n");	  
   add_item(({"stones", "ornamental stones", "white rocks", "rocks"}),
      "They are an interesting contrast to the soft greens of the garden.\n");   
  
	  
   add_exit(PATH + "garden4", "north", 0);
   add_exit(PATH + "glade", "southwest", 0);

reset_room();   
}




