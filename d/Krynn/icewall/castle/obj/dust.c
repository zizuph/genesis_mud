/* a pile of dust associated with  stac.c  for the mini-quest to */
/* fetch a hidden diamond ==> created by Stevenson for Icewall  */
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

inherit "/std/object";

create_object() {
   set_name("dust");
   set_short("pile of rocky debris");
   set_adj("rocky");
   add_name("pile");
   add_name("debris");
   
   set_long("You see a pile of mixed rock and dirt.\n");
   
   add_prop(OBJ_I_NO_GET,1);
}
