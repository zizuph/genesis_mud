inherit "/d/Emerald/std/room";

#include <stdproperties.h>

public void
create_sewer_room()
{
}

public nomask void
create_emerald_room()
{
    // Even though the sewers are underground, they are still part of
    // Telberin, and, therefore, affected by the power of Telan-Ri,
    // giving them a level of illumination.
    add_prop(ROOM_I_LIGHT, 3);
    add_prop(ROOM_I_INSIDE, 1);

    create_sewer_room();
}

public void
add_sewage_channel()
{
}
