inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
    set_short("Inside the culvert");
    set_long(BSN("Inside the culvert under the Deeping-wall. The stream "+
    "flows rapidly through the culvert, making it difficult to keep "+
    "one's balance. The noise of the water drowns other sounds."));

    add_item("culvert", "The culvert is wide and low.\n");
    add_item( ({ "water", "stream" }),
	"The water flows quite rapidly here.\n");

    add_exit(ROH_DIR+"horn/gorge/ins_wall2","southwest",0,7);
    add_exit(ROH_DIR+"horn/gorge/out_wall2","northeast",0,7);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}

