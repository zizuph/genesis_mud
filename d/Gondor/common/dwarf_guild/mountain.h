/*
 * /d/Gondor/common/dwarf_guild/mountain.h
 *
 * This file should be included in the create_room() function in any room
 * that you like some descriptions of the mountains. Include this file
 * before any redefinitions of descriptions that you may want to add.
 *
 * /Mercade, 18 January 1994
 *
 * Revision history:
 */

/*
 * The following "items" are described in this file:
 *
 * - mountain, mountains, blue mountains, ered luin
 * - floor, ground, path
 * - grass
 * - bush, bushes
 * - tree, trees
 * - wall, walls, slope
 * - rock, rocks, stone, stones
 * - top, tops, peak, peaks
 */

/*
 * We need this file for the BSN macro. This file is probably already
 * included in the main file, but we'd better be sure about it.
 */
#include "/d/Gondor/defs.h"

add_item( ({ "mountain", "mountains", "blue mountains", "ered luin" }),
    BSN("The mountain range you are in is called Ered Luin or Blue " +
    "Mountains. It is a very large range of medium-sized mountains. They " +
    "are overgrown with trees and bushes and you see rocks on several " +
    "places."));

add_item( ({ "tree", "trees" }),
    BSN("There are many trees on the slope. They are rather tall."));

add_item( ({ "bush", "bushes" }),
    BSN("All over the mountains you see low bushes. They are hard to " +
    "go through and look rather spined."));

add_item( ({ "floor", "ground", "path" }),
    BSN("The path is rocky. On it you see little vegetation, save some " +
    "grass."));

add_item( ({ "grass" }),
    BSN("It is green."));

add_item( ({ "wall", "walls", "slope" }),
    BSN("The mountain walls are not steep at all. There is much vegetation " +
    "on them. You see trees and bushes."));

add_item( ({ "rock", "rocks", "stone", "stones" }),
    BSN("Several rocks are lying all over the ground. They are of dark and " +
    "cold stone."));

add_item( ({ "top", "tops", "peak", "peaks" }),
    BSN("Some mountain tops can be seen from this position. They are " +
    "rather high and some are covered in snow."));
