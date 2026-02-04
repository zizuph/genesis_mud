
inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack"; /* Added here y nick to make this file load */

#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <poison_types.h>
#include <macros.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4
#define A_SBITE 5


#define H_HEAD 0
#define H_BODY 1

#define TP this_player()
#define TO this_object ()
#define EN environment

poisoned(object who){
   object ob;
   if(living(who)){
      if(who->query_stat(SS_DEX) < random(150)){
         seteuid(getuid());
         who->catch_msg("You fail to escape the cloud of poison!\n");
         ob = clone_object("/std/poison_effect");
         ob->move(who);
         ob->start_poison();
      }
   }
   
}


create_creature()
{
   set_name("chimera"); 
   set_race_name("chimera");
   set_short("chimera");
   set_adj(({"evil", "winged" }));
   set_long(
      "A hideous and terrifying creature, born of the dark places of the pit. "
      + "Its body that of a great lion, dark and golden. It has three heads " 
      +"One being a lion, with fiery eyes, the second being serpentine, the third, that "
      +"of a black eyed goat. Bat-like wings adorn its back.\n");
   
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 156, 167, 190, 95, 90, 100}));
   
   set_skill(SS_DEFENCE, 99);
   set_alignment(-600);
   set_fatigue(9000);
   set_hp(40000);
   set_gender(2);
   
   set_act_time(1);
   add_act("@@growls");
   add_act("@@hiss");
   add_act("@@flap");
   add_cact("@@hypn");
   add_act("@@flames");
   add_cact("@@heal");
   set_attack_unarmed(A_BITE,  90, 60, W_IMPALE, 60, "lion jaws");
   set_attack_unarmed(A_LCLAW, 73, 35, W_SLASH,  40, "left claw");
   set_attack_unarmed(A_RCLAW, 73, 40, W_SLASH,  45, "right claw");
   set_attack_unarmed(A_TAIL, 92, 50, W_BLUDGEON,  70, "barbed tail");
   set_attack_unarmed(A_HORN, 81, 66, W_IMPALE,  60, "goat horns");
   set_attack_unarmed(A_SBITE, 88, 65, W_IMPALE, 40, "serpent fangs");
   
   
   set_hitloc_unarmed(H_HEAD, ({ 85 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 90 }), 80, "body");
}

hiss(){
   tell_room(environment(this_object()), "The chimera's serpent head hisses violently.\n");
   return 1;
}
growls(){
   tell_room(environment(this_object()), "The chimera's lion head growls loudly.\n");
   return 1;
}
flap(){
   tell_room(environment(this_object()), "The chimera flaps its wings wildly.\n");
   return 1;
}
flames(){
   object poison;
   write("The chimera's serpent head spews forth a cloud of poison.\n");
   map(all_inventory(EN(TO)), poisoned);
   return 1;
}
heal(){
   tell_room(environment(this_object()), "The chimera's serpent head " +
      "hisses arcane words.\nThe chimera is surrounded by a purple glow.\n");
   this_object()->heal_hp(300);
}
hypn(){
   object target;
   int res;
   target = TO->query_attack();
   target->catch_msg("The chimera's lion head looks at you.\n");
   res = resolve_task(TASK_ROUTINE, 0, target, ({TS_DIS, TS_WIS}));
   if(res){
      tell_room(environment(this_object()), "The chimera's eyes glare at you!\n");
      tell_room(environment(this_object()), "The chimera's lion head laughs hideously, its eyes bewitch you.\n");
      target->command("drop weapon");
      return 1;
   }
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit){
   
   object poison;
   
   if(aid==A_SBITE){
      tell_object(enemy, "The chimera's serpentine fangs inject you with deadly venom!\n");
      
      poison=clone_object("/std/poison_effect");
      if(poison){
         poison->move(enemy);
         poison->set_strength(92);
         poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_CON }));
            poison->set_poison_type(POISON_HP);
         poison->start_poison();
      }
   }
   return 0;
}

/*

public void
do_die(object killer)
{
   if (query_hp() > 0)
      {
      return;
   }
   
   setuid();
   seteuid(getuid());
   
   "/d/Terel/dark/lair"->treasures_alarm(environment());
   
   ::do_die(killer);
}
*/

special_attack(object enemy){
   
   object me;
   mixed *hitresult;
   string how;
   
   me = this_object();
   if(random(5)) return 0;
   
   hitresult = enemy->hit_me(50+random(80), MAGIC_DT, me, -1);
   how = " misses";
   if(hitresult[0] > 0)
      how = " singes";
   if(hitresult[0] > 25)
      how = " burns";
   if(hitresult[0] > 40)
      how = " engulfs";
   
   me->catch_msg("You blast forth fire.\n");
   enemy->catch_msg(QCTNAME(me) + how + " you with a fiery burst from its lion's mouth.\n");
   tell_watcher(QCTNAME(me) + " breathes fire from its lion's mouth and" +
      how + " " + QTNAME(enemy) + ".\n", enemy);
   
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}


