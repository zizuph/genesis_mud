/* 
 * /d/Kalad/common/wild/pass/npc/little_blob.c
 * Purpose    : A little blog from the big blob
 * Located    : /d/Kalad/common/wild/pass/desert/salt
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_SA 0
#define A_MA 1
#define A_LA 2
#define H_MASS 0
/* by Antharanos */
create_monster()
{
    set_name("blob");
    set_race_name("blob");
    set_adj("little");
    set_long("A small amorphous mass of gelatinous tissue that oozes "+
      "in several different directions at once. Although slimy in appearance, "+
      "it does not seem to leave behind any slime trail.\n");
    set_stats(({50,25,100,5,5,50}));
    set_gender(G_NEUTER);
    set_aggressive(1);
    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(CONT_I_VOLUME,50000);
    add_prop(OBJ_I_NO_INS,1);
    set_act_time(3);
    add_act("emote makes a blubbery sound.");
    add_act("emote oozes towards you.");
    add_act("emote oozes away from you.");
    add_act("emote suddenly forms an appendage.");
    add_act("emote shivers, rippling ominously");
    set_cact_time(3);
    add_cact("emote makes a loud blubbering sound.");
    set_attack_unarmed(A_SA, 20, 20, W_BLUDGEON, 50, "small appendage");
    set_attack_unarmed(A_MA, 30, 30, W_BLUDGEON, 30, "medium appendage");
    set_attack_unarmed(A_LA, 40, 40, W_BLUDGEON, 20, "large appendage");
    set_hitloc_unarmed(H_MASS, ({ 20, 20, 50 }), 100, "amorphous body");
}
do_die(object killer)
{
    object proto;
    if (query_hp() > 0) return;

    proto = clone_object("/d/Kalad/common/wild/pass/obj/protoplasm");
    proto -> move(environment(TO));

    ::do_die(killer);
}
