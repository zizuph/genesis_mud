// Green11 (/d/Avenir/common/bazaar/green/green11.c)
// creator(s):   Tepisch Dec 1994
// last update: Lilith 6:38 PM 4/21/97 (updated herbsearch)
//              Ilyian, April 30, 1995

//		    Sirra added the search functions that include 
//		    finding the bone for the wolf quest 
// purpose:     A place for herbs, flowers, and veggies to be found
//		    Also the femur bone (FEMUR_ID) for the wolf quest is 
//		    within the fence.
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/green/std_green.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/herbs/herbsearch.h"
#include "/d/Avenir/common/holm/wolf.h"

int check_fence();

int found;
string *herbs = HERB_MASTER->query_herbs( ({"garden"}) );

void
reset_room()
{
    found = 1;

    set_searched(-2);
}

void
create_room()
{
    AE(GREEN + "green15", "south", 0);

    AI("brush", "It is composed of dense, low shrubs.\n");
    AI("shrubs", "They appear to be a strange sort of evergreen, with "
        +"twisted branches.\n");
    AI(({"vegetation", "vines", "vine"}),
       "The vegetation is so dense that it is impossible to climb over "+
       "the fence.\n");

    SHORT("Eastern garden, near gate");
    make_the_room("A low fence, over-grown with vines, blocks "+
      "passage in every direction save the one you came from. "+
      "Northwest you can see the garden gate, and beyond "+
      "it the gravelled walk leading north into the center "+
      "of the marketplace.\n");

    /*
     * This array provides the herbs to be found, the places to be 
     * searched, and the search delay.
     */
    set_up_herbs(({ ONEOF(herbs), ONEOF(herbs), ONEOF(herbs) }), 
        ({ "garden","beds","soil", "brush", "shrubs", "vegetation",
           "vines" }), 5);

    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    add_prop(OBJ_I_SEARCH_TIME,2);


    reset_room();

}

//This is a masked search_herb() copied straight from 
//~Avenir/common/herb/herbsearch.h. It is masked to 
//include the femur bone (FEMUR_ID) for the wolf quest.
string 
do_search(object player, string str)
{
    string  place,
           *herb_names = ({}),
            this_herb;
    int     i;
    object bone;

    if (!places)
        places = ({"here","ground"});

    if (sscanf(str,"%s for %s", place, this_herb) == 2
        && member_array(place,places) >= 0)
    {
        if (this_herb == "herbs")
            return this_object()->search_for_herbs(player);

        for (i = 0; i < sizeof(herbs); i++) 
            herb_names += ({ herbs[i]->query_herb_name() });
        if ((i = member_array(this_herb, herb_names)) > -1)
            return this_object()->search_for_herbs(player, herbs[i]);
    }

    if (str == "fence")
    {
	  if(found<1)
	  return "";

	  found--;

	  bone = clone_object(WOLF_BONE + "femur.c");
	  bone->move(this_player(), 1);

	  return "You find a femur bone!\n";
     }

     return "";
}

void
init()
{
    ::init();
    check_fence();
}

int
check_fence()
{
    if(found<1)
    {	
    	AI("fence", "It is a picket-style fence "
	+ "over-grown with vegetation.\n");

    	return 1;
    }

    AI("fence", "It is a picket-style fence "
	+ "over-grown with vegetation. "
	+ "Something white peeks out at an odd "
	+ "angle from between the "
	+ "boards.\n");

    return 1;
}
