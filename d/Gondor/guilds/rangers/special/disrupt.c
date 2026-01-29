/* 
 * Interrupt ability, brought over from the thief guilds.
 *
 * Zizuph 2022-06-14
 */

#include "/d/Genesis/specials/local.h"; 
inherit COMBAT_ABILITY_LIB;

#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <cmdparse.h>

// Global Variables
static mapping  targetted_ability = ([]);

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public nomask void 
config_ability()
{
    ::config_ability();
    set_ability_name("disrupt");
    set_ability_hasted(0); // no haste changes affect the timing of ability
    set_ability_prep_time(5);
    set_ability_cooldown_time(5);
    set_ability_combat_aid(25);
    set_ability_target(target_one_other_present_living_or_enemy);
    set_ability_visual(1);
} /* config_ability */

/*
 * Function name:   ability_msg
 * Description:     Handles the printing of the ability preparation.
 * Arguments:       None
 * Returns:         Nothing
 */
static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("You prepare to disrupt.\n");
    // Use if your ability has a prep time.
} /* ability_msg */

public void
resolve_combat_special(object player, object target, int hitloc,
    int random_hitloc, int pen, int damage_type, mixed * items,
    int resist, int result)
{
    object  disrupt, wep, special;
    string *player_msg, *target_msg, *others_msg, loc;
    int     msg_num = 0;
    
    player->catch_msg("Got here\n");
    disrupt = clone_object(RANGERS_SPECIAL_OBJ + "disrupt_ob.c");
    disrupt->set_interrupt_combat_aid(query_ability_combat_aid());
    disrupt->set_interrupt_chance(80);
    disrupt->set_interrupt_special(1);
    disrupt->set_interrupt_spell(1);
    disrupt->set_effect_caster(player);
    disrupt->set_effect_target(target);
    disrupt->move(target, 1);
    
    if (member_array(this_player(), m_indexes(targetted_ability)) > -1)
    {
        disrupt->set_interrupt_target(targetted_ability[this_player()]);
        m_delkey(targetted_ability, this_player());
    }
    
    loc = one_of_list(({"left", "right"}));
    
    int started = disrupt->start();
    player->catch_msg("Start: " + started + "\n");
    
    
    if (started > 0)
    {
        if (!target->query_humanoid() || target->query_prop(LIVE_I_UNDEAD))
        {
            if (sizeof(player->query_weapon(-1)))
            {
                wep = one_of_list(player->query_weapon(-1));
                msg_num = 1;
            }
            
            player_msg = ({
                "You leap into " + QTNAME(target) + " with your " + loc + " "
                + "shoulder, throwing " + target->query_objective() + " off "
                + "balance.\n",
                "You strike " + QTNAME(target) + " with the hilt of your "
                + wep->short() + ", throwing " + target->query_objective()
                + " off balance.\n",
            });
            target_msg = ({
                QCTNAME(player) + " leaps into you with "
                + player->query_possessive() + " " + loc + " shoulder, throwing "
                + "you off balance.\n",
                QCTNAME(player) + " strikes you with the hilt of "
                + player->query_possessive() + " " + wep->short() + ", throwing "
                + "you off balance.\n",
            });
            others_msg = ({
                QCTNAME(player) + " leaps into " + QTNAME(target) + " with "
                + player->query_possessive() + " " + loc + " shoulder, throwing "
                + target->query_objective() + " off balance.\n",
                QCTNAME(player)  + " strikes " + QTNAME(target) + " with the "
                + "hilt of " + player->query_possessive() + " " + wep->short()
                + ", throwing " + target->query_objective() + " off balance.\n",
            });
        }
        else
        {
            player_msg = ({
                "You drop to one knee and deliver a punch to " + QTNAME(target)
                + "'s kidney.\n",
                "You sidestep " + QTNAME(target) + " and sweep " 
                + target->query_possessive() + " " + loc + " leg, causing " 
                + target->query_objective() + " to stumble backwards.\n",
                "You move in close and swiftly knee " + QTNAME(target) + "'s "
                + "mid-section.\n",
                "You swing your " + loc + " elbow, effectively striking "
                + QTNAME(target) + " in the " + (loc != "left" ? "left" : ""
                + "right") + " temple.\n"
            });
            target_msg = ({
                QCTNAME(player) + " drops to one knee and delivers a punch to "
                + "your kidney.\n",
                QCTNAME(player) + " sidesteps your approach and sweeps your "
                + loc + " leg, causing you to stumble backwards.\n",
                QCTNAME(player) + " moves in close and swiftly knee your mid-"
                + "section.\n",
                QCTNAME(player) + " raises " + player->query_possessive() + " " 
                + loc + " elbow, striking your "
                + (loc != "left" ? "left" : "right") + " temple.\n",
            });
            others_msg = ({
                QCTNAME(player) + " drops to one knee and delivers a punch to "
                + QTNAME(target) + "'s kidney.\n",
                QCTNAME(player) + " sidesteps " + QTNAME(target) + "'s approach "
                + "and sweeps " + target->query_possessive() + " " + loc + " "
                + "leg, causing " + target->query_objective() + " to stumble "
                + "backwards.\n",
                QCTNAME(player) + " moves in close to " + QTNAME(target)
                + " and swiftly knee " + target->query_possessive() + " mid-"
                + "section.\n",
                QCTNAME(player) + " raises " + player->query_possessive() + " " 
                + loc + " elbow, striking " + QTNAME(target) + " in the "
                + (loc != "left" ? "left" : "right") + " temple.\n",
            });
            
            msg_num = random(sizeof(player_msg));
        }
        
        special = disrupt->query_interrupted_ability();
        
        player->catch_msg(player_msg[msg_num] + "\nYou successfully interrupt "
        + QTNAME(target) + " from executing "
        + LANG_ADDART(special->query_ability_name()) + ".\n");
        target->catch_msg(target_msg[msg_num] + "\nYour "
        + special->query_ability_name() + " has been interrupted.\n");
        player->tell_watcher(others_msg[msg_num], ({ target }));
        return;
    }
    
} /* resolve_combat_special */

/*
 * Function name:   hook_special_in_cooldown
 * Description:     This hook prints a message if the ability is in cooldown.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    write("You're not ready to perform another disruption again.\n");
} /* hook_special_in_cooldown */

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
    write("You feel able to disrupt again.\n");
} /* hook_special_complete */


/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object *targets)
{
    write("Your target appears to have slipped away.\n");
} /* hook_targets_gone */

/*
 * Function name:   hook_special_preparation_complete
 * Description:     This is a hook that prints a message if the preparation is
 *                  complete.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_preparation_complete()
{
    // Don't display any messages
} /* hook_special_preparation_complete */

/*
 * Function name:   hook_already_active
 * Description:     This hook prints a message if the ability is already active.
 * Arguments:       (object) ability - The active ability
 * Returns:         Nothing
 */
public void
hook_already_active(object ability)
{
    write("You are already preparing a disruption.\n");
} /* hook_already_active */

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability, object player)
{
    // Don't display any messages
} /* hook_stopped_ability */


/*
 * Function name:   do_ability
 * Description:     The main entry point for abilities
 * Arguments:       (string) arg - the argument passed in for targeting
 * Returns:         (int) 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    object *oblist;
    
    if (strlen(arg))
    {
        parse_command(arg, ({}), "[at] / [on] [the] %s", arg);
        oblist = PARSE_THIS(arg, "%l");
        
        if (!sizeof(oblist))
        {
            targetted_ability[this_player()] = arg;
            return do_ability("");
        }
    }
    
    return ::do_ability(arg);
} /* do_ability */
