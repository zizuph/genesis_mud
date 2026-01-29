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

inherit "/d/Krynn/solamn/vin_herbtr/vinherbtr_base";

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));

/* FUNCTIONS */

void
create_vin_herb_trail_room()
{
    set_skeleton_here();

    add_item(({"bones","bleached bones","skeleton","dismembered skeleton"}),
               "These remains are a solemn reminder of how quickly "+
               "the weather can turn here. "+
               "Examining the bones of the skeleton, you "+
               "feel a connection with a fellow climber -- now fallen.\n");

    add_exit(ROOM + "vinherbtr4n","north",0);
    add_exit(ROOM + "vinherbtr5","downward",0,5);
    set_climb_skill_min( 0 );
}

