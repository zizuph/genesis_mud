/*
  *  Borrowed gratefully with permission from Elessar
*
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
*  added select_herb_files to choose random herbs
*  from a set of files -- Amelia  5/10/97
 */

/*
 * Functions: set_search_places(string *places)
 * Description: sets the place(s) where the herb grows in the room.
 *   The player must then type 'search <place> for herbs' to search.
 *   If not set, it defaults to 'ground' and 'here'.
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

string *places = ({ "here", });

string *
query_search_places()
{
    return places;
}

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
 * Function name: set_up_herbs
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
 * Function name: reset_room
 * Description:   reset searched value to grow new herbs
 * Arguments:     /
 * Returns:       /
 */
public void
reset_room()
{
    this_object()->set_searched(0);
}

string *
select_herb_files(string *garden_files)
{

    int num = 4;
    int i;
    string *herbs = ({ });
    mixed nums = allocate(4);

    for (i = 0; i < 4; i++)
    {
	nums[i] = random(sizeof(garden_files));
	herbs += ({garden_files[nums[i]]});
    }
    return herbs;
}
