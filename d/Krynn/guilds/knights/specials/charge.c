/*
 * Charge Special for Knights
 *
 * /d/Krynn/gulids/knights/specials/charge.c
 * 
 * This is the charge special for knights that allows them to charge
 * an opponent to engage them in battle. it can also be used in
 * place of kattack during battle as long as the Knight is not
 * being directly attacked by any enemies.
 *
 * fixed it so monsters continue aggressive after charge happens
 *   - Petros, January 2009
 * Based on conversations in Balance, decided to allow High Knights
 * to have the same combat aid as Lord Knights.
 *   - Petros, March 2009
 *
 * 2018-11-11: The mounted combat skill in the guild was limited to 75, fixed
 *             the weight of the skill so the special reaches 80 caid. I have
 *             also removed the opportunity attack as it enforced a negative
 *             caid upon the ability that was not accounted for and made it
 *             unusable in combat. - Carnak
 * 2018-11-17: Knights now get 100 skill in mounted combat, ability altered
 *             accordingly.
 * 2019-11-19: The ability could previously be used on your own horse, odd.
 *             Fixed it. - Carnak
 */
  
#pragma strict_types

#include "../guild.h"
#include "/d/Genesis/specials/std/defs.h"

inherit DAMAGE_LIB;
inherit KNIGHT_UTILITY;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <files.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"

// Global Variables
mapping precharge_alarms = ([ ]);

// Defines
#define LAST_CHARGE_COMPLETION_TIME  "_last_knight_charge_completion_time"
#define OPPORTUNITY_ATTACK           "/d/Krynn/guilds/knights/specials/opportunity_attack"

/*
 * Function Name:   target_one_other_non_warhorse_present_living_or_enemy
 * Description:     This function makes sure that knights are unable to use this
 *                  ability to attack their horse.
 * Arguments:       (object) actor - The knight using the ability.
 *                  (string) str - The argument used along with the ability.
 * Returns:         (object *) An array of targets
 */
public object *
target_one_other_non_warhorse_present_living_or_enemy(object actor, string str)
{
    object warhorse, *oblist, enemy;

    enemy = actor->query_attack();

    if (!strlen(str))
    {
        if (!enemy || 
            /* This shouldn't happen, but we'll check just in case */
            !present(enemy, environment(actor)))
        {
            actor->catch_tell("You aren't fighting anyone!\n");
            return ({});
        }
        return ({ enemy });
    }

    warhorse = actor->query_steed();
    oblist   = PARSE_THIS(str, "[at] / [on] [the] %l") - ({ warhorse, 0 });
    
    if (!sizeof(oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific! You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist;
} /* target_one_other_non_warhorse_present_living */

public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(80);
    set_tohit(95);
    set_skills( ({ SS_MOUNTED_COMBAT }) );
    set_stats( ({ SKILL_AVG, TS_STR, TS_STR, TS_WIS, TS_DIS, SKILL_END }) );
    set_ability_name("charge");
    set_ability_vocal(0);
    set_ability_visual(0);
    set_ability_hasted(0);
    set_ability_prep_time(15);
    set_ability_cooldown_time(10);
    set_ability_attack_during_prep(0);
    set_ability_target(target_one_other_non_warhorse_present_living_or_enemy);
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
    
    // Doesnt make sense for this ability to be hastened by dual wield.
    set_ability_dual_wield(0);
}

varargs void
sever_limb(string piece)
{
    object corpse, part;
    string *str, *message, tmp, race;
    int i;

    corpse = P("corpse", E(this_player()));
    if (corpse->query_npc())
        corpse = 0;

    if (!corpse)
        return;

    // query_short might return function pointer causing runtime
    if (!stringp(corpse->short()))
        return;

    if (piece == "body")
        piece = "head";

    setuid(); seteuid(getuid());

    race = corpse->query_prop(CORPSE_S_RACE);
    if (!race || !strlen(race))
    {
        race = corpse->short();
    }
    switch(piece)
    {
    case "head":
        corpse->set_short("headless " +corpse->short());
        corpse->remove_leftover("scalp");
        corpse->remove_leftover("skull");
        part = clone_object(LEFTOVER_OBJECT);
        part->leftover_init("head", race);
        part->move(E(corpse));
        break;
    case "legs":
        corpse->set_short("legless " +corpse->short());
        corpse->remove_leftover("thighbone");
        part = clone_object(LEFTOVER_OBJECT);
        part->leftover_init("leg", race);
        part->move(E(corpse));
        break;
    case "right arm":
        corpse->set_short("armless " +corpse->short());
        part = clone_object(LEFTOVER_OBJECT);
        part->leftover_init("arm", race);
        part->move(E(corpse));
        break;
    case "left arm":
        corpse->set_short("armless " +corpse->short());
        part = clone_object(LEFTOVER_OBJECT);
        part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
        part->move(E(corpse));
        break;
    }
}

public void
add_charge_objects(object player)
{
    object charge_shadow, charge_paralyze;
    
    if (!objectp(player))
    {
        return;
    }
    
    setuid();
    seteuid(getuid());
    
    if (!player->has_knight_charge_shadow())
    {
        charge_shadow = clone_object(SPECIALS + "objects/charge_shadow");
        charge_shadow->shadow_me(player);
    }
    
    if (!present("_knight_charge_paralyze_object_", player))
    {
        charge_paralyze = clone_object(SPECIALS + "objects/charge_paralyze_object");
        charge_paralyze->move(player, 1);
    }
}

public void
remove_charge_objects(object player)
{
    object paralyze_object;
    
    if (!objectp(player))
    {
        return;
    }
    
    // First remove the alarm if it's still active.
    if (IN_ARRAY(player->query_real_name(), m_indices(precharge_alarms)))
    {
        remove_alarm(precharge_alarms[player->query_real_name()]);
    }
    m_delkey(precharge_alarms, player->query_real_name());
    
    // Remove the shadow and the paralyze object now.
    player->remove_knight_charge_shadow();
    paralyze_object = present("_knight_charge_paralyze_object_", player);
    if (objectp(paralyze_object))
    {
        paralyze_object->remove_object();
    }
}

static mixed * 
check_required_items(object actor, mixed * targets, string arg, int pretest)
{
    object weapon;
    
    weapon = query_primary_weapon(actor);

    if (!weapon)
    {
    	write("You cannot charge your enemies without a weapon!\n");
    	return 0;
    }
    return  ({ weapon });
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object enemy, target, horse, weapon;
    
    enemy = actor->query_attack();
    target = targets[0]; // should have been validated
    horse = query_mounted_solamnian_steed(actor);
    weapon = query_primary_weapon(actor, 0);
    
    if (objectp(enemy))
    {
        actor->catch_msg("You gallop away from the battle astride your " 
            + horse->short() + ", putting some distance between yourself "
            + "and the battle.\n");

        target->catch_msg(QCTNAME(actor) + " gallops away from the battle "
            + "astride " + POSSESSIVE(actor) + " "+ horse->short() 
            + ", putting some distance between " + OBJECTIVE(actor) 
            + "self and the battle.\n");

        tell_room(E(actor), QCTNAME(actor) +" gallops away "
        +    "from the battle astride "+ POSSESSIVE(actor) +" "
        +    horse->short() +", putting some distance between "
        +    OBJECTIVE(actor) +"self and the battle.\n",
          ({ target, actor }));
    }
    else
    {
        actor->catch_msg("You salute " + QTNAME(target) + " in the "
            + "traditional Solamnic manner with your " + weapon->short() 
            + ", then spur your " + horse->short() + " forward, snapping "
            + "the reins.\n");

        target->catch_msg(QCTNAME(actor) + " salutes you in the "
            + "traditional Solamnic manner with " + POSSESSIVE(actor) 
            + " " + weapon->short() +", then spurs "+ POSSESSIVE(actor) 
            + " "+ horse->short() + " forwards, snapping the reins.\n");

        tell_room(E(actor), QCTNAME(actor) + " salutes " + QTNAME(target) 
            + " in the traditional Solamnic manner with " + POSSESSIVE(actor) 
            + " " + weapon->short() + ", then spurs " + POSSESSIVE(actor) 
            + " " + horse->short() +" forwards, snapping the reins.\n", 
            ({ target, actor }));
    }

    // As the Knight charges away, we want to make sure that we stop all
    // fights currently going on. We should also introduce the concept
    // of opportunity attacks against the Knight since he is "running"
    // away from combat.
    object * attackers = filter(all_inventory(environment(actor)),
                                &operator(==)(actor) @ &->query_attack());
/*
    // 2018-11-11:  This has been removed due to negatively affecting the
    //              combat aid of the ability.
    // Invoke the opportunity attack for each enemy against the Knight
    foreach (object attacker : attackers)
    {
        object old_tp = this_player();
        set_this_player(attacker);
        OPPORTUNITY_ATTACK->do_ability("");
        set_this_player(old_tp);
    }
*/
    // Add the objects that will simulate being "far away" in the same room
    add_charge_objects(actor);
    
    attackers->stop_fight(actor);
    // Charging away disengages one from enemies
    actor->stop_fight(attackers);
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
    object  weapon,
           *attackers;
    mixed   leading;
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }

    if (!pointerp(targets) || !sizeof(targets) || !objectp(targets[0]))
    {
        player->catch_msg("You cannot charge into battle against a "
            + "non-existent target!\n");
        return 0;
    }
    
    leading = filter(player->query_following_steeds(), &->is_solamnian_steed());
    if (pointerp(leading) && sizeof(leading) && leading[0]->query_auto_mount())
        leading[0]->unlead_and_mount(0);
    
    if (!objectp(query_mounted_solamnian_steed(player)))
    {        
        player->catch_msg("You cannot charge into battle without a properly "
            + "trained Solamnian warhorse.\n");
        return 0;
    }
    
    if (player->query_skill(SS_MOUNTED_COMBAT) < 1)
    {
        player->catch_msg("You will need to train more diligently before "
            + "you master fighting in combat while mounted.\n");
        return 0;
    }
    
    if (player->query_knight_level() == L_BROSE)
    {
        player->catch_msg("As a Black Knight, you find yourself unable to "
            + "perform the Knightly actions required to charge your "
            + "opponents. You will have to atone for your past "
            + "transgressions.\n");
        return 0;
    }
    else if (player->query_knight_level() == L_SQUIRE)
    {
        player->catch_msg("Only full Knights of Solamnia know how to "
            + "charge their opponents using well-trained warhorses!\n");
        return 0;
    }
        
    if (!(weapon = query_primary_weapon(player, 0)))
    {
        if (execute)
        {
player->catch_msg("As you are about to make contact with "
                + "your foe, you realize that you are without a weapon "
                + "and quickly pull back on the reins!\n");
        }
        else
        {
            player->catch_msg("You ready your mount for a charge, but you "
                + "quickly realize that it is foolish to charge without "
                + "a weapon to strike your foes with!\n");
        }
        return 0;
    }

/*
    // As of December 21, 2013, we now allow a Knight to charge away from
    // combat even if they are already engaged.

    if (!execute)
    {
        // We don't allow a knight to charge when they are directly engaged
        // with an enemy. that means they can use it in teams when they are not
        // the tanker, and also start a fight.
        // This check only applies at the beginning of the charge. By the
        // time the charge executes, it's possible that someone could have
        // attacked them.
        attackers = filter(all_inventory(environment(player)),
    	    &operator(==)(player) @ &->query_attack());
        
        int num_attackers = sizeof(attackers);
        if (num_attackers == 1)
        {
            player->catch_msg(QCTNAME(attackers[0]) + " is paying too much "
                + "attention to you for you to maneuver your steed away to "
                + "charge.\n");
            return 0;
        }
        else if (num_attackers > 1)    
        {
            player->catch_msg("Your enemies are paying too much "
                + "attention to you for you to maneuver your steed away to "
                + "charge.\n");
            return 0;
        }
    }
*/      
    if (KATTACK_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are already preparing to use a knight "
            + "attack, and cannot focus on maneuvering your mount away "
            + "for a charge.\n");
        return 0;
    }
    
    if (KATTACK_ABILITY->query_ability_in_cooldown(player))
    {
        player->catch_msg("Having just recently completed a knightly "
            + "attack upon your foe, you are not yet ready to maneuver "
            + "your mount away for a charge.\n");
        return 0;
    }
    
    // If a Knight is blocking an exit, they can't charge
    if (strlen("/d/Genesis/specials/std/block"->query_block_room(player)))
    {
        player->catch_msg("You cannot charge away from combat while blocking "
                          + "your opponents from leaving!\n");
        return 0;
    }

    if (player->query_prop(LAST_CHARGE_COMPLETION_TIME) + 65 > time())
    {
        player->catch_msg("Having just recently charged your foe, you are still "
                        + "maneuvering your mount to get ready for another "
                        + "charge.\n");
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    // Knights are modified by Knight Sublevel
    //
    // Knights will start at 45% power. Every Knight Level gives them an extra
    // 5% in power. (Conclave with last 5%). A Knight of the Black Rose will
    // have half of the total normal combat aid
    int modifier = 45;
    int level, sublevel; 
    object player;
    
    player = this_player();
    
    // Now add the Knight Levels
    level = player->query_knight_level();
    sublevel = player->query_knight_sublevel();
    
    switch(player->query_knight_level())
    {
    case L_ROSE:
    case L_SWORD:
        // Sword and Rose Knights get their maximum
        // damage regardless of sublevel because they
        // have already been through the entire Crown
        // Order.
        modifier += 55;
        break;
        
    case L_CROWN:    
        // Crown Knights power depends on which sub level
        // they are on.
        modifier += (sublevel * 5);
        break;
        
    case L_SQUIRE:
    case L_BROSE:
        // Black Knights and Squires are not allowed to charge.
        modifier = 0;
        break;
    }
    
    return modifier;
}

void
do_charge_prespecial2(object player, object enemy, object horse)
{
    if (!P(enemy, E(player)) || player->query_prop(LIVE_O_STEED) != horse)
    {
        stop_ability(player);
        return;
    }

    player->catch_msg("You lean forward in the saddle as your "
        + horse->steed_short() + " thunders toward " + QTNAME(enemy)
        + ". Preparing yourself for the impact, you shout out a Solamnic "
        + "battlecry, barely audible over the earth-shaking rumble of "
        + "your steed!\n");

    enemy->catch_msg("The ground beneath your feet rumbles as "
        + player->query_the_name(enemy) + " thunders toward you, astride "
        + POSSESSIVE(player) + " " + horse->steed_short() + "! You feel fear "
        + "creep over you as " + PRONOUN(player) + " shouts out a "
        + "Solamnic battlecry.\n");

    player->tell_watcher("The ground rumbles beneath your feet as "
        + QTNAME(player) + " thunders toward " + QTNAME(enemy) + ", astride "
        + POSSESSIVE(player) + " "+ horse->steed_short() +". Leaning forward "
        + "in the saddle, " + QTNAME(player) + " shouts "
        + "out a Solamnic battlecry!\n", ({ enemy, player }));
}

void
do_charge_prespecial1(object player, object enemy, object horse, float next_delay)
{
    if (!P(enemy, E(player)) || player->query_prop(LIVE_O_STEED) != horse)
    {
        stop_ability(player);
        return;
    }

    player->catch_msg("Your adrenaline begins to surge as you slap "
        + "the reins back and forth as your " + horse->steed_short()
        + " gains momentum.\n");

    enemy->catch_msg(QCTNAME(player) + " slaps the reins "
        + "back and forth as " + POSSESSIVE(player) + " " + horse->steed_short()
        + " gains momentum.\n");

    player->tell_watcher(QCTNAME(player)+" slaps the reins back and forth as "
        + POSSESSIVE(player) + " "+horse->steed_short() + " gains momentum.\n",
      ({ enemy, player }));

    precharge_alarms[player->query_real_name()]
        = set_alarm(next_delay, 0.0, 
                    &do_charge_prespecial2(player, enemy, horse));      
}

/*
 * Function:    notify_prep_time
 * Description: This is a hook that abilities can use to know how long
 *              the prep time is before execution. A common usage of
 *              this may be to provide interim messages for long
 *              delays.
 * Arguments:   prep_time - the time before preparation and execution
 * Returns:     nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
    float first_time, second_time;
    object enemy;
    object horse;
    
    horse = query_mounted_solamnian_steed(actor);    
    if (!objectp(horse))
    {
        return;
    }
    
    if (!pointerp(targets) || !sizeof(targets) || !objectp(targets[0]))
    {
        return;
    }
    enemy = targets[0];
    
    first_time = 6.0 + itof(random(ftoi(actor->query_speed(3))));
    second_time = 2.0 + itof(random(ftoi(actor->query_speed(4))));

    precharge_alarms[lower_case(actor->query_real_name())]
        = set_alarm(prep_time - first_time, 0.0, 
                    &do_charge_prespecial1(actor, enemy, horse, 
                                           first_time - second_time));
}

/*
 * Function:    stop_ability
 * Description: At any time during the preparation or cooldown period,
 *              one can call this to remove the alarms.
 * Arguments:   player - player for which to stop the ability and remove
 *                       the alarms.
 * Returns:     0/1 - failure/success of stopping.
 */
public int
stop_ability(object player)
{
    int result;
    
    result = ::stop_ability(player);
    if (result)
    {
        // This ability was successfully stopped. If so, we remove
        // the charge shadow and charge paralyze objects
        set_alarm(0.0, 0.0, &remove_charge_objects(player));
    }
    
    return result;
}

public void
hook_special_preparation_complete()
{
    object * enemies;
    
    set_alarm(0.0, 0.0, &remove_charge_objects(this_player()));
    
    // We have to call init_living on each enemy in the room
    // because aggressives lose their "aggressive" abilities
    // otherwise.
    enemies = filter(all_inventory(environment(this_player())), 
                     &->query_npc());
    if (!sizeof(enemies))
    {
        return;
    }
    
    enemies->init_attack();
}

public void
hook_special_in_cooldown()
{
    write("Try as you might, you just cannot pull your steed around "
        + "quickly enough to make yet another charge.\n");
}

public void
inform_charge_ready(object player)
{
    player->catch_msg("\nYour steed is ready to charge again.\n\n");
}

public void 
hook_special_complete()
{
    // Even though the cooldown is complete, we don't want Knights to
    // charge more than once 90 seconds. Charging allows them to
    // leave combat for 15 seconds at a time, giving them quite an
    // advantage.
    set_alarm(65.0, 0.0, &inform_charge_ready(this_player()));
    set_alarm(0.0, 0.0, &remove_charge_objects(this_player()));

    if (!KATTACK_ABILITY->query_ability_in_cooldown(this_player()))
        KATTACK_ABILITY->hook_special_complete();
    
    // Set this for checking in check_valid_action
    this_player()->add_prop(LAST_CHARGE_COMPLETION_TIME, time());
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object * targets)
{
    write("You pull up sharply on the reins and come to a full stop as you "
        + "realize that your foe is no longer present.\n");    
}

public void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items)
{
    object horse, weapon, player;
    string steed_short, weapon_short, att, tar, aud;
    
    player = this_player();
    weapon = query_primary_weapon(player);
    horse = query_mounted_solamnian_steed(player);
    
    steed_short  = horse->steed_short();
    weapon_short = weapon->short();

    if (phurt < 0)
    {
        att = "Your attempt to strike " + QTNAME(enemy) 
            + " with your " + weapon_short + " misses. You tug on the "
            + "reins of your " + steed_short + ", turning to face "
            + "your foe.";

        tar = QCTNAME(player) + "'s attempt to strike you with "
            + POSSESSIVE(player) + " " + weapon_short + " misses. "
            + C(PRONOUN(player)) + " tugs on the reins of " 
            + POSSESSIVE(player) + " " + steed_short + ", turning to "
            + "face you.";

        aud = QCTNAME(player) + "'s attempt to strike " + QTNAME(enemy)
            + " with " + POSSESSIVE(player) + " " + weapon_short 
            + " misses. " + C(PRONOUN(player)) + " tugs on the reins of "
            + POSSESSIVE(player) + " " + steed_short + ", turning to face "
            + QTNAME(enemy) + ".";
    }
    else
    {        
        switch (phurt)
        {
        case 0..5:
            att = "As your " + steed_short + " bears down upon "
                + QTNAME(enemy)+ ", you strike "
                + POSSESSIVE(enemy) + " " + hdesc + " with a glancing blow from "
                + "your " + weapon_short + ".";
    
            tar = "As " + POSSESSIVE(player) + " " + steed_short + " bears down upon you, "
                + QTNAME(player) + " strikes your " + hdesc + " with a "
                + "glancing blow from " + POSSESSIVE(player) + " " + weapon_short + ".";
    
            aud = "As " + POSSESSIVE(player) + " " + steed_short + " bears down upon "
                + QTNAME(enemy) + ", " + QTNAME(player) + " strikes " + POSSESSIVE(enemy)
                + " " + hdesc + " with a glancing blow from " + POSSESSIVE(player)
                + " " + weapon_short + ".";
            break;
            
        case 6..20:
            att = "The rumbling of the ground beneath your " + steed_short 
                + "'s feet nearly drowns out the sound of the impact as you "
                + "score a moderate hit on the " + hdesc + " of "
                + QTNAME(enemy) + " with your " + weapon_short + ".";
    
            tar = "The rumbling of the ground beneath your feet nearly "
                + "drowns out the sound of the impact as "
                + QTNAME(player) + " scores a moderate hit on your "
                + hdesc + " with " + POSSESSIVE(enemy) + " " + weapon_short + ".";
    
            aud = "The rumbling of the ground beneath your feet nearly "
                + "drowns out the sound of the impact as " + QTNAME(player)
                + " scores a moderate hit on the " + hdesc + " of "
                + QTNAME(enemy) + " with " + POSSESSIVE(player) + " " + weapon_short + ".";
            break;
            
        case 21..35:
            att = "Weapon meets foe as you heavily wound "
                + QTNAME(enemy) + "'s " + hdesc + " with your "
                + weapon_short + ", the momentum of your " + steed_short + " lending its "
                + "strength to the blow.";
    
            tar = QCTNAME(player) + " heavily wounds your " + hdesc
                + " with " + POSSESSIVE(player) + " " + weapon_short + ", the momentum "
                + "of " +POSSESSIVE(player) + " " + steed_short + " lending its strength "
                + "to the blow.";
    
            aud = QCTNAME(player) + " heavily wounds " + QTNAME(enemy) + "'s " + hdesc
                + " with " + POSSESSIVE(player) + " " + weapon_short + " as the two collide, "
                + "the momentum of " + QTNAME(player) + "'s " + steed_short + " lending its "
                + "strength to the blow.";
            break;
            
        case 36..50:
            att = "Your " + steed_short + " charges by " + QTNAME(enemy)
                + ", and you land a perfectly placed blow on " + POSSESSIVE(enemy)
                + " " + hdesc + " with your " + weapon_short + ", wounding " + OBJECTIVE(enemy)
                + " badly.";
            tar = QCTNAME(player) + "'s " + steed_short + " charges by you, "
                + "and " + PRONOUN(player) + " lands a perfectly placed blow on "
                + "your " + hdesc + " with " + POSSESSIVE(player) + " " + weapon_short 
                + ", wounding you badly.";
    
            aud = QCTNAME(player) + "'s " + steed_short + " charges by " + QTNAME(enemy) + ", "
                + "and " + PRONOUN(player) + " lands a perfectly placed blow on "
                + QTNAME(enemy) + "'s " + hdesc + " with " + POSSESSIVE(player) + " "
                + weapon_short + ", wounding " + OBJECTIVE(enemy) + " badly.";
            break;
        
        case 51..100:
        default:    
            att = "Your thundering " + steed_short + " reaches "
                + QTNAME(enemy)+ ", and your " + weapon_short + " smashes "
                + "into " + POSSESSIVE(enemy) + " " + hdesc + " with a tremendous "
                + "thud and devastating power.";
    
            tar = QCTNAME(player) + "'s thundering " + steed_short + " reaches "
                + "you, and " + POSSESSIVE(player) + " " + weapon_short + " smashes into your "
                + hdesc + " with a tremendous thud and devastating power.";
    
            aud = QCTNAME(player) + "'s thundering " + steed_short + " reaches " + QTNAME(enemy)
                + ", and " + POSSESSIVE(player) + " " + weapon_short + " smashes into "
                + POSSESSIVE(enemy) + " " + hdesc + " with a tremendous thud and "
                + "devastating power.";
        }
    }
    
    player->catch_msg( att + "\n");
    enemy->catch_msg( tar + "\n");
    player->tell_watcher( aud + "\n", enemy, ({ enemy, player }));
        
    if (enemy->query_hp() < 1)
    {
        string str;
        switch( weapon->query_wt() )
        {
        case W_SWORD:   str = "severs";       break;
        case W_AXE:     str = "cleaves";      break;
        case W_KNIFE:   str = "slices into "; break;
        case W_POLEARM: str = "impales";      break;
        default:        str = "crushes";      break;
        }

        if (weapon->query_wt() == W_AXE || weapon->query_wt() == W_SWORD)
        {
            player->catch_msg("The thundering crescendo of your "
                + steed_short + " reaches its peak as you collide "
                + "with " + QTNAME(enemy) + " in a deafening "
                + "explosion of sound. Aided by your tremendous momentum, "
                + "your " + weapon_short+ " " + str + " "
                + QTNAME(enemy) + "'s " + (hdesc == "body" ? "head" :
                hdesc) + " from " + POSSESSIVE(enemy) + " body.\n");

            enemy->catch_msg("The thundering crescendo of "
                + QTNAME(player) + "'s " + steed_short
                + " reaches its peak as " + PRONOUN(player)+ " collides with "
                + "you in a deafening explosion of sound. Aided by "
                + POSSESSIVE(player) + " tremendous momentum, " +POSSESSIVE(player)
                + " " +weapon_short + " " + str + " your " 
                + (hdesc == "body" ? "head" : hdesc)+ " from your body.\n");

            player->tell_watcher("The thundering crescendo of "
                + QTNAME(player) + "'s " + steed_short + " reaches its "
                + "peak as " + PRONOUN(player) + " collides with " + QTNAME(enemy)
                + "in a deafening explosion of sound. Aided by "
                + POSSESSIVE(player)+ " tremendous momentum, " + POSSESSIVE(player)
                + " " + weapon_short + " " + str + " " + QTNAME(enemy) + "'s "
                + (hdesc == "body" ? "head" : hdesc) + " from "
                + POSSESSIVE(enemy) + " body.\n", enemy, ({ player, enemy }));
        }
        else
        {
            player->catch_msg("The thundering crescendo of your "
                + steed_short+ " reaches its peak as you collide "
                + "with " + QTNAME(enemy) + " in a deafening "
                + "explosion of sound. Aided by your tremendous momentum, "
                + "your " + weapon_short + " " + str + " "
                + QTNAME(enemy) + "'s " + hdesc + ".\n");

            enemy->catch_msg("The thundering crescendo of "
                + QTNAME(player) + "'s " + steed_short
                + " reaches its peak as " + PRONOUN(player) + " collides with "
                + "you in a deafening explosion of sound. Aided by "
                + POSSESSIVE(player) + " tremendous momentum, "
                + POSSESSIVE(player) + " " + weapon_short + " " + str
                + " your " + hdesc + ".\n");

            player->tell_watcher("The thundering crescendo of "
                + QTNAME(player) + "'s " + steed_short + " reaches its "
                + "peak as " + PRONOUN(player) + " collides with " + QTNAME(enemy)
                + "in a deafening explosion of sound. Aided by "
                + POSSESSIVE(player)+ " tremendous momentum, " + POSSESSIVE(player)
                + " " + weapon_short + " " + str + " " + QTNAME(enemy) + "'s "
                + hdesc+ ".\n", enemy, ({ player, enemy }));
        }
        enemy->do_die(player);
        sever_limb(hdesc);
    }   
}
