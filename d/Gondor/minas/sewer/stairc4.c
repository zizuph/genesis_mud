inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("This is a staircase in a small recess branching off "
      + "from the main tunnel of the sewers. A flight of stairs is "
      + "leading up.");

    add_exit(MINAS_DIR + "sewer/c1c4", "west", 0, 0);
    add_exit(MINAS_DIR + "sewer/upc4", "up",   0, 0);

    floor();
    passage();

    add_item(({"stairs", "steps", "flight of stairs", }), BSN(
        "A narrow flight of stairs is leading up. The stone steps "
      + "run alongside the southern wall of the staircase."));
}

