#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Corridor");
    set_long("You are walking down a dimly-lit corridor.\n"+
      "Several torches are mounted upon the stone walls. "+
      "This passage is bare of any furnishings or decorations, it is just "+
      "naked stone. To the west and east lie dark rooms. The corridor "+
      "continues to the north.\n");

    add_item(({ "torches" }), "They are mounted upon the walls and are "+
      "providing the sole illumination in this passage.\n");

    add_item(({ "stone walls", "walls" }), "The walls seem to have been "+
      "carved from the natural rock of this area, the stonework looks quite "+
      "ancient.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur15a", "west");
    add_exit(CVAN + "lot/ur14", "north");
    add_exit(CVAN + "lot/ur15b", "east");
}
