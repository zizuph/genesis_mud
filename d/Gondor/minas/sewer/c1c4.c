inherit "/d/Gondor/minas/sewer/sewer";

#include <macros.h>

#include "/d/Gondor/defs.h"

#define NR_RATS		5

void
create_sewer() 
{
    set_extra_long("The sewer has reached a bend here. It comes down "
      + "from the northwest and continues down to the southwest. In "
      + "the east wall there is a small opening.");

    add_exit(MINAS_DIR + "sewer/n1c4",    "northwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/stairc4", "east",      0, 0);
    add_exit(MINAS_DIR + "sewer/s1c4",    "southwest", 0, 0);

    floor("southwest");
    passage("southwest");

    add_item(({"opening", }), BSN(
        "The opening in the east wall leads into a small staircase. "
      + "A flight of stairs is leading upwards there."));

    rats = allocate(NR_RATS/2 + random(NR_RATS) + 1);

    set_alarm(3.0, 0.0, "reset_room");
}

void
reset_room()
{
    set_alarm(3.0, 0.0, "make_rat");
}

