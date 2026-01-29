
// Green1 (/d/Avenir/common/bazaar/green/green12.c)
// creator(s):   Tepisch Dec 1994
// last update: Ilyian, April 30, 1995
// purpose:     A place for herbs, flowers, and veggies to be found
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

void
create_room()
{
   AE(GREEN + "green8", "north", 0);
   AE(GREEN + "green16", "south", 0);

   AI("brush", "It is composed of dense, low-growing shrubs.\n");
   AI("shrubs", "They appear to be evergreen.\n");
   AI(({"seedlings", "vegetables", "vegetable"}), "They are too "+
      "young at this time for you to distinguish what they are.\n");
   ACI("here", "search", "The plants are too young to be of use.\n");
   SHORT("vegetable garden");
   make_the_room("Vegetable seedlings abound here, their vibrant "+
      "heads poking up from the rich black soil.\n");
 }

