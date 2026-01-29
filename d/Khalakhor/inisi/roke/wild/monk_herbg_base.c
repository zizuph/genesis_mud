/*
 * monk_herbg_base.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * This base room was created during that move.
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
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include <macros.h>

inherit "/std/room.c";
inherit HERBSEARCH;

public void
setup_herbgarden()
{
    string * herbs;

    herbs = HERBMASTER->query_herbs(
        ({TERRAIN_GARDEN,TERRAIN_RUINS,TERRAIN_MOUNTAIN}));
    set_up_herbs(({one_of_list(herbs), one_of_list(herbs),
        one_of_list(herbs), one_of_list(herbs)}));
}

void
create_herbg_room()
{
}

void
create_room()
{
    set_short("herb garden");
    OUTSIDE;

    setup_herbgarden();

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("flowers", "There are lots of different types of " +
             "flowers growing everywhere.\n");
    add_item("herbs", "You don't see any herbs directly. Maybe " +
             "you should search for them.\n");
    add_item("bushes", "The bushes are very thick " +
             "and seem impassable.\n");
    add_item("ground", "The ground is covered in grass " +
             "and sweet-smelling herbs.\n");
    reset_room();
    create_herbg_room();
}
