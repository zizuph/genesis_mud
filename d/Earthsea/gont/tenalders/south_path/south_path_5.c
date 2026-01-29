/*
 * coded by Amelia 6/1/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";
inherit "/d/Earthsea/gont/tenalders/sys/river_water";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <macros.h>
#include <stdproperties.h>

public void
create_herb_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("Mountain path");
    set_long("A mountain path. You are walking along a " +
        "whitewater river, the Ar, that rushes down the steep mountain. " +
        "The path runs along a riverbank, and to the west is a " +
        "thick forest beyond a bank of bushes. " +
        "To the east the river is wide and swift-flowing. Beyond it " +
        "is more dense forest, flanking the side of the mountain.\n");
    add_item((({"water", "whitewater", "whitewater river",
        "Ar", "river"})),
        "The river Ar rushes down the steep mountainside, its waters " +
        "cold, white, and frothy from melted snow.\n");
    add_item((({"forest", "ancient pine trees", "pine trees",
        "trees"})),
        "The old forest towers to the west of you, ascending the " +
        "steep mountain.\n");
    add_item((({"bushes", "bank of bushes"})),
        "There is a thick bank of bushes directly to your west. " +
        "On closer examination, there seems to be a spot where " +
        "you can enter them.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);
    add_exit("south_path_4", "northwest");
    add_exit("south_path_6", "southeast");
    set_tell_time(90);
    add_tell("Suddenly an arrow whizzes past your head and " +
        "lands in the bushes beyond the path.\n");
    add_tell("The hair on the back of your neck rises, and you " +
        "can feel someone staring at you.\n");
}

public int
enter_bushes(string str)
{
    object tp = this_player();

    if(str == "bushes")
    {
        write("Down on your hands and knees, you crawl into the " +
            "bushes.\n");
        tell_room(this_object(), QCTNAME(tp) +
            " gets down on all fours and climbs into the bushes.\n",
            ({ tp }));
        tp->move_living("M",
            "/d/Earthsea/gont/tenalders/south_path/bushes", 1);
        tell_room(environment(tp), QCTNAME(tp) + " crawls in.\n",
            ({ tp }));

        return 1;
    }

    return notify_fail("Enter what?\n");
}

public void
init()
{
    ::init();
    add_action(enter_bushes, "enter");
    add_action(drink_water, "drink");
    add_action(water_animal, "water");
}
