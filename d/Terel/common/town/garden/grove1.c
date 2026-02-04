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

   add_object(PATH +"fountain", 1);
   
   set_short("Grove");
   set_long(
      "A small grove of bristling fir trees, with a pool at the\n"+
      "center. A wind rushes through the needles, creating a\n"+
      "hissing sound that combines soothingly with the sound of\n"+
      "flowing water. The ground is damp and coated with a layer\n"+
      "of moss.\n");
  
     set_up_herbs( ({one_of_list(RANGER_HERBS),
                     one_of_list(MM_HERBS),
                     one_of_list(ANY_HERBS),
                  }),
                  ({"ground","garden","bushes","underbrush"}), 
                   3 );

   add_item(({"garden","sacred garden","ground", "grove",}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", "moss",
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage"}),
      "Kept in perfect condition by the vigilant gardeners.\n");
   add_item(({"berries", "red berries", "white berries"}), 
      "White and red berries add some pops of color to the mostly "+
      "green garden.\n");	  
   add_item(({"stones", "ornamental stones", "white rocks", "rocks"}),
      "They are an interesting contrast to the soft greens of the garden.\n");   

   add_item(({"pool", "water"}), "There is a pool of water here, which is "+
       "filled by the sylph pouring water from her basin.\n");
  
   add_exit(PATH + "garden3", "east", 0);
   
   reset_room();
}


