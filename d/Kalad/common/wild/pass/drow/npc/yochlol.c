/*
 * Created by Antaranos, long long ago.
 * Modified by Ibun may-june 2007'
 * typo and a bit of spacing, Meton nov 2020
 */
#pragma strict_types
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#define A_APP1 0
#define A_APP2 1
#define A_APP3 2
#define A_APP4 3
#define A_APP5 4
#define A_APP6 5
#define A_APP7 6
#define A_APP8 7
#define A_APP9 8
#define H_EYE 0
#define H_BODY 1

void
create_monster()
{
    ::create_monster();
    set_name("yochlol");
    set_race_name("yochlol");
    set_adj("terrifying");
    add_adj("grotesque");
    set_pshort("terrifying grotesque yochlol");
    set_long("A disgusting column of amorphous red flesh, with one "+
      "massive black eye situated near the top. As many as eight "+
      "pseudopods protrude from all over the column, waving ominously "+
      "before the creature.\n");

    set_alignment(-1200);
    set_knight_prestige(1200);
    set_gender(G_NEUTER);
    set_stats(({100, 125 , 150, 125, 125, 125}));
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS, 100);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 150000);
    add_prop(OBJ_I_NO_INS, 1);

    set_act_time(3);
    add_act("emote is strangely quiet.");
    set_cact_time(3);
    add_cact("emote hisses at you.");
    set_aggressive(1);

    set_attack_unarmed(A_APP1, 45, 45, W_BLUDGEON, 10, "first pseudopod");
    set_attack_unarmed(A_APP2, 45, 45, W_BLUDGEON, 10, "second pseudopod");
    set_attack_unarmed(A_APP3, 45, 45, W_BLUDGEON, 10, "third pseudopod");
    set_attack_unarmed(A_APP4, 45, 45, W_BLUDGEON, 10, "fourth pseudopod");
    set_attack_unarmed(A_APP5, 45, 45, W_BLUDGEON, 10, "fifth pseudopod");
    set_attack_unarmed(A_APP6, 45, 45, W_BLUDGEON, 10, "sixth pseudopod");
    set_attack_unarmed(A_APP7, 45, 45, W_BLUDGEON, 10, "seventh pseudopod");
    set_attack_unarmed(A_APP8, 45, 45, W_BLUDGEON, 10, "eighth pseudopod");
    set_attack_unarmed(A_APP9, 45, 45, W_IMPALE, 20, "stinger");
    set_hitloc_unarmed(H_EYE,({30,30,30}),15,"large black eye");
    set_hitloc_unarmed(H_BODY,({60,60,60}),85,"red column-like body");

    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_SEE_INVIS, 10);
    add_leftover("/d/Kalad/common/wild/pass/drow/obj/yochlol_heart.c","heart", 1, "", 1, 1);
    set_exp_factor(150); // Theese are dangerous things
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object poison;
    int dam;

    if(aid == A_APP9)
    {
        enemy->catch_msg(QCTNAME(this_object()) +"'s stinger "+
          "punctures your skin, injecting poison into your body!\n");
        poison = clone_object("/std/poison_effect");

        if(poison)
        {
            poison->move(enemy);
            poison->set_time(300 + random(300));
            poison->set_poison_type("spider");
            poison->set_interval(40); // Increased interval
            poison->set_strength(60); // Can be cured, but not so easy
            dam = (300 + random(150));
            poison->set_damage(({POISON_HP, dam, POISON_STAT, SS_CON}));
            poison->start_poison();
            if (enemy->query_wiz_level())
            {
                enemy->catch_msg("\nWizinfo: "+ dam + " damage per hit.\n");
                enemy->catch_msg("Wizinfo: "+ poison->query_interval() + " seconds " +
                    "interval between poisoneffects.\n");
                enemy->catch_msg("Wizinfo: "+ poison->query_time() + " seconds to " +
                    "heal.\n");
            }
        }
    }
    return 0;
}
