/*
 * File:          /d/Avenir/common/dark/submissions/tunnel.c
 * Creator:       Alfs
 * Date:          Tue Jun 20 12:37:12 2000
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#34342
 * Comments:      
 *                A darkened tunnel, its walls covered with
 *                fungi, the the ground slick with fetid water
 *                and moss.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("tunnel");
    set_long("A darkened tunnell, its walls covered with fungi, "
        + "the the ground slick with fetid water and moss. "
        + "The tunnel leads east and a haunting looking cave "
        + "is to the southwest. There are two obvious exits: "
        + "east and southwest.\n");

    add_item(({"walls"}),
        "Worn smooth, but not natural tunnels.\n");
    add_item(({"fungi"}),
        "Foul smelling fungus that decays all matter.\n");
    add_item(({"water"}),
        "Fetid and contaminated with dirt and minerals.\n");
    add_item(({"moss"}),
        "Its is a foul blackish green moss.\n");
    add_item(({"rock"}),
        "The rock seem could and solid.\n");
    add_item(({"floor"}),
        "A gray, dusty floor contains many remains of small "
        + "animals.\n");
    add_item(({"remains"}),
        "The remains don't look interesting.\n");
    add_item(({"dust"}),
        "The dust is equable and maybe hide some surprise.\n");
    add_item(({"scrap"}),
        "The scrap contain some words, but You don't "
        + "recognise tongue.\n");
    add_item(({"ceiling"}),
        "The ceiling seem high and natural.\n");
    add_item(({"cave"}),
        "The cave is hide with big rock.\n");
    add_cmd_item(({"moss","fungi","water","walls"}),
        ({"search"}),
        "Your search reveals nothing special.\n");
    add_cmd_item(({"dust"}),
        ({"search"}),
        "You find a scrap of old note.\n");


}
