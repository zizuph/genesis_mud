/*
 *	This file is obsolete and has been replaced by:
 *		/d/Gondor/common/lib/herbsearch.c
 *
 *	Please do not use this file anymore and replace it
 *	where it is used in old code!
 *
 *	Olorin, June 1995
 */
/*
 * Herbsearch.h
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
 *              
 */

/*
 * Functions: set_search_places(string *places)
 * Description: sets the place(s) where the herb grows in the room.
 *   The player must then type 'search <place> for herbs' to search.
 *   If not set, it defaults to 'ground' and 'here'.
 */
#include <stdproperties.h>

#ifndef HERB_SEARCH_DEFS
#define HERB_SEARCH_DEFS 

string *places;

void
set_search_places(string *places_arr)
{
    places = places_arr+({"here"});
}

void
add_search_places(string *places_arr)
{
    places = places_arr + ({"here"});
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
        && member_array(place,places))
    {
        if (this_herb == "herbs")
            return search_for_herbs(player);

        for (i = 0; i < sizeof(herbs); i++) 
            herb_names += ({ herbs[i]->query_herb_name() });
        if ((i = member_array(this_herb, herb_names)) > -1)
            return search_for_herbs(player, herbs[i]);
    }
    return "";
}

varargs int
set_up_herbs(string *hfiles, string *places = ({"ground", }), int time = 5)
{
    int     i;

    if (!sizeof(hfiles))
        return 0;

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME, time);
    set_search_places(places);

    for (i = 0; i < sizeof(hfiles); i++)
        add_herb_file(hfiles[i]);

    return 1;
}

string *
query_herbs()
{
    return query_herb_files();
}

#endif   /* HERB_SEARCH_DEFS */
