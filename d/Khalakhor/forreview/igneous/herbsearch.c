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
 * 10-dec-1997: Teth
 *   Added to Khalakhor.
 * 5-jul-1998: Igneous
 *   Added add_std_herbs for quick easy setup of herbs
 *            
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Khalakhor/sys/paths.h"

static string *places = ({ "here", });
static int    gNo_herbs;

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

/*
 * Function name: add_std_herbs
 * Description:   Adds standard type herbs for rooms
 * Arguments:     int num_herbs:   Number of herbs we want to add to this
 *                                 room
 *                int search_time: How long it will take someone to search 
 *                                 this room for a herb.
 *                int seed:        A seed to keep herbs constant from reboot
 *                                 to reboot.
 */
varargs void
add_std_herbs(int num_herbs = 3, int search_time = 5, int seed = 0)
{
    int i, ran, sz, terrain;
    string *herbs = ({ }), *herb_list, *places;

    //  Herbs have already been added to this room so don't do anthing
    if (sizeof(this_object()->query_herb_files()) || gNo_herbs)
	return;
    terrain = this_object()->query_prop(ROOM_I_TERRAIN_TYPE);
    // Mmm no terrain prop set, so stop here.
    if (!terrain)
	return;
    // Add some extra search locations based on the terrain
    switch(terrain)
    {
    case TERRAIN_OCEAN:
        places = ({"ocean", "water", "sea"});
        break;
    case TERRAIN_UNDERSEA:
    case TERRAIN_UNDERLAKE:
        places = ({"water"});
        break;
    case TERRAIN_BAY:
        places = ({"bay", "water"});
        break;
    case TERRAIN_LAKE:
        places = ({"lake", "water"});
        break;
    case TERRAIN_POND:
        places = ({"water", "pond"});
        break;
    case TERRAIN_RIVER:
        places = ({"water", "river"});
        break;
    case TERRAIN_STREAM:
        places = ({"water", "stream"});
        break;
    case TERRAIN_PLAIN:
	places = ({"plains", "grass"});
	break;
    case TERRAIN_MOOR:
        places = ({"moors"});
        break;
    case TERRAIN_GLACIER:
        places = ({"ice", "glacer"});
        break;
    case TERRAIN_TUNDRA:
        places = ({"tundra"});
        break;
    case TERRAIN_DESERT:
        places = ({"sand", "desert"});
        break;
    case TERRAIN_SCRUB:
        places = ({"scrub"});
        break;
    case TERRAIN_BADLAND:
        places = ({"badlands"});
        break;
    case TERRAIN_WASTELAND:
        places = ({"wasteland"});
        break;
    case TERRAIN_MOUNTAIN:
        places = ({"rock", "rocks", "mountain"});
        break;
    case TERRAIN_HILL:
        places = ({"hills", "hill", "grass"});
        break;
    case TERRAIN_CLIFF:
        places = ({"cliff"});
        break;
    case TERRAIN_VOLCANO:
        places = ({"rock", "rocks", "volcano"});
        break;
    case TERRAIN_LAKESHORE:
        places = ({"shore", "lakeshore"});
        break;
    case TERRAIN_COAST:
        places = ({"coastline", "coast"});
        break;
    case TERRAIN_RIVERBANK:
        places = ({"riverbank", "mud", "sand"});
        break;
    case TERRAIN_SALTBEACH:
        places = ({"sand", "beach"});
        break;
    case TERRAIN_FRESHBEACH:
        places = ({"sand", "beach"});
        break;
    case TERRAIN_SWAMP:
        places = ({"swamp"});
        break;
    case TERRAIN_MARSH:
        places = ({"marsh"});
        break;
    case TERRAIN_BOG:
        places = ({"bog"});
        break;
    case TERRAIN_THICKET:
        places = ({"ticket"});
        break;
    case TERRAIN_BUSH:
        places = ({"bush", "bushes"});
        break;
    case TERRAIN_JUNGLE:
        places = ({"jungle", "vines"});
        break;
    case TERRAIN_MIXEDWOOD:
    case TERRAIN_CONIFEROUS:
    case TERRAIN_DECIDUOUS:
        places = ({"forest", "tree", "trees"});
    case TERRAIN_NCAVETUNNEL:
        places = ({"cave", "tunnel"});   
        break;
    case TERRAIN_NCAVE:
        places = ({"cave"});
        break;
    case TERRAIN_NCAVELAKESH:
        places = ({"cave", "shore", "shoreline"});
        break;
    case TERRAIN_NCAVEMAGMA:
        places = ({"cave", "magma"});
        break;
    case TERRAIN_MINE:
        places = ({"mine"});
        break;
    case TERRAIN_ARTOPENLAVA:
        places = ({"lava"});
        break;
    case TERRAIN_ROAD:
        places = ({"road"});
        break;
    case TERRAIN_STREET:
        places = ({"street"});
        break;
    case TERRAIN_FIELD:
        places = ({"field", "fields"});
        break;
    case TERRAIN_GARDEN:
        places = ({"garden"});
        break;
    case TERRAIN_GRAVEYARD:
        places = ({"graves", "graveyard"});
        break;
    case TERRAIN_SEWER:
        places = ({"sewage", "sewer"});
        break;
    case TERRAIN_PATH:
        places = ({"path"});
        break;
    case TERRAIN_RUINS:
    case TERRAIN_INRUINS:
        places = ({"ruins"});
        break;
    case TERRAIN_TOMB:
        places = ({"tomb"});
        break;
    }
    herb_list = HERBMASTER->query_herbs(terrain);
    // Couldn't find any herbs so stop here.
    if (!sizeof(herb_list))
	return;
    i = -1;
    sz = sizeof(herb_list);
    // Make sure we aren't trying to add more herbs than we have available
    num_herbs = (num_herbs > sz ? sz : num_herbs);
    while(++i < num_herbs)
    {
	if (seed)
	{
	    ran = random(sz, seed);
	    // Alter the seed a bit for more varied results
	    seed = seed * 5 / 2;
	}
	else
	    ran = random(sz);
	herbs += ({ herb_list[ran] });
	herb_list -= ({herb_list[ran]}); // To prevent duplications
	sz -= 1;
    }
    // Now we set everything up!
    set_up_herbs(herbs, places, search_time);
}

/* Function name: set_no_herbs
 * Description:   Used with set_std_herbs function to prevent it from
 *                adding herbs to this room.  
 */
void
set_no_herbs()
{
    gNo_herbs = 1;
}
