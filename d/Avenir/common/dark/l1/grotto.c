/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/room";
#include "../dark.h"

public void
create_room(void)
{
    set_short("Grotto");
    set_long("This small grotto formed of natural crystals stands " +
	"as a nemesis to the rest of the caverns. A light seems to shine "+
	"forth from the crystals. Streams of water trickle down the "+
	"walls of the cavern.\n");

    add_item("crystal", "It is beautiful rock crystal, it forms many "+
	"strange shapes and shines a variety of hues.\n");

    add_cmd_item("crystal", "break", "They are too strong to break.\n");
    add_cmd_item("crystal", "chip", "@@chip");

    add_exit(L1 + "s3a", "north");
}

public int
chip(void)
{
    object ob = present("chisel", this_player());

    if (!objectp(ob))
    {
	write("You have no tool!\n");
	return 1;
    }

    write("You chip at the crystal formation but nothing happens.\n");
    say(QCTNAME(this_player()) +" tries to chip the crystal formations.\n");

    return 1;
}
