#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h";
#include "local.h"

inherit CLACHDUN;

// Prototypes
varargs void set_up_cords(int x, int y);

void create_building() {}

nomask void
create_clachdun()
{
    set_up_cords();
    set_short("within a strudy building inside Clach Dun");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 1);
    set_terrain(TERRAIN_HOUSE);
    create_building();
}

varargs void
set_up_cords(int x, int y)
{
    if (!x || !y)
    {
	sscanf(file_name(this_object()),
	  ROOM_DIR + "building_%d_%d", gX, gY);
    }
    else
    {
	gX = x;
	gY = y;
    }
}

void
out_message()
{
    // THink up a better message.
    // And randomize it on the OB_NUM of TP
    write("You walk outside the building and are back on the streets.\n");
}
