/*
 * monk_herbg_nw.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  updated by Amelia 6/21/97
*  to include standard hearbsearch routines (hs)
*  to include reset_room
*  to 'plant' random set of herb files whenever room is
*  loaded
 *  modified to take out Earthsea reference 9/2/97--
 *  changed to hs in ~amelia/copies/specials
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
    set_long("There is a tall oak growing here, " +
             "shrouded in ferns, and at its base is a small bench. " +
             "To the west and north thick bushes border the garden. " +
             "The garden continues to the south and east.\n");

    add_exit("monk_herbg_ne", "east");
    add_exit("monk_herbg_sw", "south");
    add_exit("monk_herbg_well", "southeast");
    OUTSIDE;

    set_up_herbs(TO->select_herb_files(GARDEN_HERBS),
                 GARDEN_LOCATIONS, 3);

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("flowers", "There are lots of different types of " +
             "flowers growing everywhere.\n");
    add_item("herbs", "You don't see any herbs directly. Maybe " +
             "you should search for them.\n");
    add_item("bench", "This is a little stone bench. Perhaps in " +
             "time you will be able\n" + "to sit on it.\n");
    add_item((({"tree", "oak"})),
             "This is a very unique tree. Its gnarled " +
             "branches twist and turn in a breathtaking " +
             "pattern, causing your eyes to linger for a " +
             "moment ...\n");
    add_item("ferns", "The lush green ferns are feathery and soft.\n");
    add_item("bushes", "The bushes seem very thick " +
             "and impassable.\n");
    reset_room();
}
