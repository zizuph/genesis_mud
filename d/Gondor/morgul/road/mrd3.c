/*
 *	/d/Gondor/morgul/road/mrd3.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/road/mroad.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

public string  enter_hole();

public string
short_desc()
{
    return "by the white bridge in the Morgul Vale";
}

public string
long_desc()
{
    return BSN(
    "You are standing just north of the white bridge, where the "+
    "road, gleaming faintly, passes over the stream in the midst of the "+
    "valley, going on south, winding up towards the dark gate of Minas "+
    "Morgul. The road continues west out of the vale. North of the " +
    "road a rock wall is running alongside the road.");
}

public void
create_area_room()
{
    add_item(({"vale","imlad morgul","morgul vale"}), BSN(
    "The Imlad Morgul, or Vale of Black Sorcery, continues further "+
    "east, narrowing to a dark cleft in the mountain-range. A foul-smelling "+
    "stream runs in the middle of the valley, and the walls of Minas Morgul "+
    "stand upon a hill on the further side. "));
    add_item(({"gate","walls","mouth"}), BSN(
    "The gate is dark in the glowing walls of the city; a black "+
    "mouth opening in the outer circle of the northward walls. "));
    add_item(({"city","tower","glow"}), BSN(
    "The pulsating glow of the city is almost enchanting to "+
    "look upon, and the luminous Tower of the Moon fills you with a desire "+
    "to run up the gleaming road to the dark gate. "));
    add_item("bridge","The white bridge gleams pale above the dark stream.\n");
    add_item(({"stream","river","morgulduin"}), 
    "The stream radiates a foul smell almost unbearable to breathe in.\n");
    add_item(({"wall","rock wall"}), BSN(
    "North of the road, a rock wall is running alongside the road, " +
    "probably to prevent rocks sliding down the steep slopes of the " +
    "mountains north of the road from tumbling onto the road. " +
    "Close to where the rock wall follows the road's turn southward, " +
    "you can make out a small gap in the wall."));
    add_item(({"hole","opening","gap"}), BSN(
        "Close to where the rock wall follows the road's turn southward, " +
        "a small hole allows passage through the rock wall."));
    add_cmd_item( ({"hole","opening","gap"}), "enter", enter_hole);
    add_item(({"road","ground"}), BSN(
        "The road continues north of the Morgulduin to the west, leading " +
        "out of the valley. To the south, it crosses the river and runs " +
        "up towards the gates of Minas Morgul."));
    add_exit(MORGUL_DIR +"road/mmead2",  "east",      block_npc,   1);
    add_exit(MORGUL_DIR +"road/mbridge", "south",     check_allow, 3);
    add_exit(MORGUL_DIR +"road/mmead1",  "southwest", block_npc,   1);
    add_exit(MORGUL_DIR +"road/mrd2",    "west",      stop_escape, 3);

    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
        ({"bank", "flat", "ground", "meadow"}), 3);

    reset_room();
    enable_reset(200);
}

public string
enter_hole()
{
    set_dircmd("hole");
    write("You crawl through the hole in the stone-wall beside the road.\n");
    say(QCTNAME(TP)+" crawls through a hole in the stone-wall beside the road.\n", TP);
    TP->move_living("M", STAIRS_DIR + "path1", 1);
    say(QCTNAME(TP) + " arrives.\n");
    return "";
}
