inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("along a poor street in Pelargir");

    set_long(BSN("This part of Pelargir is definitely underfunded. "
      + "The shacks along this street all need desperate remodelling "
      + "attention as a few of them seem to be held together by no "
      + "more than twine! To the northwest however, you can still "
      + "clearly see the Admiral's tower."));

    PADMIRAL;
    PBUILD;
    add_exit(PELAR_DIR + "street/proad3","west",0);
    add_exit(PELAR_DIR + "street/proad5","east",0);
}
