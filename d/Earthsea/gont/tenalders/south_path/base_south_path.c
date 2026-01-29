/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include <stdproperties.h>
#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h";
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

public void create_gloomy_forest() {}

public void
create_herb_room()
{
    set_short("Mountain path");
    set_long("@@long_desc");
    set_tell_time(120);
    add_tell("You feel someone staring at you.\n");
    add_tell("Somewhere in the distance a wolf howls.\n");
    add_tell("A dense cloud of fog drifts across the path.\n");
    add_tell("Dense clouds of mist swirl around you like a live thing.\n");
    add_tell("Suddenly you duck, as an arrow whizzes past your " +
        "head and lands in the bushes to your left.\n");
    add_item((({"fog", "patches"})),
        "Patches of pea-soup fog make visibility poor.\n");
    add_item((({"branches", "thick branches"})),
        "The network of branches is very dense here, blocking " +
        "much light from coming through.\n");
    add_item((({"forest", "trees", "pine trees"})),
        "The trees loom over you, blocking out light. " +
        "Moisture drips from the tips of needles and branches.\n");
    add_item((({"fog", "patches of fog", "eerie feeling"})),
        "Patches of fog drift across the path and keep " +
        "visibility to a minimum.\n");
    add_item((({"undergrowth", "dense tangle"})),
        "Alongside both sides of the path dense undergrowth in " +
        "the form of bushes, briars and vines makes a perfect spot " +
        "for an ambush.\n");
    add_item("mist", "The mist seems to have shapes and sounds in " +
        "it, causing the hair on the back of your neck to rise.\n");
    add_item((({"forest", "old forest"})),
        "The old forest climbs the flank of the mountainside, " +
        "and tall dark trees here block out the light.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    create_gloomy_forest();
    reset_room();
}

public string
long_desc()
{
    switch(random(4))
    {
        case 0:
            return "The dark evergreen forest is dense and impenetrable. " +
                "Gloomy fog permeates it all through the lower branches. " +
                "You seem to hear echoes of footsteps, and now and " +
                "again you could swear there are voices in the mist. ";
        break;
        case 1:
            return "The heavy branches from the dark evergreen trees " +
                "sway slightly in the mountain breezes, as condensed " +
                "moisture drips from them onto your face. The breezes " +
                "cause the mist to swirl around you, obstructing your " +
                "view. ";
        break;
        case 2:
            return "You look up and all you can see is the dense network " +
                "of dark larch and pine branches, looming over your head. " +
                "Just enough light filters through so that you can make " +
                "your way ahead, but you have the feeling nothing will " +
                "help you if you stray from the path. ";
        break;
        default:
            return "Thick branches block light from filtering through. " +
                "Patches of fog drift across the path and lend an eerie " +
                "feeling to the tall dark pine trees, which cast shadows " +
                "all around you. There is a dense tangle of undergrowth " +
                "to each side of the path. ";
        break;
    }
}
