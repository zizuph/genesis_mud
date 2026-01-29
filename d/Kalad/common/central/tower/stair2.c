inherit "/d/Kalad/common/central/tower/stair_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();

    add_exit(CENTRAL(tower/stair1),"down",0,3);
    add_exit(CENTRAL(tower/stair3),"up",0,3);

} 
