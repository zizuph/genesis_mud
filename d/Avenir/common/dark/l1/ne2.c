/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith Dec 2021 : Removed foreman and troll workers
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Tunnel");
    set_long("This tunnel is carved from deep black rock, veined " +
 	     "with lines of red carnelian and sardonyx. It seems as though " +
	     "it is of better work than the most of the area. " +
	     "The tunnel leads northeast a short way.\n");

    add_item("sardonyx",
	     "A stone of multi-colors, it is semi-precious.\n");
    add_item("carnelian",
	     "A red semi-precious stone. It occurs in veins\n" +
	     "in this tunnel area.\n");

    IN; BLACK;

    add_exit(L1 + "stair3", "northeast");
    add_exit(L1 + "n3", "west");
    add_npc(MON + "bat", 2);
	
 // add_npc(MON + "foreman", 1);
 // add_npc(MON + "troll_w", 2 + random(3));
}
