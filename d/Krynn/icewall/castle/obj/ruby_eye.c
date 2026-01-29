/* a Ruby Eye coded for Icewall by Stevenson */

#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit "/std/object";

void init() {
   ADA("rotate");
   ::init();
}

void
create_object() {
   set_name("eye");
   add_name("ruby");
   set_adj("ruby");
   set_short("ruby eye");
   set_long("It appears that upon death, the red dragon's "
      + "eyes crystalized, becoming rubies. This is one of those "
      + "eyes. If you rotate it, you can see it sparkle. "
      + "\n");
   
   add_prop(OBJ_I_VALUE, 2000);
   add_prop(OBJ_I_WEIGHT, 175);
}

int rotate(string arg) {
   NF("What?\n");
   if (arg != "ruby" && arg != "eye") return 0;
   write("You turn the ruby over in your hands dazed at its "
      + "brilliance.\n");
   tell_room(E(TP),"There is a bright flash of red light from "
      + QNAME(TP) + "'s hand.\n", TP);
   return 1;
}
