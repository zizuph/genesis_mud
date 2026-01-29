/*
 *  /d/Sparkle/area/tutorial/lib/herbsearch.c
 *
 *  This module makes easier the setting up of search functions for
 *  herbs in Silverdell.
 *
 *  Copied with permission from:
 *      /d/Gondor/common/lib/herbsearch.c
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
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

#define DEFAULT_PLACES ({ "here", "ground" })

string *places = DEFAULT_PLACES;

string *
query_search_places()
{
    return places;
}

void
set_search_places(string *places_arr)
{
    places = DEFAULT_PLACES;
    places += (places_arr - DEFAULT_PLACES);
}

void
add_search_places(string *places_arr)
{
    places += (places_arr - places);
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
    {
        places = DEFAULT_PLACES;
    }

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
set_up_herbs(string *hfiles, string *places_arr = ({}), int time = 5)
{
    int     i;

    if (!sizeof(hfiles))
        return 0;

    this_object()->add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    this_object()->add_prop(OBJ_I_SEARCH_TIME, time);
    set_search_places(places_arr);

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
 * Function name: reset_herbs
 * Description:   reset searched value to grow new herbs
 */
public void
reset_herbs()
{
    this_object()->set_searched(0);
}

/*
 * Function name: reset_room
 * Description:   reset searched value to grow new herbs
 */
public void
reset_room()
{
    reset_herbs();
}

