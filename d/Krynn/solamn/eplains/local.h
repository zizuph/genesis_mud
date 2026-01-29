#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"
#include <macros.h>

/* This defines the pathnames of this dir */
#define TDIR           SOLAMN_DIR + "eplains/"

/* non area base room */
#define ROOM_BASE	TDIR + "room_base"

/*special rooms*/
#define FLOODABLE_ROOMS ({ TDIR+"river1", TDIR+"river2", TDIR+"river3" })
#define VKEEP		TDIR+"rooms/eplain-4-21-V"

/* other objects */
#define UNDEAD         TDIR + "npc/deathknight"
#define FERRY          TDIR + "ferry/ferry"
#define KEY            TDIR + "obj/keys"
#define DOORINSIDE     TDIR + "obj/doori"
#define DOOROUTSIDE    TDIR + "obj/dooro"
#define VAULT_KEY      897563
#define JDAGGER        TDIR + "obj/jdagger"
#define DISPOTION      TDIR + "obj/dispotion"

#define QOBJ      "/d/Krynn/que/shu/obj/"
#define MSACK     (QOBJ + "sack")
#define STAFF     (QOBJ + "staff")
#define KNIFE     (QOBJ + "knife")
#define CLOAK     (QOBJ + "cloak")
#define LEATHERARMOR (QOBJ + "larmour")
#define SWORD     ("/d/Krynn/solamn/splains/obj/bsword")
#define JACKET    ("/d/Krynn/solamn/palan/obj/cshirt")
#define PANTS     ("/d/Krynn/solamn/palan/obj/pants")
#define BLOUSE    ("/d/Krynn/solamn/palan/obj/cblouse")
#define SKIRT     ("/d/Krynn/solamn/palan/obj/skirt")

/* connections to the world */
#define VKEEP_LINK     "/d/Krynn/solamn/splains/room/ferry"
#define KALAMAN_LINK   "/d/Ansalon/kalaman/city/gate1"
#define SOLANTHUS_LINK "/d/Krynn/solamn/south/road1"
#define DARGAARD_LINK  "/d/Ansalon/dargaard/room/road1"
#define THROTL_LINK    "/d/Krynn/throtyl/rooms/throtyl-4-2-P"
#define FORD_LINK      "/d/Krynn/solamn/splains/xxx"
