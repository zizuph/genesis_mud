inherit "/std/object.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_object()
{
   ::create_object();
   set_name("weed");
   set_adj("funny");
   add_adj("little");
   set_long("A funny-looking brown weed, it doesn't look the slightest "+
      "bit edible. However, it does appear as if you could wave it around "+
      "in the air, to spread its odor.\n");
   add_prop(OBJ_M_NO_SELL,"I don't want this weed!\n");
   add_prop(OBJ_I_VALUE,5184);
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
   add_prop(OBJ_I_LIGHT,1);
}
void
init()
{
   ::init();
   AA(wave,wave);
}
int
wave(string str)
{
   if(!str || str != "weed")
      {
      NF("You can't wave a '" + str + "'.\n");
      return 0;
   }
   write("You wave the funny little weed wildly in the air.\n");
   say(QCTNAME(TP) + " waves the funny little weed wildly in the air.\n");
   set_alarm(3.0,0.0,"effect");
   return 1;
}
void
effect()
{
   write("A horrible odor wafts throughout the room.\n");
   say("A horrible odor wafts throughout the room.\n");
   return;
}
