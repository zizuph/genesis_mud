/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Tunnel");
    set_long("A darkened tunnel, its walls covered with fungi, the " +
	     "ground slick with fetid water and moss. The walls " +
	     "here are all chipped and cracked, the floor covered " +
	     "with loose stone. It looks like a tunnel was begun in the " +
	     "northwest, but remains unfinished. " +
	     "The tunnel leads southeast.\n");

    add_item("walls", "Worn smooth, but not natural tunnels.\n");
    add_item("fungi", "Foul smelling fungus that decays all matter.\n");
    add_item("moss", "Its is a foul blackish green moss.\n");
    add_item("water", "Fetid and contaminated with dirt and minerals.\n");
    add_item("wall", "The walls are crude and need work.\n");
    add_item(({ "stone", "loose stone", "rubble"}),
	"It is rubble from the tunnels construction.\n");

    IN; BLACK;

    add_exit(L1 + "n4b", "southeast");
	
	add_npc(MON + "dark_elf", 2);
}
