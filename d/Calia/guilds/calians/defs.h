/*  ~Calia/guilds/calians/defs.h 

    (and for the time being also 
    ~Calia/glykron/palace/defs.h) 
 */

#include "/d/Calia/domain.h"

#define RANDOM_HEADER         "/d/Calia/sys/random.h"
#define MAP_HEADER            "/d/Calia/sys/map.h"
#define CALIAN_HEADER         "/d/Calia/guilds/calians/specials/calian.h"
#define COUNCIL_HEADER        "/d/Calia/guilds/calians/specials/council.h"
#define RECRUITER_HEADER      "/d/Calia/guilds/calians/specials/recruiter.h"

// Set root dirs
#define ROAD_DIR              DOMAIN_DIR + "overlord/road/rooms/"
#define CRPALACE_PATH         DOMAIN_DIR + "guilds/calians/"

#define CRPALACE_ROOMS        CRPALACE_PATH + "rooms/"
#define CRPALACE_LIGHT_ROOMS  CRPALACE_ROOMS + "light/"
#define CRPALACE_DARK_ROOMS   CRPALACE_ROOMS + "dark/"
#define CRPALACE_LIGHT_DOORS  CRPALACE_LIGHT_ROOMS + "doors/"
#define CRPALACE_DARK_DOORS   CRPALACE_DARK_DOORS + "doors/"
#define CRPALACE_OBJECTS      CRPALACE_PATH + "objects/"
#define CRPALACE_WEAPONS      CRPALACE_PATH + "weapons/"
#define CRPALACE_ARMOURS      CRPALACE_PATH + "armours/"
#define CRPALACE_SPECIALS     CRPALACE_PATH + "specials/"
#define CRPALACE_MONSTERS     CRPALACE_PATH + "monsters/"
#define CRPALACE_TEXTS        CRPALACE_PATH + "texts/"
#define CRPALACE_LOGS         CRPALACE_PATH + "logs/"

#define CALIAN_TAUNT_OBJECT   (CRPALACE_SPECIALS + "olde_insulte")
#define WARNING_SIGNAL_OBJECT (CRPALACE_SPECIALS + "warning_sig")
#define CALIAN_UTILITY        CRPALACE_SPECIALS + "calian_utility"
#define CALIAN_SPECIALS       CRPALACE_SPECIALS + "calian_specials"
#define CALIAN_CODE           CRPALACE_SPECIALS + "calian_code"
#define CALIAN_SHADOW         CRPALACE_SPECIALS + "calian_shadow"
#define CALIAN_CMDSOUL        CRPALACE_SPECIALS + "calian_cmdsoul"
#define CALIAN_MEDALLION      CRPALACE_OBJECTS + "calian_medallion"
#define CALIAN_MEMBER_DATA    CRPALACE_TEXTS + "calian_membership"
#define CALIAN_INFO_HANDLER   (CRPALACE_SPECIALS + "calian_info_handler")
#define CALIAN_TITLE_HANDLER  (CRPALACE_SPECIALS + "title_handler")
#define CALIAN_MEMBER_HANDLER (CRPALACE_SPECIALS + "calian_member_handler")
#define CALIAN_EVENTS_HANDLER (CRPALACE_SPECIALS + "calian_events_handler")
#define COUNCIL_VOTING_MANAGER (CRPALACE_SPECIALS + "council_voting_manager")
#define OLD_CALIAN_SHADOW     "/d/Calia/palace/specials/calian_shadow"
#define OLD_CALIAN_CMDSOUL    "/d/Calia/palace/specials/calian_cmdsoul"

#define GLYKRON_PATH		DOMAIN_DIR + "glykron/palace/"
#define GLYKRON_ROOMS		CRPALACE_PATH + "rooms/"
#define GLYKRON_LIGHT_ROOMS	CRPALACE_ROOMS + "light/"
#define GLYKRON_DARK_ROOMS	CRPALACE_ROOMS + "dark/"
#define GLYKRON_LIGHT_DOORS	CRPALACE_LIGHT_ROOMS + "doors/"
#define GLYKRON_DARK_DOORS	CRPALACE_DARK_ROOMS + "doors/"
#define GLYKRON_OBJECTS		CRPALACE_OBJECTS
#define GLYKRON_WEAPONS     CRPALACE_WEAPONS
#define GLYKRON_ARMOURS     CRPALACE_ARMOURS
#define GLYKRON_SPECIALS	CRPALACE_SPECIALS
#define GLYKRON_MONSTERS    CRPALACE_MONSTERS
#define GLYKRON_TEXTS       CRPALACE_TEXTS
#define GLYKRON_LOGS		CRPALACE_LOGS

#define ROOM(a)         (CRPALACE_SPECIALS + "path")->room_path(a)
#define DOOR(a)         (CRPALACE_SPECIALS + "path")->door_path(a)
#define OBJECT(a)       (CRPALACE_SPECIALS + "path")->object_path(a)
#define WEAPON(a)       (CRPALACE_SPECIALS + "path")->weapon_path(a)
#define ARMOUR(a)       (CRPALACE_SPECIALS + "path")->armour_path(a)
#define SPECIAL(a)      (CRPALACE_SPECIALS + "path")->special_path(a)
#define MONSTER(a)      (CRPALACE_SPECIALS + "path")->monster_path(a)
#define TEXT(a)		    (CRPALACE_SPECIALS + "path")->text_path(a)
#define LOG(a)		    (CRPALACE_SPECIALS + "path")->log_path(a)

#define OBJ_S_ORIGIN_ALIGNMENT	"_obj_s_origin_alignment"
#define CRYSTALLINE_KEY         456745764
#define CADET_TRAIN_ROOM        "/d/Calia/gelan/cadet/cadet_trainroom"
#define CALIAN_START_ROOM       CRPALACE_LIGHT_ROOMS + "guild"
#define FOLLOWER_START_ROOM     CRPALACE_LIGHT_ROOMS + "white"
#define OLD_CALIAN_START_ROOM   "/d/Calia/palace/rooms/light/guild"
#define OLD_FOLLOWER_START_ROOM "/d/Calia/palace/rooms/light/white"
#define DEBUGGER_TELL           "/d/Genesis/specials/debugger/debugger_tell.h"

// Used for specials
#define EVADE_BASE_OBJ          "/d/Genesis/specials/std/evade_obj_base"
#define DAMAGE_LIB              "/d/Genesis/specials/std/damage"
#define TIMED_ABILITY_LIB       "/d/Genesis/specials/timed_ability"
#define CALIAN_ATTACK_DESC      "/d/Calia/std/attack_desc"
#define SPECIALS_UTILITY        CRPALACE_SPECIALS + "calian_specials_utility"
#define SWARM_ABILITY           (CRPALACE_SPECIALS + "swarm")
#define MB_ABILITY              (CRPALACE_SPECIALS + "move_behind")
#define MBSW_ABILITY            (CRPALACE_SPECIALS + "mbsw")
#define RIPOSTE_ABILITY         (CRPALACE_SPECIALS + "riposte_attack")
#define OPPORTUNITY_ATTACK_SH   (CRPALACE_SPECIALS + "opportunity_attack_sh")
#define OPPORTUNITY_ATTACK      (CRPALACE_SPECIALS + "opportunity_attack")
#define SWARM_EVADE_OBJ         (CRPALACE_SPECIALS + "swarm_evade")
#define RIPOSTE_EVADE_OBJ       (CRPALACE_SPECIALS + "riposte_evade")
#define RIPOSTE_ATTACK          (CRPALACE_SPECIALS + "riposte_attack")
