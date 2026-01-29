inherit "/std/object";
#include "/d/Rhovanion/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"
#include "/sys/comb_mag.h"

void
create_object() {
   set_name("goo");
   set_adj("slimey");
   set_adj("brackish");
   set_short("handful of slimey, brackish goo");
   set_pshort("handfuls of slimey, brackish goo");
   set_long("This is a handful of disgusting blackish green " +
      "slimey goo.  It would be really demeaning if you threw " +
      "it at someone.\n"); 
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_I_VOLUME, 500);
}
init()
{
   ::init();
   add_action("do_throw","throw");
}
do_throw(str)
{
   int dex;
   string tname, tobj,tmp;
   object tp, env;
   mixed target;
   tp = this_player();
   env = environment(tp);
   if (environment() != tp)
      return notify_fail("First get the goo.\n");
   if (!str ||
         (!sscanf(str,"at %s",tmp) && !sscanf(str,"goo at s",tmp) &&
         !sscanf(str,"goo at %s",tmp)))
   return notify_fail("Throw at something or someone.\n");
   str = lower_case(tmp);
   target = present(str, env);
   if (!target || !CAN_SEE(TP, target))
      return notify_fail("No '" + str + "' here.\n");
   if (target == tp)
      return notify_fail("Why would you want to throw at yourself?\n");
   if (NPATTACK(target))
      return notify_fail("You cannot attack that way here.\n");
   if (living(target))
      {
      tname = QCTNAME(target);
      tobj  = target->query_objective();
   }
   else
      {
      tname = "the " + target->short();
      tobj  = "it";
   }
   dex = tp->query_stat(SS_DEX);
   if (dex + random(dex) > 15 )
      {
      tp->catch_msg("You throw the goo at " + tname + " and hit "
         + tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a handful of " +
         "slimey, brackish goo at you " +
         "and hits you.\n");
      say(QCTNAME(tp) + " throws a handful of slimey, brackish " +
         "goo at " + tname + " and hits " +
         tobj + ".\n",({target,tp}));
   }
   else
      {
      tp->catch_msg("You throw the goo at " + tname + " but miss " +
         tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a handful of slimey, " +
         "brackish goo at you " +
         "but misses.\n");
      say(QCTNAME(tp) + " throws a handful of slimey, brackish goo " +
         " at " + tname + " but misses "
         + tobj + ".\n",({tp,target}));
   }
   tp->catch_msg("The goo slides off " + tname + "'s face and " +
      "drops to the floor with a splat.\n");  
   target->catch_msg("The goo slides off your face and drops to the " +
      "floor with a splat.\n");
   say("The goo slides off " + tname + "'s face and " +
      "drops to the floor with a splat.\n",({target,tp}));
   move(env);
   return 1;
}
