/* Carridin */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit OUTER_IN;

void
create_neraka_room()
{
    set_short("in a large warehouse");
    set_long("You have entered a large dim-lit warehouse, stacked with crates. " +
        "The ceiling is high above you, shrouded in darkness. " +
        "There is an exit leading out of the warehouse to the southwest.\n");

    add_item_inside();
    add_item(({"crates","crate"}),
        "Stacks of crates line the walls. The crates are marked in some " +
        "language you do not recognize.\n");
    add_item("warehouse","@@long");
    add_item("exit","The exit leads southwest out of the warehouse.\n");
    remove_item("ceiling");
    add_item("ceiling","You can see next to nothing of the ceiling high " +
        "above you.\n");

    add_exit(NOUTER + "green/g20", "southwest");
}
