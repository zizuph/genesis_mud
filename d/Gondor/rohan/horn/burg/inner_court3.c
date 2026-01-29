inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

void create_helmsdeep_room()
{
    object door; 

    set_short_desc("The inner courtyard of the Hornburg");
    set_extra_long("The northwest corner of the inner courtyard. "+
    	"The courtyard extends to the south and southeast, "+
	"and a door leads east into the tower. ");
    set_inside_keep(1);

    GUARDS;
    WALL;
    TOWER;
    WINDOWS;
    COURTYARD;
    COBBLESTONES;
    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    INNER_WALL;

    add_exit(ROH_DIR+"horn/burg/inner_court1","south",0);
    add_exit(ROH_DIR+"horn/burg/inner_court2","southeast",0);
    door = clone_object(ROH_DIR + "horn/doors/tower_door_in"); 
    door->move(TO); 
}
