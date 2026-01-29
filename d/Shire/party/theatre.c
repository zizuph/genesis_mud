#include "defs.h"

inherit PARTY_BASE;

//object lotho;

void
create_party_room()
{
    set_short("A gently-sloping grassy ampitheatre");
    set_long("Around you the grassy hillock slopes further down to the "+
             "west in a natural bowl shape, providing an ideal ampitheatre "+
             "for the beautifully-crafted timber stage below.\n");

    add_item(({"small stage","stage","small timber stage","theatre stage"}),
      "A small stage built lovingly with gorgeous old redwood, with a raised "+
      "platform and heavy red velvet curtains hanging from a high roof.\n");
    add_item(({"bowl","ampitheatre","hillock"}),
      "The hill wraps around you, encompassing the stage just below. The "+
      "bowl shape and gentle slope of the hillock provide a natural "+
      "ampitheatre.\n");
    add_item(({"grass","turf","ground"}),
      "The lush blue-green cooch grass on the rich Shire earth provide "+
      "comfy and thankfully dry seating arrangements.\n");


    add_exit(PARTY_DIR+"stage","stage");
    add_exit(PARTY_DIR+"podium","northeast");
}

