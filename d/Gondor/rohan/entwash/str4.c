inherit "/d/Gondor/rohan/entwash/stream";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_extra_long("The Entwash continues to curve in a wide arc as"
      + " it prepares to flow east to meet with the Anduin. Looking"
      + " off in that direction one might see the beginnings of the"
      + " marshlands which accompany the meeting of those two rivers.");

    set_flow("southeast");

    add_exit(ENTWASH_DIR + "str3", "north");
    add_exit(ENTWASH_DIR + "str5", "southeast");
}
