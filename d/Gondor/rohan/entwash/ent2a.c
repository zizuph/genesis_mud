inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void reset_room();

object bug;

void
create_swamp()
{
    set_extra_long("The marsh extends in all directions now, and this"
      + " atmosphere is becoming unpleasant. The hum of insects is"
      + " everywhere, and grows louder the longer you listen.");

    add_exit(ENTWASH_DIR + "ent1a", "west");
    add_exit(ENTWASH_DIR + "ent2b", "northeast");
    add_exit(ENTWASH_DIR + "ent3a", "east");
    add_exit(ENTWASH_DIR + "ent2d", "south");

    reset_room();
}

void
add_monsters()
{
    if (!objectp(bug))
    {
        bug = clone_object(NPC_DIR + "mosquito");
        bug->set_poison_file(ENTWASH_DIR + "obj/mosquito_sting");
        bug->move_living("from somewhere", TO);
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, add_monsters);
}

