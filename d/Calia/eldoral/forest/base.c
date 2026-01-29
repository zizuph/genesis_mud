/*
 * base.c
 * 
 * This file is the baseroom for the forest on Eldoral Isle.
 *
 * Khail - Feb 24/97
 */
#pragma strict_types

#include "defs.h"

inherit "/std/room";
inherit SEERBASE;
inherit HERBMASTER;

string extra;

public int
player_knows_eldoral()
{
    if (TP->query_skill(SK_ELDORAL_CASTLE_NAME) &
        SK_CASTLE_NAME_VALUE)
        return 1;
    return 0;
}

/*
 * Function name: shore_msg
 * Description  : Just a little message delivered to players who 
 *                leave the forest onto the shore. Called by exit
 *                blocking function.
 * Arguments    : n/a
 * Returns      : 0
 */
public int
shore_msg()
{
    write("You break out of the treeline onto the shore.\n");
    return 0;
}

/*
 * Function name: create_forest
 * Description  : Turns this room into a forest.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_forest()
{
    set_short("in an ancient forest");
    set_long("You are within an ancient forest of countless " +
        "trees, ferns, and underbrush. " +
        "Far above your head soar the trunks of numerous trees " +
        "of varying species, though they seem to be primarily " +
        "firs of sorts. " +
        "Beneath the trees stretches out a knee-deep sea of green " +
        "where ferns cover masses of dried or decaying underbrush " +
        "littering the forest floor. " +
        (stringp(extra) ? extra : "") +
        "\n\n");
    add_item(({"forest", "trees"}),
        "The trees in this ancient forest appear to be evergreens of " +
        "sorts. They are tall, narrow trees with needled branches, and " +
        "dark, scaly bark. The thick, rich scent of sap assails your " +
        "senses, leaving you pleasantly refreshed.\n");
    add_item(({"ferns"}),
        "The forest floor is littered here and there with the smooth, even " +
        "green sheathe that a forest of ferns provides, all of even " +
        "height and shape, like some finely woven tapestry.\n");
    add_item(({"underbrush", "brush", "bushes"}),
        "Interspersed here and there among the ferns, a variety of bushes " +
        "form a tight network of underbrush, concealing the forest floor " +
        "from all but the tiniest creatures that skitter across the " +
        "ground beneath.\n");
    add_item(({"ground", "floor", "forest floor"}),
        "The actual floor of the forest is concealed from sight beneath " +
        "a sea of green ferns and underbrush.\n");
    add_item(({"sky"}),
        "The sky is hidden from your view by the veil of fog which " +
        "blankets the island.\n");
     add_item(({"mist", "fog"}),
         "In the upper reaches of the trees, a fine mist dances upon the " +
         "branches, caressing one tree gently, then moving to the next. " +
         "Fading from vision in one place, and reappearing in the next.\n");

  /* Add herbs to the room. */
    setup_my_herbs();
    reset_room();
}

/*
 * Function name: create_wall
 * Description  : Adds a description of the wall of the castle ruins
 *                in the specified direction.
 * Arguments    : where - The direction the wall lies in, i.e. 'east'.
 * Returns      : n/a
 */
public void
create_wall(string where)
{
    if (!extra)
        extra = "";

    extra += "A massive, crumbling wall stands to " +
        "the " + where + ", its jagged battlements resembling " +
        "a massive jaw which is missing several teeth. Here and there " +
        "along the base of the wall, the occasional pile of rubble has " +
        "crushed the plantlife and now takes its spot as a tombstone to " +
        "days gone by. ";

    add_item(({"wall", "massive wall", "crumbling wall"}),
        "The wall to the " + where + " appears to have stood there for " +
        "longer than you can imagine. The stone itself seems to have " +
        "begun to disintegrate into sand and silt from the ravages of " +
        "time and weather.\n");
    add_item(({"battlements"}),
        "Here and there along the top of the wall, worn battlements jut " +
        "up into the sky like rotten teeth on a beggar. Spaced quite " +
        "unevenly, you note that there are several gaps with holes torn " +
        "out of the wall itself where battlements might once have stood, " +
        "but have since fallen down from the top of the wall.\n");
    add_item(({"pile", "piles", "rubble"}),
        "Judging from their positions, the small piles of broken stone " +
        "are the remains of the missing battlements from the tops of the " +
        "walls. Some are relatively new, with the surrounding brush still " +
        "slumped with parts trapped beneath the stone, others appear " +
        "much older, with new plantlife growing up through the cracks in " +
        "the stone.\n");
}

/*
 * Function name: create_shore
 * Description  : Adds a shore to the room in the specified direction.
 * Arguments    : where - Direction the shore lies in, i.e. 'east'.
 * Returns      : n/a
 */
public void
create_shore(string where)
{
    if (!extra)
        extra = "";

    extra += "You find yourself just within the edge of the " +
        "treeline of the ancient forest. Through a few breaks " +
        "to the " + where + ", you can see still, black water " +
        "rolling gently in small waves across the pebbly shore. ";
    add_item(({"shore", "shoreline"}),
        "You can't see much of it through the trees, but it appears " +
        "to be a fairly unexciting shore comprised of pebbles and " +
        "the occasional bit of driftwood.\n");
    add_item(({"water", "lake"}),
        "Through the occasional break in the trees, you can see the calm, " +
        "dark waters of the lake vanishing in the distance beneath the " +
        "swirling grey mist which blankets its surface.\n");
}

/*
 * Function name: create_cliff
 * Description  : Adds a cliff to the room. Since cliffs only exist on
 *                the west-most part of the island, a direction is not
 *                needed.
 * Arguments    : where - String saying which direction the cliff
 *                        lies in, i.e. 'northwest'. Defaults to 'west'
 *                        if not set.
 * Returns      : n/a
 */
public varargs void
create_cliff(string where = "west")
{
    if (!extra)
        extra = "";

    extra += "The forest to the " + where + " comes to an " +
        "abrupt halt, as the trees drop away atop a sharp cliff. ";
    add_item(({"cliff"}),
        "To the " + where + ", a sharp cliff plummets straight " +
        "down into the cold waters of the lake. A quick glance " +
        "over the edge puts an end to any thoughts of climbing, " +
        "as the rock face is completely sheer and without handholds.\n");
}

/*
 * Function name: create_ravine
 * Description  : Adds a ravine to the room. Since the ravine lies only
 *                in the northmost part of the island, a direction
 *                is not needed.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_ravine()
{
    if (!extra)
        extra = "";

    extra += "The forest comes to a sudden halt to the north, its " +
        "contours broken by a ravine that slashes east to west across " +
        "the northern parts of " +
        (player_knows_eldoral() ? "Eldoral Isle. " : "this island. ");
    add_item(({"ravine"}),
        "The ravine is almost a small canyon, in that it slashes across the " +
        "island from the east to the west, yet is fairly wide at the " +
        "bottom, at least wide enough for a small, dark forest to have " +
        "grown and died. " +
        "It's not very deep, but the walls of the ravine are completely " +
        "sheer with no visible handholds making climbing in or out " +
        "impossible.\n");
    add_item(({"dark forest"}),
        "The forest in the ravine is somewhat different from the one up " +
        "here. While it looks like the trees were one similar, they are " +
        "now skeletal remains of what they once were, with needle-bare " +
        "branches broken and sagging beneath the weight of long beards of " +
        "bluish-grey moss.\n");
}

/*
 * Function name: create_special
 * Description  : Add a special feature to the room.
 * Arguments    : which - Integer representing which of the available
 *                        features to add.
 *                where - The direction the feature lies in.
 * Returns      : n/a
 */
public void
create_special(int which, string where)
{
    if (!extra || !strlen(extra))
        extra = "";

    switch(which)
    {
        case BUILD_RUINS:
            extra += "The sprawling remains of a stone building " +
                "lie to the " + where + ", giving no hint as " +
                "to its nature or origin, it now is little " +
                "more than a rectangular pile of rubble. ";
            add_item(({"remains", "sprawling remains", "rubble",
                "pile", "building", "stone building"}),
                "Now little more than a high, rectangular pile " +
                "of broken rubble, this was once a fairly thickly " +
                "constructed building, but its purpose eludes " +
                "you.\n");
            break;
        case CATH_RUBBLE:
            extra += "Before you, to the " + where + ", huge, " +
                "jagged chunks of stone and masonry lie piled " +
                "atop the splintered remains of several large " +
                "trees. It appears as if the wall or one of " +
                 "the upper buildings of these ruins collapsed " +
                "and took down a sizeable portion of the forest " +
                "here near the wall. The mess is completely " +
                "impassable. ";
            add_item(({"stone", "chunks", "masonry", "mess"}),
                "Broken pieces of grey stone, they were once " +
                "probably part of a wall of some sort, but now " +
                "all they do is crush the trees that happened " +
                "to be beneath them when they fell.\n");
            add_item(({"remains", "remains of trees"}),
                "It looks like this pile of stone might have " +
                "fallen down in one big piece, as the trees " +
                "around it are completely splintered and flattened, " +
                "and poking out from beneath the stones at odd " +
                "angles.\n");
            break;
        case SHRINE:
            extra += "A strange stone building rises to the " +
                where + ", tall, dark, and with simple, straight " +
                "walls, with no carvings or decorations whatsoever. " +
                "Oddly enough, it still seems to be almost " +
                "entirely intact, with little or no signs of " +
                "the passage of time. ";
            if (where == "south")
                extra += "You notice a simple stone archway " +
                    "appears to provide access to the interior of " +
                    "the strange building. ";
            add_item(({"building", "stone building"}),
                "Before you, to the " + where + ", rises a plain " +
                "stone building of some sort. In fact the only " +
                "thing even remotely interesting is that it seems " +
                "largely untouched by the ravages of time.\n");
            add_item(({"wall", "walls"}),
                "Plains surfaces, which appear to be made out of " +
                "single slabs of stone.\n");
            add_item(({"archway", "stone archway"}),
                "In the otherwise solid stone north wall of " +
                "the small building stands a narrow archway. " +
                "Little more than a hole cut through the stone, " +
                "it's adorned only by a gracefully arching frame " +
                "chiseled out of the stone.\n");
            add_item(({"frame","arching frame", "archway frame"}),
                "The frame of the archway is carved carefully " +
                "out of the stone around the opening, " +
                "it possibly once contained an actual door, " +
                "but if that was true, the door itself was " +
                "reclaimed by the forest long ago.\n");
            break;
        case SINKHOLE:
            extra += "The ground to the " + where + " seems to " +
                "have caved in upon itself, opening a massive " +
                "sinkhole in the forest floor here. In itself " +
                "there's nothing particularly dangerous about it, " +
                "but it's completely impassable. ";
            add_item(({"sinkhole"}),
                "The ground on the forest floor here appears to " +
                "fallen into a large sinkhole of some sort. Even " +
                "a large number of trees lie broken at the bottom of the " +
                 "sinkhole. You take a good look, but don't see " +
                "anything down there even remotely interesting " +
                "enough to merit attempting a climb.\n");
            break;
        case BOULDERS:
            extra += "The ground " + where + " of here is host to " +
                "several very large boulders; further passage " +
                "that way is impossible. ";
            add_item(({"boulder", "boulders","large boulders"}),
                "The boulders are quite common, despite their " +
                "size, just large masses of some granite-like " +
                "stone that have been lying here for countless " +
                "years.\n");
            break;
        case TOW_RUBBLE:
            add_item(({"buildings", "portion"}),
                "It's through the forest off to the west, and " +
                "appears to be a tower.\n");
            add_item(({"wall"}),
                "Large pieces are missing out of the walls of the " +
                "ruins here, crushed out of place by the collapse " +
                  "of some other ruins across the wall. The stone " +
                "which once filled those gaps now lies across " +
                "the forest floor around the base of the wall, and " +
                "form the basis of a rather impenetrable fence.\n");
            add_item(({"rubble", "stones", "blocks"}),
                "Nothing spectacular, these large blocks of grey " +
                "stone were once part of the walls of the ruins, " +
                "however time and misfortune have brought them " +
                "much closer to earth over the years.\n");
            break;
    }
}
