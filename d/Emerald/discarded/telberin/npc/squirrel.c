inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "default.h"

#define A_BITE  0
#define A_RCLAW 1
#define A_LCLAW 2

#define H_HEAD  0
#define H_BODY  1

void
create_creature()
{
   set_name("squirrel");
   set_adj("grey");
   set_race_name("squirrel");
   set_short("grey squirrel");
   set_long("This agitated squirrel is bounding all over the area looking " +
            "for food. It's large bushy tail springs around after him like " +
            "a ghost.\n");
   
   set_base_stat(SS_STR, 12);
   set_base_stat(SS_DEX, 10);
   set_base_stat(SS_CON, 11);
   set_base_stat(SS_INT, 10);
   set_base_stat(SS_WIS, 10);
   set_base_stat(SS_DIS, 14);
   
   heal_hp(1649);
   
   set_skill(SS_DEFENCE, 13);
   set_skill(SS_UNARM_COMBAT, 12);
   set_skill(SS_AWARENESS, 20);
   
   add_prop(OBJ_I_WEIGHT, 10000);
   add_prop(CONT_I_MAX_WEIGHT, 20000);
   add_prop(OBJ_I_VOLUME, 7000);
   add_prop(CONT_I_MAX_VOLUME, 7600);
   
   set_attack_unarmed(A_BITE, 12, 14, W_IMPALE, 20, "jaws");
   set_attack_unarmed(A_RCLAW,10, 13, W_SLASH,  35, "right claw");
   set_attack_unarmed(A_LCLAW,10, 13, W_SLASH,  35, "left claw");
   
   set_hitloc_unarmed(H_HEAD, ({ 10, 13, 12, 1 }), 25, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 14, 14, 1 }), 75, "body");
   
}
