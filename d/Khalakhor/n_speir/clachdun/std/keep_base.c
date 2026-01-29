#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h";
#include "local.h"

inherit CLACHDUN;

// Prototypes
void set_up_cords();

void create_keep() {}

nomask void
create_clachdun()
{
    set_up_cords();
    set_short("within Clach Dun Keep");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 1);
    set_terrain(TERRAIN_HALL);
    create_keep();
}

void
set_up_cords()
{
    sscanf(file_name(this_object()),
      KEEP_DIR + "keep_%d_%d", gX, gY);
}
