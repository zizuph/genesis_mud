inherit "/d/Kalad/common/central/tower/stair_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();

    add_exit(CENTRAL(tower/stair4),"down",0,4);
    add_exit(CENTRAL(tower/stair6),"up",0,4);

} 
