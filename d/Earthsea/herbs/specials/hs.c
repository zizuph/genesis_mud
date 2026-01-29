/*
 * Borrowed gratefully with permission from Elessar
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
 * added select_herb_files to choose random herbs
 * from a set of files -- Amelia  5/10/97
*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#define DEFAULT_PLACES ({ "here" })

private string *places = DEFAULT_PLACES;

public string *
query_search_places()
{
    return places;
}

public void
set_search_places(string *places_arr)
{
    places = places_arr + DEFAULT_PLACES;
}

public void
add_search_places(string *places_arr)
{
    if(!sizeof(places))
    {
        places = DEFAULT_PLACES;
    }

    places += places_arr;
}

public string
herb_search(object player, string str)
{
    string place, this_herb, *herb_names = ({});
    mixed herbs;
    object to;
    int i;

    if(!places)
    {
        places = DEFAULT_PLACES;
    }

    to = this_object();
    herbs = to->query_herb_files();

    if(sscanf(str, "%s for %s", place, this_herb) == 2 &&
        (member_array(place, places) > -1))
    {
        if(this_herb == "herbs")
        {
            return to->search_for_herbs(player);
        }

        for(i = 0; i < sizeof(herbs); i++)
        {
            herb_names += ({ herbs[i]->query_herb_name() });
        }

        if((i = member_array(this_herb, herb_names)) > -1)
        {
            return to->search_for_herbs(player, herbs[i]);
        }
    }

    return "";
}

public varargs int
set_up_herbs(string *hfiles, string *places = DEFAULT_PLACES, int time = 5)
{
    object to = this_object();
    int i;

    if(!sizeof(hfiles))
    {
        return 0;
    }

    to->add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    to->add_prop(OBJ_I_SEARCH_TIME, time);

    set_search_places(places);

    for(i = 0; i < sizeof(hfiles); i++)
    {
        to->add_herb_file(hfiles[i]);
    }

    return 1;
}

public string *
query_herbs()
{
    return this_object()->query_herb_files();
}

public void
reset_room()
{
    this_object()->set_searched(0);
}

public string *
select_herb_files(string *files)
{
    mixed nums = allocate(4);
    string *herbs = ({ });
    int num = 4, i;

    for(i = 0; i < 4; i++)
    {
        nums[i] = random(sizeof(files));
        herbs += ({ files[nums[i]] });
    }

    return herbs;
}
