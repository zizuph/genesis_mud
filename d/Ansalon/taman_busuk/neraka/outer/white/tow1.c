/* Ashlar, 21 May 97 */

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
	set_short("inside a guard tower");
    set_long("You are standing inside the guard tower at the entrance " +
        "of the White Quarter. There are a few bunks " +
        "against the walls and a table in the middle of the room. " +
        "There is a fireplace set in the south wall. " +
        "There is an exit to the north leading out to the road.\n");
    add_item(({"bunk","bunks"}),"The bunks are empty at the moment.\n");
    add_item("table","It is a square table, placed in the middle of " +
        "the room.\n");
    add_item("fireplace","There is a fire burning in the fireplace.\n");
    add_item("fire","The fire adds warmth and light to the room.\n");
    add_prop(OBJ_I_HAS_FIRE, 1);
    
    add_exit(NOUTER+"white/w1","north");

    reset_room();
}

