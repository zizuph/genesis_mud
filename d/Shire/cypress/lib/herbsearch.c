/*
 * Herbsearch.c
 * This file is included in rooms where herbs grow.
 * The file contains the search-function of the room.
 * Elessar, Gondor. Oct 92.
 *
 * Modification log:
 * 06-jan-1994: Olorin
 *   Changed herb_search so it is no possible to 
 *   'search <place> for <herb name>  following a suggestion by Falke
 *   (Works only with modified search_for_herb in /std/room/description)
 * 07-jan-1995: Olorin
 *   Add set_up_herbs() function for easy setup
 * 26-jan-1995: Olorin
 *   Changed to herbsearch.c, added reset_room()
 *              
 * Modified Gondor's file to suit the Shires needs
 * Added a add_std_herb function for lazy wizards that like herbs ;)
 * Feb 7th 1997: Igneous
 *
 * Modified to work in Mysteria
 * --Finwe, May 2001
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#ifndef CYPRESS_HERB_MASTER
#define CYPRESS_HERB_MASTER "/d/Shire/cypress/herbs/herb_master.c"
#endif

#define NUM_HERB_FILES   7
#define HERB_SEARCH_TIME 6

//  Prototypes
varargs int set_up_herbs(string *hfiles, string *places = ({"ground", }),
  int time = 5);

string *places = ({ "here", });
string *terrain = ({"road","path","forest","meadow","plains","hills",
  "hill","plain","grassland","grasslands","field"});
int no_grow = 0;


/*
 * Functions: set_search_places(string *places)
 * Description: sets the place(s) where the herb grows in the room.
 *              The player must then type 'search <place> for herbs' to search.
 *              If not set, it defaults to 'ground' and 'here'.
 */
void
set_search_places(string *places_arr)
{
    places = places_arr+({"here"});
}

void
add_search_places(string *places_arr)
{
    if (!sizeof(places))
	places = ({ "here", });
    places += places_arr;
}

string *
query_search_places()
{
    return places;
}

string
herb_search(object player, string str)
{
    string  place,
    *herb_names = ({}),
    this_herb;
    int     i;
    mixed   herbs = this_object()->query_herb_files();

    if (!places)
	places = ({"here","ground"});

    if (sscanf(str,"%s for %s", place, this_herb) == 2
      && (member_array(place,places) > -1))
    {
	if (this_herb == "herbs")
	    return this_object()->search_for_herbs(player);

	for (i = 0; i < sizeof(herbs); i++) 
	    herb_names += ({ herbs[i]->query_herb_name() });
	if ((i = member_array(this_herb, herb_names)) > -1)
	    return this_object()->search_for_herbs(player, herbs[i]);
    }
    return "";
}

/*
 * Function name: set_up_herbs(string *hfiles,string *places,int time)
 * Description:   Add herbs to the room
 * Arguments:     hfiles: Array of filenames of the herbs
 *                places: Array of names of items (added with add_item)
 *                        that can be searched to find herbs
 *                time:   Argument for OBJ_I_SEARCH_TIME
 *                        delay used in the search function
 */
varargs int
set_up_herbs(string *hfiles, string *places = ({"ground", }), int time = 5)
{
    int     i;

    if (!sizeof(hfiles))
	return 0;

    this_object()->add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    this_object()->add_prop(OBJ_I_SEARCH_TIME, time);
    set_search_places(places);

    for (i = 0; i < sizeof(hfiles); i++)
	this_object()->add_herb_file(hfiles[i]);

    return 1;
}

string *
query_herbs()
{
    return this_object()->query_herb_files();
}



/*
 * Function name: set_no_herbs
 * Description:   Makes the room unable to grow herbs
 *                when you are using the add_std_herbs function to fill
 *                the room with them.
 */
void
set_no_herbs()
{
    no_grow = 1;
}

/*
 * Function name: add_std_herbs
 * Description:   adds herbs to a room depending on the room type.
 *                (for lazy wizards who don't want to set herb files
 *                 in _every_ room)
 */
nomask varargs void
add_std_herbs(mixed type, int seed)
{
    mixed *strarr, short;
    string *places, *herbs = ({}), *herb_list = ({});
    int i, ran;

    if (sizeof(this_object()->query_herb_files()) || no_grow)
	return;

    //  We were not given a type so try and figure it out using the
    //  Short description of the room.
    //  When terrian props are added change it so we use that not the short.
    if (!type || !stringp(type))
    {
	if (!(short = this_object()->check_call(this_object()->query_short())))
	    return;

	strarr = explode(short, " ");
	strarr = filter(strarr,&operator (!=) (,-1) @ &member_array(,terrain));

	if (!sizeof(strarr))
	    return;

	// Use the first thing in the array we want "In a forest near a
	// road" to work but not "A road near a forest"
	type = strarr[0];
    }
    switch(type)
    {
    case "road":
	return;
    case "path":
	return;
    case "forest":
	places = ({"trees","tree","bushes"});
	break;
    case "meadow":
	places = ({"meadow","grass"});
	break;
    case "grassland":
    case "grasslands":
    case "field":
    case "plain":
    case "plains":
	places = ({"plains","grass"});
	break;
    case "hill":
    case "hills":
	places = ({"hill","hills","grass"});
	break;
    }
    herb_list = CYPRESS_HERB_MASTER->query_herbs(type);

    //   No herbs matched type, so we don't add any
    if (!sizeof(herb_list))
	return;
    for (i = 0; i < NUM_HERB_FILES; i++)
    {  
	if (sizeof(herb_list))
	{
	    if (seed)
	    {
		ran = random(sizeof(herb_list), seed);
		// Alter the seed a bit for wider results.
		seed = (seed * 5) / 2;
	    }
	    else
		ran = random(sizeof(herb_list));
	    herbs += ({ herb_list[ran] });
	    herb_list -= ({ herb_list[ran] }); // To prevent duplications
	}
    }

    set_up_herbs(herbs,places,HERB_SEARCH_TIME);
}


/*
 * Function name: reset_mysteria_herbs()
 * Description:   reset searched value to grow new herbs
 */
void
reset_mysteria_herbs()
{
    this_object()->set_searched(0);
}
