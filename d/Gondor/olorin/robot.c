inherit "/std/workroom";

#include "/d/Gondor/defs.h"

void
create_workroom()
{
    set_short("NPC Robots discussion room");
    set_long(BSN("A room to discuss intelligent robots and whatever we might "
      + "need to code them, like parsers etc."));
    load_board();
}
