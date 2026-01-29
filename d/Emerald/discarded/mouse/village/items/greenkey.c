/* key coded by Elizabeth Cook/Mouse, February 1997 */


inherit "/std/key.c";
#include <stdproperties.h>
#include "../../mouse.h"

void create_key() {
     set_name("silver key");
     add_name("key");
     set_short("silver skeleton key");
     set_long("A silver skeleton key with the letters 'GR' etched in the "+
          "handle.\n");
     add_prop(OBJ_I_WEIGHT, 20);
     add_prop(OBJ_I_VOLUME, 20);
     set_key(ROOT+"village/items/greenkey");
}

