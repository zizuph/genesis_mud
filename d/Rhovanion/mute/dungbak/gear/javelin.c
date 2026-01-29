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
   set_name("javelin");
   set_adj("broken");
   set_adj("old");
   set_long("This is the top half of an old wooden javelin still " +
      "still retaining its rusty head.  You could probably still " +
      "throw it at someone though it most likely wouldn't hurt them " +
      "very much.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 1400);
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
      return notify_fail("First get the javelin.\n");
   if (!str ||
         (!sscanf(str,"at %s",tmp) && !sscanf(str,"javelin at s",tmp) && !sscanf(str,"javelin at %s",tmp)))
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
      tp->catch_msg("You throw the javelin at " + tname + " and hit "
         + tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a javelin at you " +
         "and hits you.\n");
      say(QCTNAME(tp) + " throws a javelin at " + tname + " and hits " +
         tobj + ".\n",({target,tp}));
   }
   else
      {
      tp->catch_msg("You throw the javelin at " + tname + " but miss " +
         tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a javelin at you " +
         "but misses.\n");
      say(QCTNAME(tp) + " throws a javelin at " + tname + " but misses "
         + tobj + ".\n",({tp,target}));
   }
   tell_room(env, "The javelin drops to the floor.\n");
   move(env);
   return 1;
}
