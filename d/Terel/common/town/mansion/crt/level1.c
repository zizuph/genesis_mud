
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define WELL "/d/Terel/common/town/mansion/crt/well"
#define BASKET "/d/Terel/common/town/mansion/crt/basket"
#define DIR "west"

/* THIS_LEVEL: level used for well-basket */

#define THIS_LEVEL 1

#include "level.h"

create_room() {
#include "leveldesc.h"
    add_prop(ROOM_I_LIGHT,0);
    add_exit(MANSION + "crt/tunn1_1", "north",0);
}
