inherit "/d/Kalad/common/central/tower/stair_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();

    add_exit(CENTRAL(tower/stair3),"down",0,5);
    add_exit(CENTRAL(tower/stair5),"up",0,5);

} 
