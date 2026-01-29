/*all pathnames should be defined in here*/
#include "/d/Krynn/common/defs.h"

#define QUE          "/d/Krynn/que/"
#define SHU          QUE + "shu/"
#define SSTD         SHU + "std/"
#define ROOM         SHU + "room/"
#define LIV          SHU + "living/"
#define OBJ          SHU + "obj/"

/*general base for outside and inside rooms*/
#define OUTBASE_ROOM SSTD + "outside_base"
#define INBASE_ROOM  SSTD + "inside_base"

#define BARBARIAN          LIV + "barbarian";
#define SHUTABLE          "tblqueshu"
#define SHUTABLECHIEFTAIN "tblqueshuchieftain"
#define SHUTABLESHAMAN    "tblqueshushaman"


#if 0
/*the base for the changing room*
#define ATTACKROOM   ROOM + "attackroom"
/*the master for managing the attack*
#define ATTACKMASTER (ROOM + "attackmaster")

#define KIRITBL        COMMON_DIR + "rndtables/tblwarkiri"

/*other defines for the attack*
#define QUERY_STATE  (ATTACKMASTER->query_attack_state())
#define TRY_AGAIN   1000
#define FIRE_CHANCE 40
#define DIS(xx)     (xx)->query_base_stat(SS_DIS)
*/
#endif

/* defines for the inside rooms */
#define TENT      30
#define TEMPLE    31
#define SHAMANHUT 32
#define HOUSE     33
#define HALL      34


/* objects */
#define MSACK     (OBJ + "sack")
#define STAFF     (OBJ + "staff")
#define KNIFE     (OBJ + "knife")
#define CLOAK     (OBJ + "cloak")
#define LEATHERARMOR (OBJ + "larmour")
#define JACKET    ("/d/Krynn/solamn/palan/obj/cshirt")
#define PANTS     ("/d/Krynn/solamn/palan/obj/pants")
#define BLOUSE    ("/d/Krynn/solamn/palan/obj/cblouse")
#define SKIRT     ("/d/Krynn/solamn/palan/obj/skirt")


/* defines for the outside rooms */
#define MAINPATH  40
#define EASTPATH  41
#define WESTPATH  42
#define INTERSECT 43
#define SMALLPATH 44
#define NSPATH    45
#define ARENA     46
#define WELL      47

/*exits to the world*/
#define AB_PLAINS    QUE + "plains/rooms/"
#define NORTH_EXIT   AB_PLAINS + "plain-14-13-S"
#define SOUTH_EXIT   AB_PLAINS + "plain-14-11-M"
#define EAST_EXIT    AB_PLAINS + "plain-13-12-L"
#define WEST_EXIT    AB_PLAINS + "plain-15-12-A"

