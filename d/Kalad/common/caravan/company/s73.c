#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Alcove");
    set_long("You enter the deathly quiet alcove. Now that you are within "+
      "the darkness, the lack of lighting doesn't seem to bother you. In "+
      "fact, you can see quite clearly in this room. Glancing around at "+
      "your surroundings, you notice nothing interesting enough to warrant "+
      "your attention. Perhaps the only thing of note is the incredibly "+
      "beautiful marble that this place has been constructed from. Towards "+
      "the south lies the main area of the Inner Sanctum.\n");

    add_item(({ "marble" }), "You gaze in admiration at the beautifully "+
      "crafted ceiling, walls, and floor...\n");

    add_item(({ "floor" }), "It is flawlessly crafted and covers the ground "+
      "here.\n");

    add_exit(CVAN + "company/s82", "south");
}
