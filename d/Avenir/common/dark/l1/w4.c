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
    set_long("A darkened tunnel, its walls covered with fungi, the\n" +
	     "ground slick with fetid water and moss.\n" +
	     "The tunnel leads east and a haunting looking cave is to\n" +
	     "the southwest.\n");

    add_item("walls", "Worn smooth, but not natural tunnels.\n");
    add_item("fungi", "Foul smelling fungus that decays all matter.\n");
    add_item("moss", "Its is a foul blackish green moss.\n");
    add_item("water", "Fetid and contaminated with dirt and minerals.\n");

    IN; BLACK;

    add_exit(L1 + "w3", "east");
    add_exit(L1 + "stair2", "southwest");

    add_npc(MON + "foreman", 1);
    add_npc(MON + "troll_w", 2 + random(3));
}
