inherit "/std/receptacle";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
void
create_container() {
   set_name("pouch");
   set_adj("leather");
   set_adj("very old");
   set_long("This very old leather pouch appears to be suffering " +
      "from dry rot.  It is of simple design with ties for drawing " +
      "the pouch closed and ties for hanging the pouch from your belt.\n");
   add_prop(OBJ_I_VALUE,  75);
   add_prop(CONT_I_WEIGHT, 250);
   add_prop(CONT_I_VOLUME, 300);
   add_prop(CONT_I_MAX_WEIGHT, 1000);
   add_prop(CONT_I_MAX_VOLUME, 1000);
   add_prop(CONT_I_CLOSED, 1);
   set_alarm(0.0,0.0,"get_potion");
}
get_potion() {
   seteuid(getuid());
   clone_object("/d/Rhovanion/mute/dungeon1/hpotion2.c")->move(TO,1);
}
