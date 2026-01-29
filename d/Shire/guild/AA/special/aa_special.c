/*
 * special/aa_special.c
 *
 * Port of the AA specials to the shared combat library
 *
 * Created by Novo, May 2008
 *
 * Layman modifier altered to match 40 caid benefit
 * Arman (AoB) August 2019
 */

#pragma strict_types

#include "../guild.h"

inherit DAMAGE_LIB;

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define VALIDATE        "validate"

/* following constants makes layman damage
 * smaller so that we get efficiency 50% of occ member
 * This is only for scare and smash as shield stuff is modified in
 * aa_shield_sh.c
 */
// #define LAY_MOD   50
// For a caid of 40% for layman members query_combat_aid_modifier() 
// needs to return 54. 75 (occ caid) * 54% = ~40% caid.

#define LAY_MOD   54


// Prototypes
public int              query_combat_aid_modifier();
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public void             apply_costs_to_player(object player);



/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    int aid=100;
    /* efficiency restricted - punishment */
    if (TP->query_prop(AA_PUN) == 2) 
    {
        aid/=2;
    }    
    //  Reduce the skill for Laymans since skill is trainable to 100
    if (IS_LAYMAN(TP)) 
    {
        aid = (aid* LAY_MOD) / 100;
    }

    return aid;
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object enemy;

    if (!::check_valid_action(player,targets,arg,execute))
    {
        return 0;
    }

    if (player->query_prop(AA_PUN) == 3)
    {
        player->catch_msg("You are banned from using "+query_verb()+"!\n");
        return 0;
    }
    if (player->query_aa_member_killer() > 1)
    {
        player->catch_msg("You are banned from using "+query_verb()+
            " for killing army members!\n");
        return 0;
    }
    
    if (SMASH_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing your smash right now!\n");
        return 0;
    }
    if (SMACK_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing your smack right now!\n");
        return 0;
    }
    if (SCARE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing your scare right now!\n");
        return 0;
    }
    if (SMASH_ABILITY->query_ability_in_cooldown(player)
        || SMACK_ABILITY->query_ability_in_cooldown(player)
        || SCARE_ABILITY->query_ability_in_cooldown(player))
    {
        player->catch_msg("You do not feel relaxed enough to do that.\n");
        return 0;
    }

    if (player->query_aa_evade_obj()->query_defend())
    {
        player->catch_msg("You are too busy defending!\n");
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    /* add fatigue */
    if (player->query_fatigue() < 2)
    {
        player->heal_hp(-(2 - player->query_fatigue()));
        player->set_fatigue(0);
        player->catch_tell("The strain of the attack drains you.\n");
    }
    else
    {
        player->add_fatigue(-2);
    }
}

public void
hook_already_active(object ability)
{
    write("You are preparing your "+ability->short()+" right now!\n");
}

public void
hook_targets_gone(object * targets)
{
    write("Your target has escaped.\n");
}

public void hook_special_complete()
{
    write("You feel relaxed again.\n");
}

public void
pulp_him(object enemy, object who)
{
    setuid();
    seteuid(getuid());
    object pulp_sh=clone_object(AA_DIR+"shadow/pulp_sh");
    pulp_sh->shadow_me(enemy);
    enemy->set_hp(-1000);
    enemy->do_die(who);
}
