inherit "/std/container";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
void
create_container() {
   set_name("barrel");
   set_adj("rotted");
   set_adj("cracked");
   set_short("cracked and rotted barrel");
   set_pshort("cracked and rotted barrels");
   set_long("This old, dark wooded barrel is covered with slime " +
      "and brackish goo.  It has been rotted by years of exposure to " +
      "water and is cracked in a couple places, too.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(CONT_I_WEIGHT, 5000);
   add_prop(CONT_I_VOLUME,10000);
   add_prop(CONT_I_MAX_WEIGHT, 10000);
   add_prop(CONT_I_MAX_VOLUME, 20000);
   set_alarm(0.0,0.0,"get_stuff");
}
get_stuff() {
   object ob1;
   object ob2;
   object ob3;
   object ob4;
   seteuid(getuid());
   ob4 = clone_object(ONE_OF_LIST(({
               "/d/Rhovanion/common/dungeon1/gear/hpotion2.c",
               "/d/Rhovanion/common/dungeon1/gear/hpotion3.c"})))
   ->move(TO,1);
   ob1 = (MONEY_MAKE(10 + random(50), "silver")->move(TO,1));
   ob2 = (MONEY_MAKE(50 + random(100),"copper")->move(TO,1));
   ob3 = clone_object("/d/Rhovanion/common/dungeon1/gear/nosering.c")
   ->move(TO);
   return 1;
}
