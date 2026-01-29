inherit "/d/Kalad/common/central/tower/stair_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();

    add_exit(CENTRAL(tower/stair6),"down",0,2);
    add_exit(CENTRAL(tower/top),"up",0,2);

} 
