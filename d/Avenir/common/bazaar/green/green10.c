// Green10 (/d/Avenir/common/bazaar/green/green10.c)
// creator(s):   Tepisch Sept 1994
// last update: Ilyian, April 30, 1995
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
   AE(GREEN + "green6", "north", 0);
   AE(GREEN + "green9", "east", 0);
   AE(GREEN + "green14", "south", 0);

   AI("brush", "It is composed of dense, low-growing shrubs.\n");
   AI("shrubs", "They appear to be evergreen.\n");

   SHORT("Western center of garden");
   make_the_room(" A rock wall forms the western border here, "+
      "against which some brush is growing. A warm breeze is "+
      "blowing through the area.\n");

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
