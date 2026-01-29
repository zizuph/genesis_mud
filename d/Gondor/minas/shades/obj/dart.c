/*
 *  A small rock
 *                          Tricky, 6-7-92
 *  Modified to be a dart by Sithas of GondorMud
 *  9-26-94
 */
inherit "/std/object";
#include "/d/Gondor/defs.h"
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
   set_name("dart");
   set_adj("small");
   set_pname("darts");
   set_short("small dart");
   set_pshort("small darts");
   set_long(break_string(
      "This is a small dart, with the right amount of skill someone might be "
      +"throw it quite acurately.\n",70));
   add_prop(OBJ_I_VALUE, 2);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 49);
}

init()
{
   add_action("do_throw","throw");
}
do_throw(str)
{
   int my_hit, dex;
   string tname, tobj,tmp;
   object tp, env;
   mixed target;

   tp = this_player();
   env = environment(tp);

   notify_fail("First get the dart, idiot!\n");
   if (environment() != tp)
      return 0;

   notify_fail("Throw at something or someone.\n");
   if (!str ||
       (!sscanf(str,"at %s",tmp) &&
        !sscanf(str,"dart at %s",tmp) &&
        !sscanf(str,"small dart at %s",tmp)))
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
   my_hit = dex + random(100);
   if (my_hit  >= 160)
   {
      tp->catch_msg("You throw the small dart at " + tname + " and hit "
          + tobj + ".\n" +
          "The dart sticks into your enemy!\n");
      target->catch_msg(QCTNAME(tp) + " throws a small dart at you "
          + "and hits you.\n" +
          "The dart sticks in you!\n");
      say(QCTNAME(tp) + " throws a small dart at " + tname + " and hits "
          + tobj + ".\n"  +
          "The dart sticks into " +tobj+"!\n",({tp,target}));
      tp->attack_object(target);
      target->hit_me(F_PENMOD(40,40),W_IMPALE,tp,0);
      move(target);
      return 1;
   }
   if (my_hit >= 120)
   {
      tp->catch_msg("You throw the small dart at " + tname + " and hit "
           + tobj + ".\n" +
           "The small dart falls to the ground.\n");
    target->catch_msg(QCTNAME(tp) + " throws a small dart at you " + " and hits you!\n"+
           "The small dart falls to the ground.\n");
      say(QCTNAME(tp) + " throws a small dart at " + tname + " and hits "
           + tobj + ".\n"  +
           "The small dart falls to the ground.\n",({tp,target}));
      tp->attack_object(target);
      target->hit_me(F_PENMOD(20,20),W_IMPALE,tp,0);
      move(env);
      return 1;
   }
   if (my_hit >= 80)
   {
      tp->catch_msg("You throw the small dart at " + tname + " and barely hit "
           + tobj + ".\n" +
           "The small dart falls to the ground.\n");
      target->catch_msg(QCTNAME(tp) + " throws a small dart at you and barely hits you!\n" +
           "The small dart falls to the ground.\n");
     say(QCTNAME(tp)+ " throws a small dart at "+tname+" and barely hits "+
            tobj + ".\n"  +
           "The small dart falls to the ground.\n",({tp,target}));
      tp->attack_object(target);
      target->hit_me(F_PENMOD(10,10),W_IMPALE,tp,0);
      move(env);
      return 1;
   }
   else
   {
      tp->catch_msg("You throw the small dart at " + tname + " but miss " +
          tobj + ".\n");
      target->catch_msg(QCTNAME(tp) + " throws a small dart at you "
          + "but misses you.\n");
      say(QCTNAME(tp) + " throws a small dart at " + tname + " but misses "
          + tobj + ".\n",({tp,target}));
      tell_room(env, "The small dart falls to the ground.\n");
     TO->move(env); /* And drop on the floor */
      return 1;
   }
   return 1;
}
