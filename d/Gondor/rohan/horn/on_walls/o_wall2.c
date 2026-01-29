inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

#define BELOWROOM	(ROH_DIR + "horn/on_walls/h_wall1")
#define	GUARD_FILE	(ROH_DIR + "horn/npc/ow_guard")

object *Guards = allocate(3);

/* Prototypes */
void reset_room();

void create_helmsdeep_room()
{
    string location, extraline;

    location = "On top of the eastern part of the outer wall. ";
    extraline = "The outer wall runs north and southwest, and a "+
	"staircase leads down to the courtyard. ";

    set_short_desc("On top of the outer wall of the keep");
    set_extra_long(location + LONG_DESC1 + extraline);
    set_inside_keep(1);

    set_below_desc("You have a good view of the stairs down to "+
    "the Deeping-wall. ");
    set_below_room(BELOWROOM);

    add_item(({"clefts","cleft"}), down_there);
    ON_WALL;
    TOWER;
    WINDOWS;
    PARAPET;
    COURTYARD;
    KEEP;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    STAIRS;
    BOTH_WALLS;


    add_exit(ROH_DIR+"horn/on_walls/o_wall1","north",0);
    add_exit(ROH_DIR+"horn/on_walls/o_wall3","southwest",0);
    add_exit(ROH_DIR+"horn/burg/outer_court2","down",0);

    reset_room();
}

void
reset_room()
{
     set_alarm(4.0, 0.0, &clone_npcs(Guards, GUARD_FILE, 10.0));
}
