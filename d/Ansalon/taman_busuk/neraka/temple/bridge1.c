/* This room is supposed to be the post office for the PoT.
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_base.c";

void
create_temple_room()
{
    object door;
    
    set_short("The dias to the stonebridge");
    set_long("Blurpas\n");

    door = clone_object( DOOR + "bridge2.c" );
    door->move(this_object());
}
