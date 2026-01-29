/*
 *  A two headed serpent that guards the key of the second white tower.
 *  Cloned from /d/Shire/common/towers/tower13.c
 *
 *					Tricky, 28-2-92
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_FANGS    0
#define ATT_TAIL     1 
#define ATT_BREATH   2

#define HIT_LHEAD    0
#define HIT_RHEAD    1
#define HIT_BODY     2

void
create_creature()
{
    if (!IS_CLONE)
      return;

    set_name("serpent");
    set_race_name("serpent"); 
    set_gender(G_NEUTER);

    set_short("two headed serpent");
    set_adj(({"headed","two"}));
    set_long(break_string(
	  "You are looking at a vicious two headed serpent. It looks "
	+ "as if it will eat your corpse with pleasure. The left head "
	+ "bares its fangs while the right head hisses dangerously in "
	+ "your direction. Unfortunately this monster is the keeper "
	+ "of the key of the other tower.\n", 70));

    set_stats(({ 120, 90, 96, 20, 20, 200 }));
    set_hp(100000); /* Heal fully */

    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_DEFENCE, 14);
    set_skill(SS_PARRY, 12);

    set_attack_chance(96);
    set_aggressive(1);
   
		     /*  ID        Ht  Pn         Dt   %use   noise */
    set_attack_unarmed(ATT_FANGS,  14, 16,   W_IMPALE,  29,  "fangs");
    set_attack_unarmed(ATT_TAIL,    8,  4,    W_SLASH,  69,  "tail");
    set_attack_unarmed(ATT_BREATH, 70, 10, W_BLUDGEON,   2,  "poisonous bite");

    set_hitloc_unarmed(HIT_LHEAD,  ({ 2, 2, 2, 2 }), 10, "left head");
    set_hitloc_unarmed(HIT_RHEAD,  ({ 2, 2, 2, 2 }), 10, "right head");
    set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");

    add_prop(CONT_I_WEIGHT, 160000);   /* 160 Kg  */
    add_prop(CONT_I_VOLUME, 148000);   /* 148 Ltr */
    add_prop(LIVE_I_NEVERKNOWN,1);

    seteuid(getuid());
    clone_object(STAND_PARENT + "towers/tower2_key")->move(this_object());
}
