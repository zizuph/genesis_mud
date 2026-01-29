/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Cavern");
    set_long("Although this area is much the same as the rest, "+
	"being ridden with slime and fungi, it also has not been "+
	"been worked. It is a cavernous hall of nature, full of "+
	"fetid waters and putrid things.\n");

    add_item("fungi", "Foul smelling fungus that decays all matter.\n");
    add_item("moss", "Its is a foul blackish green moss.\n");
    add_item("water", "Fetid and contaminated with dirt and minerals.\n");

    IN; BLACK;

    add_exit(L1 + "se4", "north");

    add_npc(MON + "drake", 1);
	add_npc(MON + "dark_elf", 2);
}
