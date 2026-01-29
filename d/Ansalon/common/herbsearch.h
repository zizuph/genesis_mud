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
 *              
 */

/*
 * Functions: set_search_places(string *places)
 * Description: sets the place(s) where the herb grows in the room.
 *   The player must then type 'search <place> for herbs' to search.
 *   If not set, it defaults to 'ground' and 'here'.
 */

string *places;

void 
set_search_places(string *places_arr)
{
    places = places_arr+({"here"});
}

void 
add_search_places(string *places_arr)
{
    places = places_arr+({"here"});
}

string 
herb_search(object player, string str)
{
    string  place,
           *herb_names = ({}),
            this_herb;
    int     i;

    if (!places)
        places = ({"here","ground"});

    if (sscanf(str,"%s for %s", place, this_herb) == 2
        && member_array(place,places) >= 0)
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
