// Green8 (/d/Avenir/common/bazaar/green/green8.c)
// creator(s):   Tepisch Sept 1994
// last update: Lilith, 7:14 PM 4/21/97 (updated herbsearch)
//              Ilyian, April 30, 1995
// purpose:     A place for herbs, flowers, and veggies to be found
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

string *herbs = HERB_MASTER->query_herbs( ({"garden"}) );

void
create_room()
{
   AE(GREEN + "green4", "north", 0);
   AE(GREEN + "green7", "east", 0);
   AE(GREEN + "green9", "west", 0);
   AE(GREEN + "green12", "south", 0);

   SHORT("Garden center");
   make_the_room(" In every direction you look you can see "+
      "herbs and vegetables.\n");

    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs" }), 5);

}

reset_room()
{
    set_searched(-3);
}
