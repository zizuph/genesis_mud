#pragma strict_types

inherit "/d/Gondor/rohan/entwash/entwash";

#include <macros.h>
#include "/d/Gondor/defs.h"

//  Prototypes
void   stream();

void
create_swamp()
{
    set_extra_long("The river Entwade has begun to separate here into"
        + " many rivulets and streams which extend out like fingers to the"
        + " north and east. There are no worn paths here, as the"
        + " ground is very marshy and wet, but it seems possible to travel"
        + " in the directions where the streams have not cut too deeply.");
    add_item(({"river","entwash"}), BSN("The river splinters here"
      + " into many small streams which run off in various directions"
      + " to connect eventually with Anduin the Great. A bog opens up"
      + " in the direction of the flow."));

    add_exit(ENTWASH_DIR + "str6", "west", stream, 2);
    add_exit(ENTWASH_DIR + "ent1b", "northeast");
    add_exit(ENTWASH_DIR + "ent2a", "east");
}

void
stream()
{
    write("You cross over the shallow stream of the fragmented Entwash.\n");
}
