/* a sign showing who REALLY discovered icewall created by Stevenson
* for Icewall */

#include <macros.h>

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
inherit "/std/object";

void create_object() {
   set_short("small sign");
   set_name("sign");
   set_long("You examine the sign which reads:\n\n"
      + "This place has been discovered by me, Quirply Goodmapper,\n"
      + "and established for the Kender Race!\n");
   add_prop(OBJ_I_NO_GET,1);
}
