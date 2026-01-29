inherit "/d/Gondor/rohan/entwash/stream";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_extra_long("The river Entwash is gradually curving around to"
      + " begin its eastward flow here. This area seems quite removed"
      + " from any signs of dwelling or civilization. The marshy area"
      + " which surrounds the Mouths of the Entwash is still a ways to"
      + " the southeast.");

    set_flow("southeast");

    add_exit(ENTWASH_DIR + "str2", "northwest");
    add_exit(ENTWASH_DIR + "str4", "south");
}
