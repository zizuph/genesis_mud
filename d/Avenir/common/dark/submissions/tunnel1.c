/*
 * File:          /d/Avenir/common/dark/submissions/tunnel1.c
 * Creator:       Alfs
 * Date:          Tue Jun 20 14:32:42 2000
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#13040
 * Comments:      
 *                Dark and damp tunnel call unfavourable
 *                feeling
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("tunnel");
    set_long("A darkened tunnel, its walls covered with fungi, "
        + "the the ground slick with fetid water and moss. "
        + "The tunnel leads east and a haunting looking cave "
        + "is to the southwest. There are two obvious exits: "
        + "east, southwest and cave.\n");

    add_item(({"wall"," walls"}),
        "Worn smooth, but not natural tunnels.\n");
    add_item(({"fungi"}),
        "Foul smelling fungus that decays all matter.\n");
    add_item(({"ground"}),
        "the dusted ground slick with fetid water and moss.\n");
    add_item(({"dust"}),
        "the dust equable filled ground and maybe hide some "
        + "surprises.\n");
    add_item(({"water"}),
        "little Pool is filled with Fetid and contaminated "
        + "with dirt and minerals water.\n");
    add_item(({"pool"}),
        "little Pool is filled with Fetid and contaminated "
        + "with dirt and minerals water.\n");
    add_item(({"dirt"}),
        "dirt contain remains of little animals and chips "
        + "of stones.\n");
    add_item(({"remains"}),
        "it's looks like don't interesting.\n");
    add_item(({"rock"}),
        "A big rock seem grey and cold, he looks like guard "
        + "who siting ahead cave.\n");
    add_item(({"cave"}),
        "The cave seems dark and leading down, but entrance "
        + "is filled with big gray rock.\n");
    add_item(({"scarp"}),
        "little and yellow, this paper scarp contains many "
        + "old and shadowy runes.\n");
    add_item(({"runes"}),
        "You don't recognize any rune, and dont known who "
        + "may help You reading note.\n");
    add_cmd_item(({"dust"}),
        ({"search"}),
        "between old remains anchips You found a little "
        + "scarp of old note.\n");
    add_cmd_item(({"rock"}),
        ({"push"}),
        "You badly pushing this big boulder, but he easili "
        + "moves left and open entrance to cave.\n");
    add_cmd_item(({"water"}),
        ({"drink"}),
        "thin smelling water uncommonly refresh You.\n");


}
