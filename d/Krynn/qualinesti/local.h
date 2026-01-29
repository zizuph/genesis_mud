#include "/d/Krynn/common/defs.h"

#define DEBUG_WIZ  "blizzard"
#define DEBUG(x)   find_player(DEBUG_WIZ)->catch_msg( x + "\n")


#define PARENT  "/d/Krynn/qualinesti/"
#define STD     PARENT + "std/"
#define NPC     PARENT + "npc/"
#define OBJ     PARENT + "obj/"
#define WEP     PARENT + "wep/"
#define ARM     PARENT + "arm/"
#define CDIR    PARENT + "elf_camp/"
#define COBJ    CDIR + "obj/"
#define CNPC    CDIR + "npc/"
#define CWEP    CDIR + "wep/"
#define CARM    CDIR + "arm/"
#define FDIR    PARENT + "forest/"
#define FOBJ    FDIR + "obj/"
#define FNPC    PARENT + "npc/"
#define FWEP    FDIR + "wep/"
#define FARM    FDIR + "arm/"

/* inherit files */
#define CAMPBASE     STD + "elf_camp_base"
#define FORESTBASE   STD + "q_forest_base"
#define OUT          STD + "outside_base"

#define ELF_BASE     STD + "elf_base.c"

/* places to visit */
#define DEFAULT      0
#define CAMP         1
#define FOREST       2
#define ARCHER_CAMP  4

#define ELVEN_TOKEN       "_qualinesti_token"
#define I_KILLED_ELF      "_killed_qualinesti_elf"
