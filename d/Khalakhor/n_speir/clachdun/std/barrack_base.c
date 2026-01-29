#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h";
#include "local.h"

inherit CLACHDUN;

// Prototypes
void set_up_cords();

void create_barrack() {}

nomask void
create_clachdun()
{
    set_up_cords();
    set_short("within a fortified barrack inside Clach Dun");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 1);
    set_terrain(TERRAIN_HALL);
    create_barrack();
}

void
set_up_cords()
{
    sscanf(file_name(this_object()),
      ROOM_DIR + "barrack_%d_%d", gX, gY);
}
