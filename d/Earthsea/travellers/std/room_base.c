#pragma strict_types
#pragma save_binary

inherit "/d/Earthsea/std/room";

#include "../guild.h"
#include <stdproperties.h>

public void
create_traveller_room()
{
}

public nomask void
create_earthsea_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    create_traveller_room();
}

public int
is_member()
{
    object tp = this_player();

    if(!IS_MEMBER(tp) && !tp->query_wiz_level())
    {  
        write("Only members may enter there.\n");
        return 1;
    }

    return 0;
}
