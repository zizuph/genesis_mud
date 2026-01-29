inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";
inherit "/std/act/action";
inherit "/cmd/std/command_driver";

#include "defs.h"
#include <wa_types.h>

#define A_TOOTH  0
#define A_RFIN 1
#define A_LFIN 2
#define A_TAIL 3
#define A_DFIN 4

#define H_HEAD  0
#define H_BODY  1
#define H_TAIL  2


void
create_creature()
{
   set_name("shark");
   set_adj("grey");
   set_race_name("shark");
   set_short("grey shark");
   set_long("This shark looks very dangerous.\n");
   
   set_base_stat(SS_STR, 32);
   set_base_stat(SS_DEX, 29);
   set_base_stat(SS_CON, 28);
   set_base_stat(SS_INT, 21);
   set_base_stat(SS_WIS, 20);
   set_base_stat(SS_DIS,200);
   
   heal_hp(1649);
   
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_UNARM_COMBAT, 23);
   set_skill(SS_BLIND_COMBAT, 24);
   set_skill(SS_ELEMENT_LIFE, 40);
   set_skill(SS_AWARENESS, 40);
   
   add_prop(OBJ_I_WEIGHT, 76000);
   add_prop(CONT_I_MAX_WEIGHT, 200000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   set_attack_unarmed(A_TOOTH, 25, 26, W_IMPALE, 20, "teeth");
   set_attack_unarmed(A_RFIN,21, 22, W_SLASH,  35, "right fin");
   set_attack_unarmed(A_LFIN,21, 22, W_SLASH,  35, "left fin");
   set_attack_unarmed(A_TAIL,21, 22, W_SLASH,  35, "tail");
   set_attack_unarmed(A_DFIN,21, 22, W_SLASH,  35, "dorsal fin");
   
   set_hitloc_unarmed(H_HEAD, ({ 14, 15, 18, 14 }), 25, "head");
   set_hitloc_unarmed(H_BODY, ({ 16, 21, 20, 19 }), 75, "body");
   set_hitloc_unarmed(H_TAIL, ({ 14, 15, 18, 14 }), 25, "tail");
   
   set_alarm(120.0,0.0,"swim_away");
   
}

int
swim_away()
{
   tell_room(ENV(TO),"The shark swims away.\n");
   TO->remove_object();
   return 1;
}

void
do_die(object killer)
{
   tell_room(ENV(TO),"The shark died.\n");
   tell_room(killer,"You killed the shark.\n");
   tell_room(ENV(TO),"The corpse of the shark sank.\n");
   TO->remove_object();
   return;
}
