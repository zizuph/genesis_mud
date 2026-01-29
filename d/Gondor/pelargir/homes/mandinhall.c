inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the great dining hall of the mansion");

    set_long(BSN("This is the great dining hall of the mansion. The wall "
      + "hangings here are impressive, as well as the size of the "
      + "dining table which is large enough for about thirty place "
      + "settings. Those that eat here must be impeccably clean as "
      + "there are no stains on the floor or table. The doorway "
      + "leading into the kitchen is conveniently put in an "
      + "inconspicuous corner of the room, and someone has put up a "
      + "poorly stuffed trophy."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"wall hangings","hangings"}),BSN(
        "Most of these hangings are impressively designed tapestries, "
      + "doilies, and weaves. There is a stuffed trophy on the wall though."));
    add_item(({"stuffed trophy","trophy"}),BSN(
     "It is the head of a common deer.  Whoever stuffed it did not "+
     "do a very good job though, bits of stuffing are falling "+
     "out and there are even a few motheaten patches in the fur."));
    add_exit(PELAR_DIR + "homes/mangrhall","west",0);
    add_exit(PELAR_DIR + "homes/mankitchen","north",0);

    clone_object(PELAR_DIR + "obj/dintab")->move(TO);
}
