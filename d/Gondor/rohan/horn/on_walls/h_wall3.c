inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM	(ROH_DIR + "horn/gorge/out_wall2")
#define	GUARD_FILE	(ROH_DIR + "horn/npc/hw_guard")

object *Guards = allocate(2);

/* Prototypes */
void reset_room();

void create_helmsdeep_room()
{
    set_short_desc("On Helm's Wall");
    set_extra_long("On the top of the Deeping-wall.  Within the wall, "+
    "the gorge leads deeper into the "+
    "mountains. The wall runs from northwest to southeast, and "+
    "a stairway leads down to the fields inside the wall. ");

    set_below_desc("You have a good view of the slope in front of the "+
    "wall. Further down you can see Helm's Dike, "+
    "the outer fortification of the fastness. ");
    set_below_room(BELOWROOM);

    STAIRS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("wall", BSN("The wall is so broad that "+
    "four can walk abreast. Its top is sheltered by a high parapet."));
    add_item(({ "battlement", "parapet" }), BSN("Here and there are "+
    "clefts in the stone through which archers can shoot."));
    add_item(({ "clefts", "cleft" }), down_there);

    add_exit(ROH_DIR + "horn/on_walls/h_wall2", "northwest", 0);
    add_exit(ROH_DIR + "horn/on_walls/h_wall4", "southeast", 0);
    add_exit(ROH_DIR + "horn/gorge/ins_wall3", "down", 0);

    reset_room();
}

void
reset_room()
{
    set_alarm(4.0, 0.0, &clone_npcs(Guards, GUARD_FILE, 10.0));
}
