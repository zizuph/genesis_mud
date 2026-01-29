/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Dark Lair");
    set_long("A smooth stone chamber, warm and smokey. It has an oval "+
	"shape and a concave ceiling, both smooth and the stone the "+
	"color of blood. In the center of the chamber is a bed of sand.\n");

    add_item("bed", "It is sand in the center of the chamber.\n");
    add_item("sand", "It is a large bed of sand in the chamber.\n");
    add_item("ceiling", "It is concave, the stone smooth and fiery.\n");

    IN; BLACKER;

    add_exit(L1 + "stair4", "south");
    add_npc(MON + "chimera");
}
