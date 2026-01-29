#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../defs.h"

inherit "/d/Genesis/specials/std/dam_mod_obj_base";

#define TAMER_DAM_MOD_CAID  20

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_tamer_reduce_object");
    add_name( ({"tamer_reduce_object" }) );
    set_short("effect of reduction");    
    set_long("If you see this, call a wizard.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(TAMER_DAM_MOD_CAID);
}

/*
 * Function:    is_tamer_reduce_object
 * Description: Indicates whether this is the tamer reduce object. Used in
 *              filters during remove_object
 */
public int
is_tamer_reduce_object()
{
    return 1;
}

/*
 * Function     : remove_tamer_reduce_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_tamer_reduce_object()
{
    remove_object();
}

/*
 * Function     : query_dam_mod_valid
 * Description  : Validation function to see whether this damage modifier 
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 *                dt        - int, damage type
 * Returns      : 0/1 - invalid/valid
 */
public int
query_dam_mod_valid(object player, object attacker, int attack_id, int dt)
{
    object  steed;
    
    if (objectp(steed = player->query_steed()) &&
        steed->query_tamer_name() == player->query_real_name())
    {
        /* Damage mod isnt valid if the steeds health is below 70% due to
         * the tanking ability.
         */
        if (((steed->query_hp() * 100) / steed->query_max_hp()) < 70)
           return 0;
        
        return 1;
    }
    
    return 0;
}


public void
attack_modified(object player, object attacker, int attack_id)
{
    object mount = player->query_steed();
    
    if (!objectp(attacker) || !objectp(player) || !objectp(mount))
        return;
    
    if (query_dam_mod_absorb())
    {
        // absorbs damage
        player->catch_msg("The attack from " + QTNAME(attacker) + " strikes "
        + "you, but " + QTNAME(mount) + " manages to deaden the blow by "
        + "shifting its body sideways.\n");
        attacker->catch_msg("Your attack strikes " + QTNAME(player) + ", but "
        + player->query_possessive() + " " + mount->short() + " shifts its "
        + "body sideways, deadening the effects of the blow.\n");
        player->tell_watcher(QCTNAME(attacker) + " strikes " + QTNAME(player)
        + ", but the blow deadens on contact as " + player->query_possessive()
        + " " + mount->short() + " shifts its body sideways.\n",
        ({ player, attacker }));
        
        return;90
    }   
    
    return ::attack_modified(player, attacker, attack_id);
}