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
	     "ground slick with fetid water and moss. " +
	     "The tunnels lead east-west.\n");

    add_item("walls", "Worn smooth, but not natural tunnels.\n");
    add_item("fungi", "Foul smelling fungus that decays all matter.\n");
    add_item("moss", "Its is a foul blackish green moss.\n");
    add_item("water", "Fetid and contaminated with dirt and minerals.\n");

    IN; BLACK;

    add_exit(L1 + "s3a", "east");
    add_exit(L1 + "s3c", "west");
    add_npc(MON + "dark_elf", 3);
}
