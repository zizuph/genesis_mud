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
   set_long("This beautiful copse of birch and aspen has grown\n" +
      "thick and deep. The ground is coated with a fine layer\n" +
      "of leaves and moss. A few shrubs and briars grow up, but\n" +
      "not many, thus keeping the way clear.\n");

    set_up_herbs( ({TER_HERB + "whitehorn"}),
                 ({"trees","small trees", "small tree"}), 
                     3 );

   add_item(({"trees","tree","small tree","small trees", "copse"}),
      "A small group of aspen and birch trees have formed this copse.\n");
   add_item(({"garden","sacred garden"}),
      "The sacred garden looks well maintained.\n");
   add_item(({"greenery", "hollies", "yews", "box", "hedges", "bushes",
      "firs","pines","spruce", "cedar","redwood","trees","juniper", 
      "hemlock", "myrtle", "candleberry", "mosses", "shrubs", "foliage",
	  "briars", "aspen", "birch",}),
      "Kept in perfect condition by the vigilant gardeners.\n");
    add_item(({"ground", "leaves", "moss"}), "The ground is soft with "+
      "moss and leaves.\n");

   
   add_exit(PATH + "copse2", "east", 0);
   reset_room();
   
}

