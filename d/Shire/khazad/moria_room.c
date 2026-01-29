#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit SHIRE_ROOM;

void
create_moria_room()
{
}

nomask void
create_shire_room()
{
    set_short("An empty room in moria");
    set_long("An empty room in moria.\n");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);

    create_moria_room();
}
