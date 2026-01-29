inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/gorge/out_wall3"

void create_helmsdeep_room()
{
    set_short_desc("On Helm's Wall");
    set_extra_long("On the top of the Deeping-wall. Within the wall, "+
    "the gorge leads deeper into the mountains. This section of "+
    "the wall appears to have been recently repaired.  The wall "+
    "runs from southeast to northwest. ");

    set_below_desc("You have a good view of the slope in front of the "+
    "wall. Further down you can see Helm's Dike, "+
    "the outer fortification of the fastness. ");
    set_below_room(BELOWROOM);

    GORGE;
    KEEP;
    CLIFFS;
    MOUNTAINS;
    add_item("wall",BSN("The wall is so broad that "+
    "four can walk abreast. Its top is sheltered by a high parapet."));
    add_item(({"battlement","parapet"}),BSN("Here and there are clefts "+
    "in the stone through which archers can shoot."));
    add_item(({"clefts","cleft"}), down_there);

    add_exit(ROH_DIR+"horn/on_walls/h_wall3","northwest",0);
    add_exit(ROH_DIR+"horn/on_walls/h_wall5","southeast",0);
}

