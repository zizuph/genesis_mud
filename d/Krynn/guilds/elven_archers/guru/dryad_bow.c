#include <stdproperties.h>
#include <filter_funs.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include "../guild.h"

inherit "/std/bow";

#define MANA_DRAIN               15

// Global Variables
static object   gArrows, gContainer;
static status   gHaste;

public object
query_magic_quiver()
{
    return gContainer;
}
/*
 * Function name:   set_hasted
 * Description:     Sets whether or not the bow is hasted
 * Arguments:       (status) haste - 1 / 0: hasted / not hasted
 * Returns:         Nothing
 */
public void
set_hasted(status haste)
{
    gHaste = haste;
} /* set_hasted */

/*
 * Function name:   magic_missile_mana_drain
 * Description:     Drains the required mana from the wielder of the bow.
 * Arguments:       (object) archer - The archer
 * Returns:         Nothing
 */
public void
magic_missile_mana_drain(object archer)
{
    archer->add_mana(-MANA_DRAIN);
} /* magic_missile_mana_drain */

/*
 * Function name:   query_has_magical_arrows
 * Description:     Determines if the bow can shoot wind arrows, based on if the
 *                  user has mana.
 * Arguments:       None
 * Returns:         (status) 1 - has magical arrows
 *                           0 - no magical arrows
 */
public status
query_has_magical_arrows()
{
    object archer;
    
    /*
     * We dont want the arrows to be usable by anything other than this bow
     * or if the user is out of mana.
     */
    if (!objectp(archer = query_wielded()) || archer->query_mana() < MANA_DRAIN)
        return 0;
    
    return 1;
} /* query_has_magical_arrows */

/*
 * Function name:   query_sprout_short
 * Description:     Displays varying short descriptions based on if the bow has
 *                  been strung.
 * Arguments:       None
 * Returns:         (string) short description
 */
string
query_sprout_short()
{
    if (query_stringed())
        return "silvery willow-wood longbow";
    
    return "silvery willow-wood sprout";
} /* query_sprout_short */

/*
 * Function name:   query_sprout_long
 * Description:     Displays varying long description based on if the bow has  
 *                  been strung.
 * Arguments:       None
 * Returns:         (string) long description
 */
string
query_sprout_long()
{
    string str;
    
    if (query_stringed())
        str = "It has been strung tightly to craft a longbow of excellent make";
    else
        str = "It would make an excellent bow, were it to be strung";
    
    return "This is a long and sturdy willow sprout which has been plucked "
    + "before reaching maturity. The sprout is the vessel for a young dryad, "
    + "its power washing over the wood, disturbing the very air around it. "
    + str + ".\n";
} /* query_sprout_long */

/*
 * Function name:   create_bow
 * Description:     The basic bow construct
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_bow()
{
    add_name(({"sprout", "longbow"}));
    set_adj(({"slender", "willow", "wood", "willow-wood"}));
    set_short("@@query_sprout_short@@");
    set_long("@@query_sprout_long@@");
    
    set_hit(55);
    set_pen(55);
    
    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This bow is from the elven archer guru quest. It "
    + "creates its own arrows and has high hit and pen. It can only be "
    + "obtained once by completing the guru quest.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
        "This dryad sprout was plucked from the pool of reflection, before "
        + "reaching maturity.\n", 10,
        "It holds the power to pierce its foes with wind arrows.\n", 20,
        "The dryad, a nymph born of nature, has been cleansed from "
        + "corruption.", 70
    }));

    set_wf(this_object());
    
    setuid();
    seteuid(getuid());
} /* create_bow*/

/* 
 * Function name: wield
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have this function called, use the function
 *                set_wf().
 *                Note: this routine does not actually exist in /std/weapon.
 *                      A trick is used to fool the document maker.
 * Arguments    : object obj - the weapon someone tried to wield.
 * Returns      : int  0 - wield this weapon normally.
 *                     1 - wield the weapon, but print no messages.
 *                    -1 - do not wield the weapon, use default messages.
 *                string - do not wield the weapon, use this fail message.
 */
public mixed
wield(object weapon)
{
    if (gHaste)
    {
        object haste_object;
        if (haste_object = present("_loremaster_haste_object_", wielder))
            haste_object->remove_object();
        
        // Clone and move the Haste object to the wielder
        haste_object = clone_object(HASTE_OBJECT);
        haste_object->set_hasted_object(this_object());
        haste_object->move(wielder, 1);
    }
    
    if (!objectp(gArrows))
    {
        
        /*
        * We want the bow to select its magical arrows, so we make it into a
        * condition based quiver
        */
        if (!objectp(gContainer))
        {
            gContainer = clone_object("/std/container");
            gContainer->set_name("_magic_quiver_");
            gContainer->set_short("magic quiver");    
            gContainer->set_long("This is a magic quiver for the Archers of "
            + "Ansalon guru quest reward.\n");
            gContainer->add_prop(OBJ_S_WIZINFO, "This is an invisible magic "
            + "quiver for the elven archers dryad_bow.\n");
            gContainer->add_prop(OBJ_M_NO_DROP, 1);
            gContainer->add_prop(OBJ_M_NO_STEAL, 1);
            gContainer->add_prop(OBJ_M_NO_SELL, 1);
            gContainer->set_no_show();
            gContainer->add_prop(CONT_I_IS_QUIVER, &query_has_magical_arrows());
            gContainer->move(wielder, 1);
        }
    
        gArrows = clone_object(DRYAD_ARROW);
        gArrows->move(gContainer, 1);
    }
    
    set_projectile_stack(gArrows);
    return 0;
} /* wield */

/*
 * Function name: unwield
 * Description  : This function might be called when someone tries to unwield
 *                this weapon. In a launch weapon unwield causes the weapon to
 *                be unloaded as well.
 *
 * Arguments    : object obj - the weapon to stop wielding.
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */
public mixed
unwield(object obj)
{
    object  haste_object;
    int     success;
    
    if (success = ::unwield(obj))
        return success;
    
    if (haste_object = present("_loremaster_haste_object_", wielder))
        haste_object->remove_object();
    
    if (objectp(gArrows))
        gArrows->remove_object();
    
    if (objectp(gContainer))
        gContainer->remove_object();
    
    return 0;
} /* unwield */

/*
 * Function name: load_desc
 * Description  : Returns an extra description of the loaded weapon.
 *                This is meant to be overloaded in subclasses for
 *                a prettier description.
 *
 * Returns      : string - Extra description of the load status.
 */
public string
load_desc()
{
    if (!query_projectile() || MASTER_OB(query_projectile()) != DRYAD_ARROW)
        return ::load_desc();
    
    return (query_projectile() ? "It has been drawn and nocked with "
    + LANG_ADDART(query_projectile()->singular_short()) + ", surging with "
    + "the power of the wind.\n": "");
} /* load_desc */

/*
 * Function name: tell_archer_no_missiles
 * Description  : Produces a message to the wielder that he is out of missiles.
 *                This function is meant to be overridden by launch_weapon
 *                implementations.
 */
public void 
tell_archer_no_missiles()
{
    tell_object(query_wielded(), "Your continued use of the mistral arrows "
    + "have left you mentally exhausted and you have no spare arrows.\n");
} /* tell_archer_no_missiles */

/*
 * Function name: tell_archer_fatigue_unload
 * Description:   Informs the archer that he is too tired to keep the
 *                bow drawn.
 * Arguments:     archer:     Archer wileding the bow.
 *                target:     The target archer was aiming at.
 *                projectile: The projectile he is about to unload.
 */
public void 
tell_archer_fatigue_unload(object archer, object target, object projectile)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_archer_fatigue_unload(archer, target, projectile);
    
    tell_object(archer, "You are too tired to keep the " + short() + " drawn. "
    + "The " + projectile->singular_short() + " fades out of existence as you "
    + "loosen your grip on the " + short() + ".\n");
    projectile->verify_location();
} /* tell_archer_fatigue_unload */

/*
 * Function name: tell_archer_unload
 * Description  : Produces messages to the wielder when he unloads his
 *                launch_weapon. This function is meant to be overridden
 *                by launch_weapon implementations.
 *                
 * Arguments    : archer:      The archer unloading a projectile.
 *                projectile:  The projectile he unloads.
 */
public void
tell_archer_unload(object archer, object target, object projectile)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_archer_unload(archer, target, projectile);
    
    tell_object(archer, "The " + projectile->singular_short() + " fades out of "
    + "existence as you loosen your grip on the " + short() + ".\n");
    projectile->verify_location();
} /* tell_archer_unload */

/*
 * Function name: tell_others_unload
 * Description  : Produces messages to bystanders that the wielder unloads
 *                his launch_weapon. This function is meant to be
 *                overridden by launch_weapon implementaions.
 *                
 * Arguments    : archer:      The archer unloading a projectile.
 *                target:      The person the wilder aimed at.
 *                projectile:  The projectile he unloads.
 */
public void
tell_others_unload(object archer, object target, object projectile)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_others_unload(archer, target, projectile);
    
    object *bystanders;

    bystanders = all_inventory(environment(archer)) - ({ archer });
    bystanders = FILTER_IS_SEEN(archer, FILTER_LIVE(bystanders));
    bystanders = filter(bystanders, &->can_see_in_room());
    
    bystanders->catch_msg("The " + projectile->singular_short() + " fades out "
    + "of existence as " + QTNAME(archer) + " relaxes "
    + archer->query_possessive() + " grip on the " + short() + ".\n");
} /* tell_others_unload */

/*
 * Function name: tell_archer_load
 * Description  : Produces messages to bystanders when the archer wields
 *                his launch_weapon. This function is meant to be
 *                overridden by launch_weapon implementations.
 *                
 * Arguments    : archer:      The archer loading a projectile.
 *                target:      The soon to be target!
 *                projectile:  Projectile beeing loaded.
 *                adj_desc:    Description of the adjecent room.
 */
public void 
tell_archer_load(object archer, object target, object projectile,
                 string adj_desc)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_archer_load(archer, target, projectile, adj_desc);
    
    tell_object(archer, capitalize(LANG_ADDART(projectile->singular_short()))
    + " forms out of thin air as you draw your " + short() + ". You aim "
    + "carefully at " + target->query_the_name(archer) + (strlen(adj_desc) ? " "
    + adj_desc : "") + ".\n");
} /* tell_archer_load */

/*
 * Function name: tell_others_load
 * Description  : Produces messages to spectators when the player loads his
 *                launch_weapon. This method is meant to be overridden by
 *                launch_weapon implementations.
 *                
 * Arguments    : archer:     The player loading his weapon.
 *                target:     The target player is aiming at.
 *                projectile: The projectile we are loading.
 *                adj_string: Description of the adjecent location.
 */
public void 
tell_others_load(object archer, object target, object projectile,
                 string adj_desc)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_others_load(archer, target, projectile, adj_desc);
    
    tell_bystanders_miss(capitalize(LANG_ADDART(projectile->singular_short()))
    + " forms out of thin air as " + QTNAME(archer) + " draws "
    + archer->query_possessive() + " " + short() + ". "
    + capitalize(archer->query_pronoun()) + " aims carefully at "
    + QTNAME(target) + (strlen(adj_desc) ? " " + adj_desc : "") + ".\n", ""
    + capitalize(LANG_ADDART(projectile->singular_short())) + " forms out of "
    + "thin air as " + QTNAME(archer) + " draws " + archer->query_possessive()
    + " " + short() + ". " + capitalize(archer->query_pronoun()) + " aims "
    + "carefully at something" + (strlen(adj_desc) ? " " + adj_desc : "")
    + ".\n", 0, 0, archer, target, environment(archer));
} /* tell_others_load */

/*
 * Function name: tell_target_load
 * Description  : Produces a message to the player when he is loading his
 *                launch_weapon.
 *                
 * Arguments    : archer:     The player loading his weapon.
 *                target:     The target player is aiming at.
 *                projectile: The projectile we are loading.
 */
public void
tell_target_load(object archer, object target, object projectile)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_target_load(archer, target, projectile);
    
    if (environment(archer) == environment(target) &&
        CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(target))
    {
        tell_object(target, ""
        + capitalize(LANG_ADDART(projectile->singular_short())) + " forms out "
        + "of thin air as " + archer->query_The_name(target) + " draws "
        + archer->query_possessive() + " " + short() + ". "
        + capitalize(archer->query_pronoun()) + " aims carefully at you.\n");
    }
} /* tell_target_load */


/*
 * Function name: tell_archer_miss
 * Description  : Produces a message to the player when he misses his target.
 *                This function take visual conditions in consideration as
 *                well as shoots across rooms.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stand in the same room.
 */
public void
tell_archer_miss(object archer, object target, object projectile,
                 string adj_room_desc)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_archer_miss(archer, target, projectile, adj_room_desc);
    
    if (!archer->query_npc() && !archer->query_option(OPT_GAG_MISSES) &&
        !archer->query_option(OPT_NO_FIGHTS))
        tell_object(archer, "A cold gust of wind rages through the air in the "
        + "wake of the " + projectile->singular_short() + ".\n");
        
    magic_missile_mana_drain(archer);
    ::tell_archer_miss(archer, target, projectile, adj_room_desc);
} /* tell_archer_miss */

/*
 * Function name: tell_target_miss
 * Description  : Produces a message to the target when the archer tries to
 *                shoot at him but miss. This function take visual
 *                conditions in consideration as well as shoots across rooms.
 *                
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 */
public void
tell_target_miss(object archer, object target, object projectile,
                 string adj_room_desc, string org_room_desc)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_target_miss(archer, target, projectile, adj_room_desc,
                                org_room_desc);
    
    if (!target->query_npc() && !target->query_option(OPT_GAG_MISSES) &&
        !target->query_option(OPT_NO_FIGHTS))
        tell_object(target, "A cold gust of wind rages through the air in the "
        + "wake of the " + projectile->singular_short() + ".\n");
    
    ::tell_target_miss(archer, target, projectile, adj_room_desc,
                       org_room_desc);
} /* tell_target_miss */


/*
 * Function name: tell_archer_bounce_armour
 * Description  : Produces a message to the archer when his arrow hits the
 *                target without causing any harm. This is described as
 *                the arrow bouncing off his armour.
 *                
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                armour:        The armour that deflects the arrow. armour
 *                               may be 0 if no armour covers the hid.
 */
public void 
tell_archer_bounce_armour(object archer, object target, object projectile,
                          string adj_room_desc, object armour)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_archer_bounce_armour(archer, target, projectile, 
                                         adj_room_desc, armour);
    
    if (!archer->query_npc() && !archer->query_option(OPT_GAG_MISSES) &&
        !archer->query_option(OPT_NO_FIGHTS))
        tell_object(archer, "A cold gust of wind rages through the air in the "
        + "wake of the " + projectile->singular_short() + ".\n");
    
    magic_missile_mana_drain(archer);
    ::tell_archer_bounce_armour(archer, target, projectile, adj_room_desc,
                                armour);
} /* tell_archer_bounce_armour */

/*
 * Function name: tell_target_bounce_armour
 * Description  : Produces a message to the target when he is hit by
 *                an arrow that do no dammage. This is described as
 *                the arrow bouncing off his armour.
 *                
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                armour:        The armour that deflects the arrow. armour
 *                               may be 0 if no armour covers the hid.
 */
public void 
tell_target_bounce_armour(object archer, object target, object projectile,
                          string adj_room_desc, string org_room_desc,
                          object armour)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_target_bounce_armour(archer, target, projectile,
                                         adj_room_desc, org_room_desc, armour);
    
    if (!target->query_npc() && !target->query_option(OPT_GAG_MISSES) &&
        !target->query_option(OPT_NO_FIGHTS))
        tell_object(target, "A cold gust of wind rages through the air in the "
        + "wake of the " + projectile->singular_short() + ".\n");
    
    ::tell_target_bounce_armour(archer, target, projectile, adj_room_desc,
                                org_room_desc, armour);
} /* tell_target_bounce_armour */


/*
 * Function name: tell_archer_hit
 * Description  : Produces a message to the archer when he hits the target.
 *                This function takes visual conditions as well as shoots
 *                across rooms in consideration.
 *                
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                hdesc:         The hitlocation description.
 *                phurt:         The %hurt made on the enemy
 *                dt:            The current damagetype
 *                dam:           The damage caused by this weapon in hit points
 *                hid:           The hitlocation we hit.
 */
public void 
tell_archer_hit(object archer, object target, object projectile,
                string adj_room_desc, string hdesc, int dt, int phurt,
                int dam, int hid)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_archer_hit(archer, target, projectile, adj_room_desc, hdesc,
                               dt, phurt, dam, hid);
    
    if (!archer->query_npc())
        tell_object(archer, "A cold gust of wind rages through the air in the "
        + "wake of the " + projectile->singular_short() + ".\n");
        
    magic_missile_mana_drain(archer);
    ::tell_archer_hit(archer, target, projectile, adj_room_desc, hdesc, dt,
                      phurt, dam, hid);
} /* tell_archer_hit */

/*
 * Function name: tell_target_hit
 * Description  : Produces a message to the target when he is hit by the
 *                archer. This function takes visual conditions as well as
 *                shoots across rooms in consideration.
 *                
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                hdesc:         The hitlocation description.
 *                phurt:         The %hurt made on the enemy
 *                dt:            The current damagetype
 *                dam:           The damage caused by this weapon in hit points
 *                hid:           The hitlocation we hit.
 */
public void
tell_target_hit(object archer, object target, object projectile,
                string adj_room_desc, string org_room_desc, string hdesc,
                int dt, int phurt, int dam, int hid)
{
    if ((!objectp(projectile) && !objectp(projectile = query_projectile())) ||
        MASTER_OB(projectile) != DRYAD_ARROW)
        return ::tell_target_hit(archer, target, projectile, adj_room_desc,
                               org_room_desc, hdesc, dt, phurt, dam, hid);
    
    if (!target->query_npc())
        tell_object(target, "A cold gust of wind rages through the air in the "
        + "wake of the " + projectile->singular_short() + ".\n");

    ::tell_target_hit(archer, target, projectile, adj_room_desc, org_room_desc,
                      hdesc, dt, phurt, dam, hid);
} /* tell_target_hit */


/*
 * Function name: tell_all_projectile_break
 * Description  : Tells everyone when a projectile breaks.
 * Arguments    : projectile:  The projectile that breaks.
 *                enemy:       The enemy the projectile was shot at.
 *                enemy_env:   The environment of the enemy.
 */
public void 
tell_all_projectile_break(object projectile, object target)
{
    if (projectile->query_broken())
        ::tell_all_projectile_break(projectile, target);
} /* tell_all_projectile_break */


/*
 * Function name:   query_recover
 * Description:     Called to make this weapon recoverable, and to make sure the
 *                  haste status is kept.
 */
string
query_recover()
{
    return MASTER + ":DRYAD_BOW#" + gHaste + "#" + query_item_expiration_recover();
} /* query_recover */

/*
 * Function name: init_recover
 * Description  : Initiates the broken status of a projectile.
 *
 */
void
init_recover(string arg)
{
    string  head, tail;
   
    sscanf(arg, "%sDRYAD_BOW#%d#%s", head, gHaste, tail);
    init_item_expiration_recover(tail); 
} /* init_recover */


/*
 * Function name: move_projectile_to_env
 * Description  : Moves and hides a projectile at the specified location.
 *
 * Arguments    : location:   The new location of the projectile.
 *                projectile: Projectile to hide.
 */
public void
move_projectile_to_env(object location, object projectile)
{
    ::move_projectile_to_env(location, projectile);
    projectile->verify_location();
}

/*
 * Function name: move_projectile_to_target
 * Description  : Moves the projectile to the specified target.
 *
 * Arguments    : target:    The target that was hit by the projectile.
 *                projectile: Projectile that was shot.
 */
public void
move_projectile_to_target(object target, object projectile)
{
    ::move_projectile_to_target(target, projectile);
    projectile->verify_location();
}