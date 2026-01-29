#pragma strict_types
#pragma save_binary

#include "/d/Earthsea/sys/paths.h"

inherit EARTHSEA_ROOM;

#include "../guild.h"
#include <stdproperties.h>

void
create_traveller_room()
{
}

nomask void
create_earthsea_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    create_traveller_room();
}

int
is_member()
{
    if (!IS_MEMBER(this_player()) && !this_player()->query_wiz_level())
    {  
        write("Only members may enter there.\n");
        return 1;
    }

    return 0;
}
