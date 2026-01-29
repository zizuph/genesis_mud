/*
 * Herbsearch.h
 *
 * This file is included in rooms where herbs grow.
 * The file contains the search-function of the room.
 * Elessar, Gondor. Oct 92.
 *
 * Modification log:
 * 06-jan-1994: Olorin
 *   Changed herb_search so it is no possible to 
 *   'search <place> for <herb name>  following a suggestion by Falke
 *
 * Lucius, Jul 2017: A bit of recoding and cleanup.
 *              
 */
#include <stdproperties.h>

public static string *places = ({ "here" });

/*
 * Functions: set_search_places(string *places)
 * Description: sets the place(s) where the herb grows in the room.
 *   The player must then type 'search <place> for herbs' to search.
 *   If not set, it defaults to 'here'.
 */
public void 
set_search_places(string *arr)
{
    if (sizeof(arr))
	places = arr + ({ "here" });
}

public void 
add_search_places(string *arr)
{
    if (sizeof(arr))
	places |= arr;
}

public string 
herb_search(object player, string str)
{
    string place, herb;

    if (sscanf(str, "%s for %s", place, herb) == 2 &&
	member_array(place, places) >= 0)
    {
        if (herb == "herbs")
            return this_object()->search_for_herbs(player);

	string *names = map(herbs, &->query_herb_name());
	int index = member_array(herb, names);

	if (index > -1)
	    return this_object()->search_for_herbs(player, herbs[index]);
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
public varargs int
set_up_herbs(string *hfiles, string *places, int time = 5)
{
    if (!sizeof(hfiles))
        return 0;

    this_object()->add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    this_object()->add_prop(OBJ_I_SEARCH_TIME, time);

    if (sizeof(places))
	add_search_places(places);

    foreach(string file: hfiles)
	this_object()->add_herb_file(file);

    return 1;
}

public string *
query_herbs(void)
{
    return this_object()->query_herb_files();
}

public string *
query_places(void)
{
    return places + ({ });
}
