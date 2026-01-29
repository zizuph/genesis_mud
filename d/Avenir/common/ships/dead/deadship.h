#include "/d/Avenir/common/ships/ship.h"

#define WAREHOUSE    BAZAAR + "intr/dead_ware"
#define SHIPLOC      SHIP + "dead/deck"
#define DEADLOC      DEAD + "path/shore31"
#define OBJ          "/d/Avenir/common/ships/dead/obj/"

#define LANDING      "/d/Avenir/common/bazaar/intr/d_landing"
#define COFFLOC      "/d/Avenir/common/ships/dead/coffinroom"
#define DEAD_ENABLE  "_live_i_cango_dead"
#define DMASK_PROP   "_Avenir_death_mask_wearer"
#define COFFNAME     "_Avenir_coffin_"
#define COFFIN       OBJ + "coffin"
#define WOLF_BONE    "/d/Avenir/common/holm/wolf/"


//#define DEBUG

#ifdef DEBUG
#define D(x) find_player("cirion")->catch_msg("DEAD DEBUG: " + (x))
#else
#define D(x) ;
#endif

