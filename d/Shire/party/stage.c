#include "defs.h"

inherit PARTY_BASE;


void
create_party_room()
{
    set_short("A small theatre stage");
    set_long("A small theatre stage.\n");
    add_item(({"small stage","stage","small theatre stage","theatre stage"}),
      "A small stage built lovingly with gorgeous old redwood, with a raised "+
      "platform and heavy red velvet curtains hanging from a high roof.\n");


    add_exit(PARTY_DIR+"backstage","backstage");
    add_exit(PARTY_DIR+"theatre","ampitheatre");
}

