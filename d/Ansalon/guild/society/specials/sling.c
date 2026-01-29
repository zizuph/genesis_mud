/*
 * Sling special for Secret Society of Kenders.
 * 
 * Altered by Carnak.
 * Created by Petros, January 2009
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"

#include "../guild.h"

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed *items,
                                        int result);
static int              check_valid_action(object player, mixed *targets, 
                                           string arg, int execute);
public int              force_fail(object player, mixed *items, object enemy,
                                   int resist, int result);

// Global Variables

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(65);
    set_tohit(90); // 82% hit chance
    set_dt(W_BLUDGEON);
    set_stats( ({ SKILL_WEIGHT, 51, TS_DEX, SKILL_WEIGHT, 28, TS_WIS, 
                  SKILL_WEIGHT, 21, TS_STR }) );
    set_skills(({ SS_CTACT_SPECIAL }) );
    set_ability_prep_time(3);
    set_ability_cooldown_time(4);
    set_ability_name("sling");
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 *                items - 
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    object  who, pebble;
    string  dmsg1,  dmsg2,
            dmsg3,  how,
            khe,    khis,
            khim,   ktname,
            kTname, ehe,
            ehis,   ehim,
            etname, eTname;
    
    /* kender info */
    who     = this_player();
    khe     = who->query_pronoun();
    khis    = who->query_possessive();
    khim    = who->query_objective();
    ktname  = who->query_the_name(enemy);
    kTname  = who->query_The_name(enemy);

    /* enemy info */
    ehe     = enemy->query_pronoun();
    ehis    = enemy->query_possessive();
    ehim    = enemy->query_objective();
    etname  = enemy->query_the_name(who);
    eTname  = enemy->query_The_name(who);
    
    pebble = present("pebble", who);
    
    /* Removing the pebble */
    if (pebble->query_prop(HEAP_I_IS))
        pebble->reduce_heap_size(1);
    else
        pebble->remove_object();
    
    
    if (enemy->query_hp() <= 0)
    {
        if (enemy->query_guild_name_race() == "Red Fang Guild")
        {
            dmsg1 = (QCTNAME(who) + " sends a stone flying at " +
                QTNAME(enemy) + ", which strikes " + ehis +
                " heay with a loud crack. " + QCTNAME(enemy) + " slumps to " +
                "the ground, drooling slightly as " + QTNAME(who) +
                " scrunches up " + khis + " face in imitation of a goblin. " +
                "'Red Fang Forever!' " + khe + " yells in mockery.");
            dmsg2 = (kTname + " sends a stone flying at you, which strikes " +
                "your head with a loud crack. You slump to the ground, a bit " +
                "of drool slipping from between your slack lips. Just as " +
                "darkness overtakes your consciousness, you see " + ktname +
                " scrunch up " + khis + " face in imitation of a goblin. " +
                "'Red Fang Forever!' " + khe + " yells in mockery. The " +
                "words ring in your ears, the last you hear in this lifetime.");
            dmsg3 = ("You send a stone flying at " + etname + ", which " +
                "strikes " + ehis + " head with a loud crack. " + eTname +
                " slumps to the ground, drooling slightly. You scrunch up " +
                "your face in imitation of a goblin. 'Red Fang Forever!' you " +
                "yell in mockery.");
        }
        else
        {
            switch(random(7))
            {
            case 0:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak that lands with a sharp crack, square between " +
                    "the eyes of " + QTNAME(enemy) + ", who stares blankly " +
                    "into space before slumping to the ground. " +
                    QCTPNAME(who) + " concentrated expression brightens as " +
                    khe + " hugs " + khis + " hoopak, " +
                    "delighted at the wonderful shot.");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak that lands with a sharp crack, square between " +
                    "your eyes. You stare blankly into space before " +
                    "slumping to the ground, your last sight that of " +
                    ktname + " hugging " + khis + " hoopak, " +
                    "delighted at the wonderful shot.");
                dmsg3 = ("You let a stone fly from your hoopak, which lands " +
                    "with a sharp crack, square between the eyes of " +
                    etname + ", who stares blankly into space before " +
                    "slumping to the ground. You hug your hoopak, " +
                    "delighted at the wonderful shot.");
                break;
            case 1:
                dmsg1 = (QCTNAME(who) + " flings a stone from " + khis +
                    " hoopak at " + QTNAME(enemy) + " with deadly " +
                    "accuracy, and " + ehe + " staggers for a final brief " +
                    "moment. You hear some wild sounds, and are amazed to " +
                    "see " + QTNAME(who) + " dancing around with " + khis +
                    " hoopak held high, revelling in the victory.");
                dmsg2 = (kTname + " flings a stone from " + khis + " hoopak " +
                    "at you with deadly accuracy. You stagger for a brief " +
                    "moment, your final sight that of " + ktname +
                    " dancing around with " + khis + " hoopak held " +
                    "high, revelling in the victory.");
                dmsg3 = ("You fling a stone from your hoopak at " + etname +
                    " with deadly accuracy, and " + ehe + " staggers for a " +
                    "final brief moment. You hold your hoopak high " +
                    "with a mighty kender victory cry. You dance " +
                    "around with your hoopak, revelling in the " +
                    "victory.");
                break;
            case 2:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak that sends " + QTNAME(enemy) + " plummeting " +
                    "to the ground. With a cheer, " + QTNAME(who) + " swings " +
                    khis + " hoopak wildly" + " while running to " +
                    "inspect " + khis + " fallen foe. Placing " + khis +
                    " foot mightily on the corpse, " + khe + " remarks with " +
                    "a smug face: 'That'll teach 'em to mess with a kender!'");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak that sends you forcefully to the ground. With " +
                    "a cheer, " + ktname + " swings " + khis + " hoopak " +
                    "wildly while running towards you. " + khe + " places " +
                    khis + " foot on your prone form, and the last thing " +
                    "you hear is " + ktname + " remarking with a smug " +
                    "voice: 'That'll teach 'em to mess with a kender!'");
                dmsg3 = ("You let a stone fly from your hoopak that sends " +
                    etname + " plummeting to the ground. With a cheer you " +
                    "give your hoopak an expertly swing and run to inspect " +
                    "your fallen foe. Placing your foot mightily on the " +
                    "corpse, you remark in a smug voice: 'That'll teach 'em " +
                    "to mess with a kender!'");
                break;
            case 3:
                dmsg1 = ("As " + QTNAME(who) + " lets a stone fly from " +
                    khis + " hoopak, you hear a resounding thump as it " +
                    "strikes " + QTNAME(enemy) + " in the forehead. Hoopak " +
                    "in hand, " + khe + " creeps toward the fallen victim " +
                    "with a solemn expression, remarking mostly to " + khim +
                    "self: 'Some people have to learn the hard way.'");
                dmsg2 = ("As " + ktname + " lets a stone fly from " + khis +
                    " hoopak, you feel a burst of pain throughout your head " +
                    "as it strikes you. You slump to the ground. Your last " +
                    "sight is of " + ktname + " creeping towards you with a " +
                    "solemn expression. " + khe + " remarks mostly to " + khe +
                    "self: 'Some people have to learn the hard way.'");
                dmsg3 = ("As you let a stone fly from your hoopak, you hear " +
                    "a resounding thump as it strikes " + etname + " in the " +
                    "forehead. Hoopak in hand, you creep towards your fallen " +
                    "foe. Feeling very solemn, you remark to yourself: " +
                    "'Some people have to learn the hard way.'");
                break;
            case 4:
                dmsg1 = (QCTNAME(who) + " flings a stone from " + khis +
                    " hoopak at " + QTNAME(enemy) + " with " + "deadly " +
                    "accuracy, and " + QTNAME(enemy) + " staggers for a " +
                    "final brief moment. Looking at the fallen victim in " +
                    "shock, " + QTNAME(who) + " murmers: 'Oops!' " + khe +
                    " shrugs off the brief moment of silence and gives " +
                    khis + " hoopak a lovingly pet.");
                dmsg2 = (kTname + " flings a stone from " + khis + " hoopak " +
                    "at you with deadly accuracy, making you stagger " +
                    "briefly before collapsing to the ground. As your " +
                    "vision goes black, the last thing you hear is: 'Oops!'");
                dmsg3 = ("You fling a stone from your hoopak at " + etname +
                    " with deadly accuracy, and " + ehe + " staggers for a " +
                    "final brief moment. Looking at the fallen victim in " +
                    "shock, you murmur: 'Oops!' You shrug off a brief " +
                    "moment of silence and give your hoopak a lovingly pet.");
                break;
            case 5:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak that sends " + QTNAME(enemy) + " falling to " +
                    "the ground. " + QCTNAME(who) + " shows off " + khis +
                    " hoopak with a grandiose gesture, " +
                    "puffs out " + khis + " chest, and attempts to harden " +
                    khis + " childlike features into the visage of a " +
                    "fearsome warrior. You feel sure that the effort is " +
                    "in vain.");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak that sends you falling to the ground. As your " +
                    "lifeblood slowly drains from your body, you see " +
                    ktname + " show off " + khis + " hoopak " +
                    "with a grandiose gesture, puff up " + khis + " chest " +
                    "and attempt to harden " + khis + " childlike features " +
                    "into the visage of a fearsome warrior. Despite the " +
                    "gravity of the situation, you can't help but give off " +
                    "a small wry laugh.");
                dmsg3 = ("You let a stone fly from your hoopak that sends " +
                    etname + " falling to the ground with a mortal wound. " +
                    "You show off your hoopak with a grandiose " +
                    "gesture, puff out your chest, and harden your features " +
                    "into the visage of a fearsome warrior. Unexpectedly, " +
                    "you hear a small laugh come from the dying " +
                    enemy->query_art_name(who) + ". You wonder what " +
                    ehe + " was laughing about.");
                break;
            case 6:
                dmsg1 = (QCTNAME(who) + " lets a stone fly from " + khis +
                    " hoopak. You hear a resounding thump as it strikes " +
                    QTNAME(enemy) + " in the forehead. As " + QTNAME(enemy) +
                    " falls, " + QTNAME(who) + " lets out a gleeful howl of " +
                    "triumph.");
                dmsg2 = (kTname + " lets a stone fly from " + khis +
                    " hoopak. You hear a resounding thump and shooting pain " +
                    "as it strikes you in the forehead. You fall to the " +
                    "ground, " + who->query_the_possessive_name(enemy) +
                    " gleeful howls of triumph ringing in your ears.");
                dmsg3 = ("You let a stone fly from your hoopak. You hear a " +
                    "resounding thump as it strikes " + etname + " in the " +
                    "forehead. " + eTname + " falls to the ground as you " +
                    "let out a gleeful howl of triumph.");
                break;
            default:
                dmsg1 = (QCTNAME(who) + " sends a stone flying from " +
                    khis + " hoopak. It hits " + QTNAME(enemy) + " square " +
                    "in the forehead, killing " + ehim + ".");
                dmsg2 = (kTname + " sends a stone flying from " + khis +
                    " hoopak. It hits you square in the forehead with a " +
                    "mortal blow.");
                dmsg3 = ("You send a stone flying from your hoopak. It hits " +
                    etname + " square in the forehead, killing " + ehim + ".");
                break;
            }
        }

        /* Send death message to the slinger. */
        who->catch_tell(dmsg3 + "\n");

        /* Send death message to the watcher(s). */
        who->tell_watcher(dmsg1 + "\n", enemy);

        /* Send death message to the enemy. */
        enemy->catch_tell(dmsg2 + "\n");

        /* Make the enemy die. */
        enemy->do_die(who);

        return;
    }

    /* Choose hit/miss messages. */
    switch(phurt)
    {
        case -2..0:
        how = "but it flies wide and misses";
            break;
        case 1..15:
        how = "leaving slight bruises";
            break;
        case 16..25:
        how = "leaving bruises";
            break;
        case 26..40:
        how = "leaving painful bruises";
            break;
        case 41..60:
        how = "leaving severe bruises";
            break;
        case 61..80:
        how = "leaving horrible bruises";
            break;
        default:
        how = "landing with a sharp crack";
            break;
    }

    /* Send hit/miss message to slinger. */
    who->catch_tell("You let the stone fly from your hoopak " +
        "towards " + enemy->query_the_possessive_name(who) + " " + hdesc +
        ", " + how + ".\n");

    /* Send hit/miss message to enemy. */
    enemy->catch_tell(who->query_The_name(enemy) + " let's a stone fly " +
        "from " + khis + " hoopak towards your " + hdesc + ", " + how + ".\n");

    /* Send hit/miss message to watcher(s). */
    who->tell_watcher(QTNAME(who) + " let's a stone fly from " + khis +
        " hoopak towards " + QTPNAME(enemy) + " " + hdesc + ", " +
        how + ".\n", enemy);
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure that the kender has
 *                pebbles and is wielding a hoopak.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed *targets, string arg, int pretest)
{
    object *hoopaks = ({});
    
    if (!sizeof(hoopaks = filter(actor->query_weapon(-1), &->id("hoopak"))))
    {
        write("You must wield a hoopak to be able to sling.\n");
        return 0;
    }
    
    if (!objectp(present("pebble", actor)))
    {
        write("You have no pebbles to sling!\n");
        return 0;
    }
    
    return hoopaks;
}

/*
 * Function name: validate_requirements
 * Description  : Function to check all the prerequisites of charge
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_requirements(object player)
{
    seteuid(getuid()); 
    
    if (player->query_skill(SS_CTACT_SPECIAL) < 1)
    {
        player->catch_tell("You don't have enough skill to do that!\n");
        return 0;
    }
    
    /* Temporary Solution*/
    if ("/d/Ansalon/guild/society/wimpy_check.c"->wimp_check(player) < player->query_whimpy())
    {
        player->catch_tell("You're too busy thinking about running away to sling!\n");
        return 0;
    }
    
    return 1;
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
check_valid_action(object player, mixed *targets, string arg, int execute)
{
    object enemy;
    object * enemies;
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (!validate_requirements(player))
    {
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason. Called right before execution at the end
 *                of the delay
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
public int 
force_fail(object player, mixed *items, object enemy, int resist, int result)
{
    if (!validate_requirements(player))
    {
        return 1;
    }
    
    return 0;
}

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
}

public void
hook_special_in_cooldown()
{
    write("You aren't ready to sling again.\n");     
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    if (!objectp(this_player()))
        return;
    
    write("\nYou feel able to sling again.\n\n");    
}

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
    write("You pull back on the hoopak's sling but before you let it fire " +
    "you notice that your target is gone, you unload the pebble.\n");
}

static void 
ability_msg(object actor, mixed *targets, string arg)
{
    write("You load a pebble into the sling of your hoopak while taking " +
    "careful aim at " + targets[0]->query_the_name(actor) + ".\n");
    say(QCTNAME(actor) + " loads a pebble into " + actor->query_possessive() +
    " hoopak while taking aim.\n");
}

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
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    
    int reduction = 100;
    
    if (DODGE_ABILITY->query_ability_active(this_player()))
        reduction = 74; // 48.1 combat aid
    
    return reduction;
}

public int
do_ability(string arg)
{
    object  pebble;
    int     collected,
            mod_type,
            num;
            
    if (!sizeof(target_one_other_present_living_or_enemy(this_player(), arg)))
        return 1;
    
    pebble = present("pebble", this_player());
    num = (objectp(pebble) ? pebble->num_heap() / 10 : 1);
    collected = environment(this_player())->query_prop("_room_i_pebbles_taken");
    // Cant collect pebbles in the air or in water..
    mod_type = environment(this_player())->query_prop(ROOM_I_TYPE) % 4;
    if (!random(num) && (collected < (time() - 50)) && !mod_type &&
        !query_ability_active(this_player()))
    {
        setuid();
        seteuid(getuid());
        pebble = clone_object(KGOBJ + "pebble");
        pebble->set_heap_size(5);
        pebble->move(this_player());
        environment(this_player())->add_prop("_room_i_pebbles_taken", time());
        
        write("You spot a few pebbles on the ground and quickly collect "
        + "them.\n");
    }
    
    return ::do_ability(arg);
}