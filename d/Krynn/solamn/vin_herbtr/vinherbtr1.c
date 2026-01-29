/* 
   created by Vitwitch 08/2021 
   based closely on work of by Aridor 06/1993
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

#define PALANTHAS_EXTERIOR "/d/Krynn/solamn/palanthas/nobles/er6"
#define VINGAARD_HIGHROAD "/d/Krynn/solamn/vin_mount/room/road3"
#define ROOM "/d/Krynn/solamn/vin_herbtr/"

#define HARD_TO_CLIMB 20

inherit "/d/Krynn/solamn/vin_herbtr/vinherbtr_base";

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));

/* FUNCTIONS */

void
create_vin_herb_trail_room()
{
    int t = vin_herb_trail_tiredness(); 
    add_exit(ROOM + "vinherbtr2","upward",climb_up,t);
    add_exit(PALANTHAS_EXTERIOR,"downward",0,t);
    set_climb_skill_min( HARD_TO_CLIMB );
}

