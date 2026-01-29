#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/std/room";

create_room()
{
    set_short("In a coma");
    INSIDE;
    LIGHT;
    set_long("Everything is blurry.  Your head hurts...\n");

}
