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
   set_name("board");
   set_adj("wooden");
   set_adj("rotted");
   set_long("This is a length of board about three feet long " +
      "covered with slime and brackish goo that is rotted beyond " +
      "belief.  It would probably hurt if you bonked it on " +
      "someone.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 1400);
}
init()
{
   ::init();
   add_action("do_throw","bonk");
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
      return notify_fail("First get the board.\n");
   if (!str ||
         (!sscanf(str,"on %s",tmp) && !sscanf(str,"board on s",tmp) &&
         !sscanf(str,"board on %s",tmp)))
   return notify_fail("Bonk the board on someone!\n");
   str = lower_case(tmp);
   target = present(str, env);
   if (!target || !CAN_SEE(TP, target))
      return notify_fail("No '" + str + "' here.\n");
   if (target == tp)
      return notify_fail("Why would you want to bonk yourself?\n");
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
      tp->catch_msg("You bonk " + tname + " on the head with " +
         "your rotted wooden board.\n");
      target->catch_msg(QCTNAME(tp) + " bonks you on the head " +
         "with the rotted wooden board.\n");
      say(QCTNAME(tp) + " bonks " + tname + " on the head " +
         "with the rotted wooden board!\n",({target,tp}));
   }
   else
      {
      tp->catch_msg("You try to bonk " + tname + " on the head but miss " +
         tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " tries to bonk you with " +
         "the rotted wooden board but misses.\n");
      say(QCTNAME(tp) + " tries to bonk " + tname + " on the head with " +
         "the rotted wooden board but misses!\n",({tp,target}));
   }
   
   return 1;
}
