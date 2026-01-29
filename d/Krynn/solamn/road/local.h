
#include "/d/Krynn/common/defs.h"
#include <macros.h>


/* This defines the pathnames of this dir */
#define TDIR           SOLAMN_DIR + "road/"

/*inherit file*/
#define ROOM_BASE      TDIR + "room_base";
#define SOLAMNIAN      TDIR + "npc/solamnian";
#define STDDOOR        "/d/Krynn/std/door"

/*special rooms*/
#define MAP            TDIR + "map"
#define ROAD_OBJECT    TDIR + "area_obj"

#define VKEEP          TDIR + "vkeep_link"
#define KALAMAN        TDIR + "kalaman_link"
#define DARGAARD       TDIR + "dargaard_link"
#define THROTL         TDIR + "throtl_link"
#define WATERFALL      TDIR + "waterfall"
#define SOLANTHUS      TDIR + "solanthus_link"
#define SPRING         TDIR + "spring"
#define REFUGEES       TDIR + "refugees"
#define RUINS          TDIR + "ruins"
#define FORD           TDIR + "ford"
#define DRACCAMP1      TDIR + "drac_camp1"
#define DRACCAMP2      TDIR + "drac_camp2"
#define STREAMRIVER    TDIR + "streamriver"
#define CROSSROADS     TDIR + "crossroads"

#define FLOODABLE_ROOMS ({ TDIR+"river1", TDIR+"river2", TDIR+"river3" })

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



/* general defines for the area */
#define AREA_NAME      "Eastern Solamnian Plains"

/* connections to the world */
#define VKEEP_LINK     "/d/Krynn/solamn/splains/room/ferry"
#define KALAMAN_LINK   "/d/Ansalon/kalaman/city/gate1"
#define DARGAARD_LINK  "/d/Krynn/dargaard/xxx"
#define THROTL_LINK    "/d/Ansalon/throtl/xxx"
#define SOLANTHUS_LINK "/d/Krynn/solamn/south/road1"
#define FORD_LINK      "/d/Krynn/solamn/splains/xxx"
