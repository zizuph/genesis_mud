/* Ashlar, 17 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";
#include ARND_MEET

inherit OUTER_IN;

object d;

void
reset_neraka_room()
{
    if (!objectp(d))
    	d = clone_npc(GET_RANDOM_NAME(NT_OUTER),"white");
}

void
create_neraka_room()
{
    set_short("in a large warehouse");
    set_long("You have entered a large warehouse, stacked with crates. " +
        "The ceiling is at least 5 meters above you, it is hard to tell " +
        "because it is so dark up there. There is a door leading out " +
        "of the warehouse to the south.\n");

    add_item_inside();
    add_item(({"crates","crate"}),
        "Stacks of crates line the walls. The crates are marked in some " +
        "language you do not recognize.\n");
    add_item("warehouse","@@long");
    add_item("door","The door leads north out of the warehouse.\n");
    remove_item("ceiling");
    add_item("ceiling","You can see next to nothing of the ceiling high " +
        "above you.\n");

    add_exit(NOUTER + "white/w5", "south");

    reset_room();
}


