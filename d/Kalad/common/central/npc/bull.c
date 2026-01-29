inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include <wa_types.h>
#include <ss_types.h>
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_BODY 0
#define H_HEAD 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4
/* by Korat */
create_monster()
{
   set_name("bull");
   set_race_name("giant");
   set_adj("cruel");
   add_adj("mountain");
   set_long("A vicious-looking beast from the Hespyre mountains. It "+
      "looks as if it hasn't eaten in awhile.\n");
   set_stats(({219,132,168,20,10,170}));
   set_gender(G_NEUTER);
   set_skill(SS_DEFENCE, 75);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT, 580000);
   add_prop(OBJ_I_VOLUME, 200000);
   add_prop(OBJ_I_NO_INS,1);
   set_act_time(3);
   add_act("snarl all");
   add_act("growl all");
   add_act("emote grunts.");
   add_act("kick rat");
   add_act("spit rat");
   add_act("kill rat");
   set_cact_time(1);
   add_cact("emote roars angrily.");
   add_cact("kick all");
   add_cact("emote tries to grab you, but misses!");
   add_cact("emote slashes a fist out against you but misses by an inch.");
   add_cact("emote stomps on your feet, hard!");
   set_attack_unarmed(A_BITE, 45, 55, W_BLUDGEON, 20, "headbutt");
   set_attack_unarmed(A_LCLAW, 55, 60, W_BLUDGEON, 40, "huge left fist");
   set_attack_unarmed(A_RCLAW, 55, 60, W_BLUDGEON, 40, "huge right fist");
   set_hitloc_unarmed(H_HEAD, ({ 25, 45, 60 }), 10, "big head");
   set_hitloc_unarmed(H_BODY, ({ 60, 60, 60 }), 20, "broad chest");
   set_hitloc_unarmed(H_RARM, ({ 40, 40, 40 }), 20, "enormous arms");
   set_hitloc_unarmed(H_LARM, ({ 40, 30, 50 }), 30, "huge belly");
   set_hitloc_unarmed(H_LEGS, ({ 60, 60, 35 }), 20, "hairy legs");
   set_hitloc_unarmed(H_BODY, ({ 45, 35, 60 }), 80, "broad body");
}


tell_watcher(string str, object enemy)
{
   object me, *ob;
   int i;
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   string direction;
   int i;
   me = this_object();
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(400 + random(200), W_BLUDGEON, me, -1);
   how = "barely scratched";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 10)
      how = "dizzy";
   if (hitresult[0] > 20)
      how = "very dizzy";
   if (hitresult[0]> 40)
      how = "rather hurt";
   if (hitresult[0] > 60)
      how = "crushed";
   switch (random(8))
   {
      case 0: direction = "north"; break;
      case 1: direction = "east"; break;
      case 2: direction = "south"; break;
      case 3: direction = "west"; break;
      case 4: direction = "northeast"; break;
      case 5: direction = "northwest"; break;
      case 6: direction = "southeast"; break;
      case 7: direction = "southwest"; break;
      default: break;
   }
   if ((i=member_array(direction, environment(TO)->query_exit()))<0)
      {
      me->catch_msg("You hurl "+QTNAME(enemy)+" into a wall "+direction+
         " of you. he or she looks "+how+"!\n");
      enemy->catch_msg(QCTNAME(me)+" grabs you, and hurl you into the wall "+
         direction+" of you. You feel "+how+" after hitting the stones.\n");
      tell_watcher(QCTNAME(me)+" grabs "+QTNAME(enemy)+" and hurls "+
         enemy->query_objective()+" into the "+direction+"ern wall. "+
         capitalize(enemy->query_pronoun())+" looks "+how+"!\n",enemy);
      if (enemy->query_hp()<=0)
         {
         enemy->catch_msg("The hit knocks you out cold. Everything "+
            "is black...\n");
         tell_watcher(QCTNAME(enemy)+" looks uttery crushed, and you "+
            "see the eyes loose its sparkle of life.\n");
         enemy->do_die(me);
       }
      return 1;
   }
   me->catch_msg("You grab "+QTNAME(enemy)+" and hurl him "+direction+"!\n");
   enemy->catch_msg(QCTNAME(me)+" grabs you, and hurls you "+direction+
      " with an enormous power! You are flying...\n");
   tell_watcher(QCTNAME(me)+" grabs "+QTNAME(enemy)+" and hurls "+
      enemy->query_objective()+" "+direction+" with an enormous "+
      "power! "+QCTNAME(enemy)+" leaves "+direction+", flying.\n", enemy);
   enemy->command(direction);
   tell_room(environment(enemy),QCTNAME(enemy)+" comes flying into "+
      "the room, and lands hard on the floor. "+
      capitalize(enemy->query_pronoun())+" looks "+how+"!\n",enemy);
   enemy->catch_msg("You hit the floor, and feel "+how+"!\n");
   if (enemy->query_hp()<=0) enemy->do_die(me);
   return 1;
}

