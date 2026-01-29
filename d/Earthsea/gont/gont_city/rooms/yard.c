/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
 */

#pragma strict_types
#pragma no_clone

#include <stdproperties.h>

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"

#define DOOR "/d/Earthsea/gont/gont_city/obj/house_out"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Yard outside a wooden house");
    set_long("You find yourself in a small yard outside "+
        "a wooden two-story house that is just to the east. "+
        "A bit off the beaten track and away from the bustle of "+
        "the city, this yard is filled with herbs and flowers.\n");
    add_item((({"herbs", "border", "flowers" })),
        "Flowers planted around the borders of the yard and "+
        "next to the house make it a very pleasant scene.\n");
    add_item((({"house", "wooden house"})),
        "A small two-story wooden house stands just to the east, "+
        "set aside from the hustle and bustle of the city.\n");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_exit("city_street/city_road5", "west");
    clone_object(DOOR)->move(this_object(), 1);
    reset_room();
}
