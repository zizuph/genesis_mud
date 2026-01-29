inherit "/d/Gondor/common/lib/town.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int	block();

void
create_room()
{
    set_hillside("north");
    set_height(4);
    set_road(2);
    set_density(4);
    set_extraline("Above this green terrace rises a high platform, at "
      + "the foot of which a bright spring gushes forward. A stair of "
      + "stone ascends to the platform. ");
    add_exit(EDORAS_DIR + "meduseldstair", "south", block, 0);
    add_exit(EDORAS_DIR + "stairs3",       "north", 0, 0);
    make_the_room();
    add_item(({"spring","water","bright spring"}), BSN(
        "The water gushes from a stone carved in the likeness of a horse's "
      + "head; beneath it is a wide basin from which the water spills and "
      + "feeds a canal running down the hill."));
    add_item(({"canal","little canal","stream","little stream","river"}),
	BSN(
        "The little stream splashes and bubbles on its way to the "
      + "Snowstream, which runs along just outside town."));
    add_item("platform", BSN(
        "On the platform at the crown of the hill stands the golden hall "
      + "Meduseld, built by Brego, son of Eorl the Young."));
    add_item(({"seat","seats","stair","stairs","steps"}), BSN(
        "The stair leading up to the platform are high and broad. At either "
      + "side of the topmost step are stone-hewn seats for the guards."));
    add_prop(OBJ_I_CONTAIN_WATER,1);
    set_drink_from(({"bright spring", "spring", "stream", "river", }));
}

void
init()
{
    ::init();
    init_drink();
}

int
block()
{
    if (!TP->query_wiz_level())
    {
	write(BSN("You do not dare to go any further. On the platform, there "
	        + "must be many guards who probably would not welcome "
                + "intruders!"));
        return 1;
    }
    write("N.B. This exit is not open to mortals!\n");
    return 0;
}
