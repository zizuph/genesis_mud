/*
 * /d/Faerun/??/??/iron_golem.c
 *
 * Nerull 2017
 */

inherit "std/monster";

#include "../dungeon_defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

object chest;

int chest_key_id;
int maxhp;
int x = 0;


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("golem");
    add_name("golem");
    add_name("_tomb_monster");

    add_adj("enormous");
    add_adj("iron");

    set_gender(G_NEUTER);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("enormous iron golem");

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

    set_stats(({ 200, 200, 200,
                 200, 200, 200 }));

    set_hitloc_unarmed(A_HEAD,  40, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 40, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 40, 10, "left arm");
    set_hitloc_unarmed(A_BODY,  40, 45, "body");
    set_hitloc_unarmed(A_LEGS,  40, 20, "legs");

    set_attack_unarmed(0,  50, 50, W_IMPALE,
    50, "razor-sharp teeth");

    set_attack_unarmed(1,  50, 50, W_SLASH,
    50, "left lethal claw");

    set_attack_unarmed(2,  50, 50, W_SLASH,
    50, "right lethal claw");

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

    add_cact("emote says: So you have come to die by my "
    +"hands? What an honour!");
    add_cact("emote says: You will be a fine addition to the proviant.");
    add_cact("emote says: If you think you can defeat Me, think again!");
    add_cact("emote pulls a dirty trick!");
    add_cact("emote laughs at your feeble attempt at fighting!");

    set_aggressive(1);
}


/*
* Function name: query_max_hp()
* Description  : Determines the max hp of Damon Skragg.
*/
int
query_max_hp()
{
    ::query_max_hp();

    return 20000;
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
                + " downs a magical looking brew, becoming "
                + "rejuvenated and impervious to your assaults as "
                + "you notice your teamleader is "
                + "missing!\n");
            }
        }

        healmeamount = me->query_max_hp();

        me->heal_hp(healmeamount);
    }


    // The teamleader must satisfy the mininum avg requirements or
    // be thrown overboard.
    if (team_leader->query_average() < 200)
    {
        /*tell_room(MAR + "dock1", QCNAME(team_leader)
            + " crashes in from above and into the ground, "
            + "severly injured!\n", team_leader);

        tell_room(environment(this_object()), QCTNAME(team_leader)
            + " is violently grabbed and violently thrown "
            + "overboard by " + short() + " through a "
            +"window!\n", team_leader);

        team_leader->catch_tell("Tiny as you are, you are grabbed "
            + "by " + short() + " and violently thrown overboard "
            +"through a window! You "
            + "land on your head and you are severly injuried!\n");*/

        team_leader->set_hp(1);
        team_leader->set_mana(1);
        team_leader->set_fatigue(1);

        //team_leader->move_living("M", MAR + "dock1", 1);
    }


    // We scan the teammembers and if they are present.
    while (++n < sizeof(team_member))
    {
        if (present(team_member[n], environment(me)))
        {
            present_teamsize = present_teamsize + 1;

            if (team_member[n]->query_average() < 200)
            {
                /*present_teamsize = present_teamsize - 1;

                tell_room(MAR + "dock1", QCNAME(team_member[n])
                    + " crashes in from above and into the ground, "
                    + "severly injured!\n", team_member[n]);

                tell_room(environment(this_object()),
                    QCTNAME(team_member[n])
                    + " is violently grabbed and thrown overboard by "
                    + short() + "!\n", team_member[n]);

                team_member[n]->catch_tell("Tiny as you are, you "
                    + "are grabbed "
                    + "by " + short() + " and violently thrown "
                    +"overboard! You "
                    + "land on your head, and you are severly "
                    +"injuried!\n");*/

                team_member[n]->set_hp(1);
                team_member[n]->set_mana(1);
                team_member[n]->set_fatigue(1);

                //team_member[n]->move_living("M", MAR + "dock1", 1);
            }

            team_member[n]->attack_object(me);
        }
    }

    me->command("kill " + enemy->query_name());
    team_leader->attack_object(me);

    // How many of the team is actually present.
    if (present_teamsize < 3)
    {
        // The npc heals fully if the team is not big enough.
        if (this_object()->query_hp() != this_object()->query_max_hp())
        {
            if (this_object()->query_hp() <
                (this_object()->query_max_hp() - 1000))
            {
                tell_watcher(QCTNAME(me)
                    + " takes a sip from some magical "
                    + "brew and looks rejuvenated while cackling with "
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
    hitresult = enemy->hit_me(500
        + random(500), W_SLASH, me, -1);

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
            + " with your lethal claws," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with lethal claws," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at " + QCTNAME(enemy) +
            " with lethal claws," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QCTNAME(enemy)
            + " with your lethal claws," +
            how + enemy->query_possessive() + tar + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with lethal claws," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "
            + QCTNAME(enemy) + " with " +
            "lethal claws," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}



