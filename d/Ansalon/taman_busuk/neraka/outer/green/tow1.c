/* Carridin */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit OUTER_IN;

object g1,g2,g3;

void
reset_neraka_room()
{
    if (!objectp(g1))
        g1 = clone_npc(NNPC + "cityguard");
    if (!objectp(g2))
        g2 = clone_npc(NNPC + "cityguard");
    if (!objectp(g3))
        g3 = clone_npc(NNPC + "cityguard");
}

void
create_neraka_room()
{
	set_short("Inside a guard tower");
    set_long("You are standing inside the guard tower on the perimeter " +
        "between the Green and the Red Quarter. There are a few bunks " +
        "against the walls and a table in the middle of the room. " +
        "There is an exit to the southwest leading out to the road.\n");
    add_item(({"bunk","bunks"}),"The bunks are empty at the moment.\n");
    add_item("table","It is a square table, placed in the middle of " +
        "the room.\n");
	add_item_inside();

    add_exit(NOUTER+"green/g1","southwest");

	reset_room();
}

