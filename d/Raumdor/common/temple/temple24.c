/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

object npc;

void
create_room()
{
    ::create_room();
    set_short("Circular chamber of a morbid temple");
    set_long(
      "You stand to the north side of the great statue. The room smells very " +
      "strongly of death and decay. The walls are made of some old black " +
      "stone. Torches line the walls casting light in this dank dark " +
      "place.\n");
    add_item(({"statue"}),
      "This is a statue of an awful looking demon, eyes aglow. It looks " +
      "humanoid, only it has four arms. Its head is that of a skull. In each " +
      "hand it holds a likeness of a human severed head. From its back " +
      "sprouts nasty looking wings, and it has a spiked tail.\n");
    add_item(({"torches"}), "They light the area.\n");
    add_exit(TEMPLE_DIR + "temple23", "southeast", 0);
    add_exit(TEMPLE_DIR + "temple22", "south", 0);
    add_exit(TEMPLE_DIR + "temple21", "southwest", 0);
    clone_object(TEMPLE_OBJ_DIR + "altar")->move(TO);
    reset_room();
}

void
reset_room()
{
    if (!npc)
    {
        npc = clone_object(COMMON_NPC_DIR + "kpriest2");
        npc->move_living("xxx", TO);
    }
}
