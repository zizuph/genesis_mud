inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>

#define TO   this_object()
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

int change;

create_monster()
{
   change = 0;
   set_name("Jeres De Avenchir"); 
   add_name("jeres");
   add_name("nobleman");
   add_name("de avenchir");
   set_race_name("human");
   set_long("A great wolf, begotten in ages past.\n");
   set_stats(({ 50, 70, 80, 20, 5, 75}));
   set_hp(10000);
   
   set_skill(SS_DEFENCE, 60);
   set_act_time(1);
   add_act("smile");
   add_cact("@@transform");
   
   set_all_attack_unarmed(10);
   set_all_hitloc_unarmed(10);
}

transform(){
   
   if(change > 0){
      do_howl();
      return 1;
   }
   tell_room(environment(TO), "Suddenly the Jeres begins to change!\n");
   tell_room(environment(TO), "Jeres falls to the ground and becomes a werewolf!\n");
   TO->set_race_name("werewolf");
   TO->set_attack_unarmed(A_BITE,  50, 65, W_IMPALE, 50, "jaws");
   TO->set_attack_unarmed(A_LCLAW, 40, 30, W_SLASH,  35, "left claw");
   TO->set_attack_unarmed(A_RCLAW, 40, 30, W_SLASH,  35, "right claw");
   
   TO->set_hitloc_unarmed(H_HEAD, ({ 30, 25, 30, 20 }), 20, "head");
   TO->set_hitloc_unarmed(H_BODY, ({ 28, 15, 30, 30 }), 80, "body");
   change = 1;
}

do_howl(){
   tell_room(environment(TO), "The werewolf howls in perverse joy!\n");
   return 1;
}

