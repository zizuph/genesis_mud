inherit "/std/receptacle";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
void
create_container() {
   set_name("chest");
   set_adj("wooden");
   set_adj("small");
   set_long("This is a small, poor quality chest constructed " +
      "of some cheap and flimsy wood.  It has a lid and is " +
      "bolted to the floor.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_NO_GET,1);
   add_prop(CONT_I_WEIGHT, 500);
   add_prop(CONT_I_VOLUME, 550);
   add_prop(CONT_I_MAX_WEIGHT, 20000);
   add_prop(CONT_I_MAX_VOLUME, 20000);
   add_prop(CONT_I_CLOSED, 1);
   set_alarm(0.0,0.0,"get_clothes");
}
get_clothes() {
   seteuid(getuid());
   (clone_object("/d/Rhovanion/mute/dungeon1/wboots2.c")
      ->move(TO,1));
   (clone_object("/d/Rhovanion/mute/dungeon1/wpants.c")
      ->move(TO,1));
   (clone_object("/d/Rhovanion/mute/dungeon1/wshirt.c")
      ->move(TO,1));
}
