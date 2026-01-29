/*
 * /d/Raumdor/beach/bountiful/npc/damon_skragg.c
 *
 * Nerull 2021
 *
 * This npc sports 30k hitpoints for increased difficulty.
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


object chest;
int chest_key_id;
int maxhp;
int x = 0;


void
spawn_chest()
{
    chest = clone_object(BEACH_DIR + "bountiful/obj/damon_chest");
    chest->set_key_id(chest_key_id);
    chest->move(environment(this_object()), 1) ;
}


/*
 * Function name: create_monster()
 * Description  : Constructor. Edit this to change monster.
 */
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("human");
    set_name("_damon_skragg");
    add_name("captain");
    add_name("damon");
    add_name("damon skragg");
    add_name("ghoul");
    add_name("ghoul lord");
    add_adj("black-toothed");
    add_adj("scarred-faced");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("black-toothed scarred-faced captain");

    set_long("This dreadful creature is a site to behold. He "
    +"appears to be the captain of this ship, the Bountiful. "
    +"His menacing glare sets about the room, watchful eyes "
    +"darting in various directions warily searching for "
    +"trouble. His muscled arms show he has worked "
    +"diligently on the sea. Oddly, his skin seems out "
    +"of place as though there might be a nefarious "
    +"secret hidden here. Whatever it is, the captain "
    +"looks dreadful.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    set_stats(({ 270, 270, 270, 270, 270, 270 }));

    set_hitloc_unarmed(A_HEAD, 45, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 45, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 45, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 45, 45, "body");
    set_hitloc_unarmed(A_LEGS, 45, 20, "legs");

    set_attack_unarmed(W_BOTH,  50, 50, W_IMPALE,
    20, "razor-sharp teeth");

    set_attack_unarmed(W_RIGHT,  50, 50, W_SLASH,
    40, "left lethal claw");

    set_attack_unarmed(W_LEFT,  50, 50, W_SLASH,
    40, "right lethal claw");

    set_attack_unarmed(W_FOOTL,  40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTR,  40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);

    set_act_time(5);
    add_act("emote paces slowly around.");
    add_act("leer warily");
    add_act("emote glances through the window and at the "
    +"Sea of Sorrows.");
    add_act("emote mutters about the next course to take on the "
    +"Sea of Sorrows.");
    add_act("emote contemplates and plan some navigation.");
    add_act("get gems");
    add_act("get coins");
    add_act("get corpses");
    
    add_cact("emote says: So you have come to die by my " 
    +"hands? What an honour!");
    add_cact("emote says: You will be a fine addition to the proviant.");
    add_cact("emote says: If you think you can defeat Me, think again!");
    add_cact("emote pulls a dirty trick!");
    add_cact("emote laughs at your feeble attempt at fighting!");

    set_aggressive(1);

    set_exp_factor(200);
    
    chest_key_id = random(50000);
    
    set_alarm(2.0, 0.0, &spawn_chest());
}


/*
 * Function name: query_max_hp()
 * Description  : Determines the max hp of the ghast.
 */
int
query_max_hp()
{
    ::query_max_hp();

    return 50000;
}


/*
* Function name: do_die()
* Description  : When Damon dies, he drops the key to the chest.
*/
void
do_die(object killer)
{
    int i;
    object key;
    object *arr;
    
    key = clone_object(BEACH_DIR + "bountiful/obj/damon_key");
    
    key->set_key(chest_key_id);
    key->move(this_object(), 1);
    chest->despawn_trigger();
    
    MONEY_MAKE_PC(random(30) + 2)->move(this_object(), 1);

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
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your vicious claws," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with vicious claws," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at " + QCTNAME(enemy) +
            " with vicious claws," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your vicious claws," +
            how + enemy->query_possessive() + tar + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with vicious claws," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "
            + QCTNAME(enemy) + " with " +
            "vicious claws," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}

