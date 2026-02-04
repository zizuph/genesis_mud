inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP           this_player()
#define TO           this_object()

#define BEACH        "/d/Terel/port/beach/"
#define WRECK        "/d/Terel/port/wreck/"
#define GULL         "/d/Terel/port/monster/gull"

public void
create_room()
{
    set_short("in the water");
    set_long("You are in the water.\n");

    add_item(({"water"}), "It feels very cold.\n");
    add_prop(ROOM_I_INSIDE, 1);
}
