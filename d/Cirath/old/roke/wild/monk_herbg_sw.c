/*
 * monk_herbg_sw.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  updated by Amelia 6/21/97
*  to include standard herbsearch routines
*  to include reset room
*  to add random sets of herb files at loading
* 
 *  modified to take out references to Earthsea files 
*  and use ~amelia/copies/...
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
    set_long("The fresh sweet fragrance of " +
             "blossoms fills the air. To your west thick bushes " +
             "border the garden, making it impossible to go in " +
             "that direction. The garden continues to the north and " +
             "east. To the northeast you see a well.\n");

    add_exit("monk_herbg_se", "east");
    add_exit("monk_herbg_nw", "north");
    add_exit("monk_herbg_well", "northeast");
    OUTSIDE;

    set_up_herbs(TO->select_herb_files(GARDEN_HERBS),
                 GARDEN_LOCATIONS, 3);
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
}
