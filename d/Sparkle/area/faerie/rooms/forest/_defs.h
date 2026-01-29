/*
 * Local defines for Faerie
 * Created by Finwe, August 2004
 *
 * Code update - DG_CLOCK_LIBS synchronized to Sparkle
 * TAPAKAH, 18/02/2006
 * Added money defs
 * Finwe, December 5, 2007
 * copied for temporary use with ship porting
 * TAPAKAH, 10/2008
 */

#include "../../../../sys/defs.h"

#include "/d/Sparkle/area/faerie/quests/qbits.h"

// Root directory
#define FAERIE_DIR      "/d/Sparkle/area/faerie/"

// Misc directories
#define ARM_DIR         (FAERIE_DIR + "arm/")
#define FRUIT_DIR       (FAERIE_DIR + "fruit/")
#define LIB_DIR         (FAERIE_DIR + "lib/")
#define LIBRARY_DIR     (FAERIE_DIR + "library/")
#define LOG_DIR         (FAERIE_DIR + "logs/")
#define MESS_DIR        (FAERIE_DIR + "messengers/")
#define NPC_DIR         (FAERIE_DIR + "npcs/")
#define OBJ_DIR         (FAERIE_DIR + "obj/")
#define PRIV_DIR        (FAERIE_DIR + "private/")
//#define SHIP_DIR        (FAERIE_DIR + "ships/")
#define TELLS_DIR       (FAERIE_DIR + "tells/")
#define VK_SHIP_DIR     (SHIP_DIR + "vk/")
#define SP_SHIP_DIR     (FAERIE_DIR + "ships/sparkle/")
#define VK_TICKET_NAME  "_vk_faerie_ticket"
#define WEP_DIR         (FAERIE_DIR + "wep/")
 
// Room directories
#define BOARD_DIR       (FAERIE_DIR + "boards")
#define CASTLE_DIR      (FAERIE_DIR + "rooms/castle/")
#define FOOD_DIR        (FAERIE_DIR + "food/")
#define FOREST_DIR      (FAERIE_DIR + "rooms/forest/")
#define FROGOBJ_DIR     ("/d/Shire/frogmorton/obj/")
#define GIB_DIR         (FAERIE_DIR + "rooms/gibberer/")  
#define GO_DIR          (FAERIE_DIR + "rooms/greenoaks/")
#define GRAVE1_DIR      (FAERIE_DIR + "rooms/graveyard/lvl01/")
#define GRAVE2_DIR      (FAERIE_DIR + "rooms/graveyard/lvl02/")
#define GRAVE3_DIR      (FAERIE_DIR + "rooms/graveyard/lvl03/")
#define GRAVEYARD_DIR   (FAERIE_DIR + "rooms/graveyard/")
#define HERB_DIR        (FAERIE_DIR + "herbs/")
#define HERB_DATA_DIR   (HERB_DIR + "data/")
#define ORCHARD_DIR     (FAERIE_DIR + "rooms/orchard/")
#define OC_DIR          (FAERIE_DIR + "rooms/orc_camp/")
#define SHOBJ_DIR       ("/d/Shire/common/obj/")
 
// Base files
#define BEACH_BASE      (LIB_DIR + "base_beach.c")
#define CASTLE_BASE     (LIB_DIR + "base_castle.c")
#define COMMON_BASE     (LIB_DIR + "base_common.c")
#define ELFMAKER        (NPC_DIR + "elfmaker.c")
#define FOOTWEAR_BASE   (LIB_DIR + "base_footwear.c")
#define FOREST_BASE     (LIB_DIR + "base_forest.c")
#define GARDEN_BASE     (LIB_DIR + "base_garden.c")
#define GIB_BASE        (LIB_DIR + "base_gib.c")
#define GRAVEYARD_BASE  (LIB_DIR + "base_graveyard.c")
#define HERB_SEARCH     (LIB_DIR + "herbsearch.c")
#define HOUSE_BASE      (LIB_DIR + "base_house.c")
#define INDOORS_BASE    (LIB_DIR + "base_indoors.c")
#define KRYNN_OUTSIDE   "/d/Krynn/solamn/splains/room/outside_room_base"
#define MAKE_MONEY      (LIB_DIR + "make_money.c")
#define OC_BASE         (LIB_DIR + "base_camp.c")
#define OC_TOWER_BASE   (LIB_DIR + "base_orc_tower.c")
#define ORCHARD_BASE    (LIB_DIR + "base_orchard.c")
#define QUESTMASTER     (LIB_DIR + "questmaster.c")
#define ROAD_BASE       (LIB_DIR + "base_road.c")
#define SEA_CAVE_BASE   (LIB_DIR + "base_sea_cave.c")
#define SHIP_CABIN_BASE (LIB_DIR + "base_sh_cabin.c")
#define SHIP_CAPT_BASE  (LIB_DIR + "base_sh_capt.c")
#define TOWN_BASE       (LIB_DIR + "base_town.c")
#define TREE_BASE       (LIB_DIR + "base_tree.c")
#define WATER_BASE      (LIB_DIR + "base_water.c")

/* Other general defines */
#define ACADEMY_NAME    "Academy"
#define PO              previous_object()
#define QSW             query_shadow_who()
#define HE_SHE(o)       (o)->query_pronoun()
#define HIS_HER(o)      (o)->query_possessive()
#define HIM_HER(o)      (o)->query_objective()
#define QRACE(o)        (o)->query_race_name()
#define QTRACE(o)       (o)->query_race()
#define ENV(o)          environment(o)
#define E(o)            environment(o)
#define WRITE(s)        TP->catch_msg(s) 
#define WRITEN(s)       TP->catch_msg(s + "\n")
#define CAP(s)          capitalize(s)
#define LOW(s)          lower_case(s)
#define NF(s)           notify_fail(s)
#define NFN(s)          notify_fail(s + "\n")
#define NFN0(x)         { NFN(x); return 0; }
#define ROOM_TELL_TIME  100
#define NPC_TELL_TIME   90
#define FALSE           0
#define TRUE            1
#define ONE_OF_LIST(array) one_of_list(array)
#define FIXEUID         { setuid(); seteuid(getuid()); }
#define NEED_CLIMB_SKILL    15
#define F_VOLUME_ARMOUR this_object()->query_prop(OBJ_I_WEIGHT)/4
#define ADD_MONEY       (set_alarm(1.0,0.0,"get_money"))


//honey quest defines
#define MAX_HONEY       10
#define MAX_CUTS         5


// bank rate
#define BANK_FEE        21

// NPC related defines
#define YOUNG           0
#define ADULT           1
#define ELDER           2
#define GUARD           3

#define FAERIE          "_faerie_"
#define BARD            "bard"
#define HALF_ELF        "half_elf"
#define SETTLER         "settler"
#define TRAVELLER       "traveller"
#define QM_NAME         "Chief Delegate"

// orc camp names
#define ORC              "orc"
#define ORC_CAMP_NPC     "_orc_camp_orc"
#define ORC_THRALL_NAME  "_orc_thrall"
#define ORC_SCOUT_NAME   "_orc_scout"
#define ORC_SOLDIER_NAME "_orc_soldier"
#define ORC_GUARD_NAME   "_orc_guard"
#define ORC_OFFICER_NAME "_orc_officer"
#define ORC_BLACKSMITH   "_orc_blacksmith" 


// Constants that are time related
#define DG_SEC2MIN              60
#define DG_SEC2HRS              3600
#define DG_SEC2DAY              86400
#define DG_SEC2MON              2592000
#define DG_SEC2YRS              31558464

// Library Specific defs
//#define STDLIB          "/d/Krynn/std/library/"
//#define VLIB            "/d/Sparkle/guilds/mercs/library"
/*
#define BOOK            STDLIB + "book"
#define W_BOOK		    STDLIB + "bbook"
#define BOOKDIR         (LIBRARY_DIR + "books/")
#define SHORTDIR        (LIBRARY_DIR + "short/")
#define LONGDIR         (LIBRARY_DIR + "long/")

#define BEDIT           "/obj/edit"
#define MOREOBJ         "/obj/more"

#define NEW_LOG         (LIBRARY_DIR + "book_log")
*/
