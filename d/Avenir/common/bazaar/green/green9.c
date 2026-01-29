// Green9 (/d/Avenir/common/bazaar/green/green9.c)
// creator(s):   Tepisch Sept 1994
// last update: Lilith, 7:16 PM 4/21/97 (updated herbsearch)
//              Ilyian, July 1, 1995 - added standing stone
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
   AE(GREEN + "green5", "north", 0);
   AE(GREEN + "green8", "east", 0);
   AE(GREEN + "green10", "west", 0);
   AE(GREEN + "green13", "south", 0);

   SHORT("Garden center");
   make_the_room(" In every direction you look you can see "+
      "spices and vegetables.\nA large marble standing stone rests where the "+
      "paths cross.\n");

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,3);
   add_herb_file(SHIRE + "parsley");
   add_herb_file(HERB + "ronwath");
   add_herb_file(GONDOR + "sage");
   add_herb_file(GONDOR + "thyme");
   add_herb_file(GONDOR + "seregon");

   seteuid(getuid(this_object()));
     clone_object(MISC + "stone.c")->move(this_object(),1);

    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs" }), 5);

}

reset_room()
{
    set_searched(-2);
}

