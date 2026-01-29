inherit "/std/receptacle";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <money.h>
void
create_container() {
   set_name("pouch");
   set_adj("suede");
   set_adj("weathered");
   set_long("This old, weathered suede pouch has a draw string " +
      "to tie it closed and attach it to your belt.  It appears a " +
      "a little damaged by dry rot though.\n");
   add_prop(OBJ_I_VALUE,  75);
   add_prop(CONT_I_WEIGHT, 250);
   add_prop(CONT_I_VOLUME, 300);
   add_prop(CONT_I_MAX_WEIGHT, 2500);
   add_prop(CONT_I_MAX_VOLUME, 3000);
   add_prop(CONT_I_CLOSED, 1);
   set_alarm(0.0,0.0,"get_stuff");
}
get_stuff() {
   object ob1;
   object ob2;
   seteuid(getuid());
   ob1 = MONEY_MAKE(50 + random(50),"copper")->move(TO,1);
   ob2 = MONEY_MAKE(15 + random(15),"silver")->move(TO,1);
   clone_object("/d/Rhovanion/common/dungeon1/gear/ring2.c")
   ->move(TO,1);
}
