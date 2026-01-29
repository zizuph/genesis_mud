inherit "/d/Kalad/common/central/tower/stair_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();

    add_exit(CENTRAL(tower/stair5),"down",0,3);
    add_exit(CENTRAL(tower/stair7),"up",0,3);

} 
