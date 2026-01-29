/*
 * Originally coded as /d/Kalad/common/wild/pass/npc/mind_flayer.c
 * Taken from Kalad and adapted for Faerun by Finwe, July 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

int heal;

void arm_me();

void create_monster()
{
    int i;

    npc_name = "_illithid";

    set_name("illithid");
    add_name("mind flayer");
    set_name(npc_name);
    add_name("flayer");
    set_short("illithid");
    set_race_name("illithid");
    set_gender(G_NEUTER);
    set_long("A hideous creature!\n"+
       "Standing at six feet in height, the tall being has glistening " +
       "purplish-mauve skin and three-fingered hands. The most shocking " +
       "aspect of its figure is the large, octopus-like head that rests " +
       "upon its narrow shoulders. Several writhing tentacles emerge from " +
       "where its mouth should be.\n");
    for (i = 0; i < 3; i++)
    set_base_stat(i, 75 + random(30));
    set_base_stat(3, 125);
    set_base_stat(4, 100);
    set_base_stat(5, 100);
    set_skill(SS_UNARM_COMBAT,60);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_SPELLCRAFT,60);

    set_alignment(-1000);
    set_attack_unarmed(0, 45, 45, W_IMPALE, 30, "tentacles");
    set_attack_unarmed(1, 20, 20, W_BLUDGEON, 15, "right fist");
    set_attack_unarmed(2, 20, 20, W_BLUDGEON, 15, "left fist");
    set_attack_unarmed(3, 25, 25, W_BLUDGEON, 20, "right knee");
    set_attack_unarmed(4, 25, 25, W_BLUDGEON, 20, "left knee");
    set_hitloc_unarmed(1, 20, 15, "octopus head");
    set_hitloc_unarmed(2, 25, 10, "right arm");
    set_hitloc_unarmed(3, 25, 10, "left arm");
    set_hitloc_unarmed(4, 35, 45, "body");
    set_hitloc_unarmed(5, 30, 20, "legs");
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME,75000);
    add_prop(CONT_I_WEIGHT,75000);
    set_act_time(3);
    add_act("get all");
    add_act("emote stares at you with its milky white eyes.");
    add_act("emote utters something unrecognizable.");
    
    arm_me();

    set_random_move(8);
    set_restrain_path(ROOM_DIR);
    set_pick_up_team(({"illithid"}));


}
void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    arm = clone_object(ARM_DIR + "il_robe");
    arm -> move(TO);

    wep = clone_object(WEP_DIR + "il_dagger");
    wep -> move(TO);
    wep = clone_object(WEP_DIR + "il_dagger");
    wep -> move(TO);

    command("wear all");
    command("wield all");

}

tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
    if (ob[i]->query_see_blood())
        ob[i]->catch_msg(str);
}
int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = TO;
    attacktype = random(5);
    if (attacktype == 1)
    {
        ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });

        for (i = 0; i < sizeof(ob); i++)
        {
            penet = 500 + random(300);
            penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

            how == "unaffected";
            if (hitresult[0] > 0)
                how = "barely affected";
            if (hitresult[0] > 5)
                how = "slightly shaken";
            if (hitresult[0] > 10)
                how = "shaken quite badly";
            if (hitresult[0] > 15)
                how = "shaken very badly";
            if (hitresult[0] > 20)
                how = "almost overwhelmed";
            if (hitresult[0] > 25)
                how = "completely overwhelmed";
            ob[i]->catch_msg("The mind flayer focuses its attention " +
                "inward...\n"+
                "A blast of mental energy hits you!\n");
            ob[i]->catch_msg("You were " + how + " by the mind flayer's " +
                "mental blast!\n");
            tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the mind " +
                "flayer's mental blast!\n", ob[i]);

            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        return 1;
    }

    if (attacktype == 2)
    {
        if (heal == 5)
        {
            return 0;
        }
        heal += 1;
        write("The mind flayer focuses its attention inward.\n");
        say("The mind flayer focuses its attention inward.\n");
        me->heal_hp(500);
        return 1;
    }

    return 0;
}

init_living()
{
    ::init_living();
    init_team_pickup();
}
