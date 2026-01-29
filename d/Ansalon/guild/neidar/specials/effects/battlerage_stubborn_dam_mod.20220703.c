/*
 * Neidar Battlerage Stubbornly Damage Reduction Object
 * 
 * When Neidars go into Battlerage Stubborn, they gain a great
 * amount of damage reduction, essentially translating all of
 * their aid into removing damage.
 *
 * Created by Petros, May 2009
 */
 
#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../guild.h"

inherit "/d/Genesis/specials/std/dam_mod_obj_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_neidar_battlerage_stubborn_object_");
    add_name( ({"neidar_battlerage_stubborn_object_" }) );
    set_short("hidden neidar battlerage stubborn object");    
    set_long("The Battlerage Stubbornly object for Neidar Clan members.  "
        + "You shouldn't see this.\n");

    setuid();
    seteuid(getuid());

    set_dam_mod_combat_aid(BATTLERAGE_STUBBORN_DAM_REDUCE_AID);
}                           

/*
 * Function:    is_neidar_battlerage_stubborn_object
 * Description: Indicates whether this is the Neidar Battlerage Stubborn
 *              Object. Used in filters during remove_object
 */
public int
is_neidar_battlerage_stubborn_object()
{
    return 1;
}

/*
 * Function     : remove_neidar_battlerage_stubborn_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_neidar_battlerage_stubborn_object()
{
    remove_object();
}

/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    object player;
    int result;
    
    result = ::start();

    if (objectp(player = query_effect_caster())
        || objectp(player = environment(this_object())))
    {
        player->catch_tell("You roar a challenge to the heavens as you "
            + "focus your entire attention on taking the hits and blows "
            + "of your opponents.\n");
        tell_room(environment(player), QCTNAME(player) + " roars a "
            + "dwarven challenge to the heavens, as " 
            + player->query_pronoun() + " stubbornly focuses on taking "
            + "the hits and blows of " + player->query_possessive()
            + " opponents.\n", ({ player }) );
    }
    
    return result;
}

/*
 * Function     : query_dam_mod_combat_aid
 * Description  : returns the damage modifier combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_dam_mod_combat_aid(object player)
{
    int max_aid, modified_aid, skill;
    
    max_aid = ::query_dam_mod_combat_aid(player);
    skill = player->query_skill(BATTLERAGING_SKILL);
    modified_aid = max(1, max_aid * skill / 100);
    return modified_aid;
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
    // Person must be "preparing" the battlerage ability in order
    // for this effect to be valid. In cooldown, the ability effect is
    // present, but should be inactive
    if (BATTLERAGE_ABILITY->query_ability_preparing(player))
    {
        return 1;
    }
    
    return 0;
}
