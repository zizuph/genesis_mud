inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "default.h"

#define A_TOOTH  0
#define A_RLEG 1
#define A_LLEG 2

#define H_HEAD  0
#define H_BODY  1

void
create_creature()
{
   set_name("deer");
   set_adj("brown");
   set_race_name("deer");
   set_short("brown deer");
   set_long("This delicate brown deer looks majestic in the light, the " +
            "light sparkling of it's brown coat.\n");
   
   set_base_stat(SS_STR, 32);
   set_base_stat(SS_DEX, 29);
   set_base_stat(SS_CON, 28);
   set_base_stat(SS_INT, 21);
   set_base_stat(SS_WIS, 20);
   set_base_stat(SS_DIS, 28);
   
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
   set_attack_unarmed(A_RLEG,21, 22, W_SLASH,  35, "right foreleg");
   set_attack_unarmed(A_LLEG,21, 22, W_SLASH,  35, "left foreleg");
   
   set_hitloc_unarmed(H_HEAD, ({ 14, 15, 18, 14 }), 25, "head");
   set_hitloc_unarmed(H_BODY, ({ 16, 21, 20, 19 }), 75, "body");
   
}
