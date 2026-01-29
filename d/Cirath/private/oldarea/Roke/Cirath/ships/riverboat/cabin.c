inherit "/d/Genesis/ship/cabin";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/common/defs.h"
#define BOATS "/d/Roke/Cirath/ships/"

void
create_cabin()
{
    set_short("A little cabin on a small river boat");
    set_long(BS("This is a little cabin on the small river boat. It is, like "+
             "the ship, made of wood.",60));

    add_exit(BOATS+"riverboat/deck", "out", 0);

    add_prop("_room_i_no_dig",1);
}
