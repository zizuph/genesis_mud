inherit "/d/Gondor/pelargir/sewers/sewer.c";

#include "/d/Gondor/defs.h"

void
create_sewer()
{
    set_extra_long("The sewer ends here under the docks of the harbour, "
      + "releasing its contents into the waters of the Anduin.");

    add_item(({"water", "waters", "river", "anduin", "river anduin", }), BSN(
        "The waters of the Anduin can be seen to the east through the "
      + "opening in which the sewer ends. Right outside the sewer, they "
      + "are of a muddy brown colour."));
    add_item(({"opening", "hole", "outlet", }), BSN(
        "The sewer ends in a large outlet under some docks in the harbour "
      + "of Pelargir. The Anduin is visible beyond the outlet."));
    add_item(({"dock", "docks", }), BSN(
        "All that is visible of the docks from here are the wooden supports "
      + "of a pier."));

    add_exit(PELAR_DIR + "sewers/beldock", "northeast", 0, 1);
    add_exit(PELAR_DIR + "sewers/dock",   "southwest", 0, 1);

    floor("northeast");
    passage("northeast");
}


