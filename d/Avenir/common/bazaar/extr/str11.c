// Bazaar Street11 (/d/Avenir/common/bazaar/extr/str11.c)
// creator(s):   Triana 1994
// last update:  Tepisch Sept 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

init()
{
   ::init();
   ADD("do_crunch","west");
}

void
create_room()
{
   AE(EXTR + "str4", "north", 0);
   AE(EXTR + "str12", "east", 0);
   AE(EXTR + "str10", "west", 0);
   AE(EXTR + "str17", "south", 0);
   AE(INTR + "flower_stall", "stall", 0);
   AI(({"building","pink building", "pink and white building",
     "ice cream shop", "ice cream parlor", "parlor"}), 
     "It appears to have been recently painted in very bright "+
     "white and pink colours. you'll have to go north "+
     "to get to the entrance.\n");

   AI(({"compound", "south compound"}), "The sounds of training "+
     "appear to be coming from it. If you go east and then turn "+
     "south you will find the entrance.\n");

   SHORT("Western edge of Market. A flower stall");
   make_the_room("\n   North is the entrance a bright pink and white "+
      "building that was once an inn but is now an ice cream parlor. "+
      "South of you appears to be a large "+
      "garden and the entrance to an adventurer's guild. Wonderful "+
      "fragrances waft from the flower stall here.\n");
}

do_crunch()
{
   write("Gravel crunches under your feet.\n");
}
