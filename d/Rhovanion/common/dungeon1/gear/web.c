inherit "/std/receptacle";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <money.h>
void
create_container() {
   set_name("web");
   set_adj("sticky-white");
   set_adj("enormous");
   set_long("This has to be the largest web you have seen if not in your life then at least in a long, long time.  It's strands are thick as spears and probably as strong.  There seems to be a websack in the center for holding items or perhaps where the spiders sleep... if spiders do sleep that is.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(CONT_I_WEIGHT, 1000000);
   add_prop(CONT_I_VOLUME, 2000000);
   add_prop(CONT_I_MAX_WEIGHT, 10000000);
   add_prop(CONT_I_MAX_VOLUME, 10000000);
   set_alarm(0.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   object ob2;
   object ob3;
   object ob4;
   object ob5;
   object ob6;
   seteuid(getuid());
   for (i = 0; i < 3; i++)
   ob1 = clone_object("/d/Rhovanion/common/dungeon1/gear/jet.c")
   ->move(TO);
   ob2 = MONEY_MAKE(500,"copper")->move(TO);
   ob3 = MONEY_MAKE(115,"silver")->move(TO);
   ob4 = MONEY_MAKE(  3,"gold")->move(TO);
   ob5 = clone_object("/d/Rhovanion/common/dungeon1/gear/stat.c")
   ->move(TO);
   ob6 = clone_object("/d/Rhovanion/common/dungeon1/gear/ingot.c")
   ->move(TO);
}
