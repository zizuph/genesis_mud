/*
 * shrine_base.c
 *
 * Baseroom used in creation of the small shrines in
 * the forest.
 * 
 * Khail - Feb 24/97
 */
#pragma strict_types

#include "defs.h"

inherit "/std/room";
inherit SEERBASE;

/*
 * Function name: create_shrine
 * Description  : Turn this room into a shrine.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_shrine()
{
    set_short("inside a small building");
    INSIDE;
    add_prop(ROOM_I_NO_CLEANUP, 1);
    DARK;

    add_item(({"ceiling", "roof", "slab"}),
        "The roof of the building is quite plain, it looks to " +
        "be a single slab of stone laid horizontally across the " +
        "equally plain stone walls.\n");
    add_item(({"wall", "walls"}),
        "The walls of the building are unremarkable, simple " +
        "stone slabs which are probably embedded down into the " +
        "ground. The only remarkable thing is that they are " +
        "composed of just one massive slab per wall. They must " +
        "be incredibly heavy.\n");
    add_item(({"stone", "slabs"}),
        "The stone slabs are a bit strange, or rather stranger " +
        "than the other stone found on this island. Everywhere " +
        "else you see nothing but some sort of grey, granite" +
        "-like material, but this stone is much darker, almost " +
        "black.\n");
    add_item(({"floor", "ground"}),
        "The ground appears to actually be a dirt floor, " +
        "atop of which a thick layer of reddish-brown needles " +
        "that have dried out, fallen from trees and been blown inside.\n");
    add_item(({"needles"}),
        "The ground is carpeted by a thick layer of needles " +
        "that have dried up and blown inside by the wind.\n");
    add_item(({"archway"}),
        "A simple stone archway, cut into the wall slab to the " +
        "north, appears to be the only means of exiting this " +
        "structure.\n");

    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"floor", "ground", "dirt",
        "needles"}));
}
                
