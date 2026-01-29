/* Griffon coded for the Keep area by Mylos 6/5/93          */


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
#define H_WING  2

void
create_creature()
{
    set_name("griffon");
    set_adj("royal");
    set_race_name("griffon");
    set_short("royal griffon");
    set_long("A royal griffon, a mount only a member of the royal family " +
             "may ride. Its haughty features and royal bearing make it a " +
             "creature to be feared.\n");

    set_base_stat(SS_STR, 87);
    set_base_stat(SS_DEX, 90);
    set_base_stat(SS_CON, 90);
    set_base_stat(SS_INT, 87);
    set_base_stat(SS_WIS, 80);
    set_base_stat(SS_DIS, 99);

    heal_hp(2340);

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_UNARM_COMBAT, 86);
    set_skill(SS_BLIND_COMBAT, 59);
    set_skill(SS_ELEMENT_LIFE, 40);
    set_skill(SS_AWARENESS, 45);
	set_alignment(780);

    add_prop(OBJ_I_WEIGHT, 190000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);

    set_attack_unarmed(A_BITE, 30, 35, W_IMPALE, 20, "beak");
    set_attack_unarmed(A_RCLAW,40, 50, W_SLASH,  35, "right claw");
    set_attack_unarmed(A_LCLAW,40, 50, W_SLASH,  35, "left claw");
    set_attack_unarmed(A_TAIL, 30, 40, W_BLUDGEON,  10, "tail");

    set_hitloc_unarmed(H_HEAD, ({ 45, 45, 40, 50 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 42, 46, 47, 50 }), 70, "body");
    set_hitloc_unarmed(H_WING, ({ 40, 34, 42, 45 }), 10, "wing");
}
