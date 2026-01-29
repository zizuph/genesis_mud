#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Common board room of Kabal");
    set_long("\n   You are in a small and cozy room with a "+
      "large, leather sofa sits on a plush fur carpet. A table in the "+
      "center of the room has many chairs around it and seems to serve "+
      "as a meeting table. On the far north wall, a large magical board "+
      "stands.\n\n");

    add_item("sofa", "The softa is huge and seems to be made of very fine "+
      "leather. It covers the entire east wall.\n");

    add_item("table", "The table has a very smooth, honey gloss.\n");

    add_item("chairs", "The chairs are made of finely crafted wood with "+
      "small cusions on the seats.\n");

    add_exit(CVAN + "shop/wayfar_guild", "south", 0, -1);

    add_prop(ROOM_I_INSIDE, 1);

    clone_object("/d/Genesis/obj/board")->move(TO, 1);
}
