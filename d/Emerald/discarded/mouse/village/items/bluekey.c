/* key coded by Elizabeth Cook/Mouse, February 1997 */


inherit "/std/key.c";
#include "/sys/stdproperties.h" 
#include "../../mouse.h"

void create_key() {
     set_name("brass key");
     add_name("key");
     set_short("brass skeleton key");
     set_long("A brass skeleton key with the letters 'BL' etched in the "+
          "handle.\n");
     add_prop(OBJ_I_WEIGHT, 20);
     add_prop(OBJ_I_VOLUME, 20);
     set_key(ROOT+"village/items/bluekey");
}

