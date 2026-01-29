/* A carcass appearing to be whatever race you are
Created By Stevenson */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include "/sys/language.h"
inherit "/std/object";

create_object() {
   set_short("decaying corpse");
   set_adj("decaying");
   set_name("corpse");
   set_long("You see the corpse of @@adjrace@@. The body looks like it "
      + "has been ripped nearly to shreds. Perhaps you should "
      + "move along before you become the next victim. "
      + "\n");
   
   add_item("body","The poor @@race@@ didn't even stand a chance.\n");
   add_prop(OBJ_M_NO_GET,"Something might be very unhappy if you try to "
      + "steal its dinner.\n");
}

string race() {
   return TP->query_race();
}

string adjrace() {
   return LANG_ADDART(race());
}
