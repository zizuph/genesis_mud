#include "defs.h"

inherit TELBERIN_STREET;

public void
create_west_avenue()
{
}

nomask void
create_telberin_street()
{
    
    config_street_room(0, "the West Avenue");
    set_em_long("Just inside the western gate of Telberin, at the great "+
        "West Avenue and Ri Circle.  The wide avenue leads east through "+
        "two of Telberin's famous gardens; their fragrances reaching you "+
        "even from here. The line of the roadway draws your eye down its "+
        "length into the grand Royal Circle and up to the gates of the "+
        "royal palace. Its magnificent, perfectly symmetrical form dominates "+
        "the skyline. The tall, pure-white, stone spires rise toward the "+
        "sky, gleaming brilliantly in the light.\n");

    add_item(({"west avenue", "avenue", "roadway"}),
        "You look closer at the West Avenue and find it to be very wide and "+
        "it stretches to the east in a seamless pattern of cobblestones. "+
        "The street is warm and inviting, calling you down its path to "+
        "experience the many treasures that await you.\n");

    add_item(({"rose garden","rose bud", "rose buds", "roses"}),
        "You spy a few rose buds peeping through the hedge of the rose "+
        "garden. The sweet scent of roses delightfully fills your senses.\n");

create_west_avenue();
}
