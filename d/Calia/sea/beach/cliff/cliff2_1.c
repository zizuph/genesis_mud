/*  description: Room on a cliff above Calian sea: cliff3
 *  coder: Tigerlily
 *  date:  2001-12-30
 *  special: needs climb skill to access
 *  notes:
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"


inherit "/std/room";
inherit BASE_CLIFF;

void
reset_room()
{
    // removes room if no one is in it
    special_reset_room();
}



void
create_room()
{
    make_cliff_room(1);
    create_paths(file_name(this_object()), query_verb());


}
