#include "/d/Krynn/common/defs.h"
#include <macros.h>

/*pathnames used*/
#define PARENT  "/d/Krynn/solace/"
#define TDIR    PARENT + "lake/"
#define ROOM    TDIR + "room/"
#define OBJ     TDIR + "obj/"
#define LIV	TDIR + "living/"

#define STMON   PARENT + "village/monster/"


/*room bases*/
#define SWIM_ROOM "/d/Krynn/solace/lake/room/swim_room"
#define SOLACE_ROOM_BASE "/d/Krynn/solace/std/outside_base"
#define SOLACE_INSIDE_BASE "/d/Krynn/solace/std/inside_base"

/*monster bases*/
#define KAPAK    "/d/Krynn/common/monster/kapak_base"
#define SIVAK    "/d/Krynn/common/monster/sivak_base"
#define MINOTAUR "/d/Krynn/common/monster/minotaur_base"

/*monster tables*/
#define LAKETABLE "/d/Krynn/common/rndtables/tblsolacelake"
#define CAMPTABLE "/d/Krynn/common/rndtables/tblsolacecamp"

/*exits to the world*/
#define NEAR_PIER   PARENT + "new_village/west_road7"

/*formulas*/
#define F_PRESTIGE(object)  (object->query_average_stat())*\
                            (object->query_average_stat()/10)
#define PRESTIGE_ME   set_knight_prestige(F_PRESTIGE(TO));
#define ALIGN_ME   set_alignment(-(F_PRESTIGE(TO)/2));
