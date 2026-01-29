#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";
inherit "/d/Earthsea/gont/tenalders/sys/river_water";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <stdproperties.h>

public void
create_herb_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("Gravel path");
    set_long("The path emerges from the forest, opening out " +
        "to a village to the northwest. The rushing white " +
        "water of the river Ar plummets down the mountain to the " +
        "east. To the southwest the ancient evergreen forest looms " +
        "darkly. To the southeast the path runs along the riverbank.\n");
    add_item("village", "From here you can see a number of " +
        "small, mushroom-shaped huts that comprise the small village.\n");
    add_item((({"briars", "bushes", "cedar bushes", "undergrowth",
        "dense undergrowth"})),
        "As it descends into the forest, along both sides of the " +
        "path the forest vegetation is dense and smells of cedar " +
        "and pine.\n");
    add_item((({"path", "gravel path"})),
        "You see to the northwest where the path leads into a " +
        "village comprised of a group of small thatch-covered " +
        "huts.\n");
    add_item((({"water", "rushing water","river"})),
        "You hear the sound of rushing water, like a fast-flowing " +
        "river, coming from the southeast.\n");
    add_item((({"forest", "evergreen forest"})),
        "The ancient evergreen forest, with tall larches and pine " +
        "trees, descends the mountain flank to the south and " +
        "west\n.");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("../village/se5", "northwest");
    add_exit("south_path_2", "southeast");
}

public void 
init()
{
    ::init();
    add_action(drink_water, "drink");
    add_action(water_animal, "water");
}
