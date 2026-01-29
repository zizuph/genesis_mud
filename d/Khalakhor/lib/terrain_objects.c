/* File         : /d/Khalakhor/std/room/terrain_objects.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : Feb 08, 2002         
 * Purpose      : This file is included in the standard room and 
 *                the call to set_up_terrain in the create_room
 *                function automatically adds add_items and more
 *                importantly, objects to be searched for.
 * Related Files: 
 * Comments     :
 * Modifications:
 */

#pragma no_clone

public void
set_up_terrain()
{
    int terrain;

    terrain = (this_object()->query_terrain());
    // Add add_items, searches based on the terrain
    switch(terrain)
    {
    case TERRAIN_OCEAN:
//        local_places += ({"ocean", "water", "sea"});
        break;
    case TERRAIN_UNDERSEA:
    case TERRAIN_UNDERLAKE:
//        local_places += ({"water"});
        break;
    case TERRAIN_BAY:
//        local_places += ({"bay", "water"});
        break;
    case TERRAIN_LAKE:
//        local_places += ({"lake", "water"});
        break;
    case TERRAIN_POND:
//        local_places += ({"water", "pond"});
        break;
    case TERRAIN_RIVER:
//        local_places += ({"water", "river"});
        break;
    case TERRAIN_STREAM:
//        local_places += ({"water", "stream"});
        break;
    case TERRAIN_PLAIN:
	    add_item("plains", "Yes, they are plains.\n");
	    add_item("grass", "There's plenty of grass.\n");
	    add_search(({"here for stones", "plains for stones"}), 10,
	      "/d/Khalakhor/common/obj/stone", -2);
	    break;
    case TERRAIN_MOOR:
//        local_places += ({"moors"});
        break;
    case TERRAIN_GLACIER:
//        local_places += ({"ice", "glacier"});
        break;
    case TERRAIN_TUNDRA:
//        local_places += ({"tundra"});
        break;
    case TERRAIN_DESERT:
//        local_places += ({"sand", "desert"});
        break;
    case TERRAIN_SCRUB:
//        local_places += ({"scrub"});
        break;
    case TERRAIN_BADLAND:
//        local_places += ({"badlands"});
        break;
    case TERRAIN_WASTELAND:
//        local_places += ({"wasteland"});
        break;
    case TERRAIN_MOUNTAIN:
//        local_places += ({"rock", "rocks", "mountain"});
        break;
    case TERRAIN_HILL:
 //       local_places += ({"hills", "hill", "grass"});
        break;
    case TERRAIN_CLIFF:
 //       local_places += ({"cliff"});
        break;
    case TERRAIN_VOLCANO:
 //       local_places += ({"rock", "rocks", "volcano"});
        break;
    case TERRAIN_LAKESHORE:
 //       local_places += ({"shore", "lakeshore"});
        break;
    case TERRAIN_COAST:
 //       local_places += ({"coastline", "coast"});
        break;
    case TERRAIN_RIVERBANK:
//        local_places += ({"riverbank", "mud", "sand"});
        break;
    case TERRAIN_SALTBEACH:
//        local_places += ({"sand", "beach"});
        break;
    case TERRAIN_FRESHBEACH:
//        local_places += ({"sand", "beach"});
        break;
    case TERRAIN_SWAMP:
//        local_places += ({"swamp"});
        break;
    case TERRAIN_MARSH:
//        local_places += ({"marsh"});
        break;
    case TERRAIN_BOG:
 //       local_places += ({"bog"});
        break;
    case TERRAIN_THICKET:
 //       local_places += ({"thicket"});
        break;
    case TERRAIN_BUSH:
//        local_places += ({"bush", "bushes"});
        break;
    case TERRAIN_JUNGLE:
//        local_places += ({"jungle", "vines"});
        break;
    case TERRAIN_MIXEDWOOD:
    case TERRAIN_CONIFEROUS:
    case TERRAIN_DECIDUOUS:
 //       local_places += ({"forest", "tree", "trees"});
        break;
    case TERRAIN_NCAVETUNNEL:
//        local_places += ({"cave", "tunnel"});   
        break;
    case TERRAIN_NCAVE:
//        local_places += ({"cave"});
        break;
    case TERRAIN_NCAVELAKESH:
//        local_places += ({"cave", "shore", "shoreline"});
        break;
    case TERRAIN_NCAVEMAGMA:
 //       local_places += ({"cave", "magma"});
        break;
    case TERRAIN_MINE:
//        local_places += ({"mine"});
        break;
    case TERRAIN_ARTOPENLAVA:
 //       local_places += ({"lava"});
        break;
    case TERRAIN_ROAD:
 //       local_places += ({"road"});
        break;
    case TERRAIN_STREET:
 //       local_places += ({"street"});
        break;
    case TERRAIN_FIELD:
 //       local_places += ({"field", "fields"});
        break;
    case TERRAIN_GARDEN:
 //       local_places += ({"garden"});
        break;
    case TERRAIN_GRAVEYARD:
 //       local_places += ({"graves", "graveyard"});
        break;
    case TERRAIN_SEWER:
 //       local_places += ({"sewage", "sewer"});
        break;
    case TERRAIN_PATH:
 //       local_places += ({"path"});
        break;
    case TERRAIN_RUINS:
    case TERRAIN_INRUINS:
 //       local_places += ({"ruins"});
        break;
    case TERRAIN_TOMB:
//        local_places += ({"tomb"});
        break;
    default:
        break;
    }
}
