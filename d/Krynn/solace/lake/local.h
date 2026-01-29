
#include "/d/Krynn/common/defs.h"
#include <macros.h>

/*pathnames used*/
#define PARENT  "/d/Krynn/solace/"
#define AREADIR  PARENT + "lake/"
#define ROOM    AREADIR + "room/"
#define OBJ     AREADIR + "obj/"
#define NPC     AREADIR + "npc/"
#define LOGS    AREADIR + "logs/"
#define STD     AREADIR + "std/"
#define CONNECT "/d/Krynn/solace/new_village/"

/*room bases*/
#define SOLACE_ROOM_BASE "/d/Krynn/solace/std/outside_base"
#define SOLACE_INSIDE_BASE "/d/Krynn/solace/std/inside_base"
#define VILLAGE_BASE_OUT "/d/Krynn/solace/lake/std/village_base_out"
#define VILLAGE_BASE_IN "/d/Krynn/solace/lake/std/village_base_in"

/*monster bases*/
#define MINOTAUR "/d/Krynn/solace/lake/std/minotaur_base"
#define KAPAK    "/d/Krynn/common/monster/kapak_base"
#define SIVAK    "/d/Krynn/common/monster/sivak_base"


/*monster tables*/
#define LAKETABLE "/d/Krynn/common/rndtables/tblsolacelake"
#define CAMPTABLE "/d/Krynn/common/rndtables/tblsolacecamp"

/*monster tables*/
#define LAKETABLE "/d/Krynn/common/rndtables/tblsolacelake"
#define CAMPTABLE "/d/Krynn/common/rndtables/tblsolacecamp"

/*formulas*/
#define F_PRESTIGE(object)  (object->query_average_stat())*\
                            (object->query_average_stat()/10)
#define PRESTIGE_ME   set_knight_prestige(F_PRESTIGE(TO));
#define ALIGN_ME   set_alignment(-(F_PRESTIGE(TO)/2));
