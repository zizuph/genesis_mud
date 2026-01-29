inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("A ruined pier in Tharbad, in the south of Eriador");
    set_long(BSN("You are on an old abandoned pier on the Gwathlo River. "+
        "Other than the water, you see little sign that ships land here. "+
        "Now and then, ships from far away dock here, but since Tharbad is "+
        "deserted, you could wait for days and still not see a ship. "+
        "Northeast are the fords, and to the southwest, the riverbank stretches into "+
        "the distance."));

    add_exit(THARBAD_DIR + "pier/pier2","northeast",0,2);
    add_exit(THARBAD_DIR + "pier/pier4","southwest",0,2);

    add_item(({"pier","piers","dock"}), BSN(
        "The piers line the southwest side of the Greyflood river. This one seems in "+
        "rather poor condition."));
}
