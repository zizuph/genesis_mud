inherit "/d/Gondor/rohan/entwash/stream";

#include "/d/Gondor/defs.h"

void
create_stream()
{
    set_extra_long("Here on the eastern bank of the River Entwash"
      + " the plains of the East Emnet expand for many miles. Far in"
      + " the distance to the east, the hills of the Emyn Muil are"
      + " visible rising to meet the sky.");

    set_flow("south");

    add_exit("/d/Gondor/rohan/plains/k10", "west");
    add_exit(ENTWASH_DIR + "str2", "south");
}
