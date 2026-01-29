inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

#define NR_BUGS		2

void
create_swamp()
{
    set_extra_long("This area of the fens is rather awful. All about"
      + " the water are mosquitos darting this way and that. A number"
      + " of pools are strewn about, but a particularly large one is"
      + " visible to the east.");

    add_item(({"mosquito","mosquitos"}), BSN("For the most part, they"
      + " seem to be keeping to themselves, but now and then, one will"
      + " rise from the water and become quite annoying."));
    add_item(({"pool"}), BSN("Pools are all around this area, but a rather"
      + " expansive one seems to lie east of here."));

    add_exit(ENTWASH_DIR + "ent2a", "north");
    add_exit(ENTWASH_DIR + "ent2e", "east");

    bugs = allocate(NR_BUGS/2 + random(NR_BUGS) +1);
    set_alarm(3.0, 0.0, reset_room);
}

void
reset_room()
{
    set_alarm(3.0, 0.0, make_bug);
}

