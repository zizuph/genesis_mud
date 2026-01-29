/* Ashlar, 25 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit OUTER_IN;

void
create_neraka_room()
{
    set_short("in a large warehouse");
    set_long("You have entered a large warehouse, stacked with crates. " +
        "The ceiling is at least 5 meters above you, it is hard to tell " +
        "because it is so dark up there. There is a door leading out " +
        "of the warehouse to the east.\n");

    add_item_inside();
    add_item(({"crates","crate"}),
        "Stacks of crates line the walls. The crates are marked in some " +
        "language you do not recognize.\n");
    add_item("warehouse","@@long");
    add_item("door","The door leads east out of the warehouse.\n");
    remove_item("ceiling");
    add_item("ceiling","You can see next to nothing of the ceiling high " +
        "above you.\n");

    add_prop(ROOM_I_ALLOW_STEED, 1);

    add_exit(NOUTER + "main/r8", "east");
}


