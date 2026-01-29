inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("All about, the fen is covered with puddles and"
      + " weeds. There is a calm that pervades the environment here,"
      + " almost as if the presence of intruders has been noticed, and"
      + " given cause for silence.");

    add_exit(ENTWASH_DIR + "ent4a", "west");
}
