// Green3 (/d/Avenir/common/bazaar/green/green3.c)
// creator(s):   Tepisch Sept 1994
// last update: Lilith, 7:02 PM 4/21/97 (updated herbsearch)
//              Ilyian, April 30, 1995
// purpose:     A place for herbs, flowers, and veggies to be found
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

string *herbs = HERB_MASTER->query_herbs( ({"garden", "forest"}) );

void
create_room()
{
   AE(GREEN + "green6", "south", 0);


   SHORT("Northwest corner of garden");
   make_the_room(" Plants creep up the stone wall which borders "+
      "this corner on the north and west sides. A thorny bush " +
      "blocks the way east.\n");

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
