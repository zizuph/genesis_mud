/*
 * Wraith Evade Object
 * 
 * Wraiths have the ability to evade their enemies.
 *
 * Created by Petros, November 2008
 *
 */
 
#pragma strict_types

#include "defs.h"

inherit "/d/Genesis/specials/std/evade_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function     : is_wraith_evade
 * Description  : Easy way to identify a evade object
 * Arguments    : none
 * Returns      : 1 - always returns true
 */
public int
is_wraith_evade()
{
    return 1;
}

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_wraith_evade_object_");
    add_name( ({"wraith_evade_object" }) );
    set_short("hidden wraith evade object");    
    set_long("The object that grants evade to a wraith. Should not be "
        + "visible to the users.\n");

    setuid();
    seteuid(getuid());

    set_evade_stats( TS_DEX );
    set_evade_skills( ({ SS_DEFENCE }) );
    set_evade_combat_aid(10);
}                           

/*
 * Function     : remove_wraith_evade_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_wraith_evade_object()
{
    remove_object();
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    string attacker_desc, watcher_desc;
    
    switch (random(2))
    {
    case 1:
        attacker_desc = "You strike out at " + QTNAME(player) + ", but "
                      + "it phases out of sight just as you are about "
                      + "to make contact, and reappears immediately "
                      + "afterwards.\n";
        watcher_desc = QCTNAME(attacker) + " strikes out at " 
                     + QTNAME(player) + ", but it phases out of sight "
                     + "just as " + attacker->query_pronoun() + " is "
                     + "about to make contact, and reappears immediately "
                     + "afterwards.\n";
        break;
        
    case 0:
    default:
        attacker_desc = "You swing at " + QTNAME(player) + " but you "
                    + "don't hit anything as your attack just seems to "
                    + "pass right through its incorporeal body.\n";
        watcher_desc = QCTNAME(attacker) + " swings at " 
                    + QTNAME(player) + " but " 
                    + attacker->query_pronoun() + " doesn't hit anything "
                    + "as " + attacker->query_possessive() + " attack just "
                    + "seems to pass right through its incorporeal body.\n";
    }

    attacker->catch_msg(attacker_desc);
    attacker->tell_watcher(watcher_desc, player, ({ attacker, player }));
}

