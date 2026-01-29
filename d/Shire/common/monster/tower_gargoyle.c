/*
 *  A gargoyle that blocks the entrance up of the third floor
 *  of the second hite tower.
 *
 *					Tricky, 28-2-92
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_TAIL     0
#define ATT_RPAW     1
#define ATT_LPAW     2
#define ATT_JAWS     3

#define HIT_HEAD     1
#define HIT_BODY     2
#define HIT_TAIL     3
#define HIT_LPAW     4
#define HIT_RPAW     5

void
create_creature()
{
    if (!IS_CLONE)
      return;

    set_name("gargoyle");
    set_race_name("gargoyle"); 
    set_short("hideous gargoyle");
    set_adj("hideous");
    set_gender(G_NEUTER);
    set_long(break_string(
	  "The hideous creature you are looking at is a kind of gargoyle. "
	+ "It has big jaws, two big paws with sharp claws at the end, "
	+ "and a long, scaled tail. "
	+ "You do not know much about these beings, but this one sure "
	+ "looks lethal to you.\n", 70));

    set_stats(({ 210, 160, 155, 20, 20, 300 }));
    set_hp(100000); /* Heal fully */

    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 75);

    set_attack_chance(50);
    set_aggressive(1);
   
		     /*  ID        Ht  Pn         Dt   %use   noise */
    set_attack_unarmed(ATT_TAIL,    8,  4, W_BLUDGEON,  10,  "tail");
    set_attack_unarmed(ATT_RPAW,   20,  4,   W_IMPALE,  40,  "right paw");
    set_attack_unarmed(ATT_LPAW,   20,  4,   W_IMPALE,  40,  "left paw");
    set_attack_unarmed(ATT_JAWS,   55, 10,   W_IMPALE,  10,  "big jaws");

    set_hitloc_unarmed(HIT_HEAD,  ({ 2, 2, 2, 2 }), 10, "head");
    set_hitloc_unarmed(HIT_BODY,  ({ 8, 8, 8, 8 }), 40, "body");
    set_hitloc_unarmed(HIT_TAIL,  ({ 8, 8, 8, 8 }), 40, "tail");
    set_hitloc_unarmed(HIT_LPAW,  ({ 8, 8, 8, 8 }), 40, "left paw");
    set_hitloc_unarmed(HIT_RPAW,  ({ 8, 8, 8, 8 }), 40, "right paw");

    set_act_time(3);
    add_act("growl");

     set_cact_time(2);
    set_cact_time("growl");
    add_prop(CONT_I_WEIGHT, 130000);   /* 130 Kg  */
    add_prop(CONT_I_VOLUME, 140000);   /* 140 Ltr */
    add_prop(LIVE_I_NEVERKNOWN,1);
}
