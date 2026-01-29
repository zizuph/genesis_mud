inherit "/d/Emerald/keep/std/treasure_room";

#include "../keep.h"

void
create_treasure_room()
{
    set_keep_master_file(KEEP_MASTER);
    set_long("This is a treasure room in the testkeep.\n");
}
