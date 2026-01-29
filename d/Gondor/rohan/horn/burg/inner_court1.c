inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    object door;


    set_short_desc("The inner courtyard of the Hornburg");
    set_extra_long("The southwest corner of the inner courtyard. "+
	"The gate to the outer courtyard is to the south. The "+
	"inner courtyard extends to the north and east, "+
	"circling a lofty tower. ");
    set_inside_keep(1);

    GUARDS;
    WALL;
    TOWER;
    WINDOWS;
    COURTYARD;
    COBBLESTONES;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    INNER_WALL;

    add_exit(ROH_DIR+"horn/burg/inner_court3","north",0);
    add_exit(ROH_DIR+"horn/burg/inner_court2","east",0);
    door = clone_object(ROH_DIR + "horn/doors/innerwall_gate_out"); 
    door->move(TO);
}

