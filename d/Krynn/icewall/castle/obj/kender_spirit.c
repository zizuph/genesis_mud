/* spirit of the frozen kender created by Stevenson 
* for Icewall */

#include <macros.h>

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
inherit "/std/object";

void create_object() {
   set_short("strange mist");
   set_name("mist");
   add_name("kender_spirit");
   set_adj("strange");
   set_long("This mist is the spirit of a kender who was frozen to death "
      + "while mapping out the caverns of Icewall.\n");
   
   add_prop(OBJ_M_NO_GET,"You close your hand around the mist and it seeps "
      + "through your fingers.\n");
   add_prop(OBJ_I_WEIGHT, 2);
   add_prop(OBJ_I_VOLUME, 2);
}
