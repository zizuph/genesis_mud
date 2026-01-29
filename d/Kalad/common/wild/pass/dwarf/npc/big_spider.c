/* A mean spider
   Made by Korat
   nov. 1996
*/
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";

#include <poison_types.h>
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LWING 1
#define A_RWING 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WINGS 3

create_monster() 
{
   ::create_monster();
   set_name("spider");
   set_race_name("spider");
   set_adj("monstreous");
   set_long("A gigantic arachnid, measuring as much as thirty feet across "+
      "when including the legs. That however is not the most amazing thing "+
      "about it, for spouting upon its back are two gossamer wings!\n");
   set_gender(G_NEUTER);
   set_stats(({100,120,100,90,80,100}));
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_AWARENESS,100);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,100000);
   add_prop(OBJ_I_NO_INS, 1);
   set_aggressive(1);
   set_act_time(3);
   add_act("emote clacks its mandibles together.");
   add_act("emote flaps its wings ever so slightly.");
   add_act("emote turns towards you, with venom dripping from "+
      "its mandibles.");
   set_attack_unarmed(A_BITE, 80, 80, W_IMPALE, 20, "poisonous mandibles");
   set_attack_unarmed(A_LWING, 50, 50, W_BLUDGEON, 40, "left wing-claw");
   set_attack_unarmed(A_RWING, 50, 50, W_BLUDGEON, 40, "right wing-claw");
   set_hitloc_unarmed(H_HEAD, ({ 50, 45, 45 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 60, 65, 65 }), 40, "scaled abdomen");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "hairy black legs");
   set_hitloc_unarmed(H_WINGS, ({ 10, 10, 10 }), 20, "clawed wings");
   add_prop(LIVE_I_SEE_DARK,10);
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(aid==A_BITE) {
      tell_object(enemy, "The spider swoops down and clamps its mandibles into you!\n");
      seteuid(getuid(TO));
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(200);
         poison->set_strength(50);
         poison->set_damage(({POISON_FATIGUE, 100, POISON_STAT, SS_CON}));
         poison->start_poison();
      }
   }
   return 0;
}

int
special_attack(object enemy)
{
   object me;
   object *ob;
   object stun;
   mixed* hitresult;
   string how;
   int i;
   me = this_object();
   if (random(4))
      return 0;
   ob = all_inventory(enemy);
   for(i=0;i<sizeof(ob);i++)
   {
      if(ob[i]->query_name()=="stun")
      {
         return 0;
      }
   }
   hitresult = enemy->hit_me(150 + random(100), W_BLUDGEON, me, -1);
   if(hitresult[0]>0)
      {
      me->catch_msg("The enormous spider pushes you hard with "+
         "its head towards the cobweb. The enemy is stuck!\n");
      enemy->catch_msg(QCTNAME(me)+" pushes you hard with "+
         "its head towards the cobweb. You are stuck!\n");
      tell_watcher(QCTNAME(me)+ " pushes "+QTNAME(enemy)+" hard "+
         "with its head towards the cobweb! "+
         QCTNAME(enemy)+" is stuck!\n",enemy);
      if (enemy->query_hp()<=0)
         {
         enemy->catch_msg("The touch seems to draw out the rest of your "+
            "life-energy.\n");
         tell_watcher(QCTNAME(enemy)+" starts to shake as the rest of "+
            enemy->query_possessive()+" energy of life is drawn out of "+
            "the body.\n",enemy);
         enemy->do_die(me);
      }
      seteuid(getuid(TO));
      stun=clone_object(CPASS(dwarf/obj/stun_web));
      stun->move(enemy);
      return 1;
   }
   me->catch_msg("You try to touch your enemy but miss.\n");
   enemy->catch_msg(QCTNAME(me)+" tries to push you into the cobweb "+
      "but misses.\n");
   tell_watcher(QCTNAME(me)+" tries to push "+QTNAME(enemy)+
      "but misses.\n",enemy);
   return 1;
}
