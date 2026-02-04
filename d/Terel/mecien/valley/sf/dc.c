inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/domove";
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <wa_types.h>
#include <poison_types.h>

#define ENV environment
#define TO this_object()

#define W_BITE 0
#define W_RCLAW 1
#define W_LCLAW 2

#define H_BODY 0
#define H_HEAD 1

create_creature(){
   set_name("shadow");
   set_adj("horrifying");
   set_race_name("shadow");
   set_long(
      "A horrifying demon creature, spawn of the abyss. Its claws long\n"
      +"and wicked, its form black and shadowy. Its eyes burn with a strange\n"
      + "purple fire, yet it looks magnificent, a dark beauty, human-like in body,\n"
      + "dazzling to behold.\n"
   );
   set_gender(2);
   set_base_stat(SS_INT, 50);
   set_base_stat(SS_WIS, 60);
   set_base_stat(SS_DIS, 80);
   set_base_stat(SS_STR, 100);
   set_base_stat(SS_DEX, 125);
   set_base_stat(SS_CON, 100);
   set_skill(SS_WEP_SWORD, 90);
   set_skill(SS_WEP_KNIFE, 120);
   set_skill(SS_PARRY, 70);
   set_skill(SS_DEFENCE, 100);
   set_hp(10000);
   
   set_aggressive(1);
   set_hitloc_unarmed(H_BODY, 70, 90, "body");
   set_hitloc_unarmed(H_HEAD, 50, 10, "head");
   
   set_act_time(4);
   add_act("emote poises itself, as if to attack!");
   add_act("emote hisses out a deep gutteral sound.");
   add_act("emote hunches over and whispers some cryptic language.");
   set_cact_time(1);
   add_cact("@@spit");
   add_prop(LIVE_I_UNDEAD, 90);
   add_prop(LIVE_I_NO_CORPSE, 1);
   
   set_alignment(-900);
   
   set_attack_unarmed(W_BITE, 50, 45, W_IMPALE, 40, "hideous fangs");
   set_attack_unarmed(W_RCLAW, 70, 40, W_SLASH, 70, "hideous fangs");
   set_attack_unarmed(W_LCLAW, 70, 40, W_SLASH, 70, "hideous fangs");
   
   
}

spit(){
   
   object enemy;
   int num;
   
   enemy = TO->query_attack();
   num = random(100) + (TO->query_stat(SS_DEX)/10) -
   (enemy->query_stat(SS_DEX)/10);
   if(num > 100){
      enemy->catch_msg("The horrifying shadow strikes you with spittle!\n");
      tell_room(ENV(TO), "The horrifying shadow strikes " +
         QCTNAME(enemy) + " with a bit of spittle!\n", enemy);
      set_alarm(10.0, -1.0, "it_burns", enemy);
   }
   enemy->catch_msg("The horrifying shadow spits at you.\n");
   tell_room(ENV(TO), "The horrifying shadow spits at " +
      QCTNAME(enemy) + ".\n", enemy);
}

destroy_weapon(object weapon, object att){
   
  weapon->move(TO);
   tell_room(ENV(att), "The " + weapon->query_short() +
      " wielded by " + QCTNAME(att) + " is consumed by darkness!\n", att);
   att->catch_msg("Your " + weapon->query_short() + " is consumed by " 
      + "darkness!\n");
   weapon->remove_object();
}
int
query_not_attack_me(object att, int att_id)
{
   object weapon = att->query_weapon(att_id);
   
   
   if (!weapon) 
      return 1;
  if(!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
   {
    if(random(10))
   {
    att->catch_msg("Your " + weapon->query_short() +
     " passes right through the shadow's body!\n");
         tell_room(ENV(TO),QCTNAME(att)+"'s " + weapon->query_short() +
         " passes through the shadow's body!\n",att);
   }
      else 
   {
         destroy_weapon(weapon,att);
      return 1;
   }
   }
}



do_die(object killer){
   ::do_die(killer);
   tell_room(ENV(killer), "The horrifying shadow" +
      " dissolves into a black mist.\n");
}

enter_env(object to, object from){
   tell_room(ENV(TO), QCTNAME(TO) + " cries out in primal joy!\n");
   ::enter_env(to, from);
}

/*
* Function name: cr_did_hit
* Description:   This function is called from the combat object to give
*                appropriate messages.  We shall remain content to let 
*                the default messages be sent, but we will give poison 
*                to the hit creature.
* Arguments:     aid:   The attack id
*                hdesc: The hitlocation description.
*                phurt: The %hurt made on the enemy
*                enemy: The enemy who got hit
*                dt:    The current damagetype
*                phit:  The %success that we made with our weapon
*                       If this is negative, it indicates fail
*/

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   
   /* I believe the spider poisons the player each bite. it should of course
   * be harder to poison the player again and again, Nick */
   
   if(aid==W_BITE) {
      tell_object(enemy, "The horrifying shadow's fangs burn you.\n");
      
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(80);
         poison->set_strength(35);
         poison->set_damage(({POISON_MANA, 50, POISON_STAT, SS_DIS }));
         poison->start_poison();
         
      }
   }
   
   if(aid==W_RCLAW) {
      tell_object(enemy, "The horrifying shadow's claw numbs you.\n");
      enemy->add_tmp_stat(0, -1, 300);
      enemy->add_tmp_stat(1, -1, 300);
      
   }
   
   if(aid==W_RCLAW) {
      tell_object(enemy, "The horrifying shadow's claw numbs you.\n");
      enemy->add_tmp_stat(0, -1, 300);
      enemy->add_tmp_stat(2, -1, 300);
      
   }
   
   return 0;
}



int
special_attack(object enemy){
   
   object me;
   mixed* hitresult;
   string how;
   
   me = this_object();
   if(random(3))
      return 0;
   
   if(present("mystic_guardians", enemy)){
      enemy->catch_msg(QCTNAME(me) + " places a claw to your chest but draws it back in fear!\n");
      tell_watcher(QCTNAME(me) + " places its claw before the chest of " +
         QTNAME(enemy) + " but draws back in fear!\n", enemy);
      return 0;
   }
   hitresult = enemy->hit_me(35+random(40), MAGIC_DT, me, -1);
   me->catch_msg("You rape the soul of your victim!\n");
   enemy->catch_msg(QCTNAME(me) + " places a claw to your chest and draws out your life force!\n");
   tell_watcher(QCTNAME(me) + " places its claw before the chest of " +
      QTNAME(enemy) + " and part of " + enemy->query_possessive() + 
      " life force is taken away.\n", enemy);
   me->heal_hp(100);
   enemy->add_exp(-100);
   
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 0;
}

