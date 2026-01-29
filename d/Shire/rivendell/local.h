/*
 * Local defines for Rivendell
 * Created by Finwe, November 1997
 *
 * Added ranger related definitions
 * - Finwe Feburary 2002
 */

// Included files
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
 
// Root directory
#define RIVENDELL_DIR      "/d/Shire/rivendell/"
 
// Object directories
#define RARM_DIR           (RIVENDELL_DIR + "arm/")
#define RWEP_DIR           (RIVENDELL_DIR + "wep/")
#define ROBJ_DIR           (RIVENDELL_DIR + "obj/")
#define RNPC_DIR           (RIVENDELL_DIR + "npc/")
#define FRUIT_DIR          (RIVENDELL_DIR + "fruit/")
#define SPELLS_DIR         (RIVENDELL_DIR + "spells/")
#define COURIER_DIR        (RIVENDELL_DIR + "couriers/")
#define STEEDS_DIR         (RIVENDELL_DIR + "steeds/")
#define RANGER_NPC          "/d/Gondor/common/npc/"

 
// Room directories
#define VALLEY_DIR         (RIVENDELL_DIR + "room/valley/")
#define FOREST_DIR         (RIVENDELL_DIR + "room/forest/")
#define RIVER_DIR          (RIVENDELL_DIR + "room/river/")
#define LANDING_DIR        (RIVENDELL_DIR + "room/river/")
#define TREES_DIR          (RIVENDELL_DIR + "room/trees/")
#define WR_DIR             "/d/Shire/eastroad/eastern/"
#define TROLLSH_DIR        "/d/Shire/common/trollsh/"

 
// Base files
#define FOREST_BASE        (RIVENDELL_DIR + "forest_base.c")
#define HOUSE_IN_BASE      (RIVENDELL_DIR + "house_in_base.c")
#define VALLEY_BASE        (RIVENDELL_DIR + "valley_base.c")
#define GARDEN_BASE        (RIVENDELL_DIR + "garden_base.c")
#define RIVER_BASE         (RIVENDELL_DIR + "river_base.c")
#define LANDING_BASE       (RIVENDELL_DIR + "landing_base.c")
#define SHORE_BASE         (RIVENDELL_DIR + "shore_base.c")
#define TREES_BASE         (RIVENDELL_DIR + "trees_base.c")
 

// Lirary Files and Directory
#define LIBRARY_DIR         (RIVENDELL_DIR + "library/"
#define LIBRARY_ACC_DIR     (LIBRARY_DIR + "accepted/"
#define LIBRARY_BOOKS_DIR   (LIBRARY_DIR + "library/"
#define LIBRARIAN           "_rivendell_librarian"

//  Important files
#define RIVENDELL_MASTER   (RIVENDELL_DIR + "master")
#define RIVENDELL_SAVE     ("/d/Shire/log/elf_killers.o")
 
//  Important Macros
#define CAN_ENTER(x)       RIVENDELL_MASTER->query_allowed_enter_rivendell(x)
#define IS_ATTACKER(x)     RIVENDELL_MASTER->query_elf_attacker(x)
#define IS_KILLER(x)       RIVENDELL_MASTER->query_elf_killer(x)
#define ROOM_TELL_TIME     random(180)+30
#define NPC_TELL_TIME      90
#define NOLDOR_ELF         "Noldor of Imladris"
 
// Guild related defs
// Moved to domain defs.h file May 3, 2004 by Finwe
/*
#define RANGER_S_GUILD_NAME     "Gondorian Rangers Guild"
#define RANGER_N_GUILD_NAME     "Rangers of the North"
#define DUNEDAIN_S_GUILD_NAME	"Dunedain"
#define SINDAR_S_GUILD_NAME     "Sindar of Lorien"

 
#define IS_RANGER(x)    ((x)->query_guild_name_occ() == RANGER_S_GUILD_NAME)
#define IS_NRANGER(x)   ((x)->query_guild_name_occ() == RANGER_N_GUILD_NAME)
#define IS_CAPTAIN(x)   ((x)->test_bit("Gondor", 1, 19))
 
#define IS_DUNADAN(x)	((x)->query_guild_name_race() == DUNEDAIN_S_GUILD_NAME)
#define IS_SINDAR(x)    ((x)->query_guild_name_race() == SINDAR_S_GUILD_NAME)
 */

// Props

/* moved from ~rivendell/room/river/riverbank.c Placed in player 
 * when they attack npcs in valley
 */
#define RIV_ENEMY   "_rivendell_enemy_"
#define LEAF_PROP   "_have_looked_at_leaves"
#define CHECK_STATS (TP->query_skill(SS_AWARENESS)>24) && (TP->query_skill(SS_TRACKING)>24)

#define NO_CROSS_PROP "_no_cross_"
#define SHIRE_NPC     "_riv_elf_"
