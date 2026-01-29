inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

//  Prototypes
int     check_exit();

void
create_swamp()
{
    set_extra_long("The pools of water and streams here have joined"
      + " with a much larger body of water which laps quietly along"
      + " this muddy shore. This is the river Anduin, though all that"
      + " is visible is a wavy surface of water extending to into the"
      + " northern wall of mist.");

    add_item(({"water","river","anduin","surface","river anduin"}),BSN(
        "The edge of the river is calm against the banks of the fen."
      + " Mists twist and curl over its silent surface."));
    add_item(({"shore","bank","banks"}), BSN("The bank here is uneven"
      + " and very slight. Ground and river flow into one another"
      + " without any visible depression."));

    add_exit(ENTWASH_DIR + "ent1b", "southwest");
    add_exit(ENTWASH_DIR + "ent1e", "northeast", check_exit, 1, 1);
}

int
check_exit()
{
    if (this_player()->query_wiz_level())
    {
        write("\nThis area is still closed to mortals, Wizards!\n\n");
        return 0;
    }
    write("There is no obvious exit northeast.\n");
    return 1;
}
