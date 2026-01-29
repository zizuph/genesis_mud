#include "defs.h"

#define S_LOCAL_ARM_DIR		(S_AREA_ARM_DIR + S_AREA_TOWER)
#define S_LOCAL_NPC_DIR		(S_AREA_NPC_DIR + S_AREA_TOWER)
#define S_LOCAL_OBJ_DIR		(S_AREA_OBJ_DIR + S_AREA_TOWER)
#define S_LOCAL_WEP_DIR		(S_AREA_WEP_DIR + S_AREA_TOWER)
#define S_LOCAL_ROOM_DIR	(S_AREA_ROOM_DIR + S_AREA_TOWER)

//--------------------------------------------------------------------------

// This part contains definitions that legacy code from Tower
// relies on. Using the definitions elsewhere is discouraged.

#ifndef TOWER_OF_REALMS_DEFS
#define TOWER_OF_REALMS_DEFS

/* The maximum number of info offices on each floor may be changed
   since there was an idea to possibly have a non-homogeneous structure. */

#define MAX_OFFICES ({ 0, 5, 5, 5, 5 })
#define FLOOR_NAMES ({ "tower", "tfloor1", "tfloor2", "tfloor3", "tfloor4" })

#define TOWER_OFFICE	(S_LOCAL_ROOM_DIR + "tower_office")
#define TOWER_FLOOR	(S_LOCAL_ROOM_DIR + "tower_floor")
#define TOWER		(S_LOCAL_ROOM_DIR + "tower")
#define TOWER_SAVE	(S_AREA_VAR_DIR + "tower_save")
#define FLOOR_EXITS(floor) TOWER->query_floor_exits(floor)
#define OFFICE_FLOOR(domain_name) TOWER->query_office_floor(domain_name)
#define OFFICE_PATH(domain_name) TOWER->query_office_path(domain_name)
#define PROJ_EXT ".prj"
#define OFFICE_SIGN_TEXT "Commands:\n" + \
      "wizards                  - Lists the wizards of this domain.\n" + \
      "projects <domain/wizard> - The projects of the domain/wizard.\n"

#define FLOOR_MAINDESC \
           ("The floor and walls are made of polished marble, " + \
            "reflecting your image as you look around in wonder. " + \
            "From each floor it is possible to access " + \
            "the information office of one or more domains. ")

#define FLOOR_STAIRDESC \
           "Broad stairs lead up to the next floor of the tower. "

#define ADD_FLOOR_ITEMS add_item(({"floor", "marble", "walls", "stairs"}), \
        "Everything here seems to be made of finely polished marble.\n");

#endif
