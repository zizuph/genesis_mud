/*
 * monk_herbg_se.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  updated 6/21/97 by Amelia:
*  to include standard herbsearch routines,
*  to include reset_room,
*  to add a wider variety of herbs--each time room is 
*  loaded, a random set of herbs from roke_herbs.h
*  is added
*  set_short added
*
*  removed references to Earthsea...9/2/97 Amelia
*  (substituted ~amelia/copies)
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room.c";
inherit ROKEDIR + "lib/herbsearch.c";

#include <macros.h>
#include "/d/Roke/amelia/copies/herb_sets/roke_herbs.h"
//FIXA

void
create_room()
{
    set_short("herb garden");
    set_long("A well kept herb garden. " +
             "The woodsy perfume of fresh blooms fills the air " +
             "of this quaint little garden. Its lush herbs and " +
             "flowers appear to be in full bloom. In the middle of " +
             "the garden there is a well. The garden continues to " +
             "the west, and is bordered by thick bushes, but it " +
             "seems to be possible to get out to the east.\n");

    add_exit("p6", "east");
    add_exit("monk_herbg_sw", "west");
    add_exit("monk_herbg_ne", "north");
    add_exit("monk_herbg_well", "northwest");
    OUTSIDE;

    set_up_herbs(TO->select_herb_files(GARDEN_HERBS),
                 GARDEN_LOCATIONS, 3);

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("flowers", "There are lots of different types of " +
             "flowers growing everywhere.\n");
    add_item("herbs", "You don't see any herbs directly. Maybe " +
             "you should search for them.\n");
    add_item("bushes", "The bushes seem thin enough to " +
             "to walk through to the east.\n");
    add_item("ground", "The ground is covered in grass " +
             "and sweet-smelling herbs.\n");
    reset_room();
}
