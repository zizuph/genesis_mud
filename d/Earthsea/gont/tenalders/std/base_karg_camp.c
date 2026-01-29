/*
 *
 * Base Karg Camps
 *
 * Ckrik June 1998.
 *
 * 
 */

#pragma strict_types
#pragma no_clone

inherit "/d/Earthsea/std/room.c";

#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

private string extra = "\n";

public void create_camp() { }

public void
add_long(string str)
{
    extra = str;
}

public string
query_extra_long()
{
    return extra;
}

public string
query_camp_long(){
    return "A camp in the forest. Someone seems to have setup up " +
        "camp here and in the process, raped and pillaged this once " + 
        "virgin forest. Camp fires, some with the day's catch " +
        "roasting on top, litter the camp. " +
        "Refuse is scattered all around the area. Judging from " +
        "what is going on here, the occupants of this camp do " +
        "not seem too friendly. Something tells you that this is " +
        "not a good place for you to stay. " +
        query_extra_long(); 
}

public nomask void
create_earthsea_room()
{    
    set_short("A camp in the forest");
    set_long(query_camp_long());
    add_item((({"forest", "trees", "tree", "forests"})),
        "There is not much of that here now, the occupants of " +
        "of this camp chopped down all the trees in the vicinity.\n");
    add_item((({"fire", "fires", "catch"})),
        "You see meat roasting over the fire.\n");
    add_item((({"refuse", "trash", "litter"})), "What a mess!\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    create_camp();
}
