inherit "/std/container";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
void
create_container() {
   set_name("helmet");
   set_adj(({"cracked","corroded"}));
   set_short("cracked and corroded helmet");
   set_pshort("a couple of crappy helmets");
   set_long("This ancient looking headpiece is styled with " +
      "a flanged neckpiece and nose guard and covered with slime " +
      "and goo making it undesirable to wear even if it were " +
      "possible to do so.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(CONT_I_WEIGHT, 3000);
   add_prop(CONT_I_VOLUME, 2500);
   add_prop(CONT_I_MAX_WEIGHT, 6000);
   add_prop(CONT_I_MAX_VOLUME, 5000);
   add_cmd_item("helmet","wear","@@try_wear");
   set_alarm(0.0,0.0,"get_stuff");
}
get_stuff() {
   object ob1;
   object ob2;
   object ob3;
   seteuid(getuid());
   ob1 = (MONEY_MAKE(random(50),"copper")->move(TO,1));
   ob2 = (MONEY_MAKE(random(2),"gold")->move(TO,1));
   ob3 = clone_object("/d/Rhovanion/common/dungeon1/gear/quartz.c")
   ->move(TO);
   return 1;
}
try_wear() {
   write("You can't wear broken armours!\n");
   return 1;
}
