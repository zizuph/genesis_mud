#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h";
#include "local.h"

inherit CLACHDUN;

// Prototypes
void set_up_cords();

void create_path() {}

nomask void
create_clachdun()
{
    set_up_cords();
    set_short("along a narrow winding mountain pass");

    remove_prop(ROOM_I_INSIDE);
    add_prop(ROOM_I_LIGHT, 1);
    set_terrain(TERRAIN_PATH);
    create_path();
}

void
set_up_cords()
{
    sscanf(file_name(this_object()),
      FOREST_DIR + "path_%d_%d", gX, gY);
}
