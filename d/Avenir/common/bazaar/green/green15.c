
// Green15 (/d/Avenir/common/bazaar/green/green15.c)
// creator(s):   Tepisch Dec 1994
// last update: Lilith 6:43 PM 4/21/97 (updated herbsearch)
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
    AE(GREEN + "green16", "west", 0);
    AE(GREEN + "green11", "north", 0);

   AI("brush", "It is composed of dense, low-growing shrubs.\n");
   AI("shrubs", "They appear to be evergreen.\n");
   AI("fence", "It is a picket-style fence over-grown with vegetation.\n");

   SHORT("Southeast garden");
   make_the_room("This is a less well-tended part of the garden. "+
      "The low fence to the east is overgrown with vines.\n");

    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs" }), 5);
    add_herb_file(GONDOR + "laurel");
    add_herb_file(GONDOR + "holly");
    add_herb_file(GONDOR + "tuo");

}

reset_room()
{
set_searched(-2);
}
