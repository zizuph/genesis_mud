inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM ROH_DIR + "horn/on_walls/h_wall5"

void create_helmsdeep_room()
{
    set_short_desc("On top of the Helm's Wall tower");
    set_extra_long("On top of the Helm's Wall tower. "+
    "This small round tower guards "+
    "the southeastern end of the wall. The tower is sheltered by a "+
    "high parapet. ");
    set_inside_keep(1);

    set_below_desc("You have a good view of Helm's wall. ");
    set_below_room(BELOWROOM);

    add_item("wall",BSN("The wall below is so broad that "+
    "four can walk abreast. The top is sheltered by a high parapet."));
    add_item(({"battlement","parapet"}),BS("Here and there are clefts "+
    "in the stone through which archers can shoot.\n"));
    add_item(({"clefts","cleft"}), down_there);

    add_exit(ROH_DIR+"horn/on_walls/ins_hw_tower","down", 0);
}
