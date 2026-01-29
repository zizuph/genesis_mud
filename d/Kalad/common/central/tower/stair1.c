inherit "/d/Kalad/common/central/tower/stair_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();

    add_exit(CENTRAL(tower/base),"down",0,2);
    add_exit(CENTRAL(tower/stair2),"up",0,2);

} 
