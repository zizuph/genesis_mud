#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/dunland/wild/dunlendings.h"

public void
create_gondor()
{

    set_short("Inside a small wooden house.");
    set_long("The house is very small, but along the "
      + "walls stands four bunk beds, two at the "
      + "eastern wall and two at the western. A "
      + "small table stands in the middle of the " 
      + "the room, with some stools around it. It "
      + "is all very simply furnished, it is "
      + "obvious that people only live here "
      + "temporarely.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_item(({"wall","walls"}), BSN(
	"The walls are made of wood like the rest of the "
	+ "house. They are completely bare."));
    add_item(({"beds", "bed", "bunk bed", "bunk beds"}), BSN(
	"When you examine the bunk beds closer, you notice that "
	+ "they all have been recently used."));
    add_item(({"table", "stool", "stools"}), BSN(
	"In the centre of the house stands a small table, " 
	+ "surrounded by some wooden stools. The table have "
	+ "some smaller knife marks in it, and it is covered "
	+ "with spilled beer."));
    add_item(({"floor", "boards", "wooden boards"}), BSN(
	"The floor is made of wooden boards. It "
	+ "crunches a bit when you walk on it.\n"));
    add_item("ceiling", "The ceiling is made of wood. It looks "
      + "as if the one who built it is certain that it does not "
      + "rain in Rohan.\n");
    add_item(({"beer", "spilled beer"}), BSN(
	"On the table someone have spilled beer, but it is "
	+ "dried now."));

    set_no_exit_msg(({"southwest","south","southeast"}),
      "You decide to walk up to the southern walls, but they look " +
      "quite simple and ordinary. You decide to walk back to the " +
      "centre of the room.\n");
    set_no_exit_msg(({"northwest","north","northeast"}),
      "You decide to walk up to the northern walls, but they look " +
      "quite simple and ordinary. You decide to walk back to the " +
      "centre of the room.\n");
    set_no_exit_msg("west", "You decide to walk up to the western " +
      "wall but it looks quite simple and ordinary. You decide to " +
      "walk back to the centre of the room.\n");
    set_no_exit_msg("east", "You decide to walk up to the eastern " +
      "wall but it looks quite simple and ordinary. You decide to " +
      "walk back to the centre of the room.\n");



    add_exit(DUN_WILD_ROOMS + "field05", "out");

    add_npc(DUN_WILD_NPC + "dunl_soldier", 2 + (random(3)));
}
