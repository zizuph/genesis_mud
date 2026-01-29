/*
 * monk_herbg_ne.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  updated by Amelia to include standard herbsearch
*  routines, and to plant a wider variety of herbs.
*  Each time room loads, a random set of herbs from
*  roke_herbs.h is 'planted'
*  also, fixing the reset_room, so herbs reset
*  6/21/97
 * 
 *  Took out references to Earthsea files, left copies in
 *  ~amelia/copies/    9/2/97
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room.c";
inherit ROKEDIR + "lib/herbsearch.c";

#include <macros.h>
#include "/d/Roke/amelia/copies/herb_sets/roke_herbs.h"
//FIXA

object places;

void
create_room()
{
    set_short("herb garden");
    set_long("The song of some little birds " +
             "can be heard in the distance. The garden is bordered " +
             "by thick bushes to the east and north and continues " +
             "to the south and west. There is a small rock here.\n");

    add_exit("monk_herbg_se", "south");
    add_exit("monk_herbg_nw", "west");
    add_exit("monk_herbg_well", "southwest");
    set_up_herbs(TO->select_herb_files(GARDEN_HERBS),
                 GARDEN_LOCATIONS, 3);
    OUTSIDE;

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("flowers", "There are lots of different types of " +
             "flowers growing everywhere.\n");
    add_item("herbs", "You don't see any herbs directly. Maybe " +
             "you should search for them.\n");
    add_item("rock", "It's just a rock.\n");
    add_item("bushes", "The bushes seem very thick and " +
             "impassable.\n");
    add_item("ground", "The ground is covered in grass " +
             "and sweet-smelling herbs.\n");
    reset_room();
}
