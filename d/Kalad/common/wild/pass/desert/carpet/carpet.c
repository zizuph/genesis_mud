inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <cmdparse.h>
/* by Antharanos */
create_object()
{
   set_name("carpet");
   set_pname("carpets");
   set_adj("flying");
   set_short("flying carpet");
   set_long("A magnificent carpet woven out of golden thread, intermixed with "+
      "shining platinum fibers. It is truly a stunning work of art. Although "+
      "it is hovering several feet off the ground, it looks possible to "+
      "board it.\n");
   add_prop(OBJ_M_NO_GET,"As you attempt to take the flying carpet, it "+
      "flies out of your reach.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
   add_prop(OBJ_I_VALUE,17280);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}

init()
{
   ::init();
   AA(all_aboard,board);
   AA(all_aboard,enter);
   AA(all_aboard,in);
   AA(all_aboard,go);
}
all_aboard(str) {
   if (query_verb() == "in")
      {
      if(str)
         return;
   }
   else if (!str)
      {
      NF("Go what?\n");
      if (query_verb() == "go")
         return 0;
   }
   else
      {
      NF(C(query_verb()) + " what?\n");
      if (str != "carpet" && str != "flying carpet")
         return 0;
   }
   TP->move("/d/Kalad/common/wild/pass/desert/carpet/on_carpet");
   tell_room(environment(TO),(QCTNAME(TP) + " boards the flying carpet.\n"),TP);
   tell_room(environment(TP),
      (QCTNAME(TP) + " arrives.\n"),TP);
   tell_object(TP,
      "You climb aboard the flying carpet.\n");
   TP->command("look");
   return 1;
}
