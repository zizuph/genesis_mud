inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <wa_types.h>

#define A_BITE  0
#define A_RCLAW 1
#define A_LCLAW 2

#define H_HEAD  0
#define H_BODY  1
#define H_WING  2

void
create_creature()
{
   if (!IS_CLONE)
      return;
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   set_name("freddie");
   add_name("dragon");
   set_adj(({"fiery","vicious"}));
   set_race_name("dragon");
   set_short("terrifying, vicious dragon");
   set_long(break_string("This blazing dragon glows with the power"+
         " of death.  It is a massive creature, and it sits upon its"+
         " throne of treasure with a commanding presence.\n",76));
   
   set_base_stat(SS_STR, 300);
   set_base_stat(SS_DEX, 300);
   set_base_stat(SS_CON, 300);
   set_base_stat(SS_INT, 300);
   set_base_stat(SS_WIS, 300);
   set_base_stat(SS_DIS, 300);
   
   heal_hp(10000);
   
   set_skill(SS_DEFENCE, 150);
   set_skill(SS_UNARM_COMBAT, 150);
   set_skill(SS_BLIND_COMBAT, 150);
   set_skill(SS_AWARENESS, 150);
   set_alignment(0);
   
   set_attack_unarmed(A_BITE, 30, 35, W_IMPALE, 20, "teeth");
   set_attack_unarmed(A_RCLAW,40, 50, W_SLASH,  35, "right claw");
   set_attack_unarmed(A_LCLAW,40, 50, W_SLASH,  35, "left claw");
   
   set_hitloc_unarmed(H_HEAD, ({ 45, 45, 40, 50 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 42, 46, 47, 50 }), 70, "body");
   set_hitloc_unarmed(H_WING, ({ 40, 34, 42, 45 }), 10, "foot");
   
   set_act_time(10);
   add_act(({"emote stops inspecting his weapons and begins counting"+
            " his vast supply of gold coins.",
            "emote stops counting his gold and begins to inspect his"+
            " incredible array of deadly weapons."}));
   
   
}


void
do_die(object enemy)
{
   if (this_object()->query_hp()<1)
      {
      command("I can't be killed.");
      set_hp(10000);
   }
}
