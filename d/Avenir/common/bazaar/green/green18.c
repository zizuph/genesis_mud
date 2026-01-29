
// Green18 (/d/Avenir/common/bazaar/green/green18.c)
// creator(s):   Tepisch Dec 1994
// last update: Lilith 6:56 PM 4/21/97 (updated herbsearch)
//              Ilyian, April 30, 1995
// purpose:     A place for herbs, flowers, and veggies to be found
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"

string *herbs = HERB_MASTER->query_herbs( ({"forest", "cave"}) );

// Temp for union accepted to do entrance quest.
#define LIST       ("/d/Avenir/union/list")
int
try_south(string cmd)
{   
    if(LIST->query_accepted(TP->query_real_name()))
    {
        write("You climb the branches of the tree and "+
            "leap down to the other side.\n");
        return 0;
    }

    if (query_verb() == ("climb"))
        write("You cannot climb the tree.\n");
    else
        write("There is no obvious exit south.\n");
    return 1;
}


void
create_room()
{
// Temp for union accepted to do entrance quest.
   add_exit(GREEN +"s_shore", "south", "@@try_south", 1, 1);
   add_exit(GREEN +"s_shore", "climb", "@@try_south", 1, 1);

   AE(GREEN + "green14", "north", 0);
   AI("tree", "It is stunted, with bare branches. Its dried husk "
       +"seems brittle and hollow.\n");
   ACI("tree", "climb", "The branches would not support your weight.\n");
   SHORT("Southwest corner of garden");
   make_the_room("Some interesting plants grow here beneath the "+
      "bare branches of a twisted tree.\n");


    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs", "tree" }), 5);

    add_herb_file(HERB + "nightshade");
    add_herb_file(SHIRE + "treemushroom");

}

reset_room()
{
    set_searched(-4);
}
