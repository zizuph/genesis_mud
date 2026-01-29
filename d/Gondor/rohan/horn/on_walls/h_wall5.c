inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/gorge/out_wall4"

void create_helmsdeep_room()
{
    object door;

    set_short_desc("On Helm's Wall");
    set_extra_long("On the top of the Deeping-wall, at its "+
    "southeastern end. Within the wall, the gorge goes deeper "+
    "into the mountains. The wall ends here with a tower at the "+
    "southern cliff. A stairway leads down to the fields inside the wall. ");

    set_below_desc("You have a good view of the slope in front of the "+
    "wall. Further down you can see Helm's Dike, "+
    "the outer fortification of the fastness. ");
    set_below_room(BELOWROOM);

    STAIRS;
    GORGE;
    WALLTOWER;
    MOUNTAINS;
    add_item("cliff","The cliff is high and steep, impossible to climb.\n");
    add_item("wall",BSN("The wall is so broad that "+
    "four can walk abreast. The top is sheltered by a high parapet."));
    add_item(({"battlement","parapet"}),BSN("Here and there are clefts "+
    "in the stone through which archers can shoot."));
    add_item(({"clefts","cleft"}), down_there);

    add_exit(ROH_DIR+"horn/on_walls/h_wall4","northwest",0);
    add_exit(ROH_DIR+"horn/gorge/ins_wall5","down",0);

    door = clone_object(ROH_DIR + "horn/doors/hw_tower_in"); 
    door->move(TO);
}
