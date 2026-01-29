/*
 * Room of the Old Road in Mirkwood.
 *
 */

#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";

/*
 * Function name: create_mirkwood_road_room
 * Description  : Create this room of the old road
 */
void create_mirkwood_road_room()
{
    // Force the randomized messages to always be the same for roads
    set_room_seed(43);
    set_mirkwood_location(LOCATION_EAST_PART);
    set_add_riverrun_far();
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the eastern part of Mirkwood Forest");

    add_long("Looming high above you, in a small clearing on the north " +
        "side of the road, is a massive stone monument. ",
        ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"monument","stone monument","massive monument","massive stone monument"}),
        "As you examine the monument closely, you notice that it was apparently " +
        "an ancient sign-post of sorts. While you can imagine that at one time, " +
        "the letters must have been bold and cleanly chiseled, now they have worn " +
        "and weathered with the passing years. However, they still appear to be " +
        "somewhat legible.\n", ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"writing","sign","sign-post","letters", "chiseled letters"}),
        "You can make out what appear to be Dwarven runes, which cover the " +
        "surface of this monument. You think that perhaps you could read " +
        "them.\n", ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"sanctuary"}),
        "The closest thing you can see to a sanctuary is the clearing " +
        "here.\n", ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"clearing"}),
        "There is a small clearing around the stone monument here. Strangely " +
        "enough, you do not see a sign of anyone maintaining it. Given how dense " +
        "the rest of Mirkwood is, you are a little surprised that the forest has " +
        "not overgrown this clearing as well.\n", ({LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_exit("r44", "east");
    add_exit("r42", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f47", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f48", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f49", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f47", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f48", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f49", "southeast");
}

public int read_sign() {
    if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_WIS, SS_LANGUAGE })) <= 0) {
        write("Try as you might, you cannot decipher these runes!\n");
        say(QCTNAME(TP) + " looks slightly confused.\n");
        return 1;
    }

    write("You decipher the runes and read the following:\n" +
        "Welcome friend, to the eastern edge of Greenwood the Great. " +
        "To the west, this road shall take you to the legendary " +
        "city of Khazad-Dum.\n" +
        "\n" +
        "To the east, this road shall lead you to Erebor and then " +
        "to the mines of the Iron Hills.\n"+
        "\n" +
        "Please enjoy the sanctuary to rest yourself upon this " +
        "great journey.\n");
}

public void
init()
{
    ::init();
    add_action(read_sign, "read");
}
