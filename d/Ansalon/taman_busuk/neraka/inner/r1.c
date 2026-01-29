/* Ashlar, 4 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit INNER_OUT;

object g1,g2;

void
reset_neraka_room()
{
    if (!objectp(g1))
        g1 = clone_npc(NNPC + "cityguard");
    if (!objectp(g2))
    {
        g2 = clone_npc(NNPC + "cg_leader");
        g2->start_patrol();
    }
}

void
create_neraka_room()
{
    set_short("start of the Queen's Way");
    set_extra_long("You are standing at the start of the Queen's Way, " +
        "just south of the Main Gate. To the east is the entrance to " +
        "a hulking blockhouse. The Queen's Way leads west, flanked " +
        "on both sides by the tall city walls. Another gate, smaller " +
        "than the Main Gate, is set in the south wall.");

    add_item_citywalls();
    add_item_street1();
    add_item(({"gate","main gate"}),"The Main Gate stands to the north, " +
        "leading out of the city. The gate is set in between two tall " +
        "massive towers.\n");
    add_item(({"towers","tower","tall towers","massive towers"}),
        "Two tall massive towers stand on each side of the Main Gate. " +
        "The towers are half again as tall as the wall.\n");
    add_item(({"smaller gate","small gate","south gate"}),
        "The smaller gate leads south into the city.\n");

    add_item(({"blockhouse","hulking blockhouse"}),
        "The hulking blockhouse stands to the east, with an entrance to " +
        "the street.\n");
    add_item(({"entrance","entrance to blockhouse"}),
        "The entrance leads east into the blockhouse.\n");

    add_exit(NOUTER + "main/tunnel", "north");
    add_exit("", "east", "@@go_east");
    add_exit(NINNER + "g1", "south");
    add_exit(NINNER + "r2", "west");

    reset_room();
}

int
go_east()
{
    write("The barracks are closed at the moment. Please try again later.\n");
    return 1;
}
