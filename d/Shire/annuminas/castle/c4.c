inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


void
create_room()
{
    set_short("great hall");
    set_long("The walls open out onto a great hall with " +
        "a vast domed ceiling curving upward into " +
        "darkness. The tiled marble floor is still somewhat intact, " +
        "as are two rows of tall pillars. A raised dias stands against the " +
        "northern wall, where once the King of Arnor held court. " +
        "However, the throne has long since vanished, no doubt carried " +
        "away as a trophy. The walls have been stripped bare of decoration, " +
        "and what was once a graceful room full of light, beauty and music " +
        "is dark and still as a tomb. The hall extends to the east and " +
        "west.\n");

    add_item(({"pillars", "pillar", "tall pillars",}),
        "The pillars are massive, and stand symmetrically in two rows along " +
        "the east and west walls of the hall. The pillars to the east " +
        "appear to be most intact, while the others are crumbling in " +
        "various stages of decay. You have to approach closer to " +
        "get a better look.\n");
    add_item(({"floor", "marble floor", "tiled marble floor", "slabs",
        "marble slabs"}), 
        "The floor is blackened, yet mostly intact. Here and there the " +
        "slabs of marble tiles have been shattered as if with great force.\n");
    add_item(({"ceiling"}),"The ceiling extends overhead into the " +
        "overarcing darkness above. Since it blocks any light from sun " +
        "or stars, you assume that it must be mostly intact.\n");
    add_item(({"dais", "raised dais"}), "The dais stands against " +
        "the northern wall and has a series of steps that lead up " +
        "to it.\n");

    add_exit(CASTLE_DIR + "c3", "south", 0, 0);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, -1);


}

