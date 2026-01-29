/*  ~Calia/palace/defs.h 

    (and for the time being also 
    ~Calia/glykron/palace/defs.h) 
 */

#include "/d/Calia/domain.h"

#define RANDOM_HEADER         "/d/Calia/sys/random.h"
#define MAP_HEADER            "/d/Calia/sys/map.h"
#define CALIAN_HEADER         "/d/Calia/palace/specials/calian.h"
#define COUNCIL_HEADER        "/d/Calia/palace/specials/council.h"
#define RECRUITER_HEADER      "/d/Calia/palace/specials/recruiter.h"

#define CALIAN_TAUNT_OBJECT "/d/Calia/palace/specials/olde_insulte"
#define CALIAN_INFO_HANDLER  \
                 "/d/Calia/palace/specials/calian_info_handler"
#define WARNING_SIGNAL_OBJECT "/d/Calia/palace/specials/warning_sig"
#define CALIAN_TITLE_HANDLER "/d/Calia/palace/specials/title_handler"

#define ROAD_DIR              DOMAIN_DIR + "overlord/road/rooms/"
#define CRPALACE_PATH         DOMAIN_DIR + "palace/"
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

#define GLYKRON_PATH		DOMAIN_DIR + "glykron/palace/"
#define GLYKRON_ROOMS		GLYKRON_PATH + "rooms/"
#define GLYKRON_LIGHT_ROOMS	GLYKRON_ROOMS + "light/"
#define GLYKRON_DARK_ROOMS	GLYKRON_ROOMS + "dark/"
#define GLYKRON_LIGHT_DOORS	GLYKRON_LIGHT_ROOMS + "doors/"
#define GLYKRON_DARK_DOORS	GLYKRON_DARK_ROOMS + "doors/"
#define GLYKRON_OBJECTS		CRPALACE_OBJECTS
#define GLYKRON_WEAPONS       CRPALACE_WEAPONS
#define GLYKRON_ARMOURS       CRPALACE_ARMOURS
#define GLYKRON_SPECIALS	GLYKRON_PATH + "specials/"
#define GLYKRON_MONSTERS      CRPALACE_MONSTERS
#define GLYKRON_TEXTS         CRPALACE_TEXTS
#define GLYKRON_LOGS		CRPALACE_LOGS

#define ROOM(a)         (GLYKRON_SPECIALS + "path")->room_path(a)
#define DOOR(a)         (GLYKRON_SPECIALS + "path")->door_path(a)
#define OBJECT(a)       (GLYKRON_SPECIALS + "path")->object_path(a)
#define WEAPON(a)       (GLYKRON_SPECIALS + "path")->weapon_path(a)
#define ARMOUR(a)       (GLYKRON_SPECIALS + "path")->armour_path(a)
#define SPECIAL(a)      (GLYKRON_SPECIALS + "path")->special_path(a)
#define MONSTER(a)      (GLYKRON_SPECIALS + "path")->monster_path(a)
#define TEXT(a)		(GLYKRON_SPECIALS + "path")->text_path(a)
#define LOG(a)		(GLYKRON_SPECIALS + "path")->log_path(a)

#define OBJ_S_ORIGIN_ALIGNMENT	"_obj_s_origin_alignment"
#define CRYSTALLINE_KEY 456745764
