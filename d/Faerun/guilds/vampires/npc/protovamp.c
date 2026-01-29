/*
 * /d/Raumdor/beach/bountiful/npc/bount_ghast4.c
 *
 * Nerull 2021
 *
 * This npc sports 10k hitpoints for increased difficulty.
 *
 * Xp-factor is set to 200.
 */

#include "../guild.h"
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

    set_race_name("human");
    add_name("vampire");
    add_name("anchilla vampire");

    add_adj("dirty");
    add_adj("scabbed");

    set_gender(G_MALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_long("Puss filled scabs and alchemial burns cover "
    +"this mans body, from all the  blasts gone wrong. The "
    +"scabs are infected and he smells of rotting flesh, "
    +"even as he smiles at his barrels of powder. Something "
    +"about his wounds you just know none could live "
    +"through, but here he is, smiling at his barrels.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);

    set_stats(({ 200, 200, 200, 200, 200, 200 }));

    set_hitloc_unarmed(A_HEAD, 35, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 35, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 35, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 35, 45, "body");
    set_hitloc_unarmed(A_LEGS, 35, 20, "legs");

    set_attack_unarmed(W_BOTH,  40, 40, W_IMPALE,
    20, "sharp fangs");

    set_attack_unarmed(W_RIGHT,  40, 40, W_SLASH,
    40, "left sharp claw");

    set_attack_unarmed(W_LEFT,  40, 40, W_SLASH,
    40, "right sharp claw");

    set_attack_unarmed(W_FOOTL,  40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTR,  40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,90);

    set_act_time(10);
    //add_act("emote makes a joke about the denizens of Martira Bay.");
    //add_act("emote clears his throat.");
    //add_act("emote rubs his cheek.");

    add_cact("emote narrows his eyes in anticipation of fresh flesh.");
    add_cact("emote says: Your blood..I want your Blood!");
}


public int 
check_seen(object for_obj)
{
    // Wizards can always see us.
    if (for_obj->query_wiz_level())
    {
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= 7001)
    {
        return 1;
    }
               
    return 0;
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

    mixed *hitresult;
    string how;
    string ohow;
    string tar;

    int     n = -1;
    
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
            + " with your sharp claws," + how + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with sharp claws," +
            ohow + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at " + QTNAME(enemy) +
            " with sharp claws," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        me->catch_msg("You strike out at " + QTNAME(enemy)
            + " with your sharp claws," +
            how + enemy->query_possessive() + tar + ".\n");

        enemy->catch_msg(QCTNAME(me)
            + " strikes out at you with sharp claws," +
            ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(me) + " strikes out at "
            + QTNAME(enemy) + " with " +
            "sharp claws," +
            ohow + enemy->query_possessive() + tar + ".\n", enemy);

        if (enemy->query_hp() <= 0);
        enemy->do_die(me);

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}


int
do_vamp_reveal(string str)
{
    if (str == "vampire" || str == "reveal the vampire")
    {
        // Tier 3 vampires.
        if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= 7001)
        {
            this_player()->catch_tell("You carefully aknowledge the presence of the "
            +"Ancilla Vampire, whichs nods back at you and silently steps out "
            +"of the shadows and greets you carefully.\n");
            
            unset_no_show();
            
            return 1;
        }
    }
    
    return 0;
}


void
do_vamp_notify()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
	{   
        // Tier 3 vampires.
        if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= 7001)
        {
            this_player()->catch_tell("\nYou sense the presence of an Ancilla "
            +"Vampire here, watching you.\nYou may reveal the vampire if you wish.\n");
            
            return;       
        }
    }        
 
    return; 
}


void
init_living()
{
    ::init_living();
     
    set_alarm(0.2, 0.0, &do_vamp_notify());
    
    add_action(do_vamp_reveal, "reveal");
}