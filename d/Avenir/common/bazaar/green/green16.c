
// Green16 (/d/Avenir/common/bazaar/green/green16.c)
// creator(s):   Tepisch Dec 1994
// last update: Lilith 6:47 PM 4/21/97 (updated herbsearch)
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
    AE(GREEN + "green12", "north", 0);
    AE(GREEN + "green15", "east", 0);

   SHORT("South-central garden");
   make_the_room("There are more flowers here, interspersed "+
      "with some recognizeable herbs.\n");

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
