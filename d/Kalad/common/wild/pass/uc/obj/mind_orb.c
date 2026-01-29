inherit "/std/object";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("orb");
   set_adj("featureless");
   add_adj("white");
   set_long("An orb with a milkish-white quality to it, the varying hues of "+
      "white seem to twirl around violently within it.\n");
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
}
void
init()
{
   ::init();
   AA(use,use);
}
int
use(string str)
{
   if(!str || str != "orb")
      {
      NF("You can't use a '" + str + "'.\n");
      return 0;
   }
   write("You use the featureless white orb.\n");
   say(QCTNAME(TP) + " uses the featureless white orb.\n");
   set_alarm(3.0,0.0,"effect");
   return 1;
}
void
effect()
{
   write("An intense beam of green energy races from the featureless "+
      "white orb and bathes the room in its sickly light.\n");
   say("An intense beam of green energy races from the featureless "+
      "white orb held by " + QTNAME(TP) + " as it bathes the room in its "+
      "sickly light.\n");
   return;
}
