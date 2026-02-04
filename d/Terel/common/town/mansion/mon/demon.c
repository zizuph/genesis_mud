/*
/doc/examples/mobiles/tiger2.c

JnA 920111

A sample creature 

This creature uses no tools for fighting. 
It inherits the routines for unarmed combat.

This is a rather tough beast. You need on average 30 or more in your
stats to handle it. You also need wc30 weapon with skills to match.

*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack"; /* Added here y nick to make this file load */

#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
   set_name("demon"); 
   set_race_name("demon");
   set_short("abyssmal shadow demon");
   set_adj(({"abyssmal", "shadow" }));
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 165, 121, 140, 87, 78, 106}));
   
   set_skill(SS_DEFENCE, 99);
   set_aggressive(1);
   set_alignment(-890);
   set_fatigue(9000);
   set_hp(40000);
   set_gender(2);
   
   set_act_time(1);
   add_act("@@howl");
   add_act("@@bellow");
   add_act("@@flap");
   add_cact("@@hypn");
   add_cact("@@bash");
   add_cact("@@flame");
   set_attack_unarmed(A_BITE,  90, 60, W_IMPALE, 30, "lion jaws");
   set_attack_unarmed(A_LCLAW, 50, 35, W_SLASH,  10, "left claw");
   set_attack_unarmed(A_RCLAW, 55, 40, W_SLASH,  10, "right claw");
   set_attack_unarmed(A_TAIL, 80, 50, W_BLUDGEON,  25, "barbed tail");
   set_attack_unarmed(A_HORN, 60, 40, W_IMPALE,  25, "goat horns");
   
   set_hitloc_unarmed(H_HEAD, ({ 82 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 88 }), 80, "body");
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
   write("The chimera's serpent head spews forth a cloud of fire.\n");
   return 1;
}
heal(){
   tell_room(environment(this_object()), "The chimera's serpent head " +
      "hisses arcane words.\nThe chimera is surrounded by a purple glow.\n");
   this_object()->heal_hp(40);
}
hypn(){
   object target;
   int res;
   target = query_attack();
   if (!target || environment(target) != environment(this_object()))
    return 1;
   target->catch_msg("The chimera's lion head looks at you.\n");
   res = resolve_task(TASK_ROUTINE, 0, target, ({TS_DIS, TS_WIS}));
   if(res > 0) {
      if(target->query_weapon()){
         tell_room(environment(this_object()), "The chimera's lion head laughs hideously, its eyes bewitch you.\n");
         target->command("$drop " + query_weapon()->query_name());
         return 1;
      }
   }
}




