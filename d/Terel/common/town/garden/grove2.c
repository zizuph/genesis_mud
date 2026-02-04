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
   set_short("Grove");
   set_long("This is a grove of cedar trees. Their trunks glisten\n" +
      "red in the bits of sun that shine through their thick\n" +
      "canopies. The cedars smell very wonderful. The ground\n"+
      "is soft and spongy with moss.\n");
   
   add_exit(PATH + "glade", "south", 0);
   add_object(PATH + "statue", 1);

   add_item(({"cedar", "cedars", "tree", "trees"}),
	    "Normal, healthy cedar trees.\n");

    set_up_herbs( ({one_of_list(RANGER_HERBS),
                    one_of_list(MM_HERBS),
                    one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","rows","here"}), 
                   3 );
   add_item("grove", "It is a small stand of cedar trees.\n");
   add_item(({"garden","sacred garden","ground"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage",
      "moss", "ivy", "forest"}),
      "Kept in perfect condition by the vigilant gardeners.\n");
   add_item(({"berries", "red berries", "white berries"}), 
      "White and red berries add some pops of color to the mostly "+
      "green garden.\n");
	  
}


