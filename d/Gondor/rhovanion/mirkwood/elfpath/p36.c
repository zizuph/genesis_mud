#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "../defs.h"


inherit MIRKWOOD_ELFPATH_DIR + "base";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit MIRKWOOD_LIB_DIR + "follow_river";

public void drink_message(string from);


void create_mirkwood_elfpath_room()
{
	set_room_seed(36);
	set_mirkwood_location(LOCATION_EAST_EDGE);

	::create_mirkwood_elfpath_room();

    add_long("Immediately to the west, an imposing set of stone doors " +
        "sit in the face of a cliff which overlooks the river before " +
        "you. The path you are walking on leads from those doors, across " +
        "a narrow wooden bridge, before trailing off to the southwest. A " +
        "much newer trail connects here, following the river east. ",
        LIGHT_ALL);

    add_item_light(({"door", "doors", "stone door", "stone doors"}),
        "This pair of stone doors has been set directly into the face " +
        "of a stone cliff which overlooks the forest river. A narrow " +
        "wooden bridge connects these doors to the path you are " +
        "currently walking on.\n", LIGHT_ALL);
    add_item_light(({"bridge", "wooden bridge", "narrow bridge"}),
        "Stretching across the river here is a narrow wooden bridge which " +
        "spans the rushing waters of the forest river below. The bridge " +
        "appears to lead directly into the side of a cliff where a " +
        "pair of stone doors stand guard.\n", LIGHT_ALL);
    add_item_light(({"cliff", "rocky cliff"}),
        "This rocky cliff rises up out of a deep canyon, reaching high " +
        "above the rushing waters of the forest river that cut through the " +
        "land below.\n", LIGHT_ALL);
    add_item_light(({"river", "forest river"}),
        "The rushing waters of the forest river have cut through the " +
        "land here, creating a deep canyon. The opposing cliff face " +
        "has a pair of stone doors which stare silently towards you " +
        "across a narrow wooden bridge. The river flows from the west " +
        "to the east, emptying out into Long Lake.\n", LIGHT_ALL);
    add_item_light(({"canyon", "deep canyon"}),
        "The forest river rushes along at the base of a deep canyon, which " +
        "winds its way deeper into Mirkwood forest to the northwest. The " +
        "steep slopes of the canyon make it impossible to follow the " +
        "river west from here.\n", LIGHT_ALL);

	set_add_wildlife();
    set_drink_from(({"forest river", "river"}));

    add_exit(MIRKWOOD_DIR + "elves/entrance", "west");
    add_exit("p35", "southwest");
    add_exit("p37", "east");
    add_exit("p36", "southeast", "@@block@@",2,1);

    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r04/f37", "northeast", "@@river@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r04/f36", "north", "@@river@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r04/f35", "northwest", "@@river@@",2,1);
        
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r20/f36", "south");   

    set_river_name("forest river");
    add_follow_direction(MIRKWOOD_DIR + "elfpath/p37", "east", 
        "downstream, following the new Elf Path to Esgaroth.");
  

}

void
init()
{
    ::init();
    init_drink();
    init_follow_river();
}

public void
drink_message(string from)
{
    write("You bend down and cup your hands to drink a mouthful of water from " 
        + "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}

int
river()
{
write("The forest river is too wide to cross here, you will have to go in " +
    "a different direction.\n");
return 1;
}

int
block()
{
write("It seems as if the forest river has flooded here, preventing " +
    "you from going any further east and leaving Mirkwood.\n");
return 1;
}