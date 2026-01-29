/*
 * /d/Gondor/common/dwarf_guild/cavedesc.h
 *
 * This file should be included in the create_room() function in any room
 * that you like some descriptions of the rocky cave. Include this file
 * before any redefinitions of descriptions that you may want to add.
 *
 * /Mercade, 9 January 1994
 */

/*
 * The following "items" are described in this file:
 *
 * - floor, ground
 * - cave, caves as VBFC to long()
 * - wall, walls
 * - ceiling
 * - rock, rocks, stone, stones
 * - torch, torches, stand, stands, bracket, brackets, torch stand,
 *   torch stands, torchstand, torchstands
 */

/*
 * We need this file for the BSN macro. This file is probably already
 * included in the mail file, but we'd better be sure about it.
 */
#include "/d/Gondor/defs.h"

add_item( ({ "floor", "ground" }),
    BSN("The floor of this cave is very rocky indeed. It was hewn out of " +
    "solid rock a long time ago and it is remarkably smooth, like the " +
    "walls of this cave. No specific details can be found on the ground."));

add_item( ({ "cave", "caves" }), "@@long@@");

add_item( ({ "wall", "walls" }),
    BSN("The walls of this cave are very smooth even though they are hewn " +
    "out of rock a long time ago. There is a very beautiful structure " +
    "visible in the walls."));

add_item( ({ "ceiling" }),
    BSN("In contrast with the floor and the walls, the ceiling of this " +
    "cave has bulges. But then, no dwarf will even dance on the ceiling."));

add_item( ({ "rock", "rocks", "stone", "stones" }),
    BSN("This cave is hewn out of solid rock. The walls, ceiling and floor " +
    "are therefore rocky and cold."));

add_item( ({ "torch", "torches", "stand", "stands", "bracket", "brackets",
    "torch stand", "torch stands", "torchstand", "torchstands" }),
    BSN("Several torches are in brackets, secured to the wall. They shed " +
    "some light on the dark walls surrounding you."));
/*
 * Command items are not added at the end of the localcmd set, so they might
 * block normal torches.
 *
add_cmd_item( ({ "torch", "torches", "all" }), ({ "light", "extinguish" }),
    BSN("The torchstands are mounted too high on the wall. You cannot " +
    "reach the torches in it."));
 */
