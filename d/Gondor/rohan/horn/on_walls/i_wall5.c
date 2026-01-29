inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM	(ROH_DIR + "horn/gorge/n_path2")
#define	GUARD_FILE	(ROH_DIR + "horn/npc/iw_guard")

object Guard;

/* Prototypes */
void reset_room();

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the northern part of the inner wall. ";
    extraline = "The inner wall runs west and east. ";

    set_short_desc("On top of the inner wall of the keep");
    set_extra_long(location + LONG_DESC2 + extraline);
    set_inside_keep(1);

    set_below_desc("Two furlongs north of the keep is the "+
    "Dike, an old trench functioning as an outer fortification. Beyond "+
    "the Dike the Coomb begins. ");
    set_below_room(BELOWROOM);

    add_item(({ "clefts", "cleft" }), down_there);
    ON_WALL;
    TOWER;
    PARAPET;
    COURTYARD;
    KEEP;
    WINDOWS;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    INNER_WALL;

    add_exit(ROH_DIR + "horn/on_walls/i_wall6", "west", 0);
    add_exit(ROH_DIR + "horn/on_walls/i_wall4", "east", 0);

    reset_room();
}

void
reset_room()
{
     Guard = clone_npc(Guard, GUARD_FILE);
}

