/*
 * /d/Raumdor/beach/bountiful/npc/bount_ghast_courier.c
 *
 * Nerull 2021
 *
 * This npc sports 7k hitpoints for increased difficulty.
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

int counter;

void
move_east()
{
    this_object()->command("east");
    
    counter = counter + 1;
    
    if (counter >= 22)
    {
        tell_room(environment(this_object()), "The "+short()+" scales the "
        +"mountainside and is gone.\n");
        
        remove_object();
    }
}


/*
* Function name: do_die()
* Description  : When Damon dies, he drops the key to the chest.
*/
void
do_die(object killer)
{
    object box;
    
    
    box = clone_object(BEACH_DIR + "bountiful/obj/crate");
       
    box->move(this_object(), 1);
    
    MONEY_MAKE_GC(random(15) + 2)->move(this_object(), 1);

    ::do_die(killer);
}
    
    
/*
 * Function name: create_monster()
 * Description  : Constructor. Edit this to change monster.
 */
nomask void create_monster()
{
    seteuid(getuid());
    
    counter = 0;

    set_race_name("crewman");
    add_name("human");
    add_name("ghast");
    add_name("_supply_ghast");

    add_adj("strong");
    add_adj("determined");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_long("This crewman looks like a member of "
    +"some sailing vessel judging by his clothing. He is currently "
    +"carrying a large wooden crate that seems impossible heavy, but yet "
    +"he is carrying with little to no struggle, as if he somehow "
    +"possesses supernatural strength. He is moving eastwards through "
    +"the forest of shadows.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    set_stats(({ 240, 240, 240, 240, 240, 240 }));

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
    add_cact("emote narrows his eyes in anticipation of fresh flesh.");
    add_cact("emote says: Your blood..I want your Blood!");

    set_aggressive(1);
    
    set_alarm(160.0, 160.0, &move_east());
}


/*
 * Function name: query_max_hp()
 * Description  : Determines the max hp of the ghast.
 */
int
query_max_hp()
{
    ::query_max_hp();

    return 7000;
}


/*
* Function name: special_attack()
* Description  : The special attack vs player teams.
*/
int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    string how;
    string ohow;
    string tar;
    
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

