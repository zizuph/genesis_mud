inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/gorge/out_wall1"

void create_helmsdeep_room()
{
    object door;
	
    set_short_desc("On top of Helm's Wall");
    set_extra_long("On the top of the Deeping-wall, near the "+
    "northwestern end. Within the wall, the gorge goes deeper "+
    "into the mountains. A door pierces the outer wall of the "+
    "keep to the northwest, and a staircase leads down to "+
    "the fields inside the wall. ");

    set_below_desc("You have a good view of the slope in front of the "+
    "wall. Further down you can see Helm's Dike, "+
    "the outer fortification of the fastness. ");
    set_below_room(BELOWROOM);

    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    FIELD;
    add_item("wall",BSN("The wall is so broad that four "+
    "can walk abreast. Its top is sheltered by a high parapet."));
    add_item(({"battlement","parapet"}),BSN("Here and there are clefts "+
    "in the stone through which archers can shoot."));
    add_item(({"clefts","cleft"}), down_there);

    add_exit(ROH_DIR+"horn/on_walls/h_wall2","southeast",0);
    add_exit(ROH_DIR+"horn/gorge/ins_wall1","down",0);

    door = clone_object(ROH_DIR + "horn/doors/wall_door_in");
    door->move(TO);
}

