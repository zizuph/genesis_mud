/* Wyvern coded for the Royalty quest.  05.06.93          */


inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "default.h"

#define A_BITE  0
#define A_RCLAW 1
#define A_LCLAW 2
#define A_TAIL  3

#define H_HEAD  0
#define H_BODY  1
#define H_TAIL  2

void
create_creature()
{
   set_name("wyvern");
   set_adj("black");
   set_race_name("wyvern");
   set_short("black wyvern");
   set_long("This relative of the dragon family looks mean and hungry. Its " +
            "ebon scales glint in the light here.\n");
   
   set_base_stat(SS_STR, 72);
   set_base_stat(SS_DEX, 54);
   set_base_stat(SS_CON, 70);
   set_base_stat(SS_INT, 32);
   set_base_stat(SS_WIS, 30);
   set_base_stat(SS_DIS, 67);
   
   heal_hp(10000);
   
   set_skill(SS_DEFENCE, 67);
   set_skill(SS_UNARM_COMBAT, 64);
   set_skill(SS_BLIND_COMBAT, 60);
   
   add_prop(CONT_I_WEIGHT, 190000);
   add_prop(CONT_I_MAX_WEIGHT, 200000);
   add_prop(CONT_I_VOLUME, 190000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   set_alignment(-461);
   
   set_attack_unarmed(A_BITE, 30, 35, W_IMPALE, 20, "jaws");
   set_attack_unarmed(A_RCLAW,40, 50, W_SLASH,  35, "right claw");
   set_attack_unarmed(A_LCLAW,40, 50, W_SLASH,  35, "left claw");
   set_attack_unarmed(A_TAIL, 30, 40, W_BLUDGEON,  10, "tail");
   
   set_hitloc_unarmed(H_HEAD, ({ 45, 45, 40, 50 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 42, 46, 47, 50 }), 70, "body");
   set_hitloc_unarmed(H_TAIL, ({ 40, 34, 42, 45 }), 10, "tail");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("snarl");              /* A few courteous actions       */
   add_act("growl");
   
   add_leftover(OBJ_DIR + "wyv_pla","plate",1,0,0,0);
   add_leftover(OBJ_DIR + "w_tooth","tooth",1,0,0,0);
   add_leftover(ARM_DIR + "wyv_sca", "scale",1,0,0,0);
}
