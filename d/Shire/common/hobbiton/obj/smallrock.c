/*
 *  A small rock
 *                          Tricky, 6-7-92
 */

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"
#include "/sys/comb_mag.h"

void
create_object()
{
   set_name(({"_prot_spell_ingr1_","stone","rock"}));
   set_adj("small");
   set_pname(({"stones","rocks"}));
   set_short("small rock");
   set_pshort("small rocks");
   set_long(break_string(
      "This is a small piece of rock, like often found in rocky areas. "
    + "It looks utterly useless.\n",70));

   add_prop(OBJ_I_VALUE, 2);
   add_prop(OBJ_I_WEIGHT, 507);
   add_prop(OBJ_I_VOLUME, 492);
}

init()
{
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

   notify_fail("First get the small rock.\n");
   if (environment() != tp)
      return 0;

   notify_fail("Throw at something or someone.\n");
   if (!str ||
       (!sscanf(str,"at %s",tmp) &&
        !sscanf(str,"rock at %s",tmp) &&
        !sscanf(str,"small rock at %s",tmp)))
      return 0;

   str = lower_case(tmp);
   notify_fail("No " + str + " here.\n");
   if (!(target = present(str, env)))
      return 0;

   notify_fail("Why would you want to throw at yourself?\n");
   if (target == tp)
      return 0;

   notify_fail("You cannot attack that way here.\n");
   if(NPATTACK(target))
      return 0;

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
   if (dex + random(dex) > 25)
   {
      tp->catch_msg("You throw the small rock at " + tname + " and hit "
          + tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a small rock at you "
          + "and hits you.\n");
      say(QCTNAME(tp) + " throws a small rock at " + tname + " and hits "
          + tobj + ".\n",({target,tp}));
      tp->attack_object(target);
      target->hit_me(F_PENMOD(7,7),W_IMPALE,tp,0);
   }
   else
   {
      tp->catch_msg("You throw the small rock at " + tname + " but miss " + tobj
          + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a small rock at you "
          + "but misses you.\n");
      say(QCTNAME(tp) + " throws a small rock at " + tname + " but misses "
          + tobj + ".\n",({tp,target}));
   }
   tell_room(env, "The small rock falls on the floor.\n");
   move(env); /* And drop on the floor */
   return 1;
}
