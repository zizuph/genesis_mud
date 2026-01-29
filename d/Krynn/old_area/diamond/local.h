/* Definitions */
#define PARENT       "/d/Krynn/"
#define DIDIR         PARENT + "diamond/"
#define DIARM         DIDIR + "armour/"
#define DILOG         DIDIR + "log/"
#define DINPC         DIDIR + "npc/"
#define DIOBJ         DIDIR + "obj/"
#define DIROOM        DIDIR + "room/"
#define DIDOORS       DIROOM + "doors/"
#define DISTD         DIDIR + "std/"
#define DITEXT        DIDIR + "text/"
#define DIWEP         DIDIR + "weapon/"

#define DRDIR         DIDIR + "drunks/"
#define DRLOG         DRDIR + "log/"
#define DROBJ         DRDIR + "obj/"
#define DRTEXT        DRDIR + "text/"

#define VK_NOBUY     "_vkeep_shop_no_buy"

#define IN_BASE      DISTD + "i_room_base"
#define OUT_BASE     DISTD + "o_room_base"
#define STREET       DISTD + "street_base"
#define BEACH        DISTD + "beach_base"

#define BARRACK      DISTD + "barrack_base"

#define TAPMASTERS   ({"kentari", "karath"})

/* Typical includes */
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

/* Helpful Coding Definitions */
#define AI           add_item
#define ACI          add_cmd_item
#define AE           add_exit

