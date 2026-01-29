/*
 * /d/Faerun/guilds/vampires/npc/ward.c
 *
 * Nerull 2021
 *
 * This npc serves as a covinward for the 
 * various vampire covens.
 *
 * It requires a team of x players to defeat, and once
 * defeated, the ward goes into an reinforced mode where it
 * becomes more or less impossible to kill it.
 *
 * However, it slowly deteriorates by itself, and if left in
 * this mode, the ward disintegrates after 24 hours.
 *
 * The ward ensures that only covenmembers can access the 
 * coven-specific rooms.
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>


int reinforced = 0;
int counter = 1440;

/*
 * Function name: create_monster()
 * Description  : Constructor. Edit this to change monster.
 */
nomask void create_monster()
{
    seteuid(getuid());

    set_name("_vampire_ward_gargoyle");
    add_name("gargoyle");
    
    add_adj("large");
    add_adj("menacing");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 50);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    
    set_short("large menacing gargoyle");

    set_long("This is a large menacing gargoyle of "
    +"stone, sculptured like a pit fiend from Abyss. Long "
    +"vicious claws of stone reaches towards you in a "
    +"threatening manner. A pair of large wings of stone "
    +"proluding from its back.\n");

    add_prop(CONT_I_WEIGHT, 1100000);
    add_prop(CONT_I_HEIGHT, 250);

    set_stats(({ 250, 250, 250, 250, 250, 250 }));

    set_hitloc_unarmed(A_HEAD, 60, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 60, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 60, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 60, 45, "body");
    set_hitloc_unarmed(A_LEGS, 60, 20, "legs");

    set_attack_unarmed(W_RIGHT,  60, 60, W_SLASH,
    50, "left stone claw");

    set_attack_unarmed(W_LEFT,  60, 60, W_SLASH,
    50, "right stone claw");

    set_attack_unarmed(W_FOOTL,  60, 60, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTR,  60, 60, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);

    set_exp_factor(200);
    
    reinforced = 0;
    counter = 1440;
}


/*
 * Function name: query_max_hp()
 * Description  : Determines the max hp.
 */
int
query_max_hp()
{
    ::query_max_hp();

    return 100000;
}


void
reduce_me()
{
    
    if (reinforced == 0)
    {
        return;
    }
    
    counter = counter - 1;
    
    this_object()->set_hp(1000000);
    
    if (counter <= 1)
    {
        tell_watcher(QCTNAME(this_object())
        +" suddenly collapses into a pile of "
        +"fine dust, and is gone!\n");
        
        WARD_LOG("ward_log",
            "Ward 1 disintegrated.\n");
        
        remove_object();
        
        return;
    }
    
    tell_watcher(QCTNAME(this_object())
        +" emits a red sickening glow while shaking "
        +"violently!\nThe "+short()+" is slowly deteriorating "
        +"in structural integrity!\n");
        
    WARD_LOG("ward_log",
            "Ward 1 weakened.\n");  

    set_alarm(60.0, 0.0, &reduce_me());            
    
    return;
}


/*
* Function name: do_die()
* Description  : Sets the items that this monster might drop.
*/
void
do_die(object killer)
{
    if (reinforced == 0)
    {
        reinforced = 1;
        
        this_object()->set_hp(1000000);
        
        set_alarm(1.0, 0.0, &reduce_me());
        
        tell_watcher(QCTNAME(this_object())
        +" suddenly becomes "
        +"fully restored! However, you notice it is "
        +"now emitting a red alerting glow, and it is "
        +"trembling violently!\nYou think the "+short()+" is "
        +"starting to weaken every passing minute!\n");
        
        this_object()->set_long("This is a large menacing gargoyle of "
        +"stone, sculptured like a pit fiend from Abyss. Long "
        +"vicious claws of stone reaches towards you in a "
        +"threatening manner. A pair of large wings of stone "
        +"proludes from its back.\nIt is emitting a red "
        +"glowing and alarming light!\nIt looks like it's "
        +"deteriorating every minute, losing structural "
        +"integrity!\n");
        
        WARD_LOG("ward_log",
            "Ward 1 put into reinforced mode.\n");
        
        return;
    }
    
    return;
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
                    + "fully healed and impervious to your assaults as "
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
    if (present_teamsize < 9)
    {
        // The npc heals fully if the team is not big enough.
        if (this_object()->query_hp() != this_object()->query_max_hp())
        {
            if (this_object()->query_hp() <
                (this_object()->query_max_hp() - 1000))
            {
                tell_watcher(QCTNAME(me)
                    + " suddenly looks fully healed while grinning with "
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
            + " with your stone claws," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with stone claws," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at " + QTNAME(enemy) +
            " with stone claws," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QTNAME(enemy)
            + " with your stone claws," +
            how + enemy->query_possessive() + tar + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with ston claws," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "
            + QTNAME(enemy) + " with " +
            "stone claws," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}


int
reset_gargoye(string str)
{
    if (str == "warden")
    {        
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {
            if (reinforced == 0)
            {
                write("The warden is stabile.\n");
                
                return 1;
            }
                    
            int thirstval = VAMPIRES_MAPPINGS->query_thirst_gauge(this_player()->query_name());
            
            if (thirstval < 380)
            {
                write("You aren't sufficient saturated to stabilize the warden!\n");
                
                return 1;
            }
            
            int thirstnew = thirstval - 380;
            
            if (thirstnew < 0)
            {
                thirstnew = 1;
            }
            
            VAMPIRES_MAPPINGS->set_thirst_gauge(drainer->query_name(), thirstnew);
            
            write("You channel a large portion of your blood into "
            +"the warden!\nThe warden stabilizes!\n");
            
            tell_others(QCTNAME(this_player()) + " streams a large torrent "
            +"of blood into the body of the large menacing "
            +"gargoyle!\nThe large "
            +"menacing gargoyle seems to stabilize and return to "
            +"normal!\n", ({ this_object(), this_player() }));
                       
            reinforced = 0;
            
            this_object()->set_long("This is a large menacing gargoyle of "
            +"stone, sculptured like a pit fiend from Abyss. Long "
            +"vicious claws of stone reaches towards you in a "
            +"threatening manner. A pair of large wings of stone "
            +"proludes from its back.\n");
           
            return 1;
        }
        
        
        
    }
}


void
init_living()
{
    ::init_living();
    add_action(reset_gargoyle, "stabilize");
}

