
// Green2 (/d/Avenir/common/bazaar/green/green2.c)
// creator(s):   Tepisch Sept 1994
// last update: Lilith 7:00 PM 4/21/97 (updated herbsearch)
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
   AE(GREEN + "green1", "east", 0);
   AE(GREEN + "green5", "south", 0);

   AI("bench", "It is carved from the living rock which blocks "+
     "the way north.\n");
   ACI(({"bench", "rock"}), ({"sit", "sit on"}), "It is rather "+
     "hard, but not so uncomfortable that you can't sit a while.\n");
   ACI(({"bench", "rock"}), ({"climb", "climb up"}), "You decide "+
     "not to risk breaking your precious neck.\n");

   SHORT("North garden");
   make_the_room(" There is a bench here upon which you "+
      "may rest and enjoy a moment of solitude. A blueberry "+
      "bush blocks the way west.\n");

    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs", "bush" }), 5);
   add_herb_file(GONDOR + "blueberry");

}

reset_room()
{
    set_searched(-2);
}
