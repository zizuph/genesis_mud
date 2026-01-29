/* this is the include file for all programms in the lost land

history:

DATE		WHAT DONE					WHO DID
23.10.93	created						Deinonychus

*/

#include "/d/Calia/deinonychus/dino.h"

#define DUST		"/d/Terel/dust/"

#define VOLCANO		DINO + "volcano/"
#define ROOMS		VOLCANO + "rooms/"
#define CAVE1		ROOMS + "cave1/"
#define CAVE2		ROOMS + "cave2/"
#define TRACK		ROOMS + "track/"
#define OBJECTS		VOLCANO + "objects/"
#define WEAPONS		VOLCANO + "weapons/"
#define ARMOURS		VOLCANO + "armours/"
#define MONSTERS	VOLCANO + "monsters/"
#define SPECIALS	VOLCANO + "specials/"

/* functions to use the string functions */
/* eventually you'll have to use seteuid(getuid()); before a call */

#define ROOM(x)         (SPECIALS + "path")->room_path(x)
#define OBJECT(x)       (SPECIALS + "path")->object_path(x)
#define WEAPON(x)       (SPECIALS + "path")->weapon_path(x)
#define ARMOUR(x)       (SPECIALS + "path")->armour_path(x)
#define DOOR(x)         (SPECIALS + "path")->door_path(x)
#define SPECIAL(x)      (SPECIALS + "path")->special_path(x)
#define MONSTER(x)      (SPECIALS + "path")->monster_path(x)

#define DESC(x)		(SPECIAL("desc"))->desc(x)
