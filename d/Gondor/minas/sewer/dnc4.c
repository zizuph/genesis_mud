inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

#define NR_RATS		5

void    reset_room();

void
create_sewer() 
{
    set_extra_long("This is a a deadend. The tunnel is leading "
      + "out of here to the east. In the roof a drain is leading "
      + "down from the surface.");

    add_exit(MINAS_DIR + "sewer/n5c4", "east", 0, 0);

    floor("east");
    passage("east");
    roof("drain");

    rats = allocate(NR_RATS/2 + random(NR_RATS) + 1);

    set_alarm(3.0, 0.0, "reset_room");
}

void
reset_room()
{
    set_alarm(3.0, 0.0, "make_rat");
}

