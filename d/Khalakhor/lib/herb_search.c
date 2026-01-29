/* File         : /d/Khalakhor/std/room/herbsearch.c
 * Creator      : Elessar@Genesis
 * Date         : October 92
 * Purpose      : Sets up standard herb search functions.
 * Related Files: /d/Gondor/???/herbsearch.c
 * Comments     :
 * Modifications: 06-Jan-1994 Olorin
 *                Changed herb_search so it is now possible to
 *                'search <place> for <herb name>  following a 
 *                suggestion by Falke
 *                (Works only with modified search_for_herb in
 *                 /std/room/description)
 *              : 07-Jan-1995 Olorin
 *                Add set_up_herbs() function for easy setup
 *              : 26-Jan-1995 Olorin
 *                Changed to herbsearch.c, added reset_room()
 *              : 10-Dec-1997 Teth
 *                Added to Khalakhor
 *              : 05-Jul-1998 Igneous
 *                Added add_std_herbs for quick setup of herbs
 *              : 06-Feb-2002 Teth
 *                Modified to use new mudlib terrain system
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrain.h"
#include "/d/Khalakhor/sys/paths.h"

static string *places = ({ "here", });
static int    gNo_herbs;

string *
query_search_places()
{
    return places;
}

/*
 * Functions: set_search_places(string *places_arr)
 * Description: sets the place(s) where the herb grows in the room.
 *   The player must then type 'search <place> for herbs' to search.
 *   If not set, it defaults to 'ground' and 'here'.
 */
void
set_search_places(string *places_arr)
{
    places += places_arr;
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
 *                srch_places: Array of names of items (added with add_item)
 *                        that can be searched to find herbs
 *                time:   Argument for OBJ_I_SEARCH_TIME
 *                        delay used in the search function
 */
varargs int
set_up_herbs(string *hfiles = ({ }), string *srch_places = ({ }), int time = 5)
{
    int     i;

    if (!sizeof(hfiles))
	return 0;

    this_object()->add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    this_object()->add_prop(OBJ_I_SEARCH_TIME, time);
    set_search_places(srch_places);

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
    int i, ran, indx, terrain;
    string *herbs = ({ }),
           *herb_list = ({ }),
           *local_places = ({ });

    //  Herbs have already been added to this room so don't do anything
    if (sizeof(this_object()->query_herb_files()) || gNo_herbs)
	return;
    terrain = (this_object()->query_terrain());
    // Add some extra search locations based on the terrain
    switch(terrain)
    {
    case TERRAIN_OCEAN:
        local_places += ({"ocean", "water", "sea"});
        break;
    case TERRAIN_UNDERSEA:
    case TERRAIN_UNDERLAKE:
        local_places += ({"water"});
        break;
    case TERRAIN_BAY:
        local_places += ({"bay", "water"});
        break;
    case TERRAIN_LAKE:
        local_places += ({"lake", "water"});
        break;
    case TERRAIN_POND:
        local_places += ({"water", "pond"});
        break;
    case TERRAIN_RIVER:
        local_places += ({"water", "river"});
        break;
    case TERRAIN_STREAM:
        local_places += ({"water", "stream"});
        break;
    case TERRAIN_PLAIN:
	    local_places += ({"plains", "grass"});
	    break;
    case TERRAIN_MOOR:
        local_places += ({"moors"});
        break;
    case TERRAIN_GLACIER:
        local_places += ({"ice", "glacier"});
        break;
    case TERRAIN_TUNDRA:
        local_places += ({"tundra"});
        break;
    case TERRAIN_DESERT:
        local_places += ({"sand", "desert"});
        break;
    case TERRAIN_SCRUB:
        local_places += ({"scrub"});
        break;
    case TERRAIN_BADLAND:
        local_places += ({"badlands"});
        break;
    case TERRAIN_WASTELAND:
        local_places += ({"wasteland"});
        break;
    case TERRAIN_MOUNTAIN:
        local_places += ({"rock", "rocks", "mountain"});
        break;
    case TERRAIN_HILL:
        local_places += ({"hills", "hill", "grass"});
        break;
    case TERRAIN_CLIFF:
        local_places += ({"cliff"});
        break;
    case TERRAIN_VOLCANO:
        local_places += ({"rock", "rocks", "volcano"});
        break;
    case TERRAIN_LAKESHORE:
        local_places += ({"shore", "lakeshore"});
        break;
    case TERRAIN_COAST:
        local_places += ({"coastline", "coast"});
        break;
    case TERRAIN_RIVERBANK:
        local_places += ({"riverbank", "mud", "sand"});
        break;
    case TERRAIN_SALTBEACH:
        local_places += ({"sand", "beach"});
        break;
    case TERRAIN_FRESHBEACH:
        local_places += ({"sand", "beach"});
        break;
    case TERRAIN_SWAMP:
        local_places += ({"swamp"});
        break;
    case TERRAIN_MARSH:
        local_places += ({"marsh"});
        break;
    case TERRAIN_BOG:
        local_places += ({"bog"});
        break;
    case TERRAIN_THICKET:
        local_places += ({"thicket"});
        break;
    case TERRAIN_BUSH:
        local_places += ({"bush", "bushes"});
        break;
    case TERRAIN_JUNGLE:
        local_places += ({"jungle", "vines"});
        break;
    case TERRAIN_MIXEDWOOD:
    case TERRAIN_CONIFEROUS:
    case TERRAIN_DECIDUOUS:
        local_places += ({"forest", "tree", "trees"});
        break;
    case TERRAIN_NCAVETUNNEL:
        local_places += ({"cave", "tunnel"});   
        break;
    case TERRAIN_NCAVE:
        local_places += ({"cave"});
        break;
    case TERRAIN_NCAVELAKESH:
        local_places += ({"cave", "shore", "shoreline"});
        break;
    case TERRAIN_NCAVEMAGMA:
        local_places += ({"cave", "magma"});
        break;
    case TERRAIN_MINE:
        local_places += ({"mine"});
        break;
    case TERRAIN_ARTOPENLAVA:
        local_places += ({"lava"});
        break;
    case TERRAIN_ROAD:
        local_places += ({"road"});
        break;
    case TERRAIN_STREET:
        local_places += ({"street"});
        break;
    case TERRAIN_FIELD:
        local_places += ({"field", "fields"});
        break;
    case TERRAIN_GARDEN:
        local_places += ({"garden"});
        break;
    case TERRAIN_GRAVEYARD:
        local_places += ({"graves", "graveyard"});
        break;
    case TERRAIN_SEWER:
        local_places += ({"sewage", "sewer"});
        break;
    case TERRAIN_PATH:
        local_places += ({"path"});
        break;
    case TERRAIN_RUINS:
    case TERRAIN_INRUINS:
        local_places += ({"ruins"});
        break;
    case TERRAIN_TOMB:
        local_places += ({"tomb"});
        break;
    default:
        break;
    }
    herb_list = TERRAINSERVER->query_herbs(terrain);
    // Couldn't find any herbs so stop here.

    if (!sizeof(herb_list))
	return;
    i = -1;
    indx = (sizeof(herb_list) - 1);
    // Make sure we aren't trying to add more herbs than we have available
    num_herbs = (num_herbs > indx ? indx : num_herbs);
    while(++i < num_herbs)
    {
	if (seed)
	{
	    ran = random(indx, seed);
	    // Alter the seed a bit for more varied results
	    seed = seed * 5 / 2;
	}
	else
	    ran = random(indx);
	herbs += ({ herb_list[ran] });
	herb_list -= ({herb_list[ran]}); // To prevent duplications
	indx -= 1;
    }
    // Now we set everything up!
    set_up_herbs(herbs, local_places, search_time);
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
