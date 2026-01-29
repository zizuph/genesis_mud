/* lyden.c: Lyden, Huge Gladiator. 
            -Revised by Serpine, 11/24/95.
            -Mutilated and castrated by Decius, Sept 1, 1999
    -Revised for the new gladiator guru quest, Casimir, May 2001
    (also set_xp_factor()) 
    
    Reworked into new NPC template by Meton 2020.
*/
#pragma strict_types
#pragma save_binary

inherit "/d/Cirath/std/monster.c";
inherit "/lib/unique";

#include <wa_types.h>
#include "../local.h"
#include "/d/Cirath/athas/gladiator/guruquest/guruquest.h";


void
arm_me()
{
    object gloves,boots;
    seteuid(getuid(TO));

    gloves = clone_unique(ARM +"fire_gloves", 10, ARM + "l_gaunt");
    gloves->move(TO);

    boots = clone_unique(ARM + "fire_boots", 10, ARM +"l_boots");
    boots->move(TO);

    clone_unique(WEP + "lotulis", 20,)->move(TO);

    equip(({
        gloves,
        boots,
        ARM + "l_greave",
        ARM + "l_vhelm",
        ARM + "body_scl",
        ARM + "l_bracers",
        }));
    set_alarm(1.0, 0.0, &command("attune gloves"));
    set_alarm(1.0, 0.0, &command("attune boots"));
    command("wield lotulis");
}

void
create_monster()
{
    set_living_name("lyden");
    set_name("lyden");
    set_title("Independent Gladiator of World Renown");
    set_race_name("human");
    set_adj("gargantuan");
    add_adj("tanned");
    set_long("Once a slave in Tyr, the awesome power of this gladiator "
            +"won both fame and his freedom. But true freedom escaped "
            +"him, for he was still chained to his lust for blood. His "
            +"life has become an endless string of battles, a search for "
            +"what few worthy opponents he can find.\n"
            +"A chain runs from each of his ears to a ring in his nose.\n"
            +"He has the brutal scars of a Gladiator.\n");

    set_stats(({150,150,150,100,100,125}));
    set_all_hitloc_unarmed(50);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_ELEMENT_FIRE,100);
    set_alignment(0);

    add_prop(C_I_AM_PRESERVER,1);
    set_exp_factor(200); //huge AC, deadly special, great combat skills
    set_act_time(3);
    add_act("emote laughs harshly at your puny body.");
    add_act("emote breaks a cinder block over his head.");
    add_act("spit");
    add_act("emote stomps on the ground, shaking the earth.");
    add_act("shout I am the greatest warrior in the world!");
    add_act("' No one can defeat me!");
    add_act("' I challenge anyone to a fair fight!...\n"
        +"Hell! I challenge anyone to an unfair fight!");
    add_act("' Are you even brave enough to attack, small one?");

    set_cact_time(3);
    add_cact("' I will do away with you quickly, flea!");
    add_cact("' Why persist? You have no chance of defeating me!");
    add_cact("' Is that the best you can do?");
    add_cact("emote works himself into a wild battlerage.");
    add_cact("emote breaks into a sweat as his breathing becomes heavier.");
    
    LOAD_GURU_SHADOW(LYDEN);
    arm_me();

}

/* **************** LYDEN CHARGES! ******************** */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me=this_object();

    if(random(8)) return 0;

    hitresult = enemy->hit_me(200 + random(200), W_BLUDGEON, me, -1);
    how = "amazed by such a feeble attack";
    if (hitresult[0] > 0) how = "dazed";
    if (hitresult[0] > 15) how = "injured";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "severely hurt";
    if (hitresult[0] > 75) how = "on the verge of collapse";

    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                    HIS_HER(me) + " leaping charge.\n");
    enemy->catch_msg("You feel " + how + ".\n");

    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                " with " + HIS_HER(me) + " leaping charge.\n",
                me, enemy);

    if(enemy->query_hp() <= 0) enemy->do_die(me);

    return 1;
}











