inherit "/std/receptacle";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
void
create_container() {
   set_name("hand");
   set_adj("human");
   set_adj("rotted");
   set_long("This is the detached hand of some unfortunate " +
      "human.  It's pretty decayed and smells awful!\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(CONT_I_WEIGHT, 500);
   add_prop(CONT_I_VOLUME, 550);
   add_prop(CONT_I_MAX_WEIGHT, 2000);
   add_prop(CONT_I_MAX_VOLUME, 2000);
   add_prop(CONT_I_CLOSED, 1);
   set_alarm(0.0,0.0,"get_ingot");
}
get_ingot() {
   seteuid(getuid());
   return (clone_object("/d/Rhovanion/common/dungeon1/gear/ingot.c")
      ->move(TO,1));
}
