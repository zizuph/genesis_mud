/* ~glykron/palace/defs.h */

#include "/d/Calia/domain.h"

#define RANDOM_HEADER		"/d/Calia/sys/random.h"
#define MAP_HEADER		"/d/Calia/sys/map.h"
#define CALIAN_HEADER		"/d/Calia/glykron/palace/specials/calian.h"
#define COUNCIL_HEADER		"/d/Calia/glykron/palace/specials/council.h"
#define RECRUITER_HEADER        "/d/Calia/glykron/palace/specials/recruiter.h"

#define ROAD_DIR		DOMAIN_DIR + "overlord/road/rooms/"
#define GLYKRON_PATH		DOMAIN_DIR + "glykron/palace/"
#define GLYKRON_ROOMS		GLYKRON_PATH + "rooms/"
#define GLYKRON_LIGHT_ROOMS	GLYKRON_ROOMS + "light/"
#define GLYKRON_DARK_ROOMS	GLYKRON_ROOMS + "dark/"
#define GLYKRON_LIGHT_DOORS	GLYKRON_LIGHT_ROOMS + "doors/"
#define GLYKRON_DARK_DOORS	GLYKRON_DARK_ROOMS + "doors/"
#define GLYKRON_OBJECTS		GLYKRON_PATH + "objects/"
#define GLYKRON_WEAPONS		GLYKRON_PATH + "weapons/"
#define GLYKRON_ARMOURS		GLYKRON_PATH + "armours/"
#define GLYKRON_SPECIALS	GLYKRON_PATH + "specials/"
#define GLYKRON_MONSTERS	GLYKRON_PATH + "monsters/"
#define GLYKRON_TEXTS		GLYKRON_PATH + "texts/"
#define GLYKRON_LOGS		GLYKRON_PATH + "logs/"

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
