/*
 * /d/Raumdor/beach/bountiful/npc/bount_ghast1.c
 *
 * Nerull 2021
 *
 * This npc sports 10k hitpoints for increased difficulty.
 *
 * Xp-factor is set to 200.
 */

#include "../defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>

inherit "std/monster.c";
inherit "/std/combat/unarmed";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";


/*
 * Function name: create_monster()
 * Description  : Constructor. Edit this to change monster.
 */
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("crewman");
    add_name("human");
    add_name("ghast");
    add_name("_deck_ghast");
    add_name("_deck_ghast1");

    add_adj("gruff");
    add_adj("steely-eyed");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_long("The Captain of Marines walks about the deck "
    +"with a determined rhythmatic gait. You can easily "
    +"count the cadence as he turns left and right in a "
    +"lock step fashion. Always staring at something distant "
    +"you know he does not miss anything on this ship. Attention "
    +"to detail bleeds from his demeanor. There is something "
    +"strange about him. No person is this focused.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    set_stats(({ 220, 220, 220, 220, 220, 220 }));

    set_hitloc_unarmed(A_HEAD, 35, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 35, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 35, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 35, 45, "body");
    set_hitloc_unarmed(A_LEGS, 35, 20, "legs");

    set_attack_unarmed(W_BOTH,  40, 40, W_IMPALE,
    20, "sharp teeth");

    set_attack_unarmed(W_RIGHT,  40, 40, W_SLASH,
    40, "left vicious claw");

    set_attack_unarmed(W_LEFT,  40, 40, W_SLASH,
    40, "right vicious claw");

    set_attack_unarmed(W_FOOTL,  40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTR,  40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,90);

    set_act_time(10);
    add_act("emote makes a joke about the denizens of Martira Bay.");
    add_act("emote clears his throat.");
    add_act("emote rubs his cheek.");

    add_cact("emote narrows his eyes in anticipation of fresh flesh.");
    add_cact("emote says: Your blood..I want your Blood!");

    set_aggressive(1);

    set_exp_factor(200);
}


/*
 * Function name: query_max_hp()
 * Description  : Determines the max hp of the ghast.
 */
int
query_max_hp()
{
    ::query_max_hp();

    return 10000;
}


/*
* Function name: do_die()
* Description  : Sets the items that this monster might drop.
*/
void
do_die(object killer)
{
    MONEY_MAKE_PC(random(15) + 2)->move(this_object(), 1);

    ::do_die(killer);
}


/*
* Function name: special_attack()
* Description  : The special attack vs player teams.
*/
int
special_attack(object enemy)
{
    object me = this_object();

    object *team_member = 0;

    object team_leader = 0;

    mixed *hitresult;
    string how;
    string ohow;
    string tar;

    int     n = -1;
    int present_teamsize = 0;
    int healmeamount;

    // We'll make sure the enemy is redefined.
    enemy = me->query_attack();


    // This means the enemy is a teamleader
    if (enemy->query_team() != 0)
    {
        // We find and set the leader of the team
        team_leader = enemy;

        // We now check the array of teammembers of the teamleader
        team_member = team_leader->query_team();
    }

    // If we are a team member, we find the leader
    if (enemy->query_leader() != 0)
    {
        // We find and set the leader of the team
        team_leader = enemy->query_leader();

        // We now check the array of teammembers of the teamleader
        team_member = team_leader->query_team();
    }

    // Check if the teamleader is missing.
    if (!present(team_leader, environment(me)))
    {
        // The npc heals fully if the teamleader is missing.
        if (this_object()->query_hp() != this_object()->query_max_hp())
        {
            if (this_object()->query_hp() <
                (this_object()->query_max_hp() - 1000))
            {
                tell_watcher(QCTNAME(me)
                    + " suddenly becomes "
                    + "rejuvenated and impervious to your assaults as "
                    + "you notice your teamleader is "
                    + "missing!\n");
            }
        }

        healmeamount = me->query_max_hp();

        me->heal_hp(healmeamount);
    }

    // We scan the teammembers and if they are present.
    while (++n < sizeof(team_member))
    {
        if (present(team_member[n], environment(me)))
        {
            present_teamsize = present_teamsize + 1;

            team_member[n]->attack_object(me);
        }
    }

    me->command("kill " + enemy->query_name());
    team_leader->attack_object(me);

    // How many of the team is actually present.
    if (present_teamsize < 2)
    {
        // The npc heals fully if the team is not big enough.
        if (this_object()->query_hp() != this_object()->query_max_hp())
        {
            if (this_object()->query_hp() <
                (this_object()->query_max_hp() - 1000))
            {
                tell_watcher(QCTNAME(me)
                    + " suddenly looks rejuvenated while cackling with "
                    + "glee at so few adversaries!\n");
            }

            healmeamount = me->query_max_hp();

            me->heal_hp(healmeamount);
        }
    }

    if (random(4))
    {
        return 0;  /* Continue with the normal attacks */
    }

    // The special.
    hitresult = do_stat_based_attack(me, enemy, W_SLASH);

    how = " but miss";
    ohow = " but misses";

    if (hitresult[0] >= 0)

    {
        how = " and slashes across ";
        ohow = " and slashes across ";
        tar = " chest";
    }

    if (hitresult[0] > 10)
    {
        how = " and rip across ";
        ohow = " and rips across ";
        tar = " chest";
    }

    if (hitresult[0] > 20)
    {
        how = " and brutaly rakes across ";
        ohow = " and brutaly rakes across ";
        tar = " body, spraying blood and gore everywhere";
    }

    if (hitresult[0] == -1)
    {
        me->catch_msg("You strike out at " + QTNAME(enemy)
            + " with your vicious claws," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with vicious claws," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at " + QTNAME(enemy) +
            " with vicious claws," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QTNAME(enemy)
            + " with your vicious claws," +
            how + enemy->query_possessive() + tar + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with vicious claws," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "
            + QTNAME(enemy) + " with " +
            "vicious claws," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}


