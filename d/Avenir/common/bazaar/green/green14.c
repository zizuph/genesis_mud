// Green14 (/d/Avenir/common/bazaar/green/green14.c)
// creator(s):   Tepisch Dec 1994
// last update: Lilith 6:40 PM 4/21/97 (updated herbsearch)
//              Ilyian, April 30, 1995
//              Lucius 2008: Changed quest checks so that only
//                           Union seekers can find the objects.
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
reset_room()
{
    set_searched(-2);
}

void
create_room()
{
    AE(GREEN + "green18", "south", 0);
    AE(GREEN + "green10", "north", 0);

   AI("brush", "It is composed of dense, low-growing shrubs.\n");
   AI("shrubs", "They appear to be evergreen.\n");
   AI("soil", "It is thick and black, damp and rich with minerals.\n");
   AI(({"wall","walls"}),"It is a natural formation of the dark volcanic "
      +"rock which has enriched the soil. The face of the wall bears numerous "
      +"cracks in it.\n");
   AI(({"crack","cracks"}),"They are large and dark.\n");
   SHORT("Southwest garden");
   make_the_room("A rock wall forms the western border here. "+
      "The soil is damp and gives off a vaguely unpleasant smell "+
      "of decay.\n");


    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs" }), 5);
    add_herb_file(HERB + "carlith");
    add_herb_file(GONDOR + "tuo");

    add_prop(OBJ_S_SEARCH_FUN, "search_me");
    reset_room();
}

#include "/d/Avenir/union/lib/bits.h"
#define LIST ("/d/Avenir/union/list")

string search_me(object player, string str)
{
    if (player->query_prop("found_it_yet") ||
	player->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) ||
	!LIST->query_accepted(player->query_real_name()))
    {
        return herb_search(player, str);
    }
 
    if (!parse_command(str, ({ }),
	    "[the] 'wall' / 'crack' / 'hole' / 'cracks'"))
    {
        return herb_search(player, str);
    }

    player->add_prop("found_it_yet", 1);
    object ob = clone_object(UNION+"obj/quest/ball");
    ob->move(player, 1);

    return "You find "+LANG_ASHORT(ob)+" in a crack in the wall.\n";
}

