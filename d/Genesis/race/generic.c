/*
 * /d/Genesis/race/generic.c
 *
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 *
 * The generic race object for all the races in Genesis.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/player";
inherit "/std/combat/humunarmed";

#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <mail.h>
#include <money.h>
#include <options.h>
#include <std.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Genesis/race/racial_abilities.h"
#include "/d/Genesis/login/login.h"
#include "/d/Genesis/ateam/aoe/events/event.h"

#define COMMON_BOARD    ("/d/Genesis/obj/common_master")
#define DOT_LOGIN(name) (SECURITY->query_wiz_path(name) + "/private/.login")
#define YOUNG_AGE       3600 /* Age of young players to get a nice mail. */
#define YOUNG_AGE_MAIL  ("/d/Genesis/doc/login/NEW_PLAYER_MAIL")

#define BASE_RACE_SOUL ("/d/Genesis/race/race_soul")

public nomask int query_statmod(int stat);    
static mixed stat_modifiers = RACESTATMOD;

static mapping racial_skill_modifiers = ([]);

static int fleet_footed_alarm;

static int has_resilient_resistance;

public string query_extended_intoxicated();
public string query_extended_stuffed();

/*
 * Function name: In this function you can do the add_actions for Genesis
 *                specific commands.
 */
static void 
genesis_commands()
{
}

/*
 * Function name: query_race
 * Description  : Returns the "true" race for this player. This function
 *                is masked in the individual standard race files.
 * Returns      : string "human" - here, will be masked.
 */
string
query_race()
{
    return "human";
}


/*
 * Function name: notify_you_killed_me
 * Description  : This routine is called in the killer when it causes the death
 *                of the victim. It can be used for additional processing.
 *
 *                This routin does not actually exist. It is a trick to fool
 *                the document maker.
 * Argum: object victim - the victim we caused to perish.
 */
void notify_you_killed_me(object victim)
{
    // There is no /std/living implementation of this, surprisingly.
    //::notify_you_killed_me(victim);
    if (!HAS_RACIAL_ABILITY(this_object(), SCAVENGER))
    {
        return;
    }
    if (victim->query_average_stat() * 2 > query_average_stat())
    {
        if (random(100) < SCAVENGER_PERCENTAGE)
        {
            MONEY_MAKE(1, "platinum")->move(this_object(), 1);
            this_object()->catch_msg(
               "As " + QTNAME(victim) + " falls a platinum coin tumbles out " +
               "which you quickly pocket.\n");
        }
    }
}

/*
 * Function name:   query_critical_hit_frequency
 * Description:     The attacker has a one in <frequency> chance of scoring
 *                  a critical hit from their attack.  This can override
 *                  the default value.
 * Returns:         int The frequency to be used by the critical hits
 *                  system.
 */
int query_critical_hit_frequency()
{
    int frequency = ::query_critical_hit_frequency();
    
    // 1 in 10000, turned into 1 in 2000.
    if (HAS_RACIAL_ABILITY(this_object(), OPPORTUNISTIC))
    {
        frequency /= OPPORTUNISTIC_MULTIPLIER;
    }
    return frequency;
}


static object* visited_banks = ({});

/*
 * Function name:   query_bank_fee_reduction_percent
 * Description:     Bank exchange fees reduction.
 * Returns:         int The percentage to reduce the fee.
 */
int query_bank_fee_reduction_percent()
{
    if (HAS_RACIAL_ABILITY(this_object(), WELL_CONNECTED))
    {
        object bank = environment(this_object());
        if (member_array(bank, visited_banks) < 0)
        {
            visited_banks += ({ bank });
            this_object()->catch_msg(
                "You negotiate a discounted exchange rate at this bank.\n");
        }
        return WELL_CONNECTED_PERCENT;
    }
    return 0;
}

public void notify_select_abilities()
{
    if (this_object()->query_skill(RACIAL_ABILITY_SKILL))
        return;
    add_prop(SELECT_BENEFITS_NOTIFY, 1);
    if (this_object()->query_wiz_level())
        return;
    catch_msg("\n\n");

    catch_msg("+---------------------------------------------------------------+\n");
    catch_msg("|                                                               |\n");
    catch_msg("|   Genesis has a new racial system! Please see <help races>    |\n");
    catch_msg("|   to learn more and then <select abilities> to choose your    |\n");
    catch_msg("|   two racial abilities. In order to make the transition to    |\n");
    catch_msg("|   the new system easier you also get one free stat refocus    |\n");
    catch_msg("|   and one free race/body change. These services are provided  |\n");
    catch_msg("|   by the thaumaturgist in Palanthas.                          |\n");
    catch_msg("|                                                               |\n");
    catch_msg("+---------------------------------------------------------------+\n");
}



void set_racial_bonus(int skill, int bonus)
{
    int current = racial_skill_modifiers[skill];
    int allowed = max(0, min(bonus, MAX_RACIAL_SKILL - query_base_skill(skill)));
    if (current == allowed)
    {
        return;
    }
    int desired = query_skill_extra(skill) - current + allowed;
    set_skill_extra(skill, desired);
    racial_skill_modifiers[skill] = allowed;
}

public nomask void configure_racial_skill_bonuses()
{
    if (HAS_RACIAL_ABILITY(this_object(), EXPLORER))
    {
        set_racial_bonus(SS_HERBALISM, 10);
        set_racial_bonus(SS_AWARENESS, 10);
        set_racial_bonus(SS_TRACKING, 10);
        set_racial_bonus(SS_LOC_SENSE, 10);
    }
    else
    {
        set_racial_bonus(SS_HERBALISM, 0);
        set_racial_bonus(SS_AWARENESS, 0);
        set_racial_bonus(SS_TRACKING, 0);
        set_racial_bonus(SS_LOC_SENSE, 0);
    }
    if (HAS_RACIAL_ABILITY(this_object(), STEALTHY))
    {
        set_racial_bonus(SS_SNEAK, 10);
        set_racial_bonus(SS_HIDE, 10);
    }
    else
    {
        set_racial_bonus(SS_SNEAK, 0);
        set_racial_bonus(SS_HIDE, 0);
    }
    if (HAS_RACIAL_ABILITY(this_object(), EYE_FOR_DETAIL))
    {
        set_racial_bonus(SS_TRADING, 20);
        set_racial_bonus(SS_APPR_OBJ, 20);
        set_racial_bonus(SS_APPR_VAL, 20);
    }
    else
    {
        set_racial_bonus(SS_TRADING, 0);
        set_racial_bonus(SS_APPR_OBJ, 0);
        set_racial_bonus(SS_APPR_VAL, 0);
    }
    if (HAS_RACIAL_ABILITY(this_object(), LIGHT_FINGERED))
    {
        set_racial_bonus(SS_PICK_POCKET, 20);
    }
    else
    {
        set_racial_bonus(SS_PICK_POCKET, 0);
    }
    if (HAS_RACIAL_ABILITY(this_object(), RESILIENT))
    {
        if (!has_resilient_resistance)
        {
            inc_prop(OBJ_I_RES_MAGIC,   RESILIENT_MAGIC_RES);
            inc_prop(OBJ_I_RES_POISON,  RESILIENT_POISON_RES);
            has_resilient_resistance = 1;
        }
    }
    else
    {
        if (has_resilient_resistance)
        {
            dec_prop(OBJ_I_RES_MAGIC);
            dec_prop(OBJ_I_RES_POISON);
            has_resilient_resistance = 0;
        }
    }
}

public int set_skill(int skill, int val)
{
    int ret = ::set_skill(skill, val);
    configure_racial_skill_bonuses();
    return ret;
}

int light_footed_footprints()
{
    if (HAS_RACIAL_ABILITY(this_object(), LIGHT_FOOTED))
    {
        if (random(100) < LIGHT_FOOTED_PERCENTAGE)
        {
            if (!this_object()->is_steed_shadow())
            {
                this_object()->catch_msg(
                    "Your step is light as you travel along.\n");
            }
            return 1;
        }
    }
    return 0;
}

void fleet_footed_regeneration()
{
    if (HAS_RACIAL_ABILITY(this_object(), FLEET_FOOTED))
    {
        if (random(100) < FLEET_FOOTED_PERCENTAGE && query_relaxed_from_combat()
            && query_fatigue() < query_max_fatigue())
        {
            add_fatigue(FLEET_FOOTED_AMOUNT);
            if (random(100) < 15)
            {
                this_object()->catch_msg(
                    "You feel an extra spring in your step as some of your " +
                    "fatigue slips away.\n");
            }
        }
    }
}

int herb_ingest_interval()
{
    int interval = F_HERB_INTERVAL;
    if (HAS_RACIAL_ABILITY(this_object(), APOTHECARY))
    {
        interval = APOTHECARY_HERB_INTERVAL(interval);
    }
    return interval;
}    

int max_remembered()
{
    int max = ::max_remembered();
    if (HAS_RACIAL_ABILITY(this_object(), GOOD_MEMORY))
    {
        return F_GOOD_MEMORY(max);
    }
    return max;
}

int max_weight()
{
    int bonus = 0;

    if (HAS_RACIAL_ABILITY(this_object(), STALWART))
    {
        // Effective bonus of +10 STR.
        bonus = 10000;
    }    
    return ::max_weight() + bonus;
}

void configure_racial_bonuses()
{
    if (HAS_RACIAL_ABILITY(this_object(), SCOTOPIC_VISION))
    {
        try {
            object shadow = clone_object(SCOTOPIC_VISION_SHADOW_PATH);
            shadow->shadow_me(this_object());
        }
        catch (mixed ex) {
        }
    } else
    {
        this_object()->remove_infravision_shadow();
    }
    add_prop(LIVE_I_NO_FOOTPRINTS, light_footed_footprints);
    add_prop(LIVE_I_HERB_INTERVAL, herb_ingest_interval);
    add_prop(LIVE_S_EXTENDED_STUFF, query_extended_stuffed);
    add_prop(LIVE_S_EXTENDED_INTOX, query_extended_intoxicated);
    configure_racial_skill_bonuses();
    if (!fleet_footed_alarm)
    {
        fleet_footed_alarm = set_alarm(FLEET_FOOTED_INTERVAL, FLEET_FOOTED_INTERVAL,
           fleet_footed_regeneration);
    }
    set_alarm(20.0, 0.0, notify_select_abilities);
}



/*
 * Function name: common_board_check
 * Description  : This function will check the common board and see whether
 *                a new note has been posted since we last logged in.
 *                It will also inform about mail in the nearby post office.
 * Function name: int last_time - the time I logged in at previously.
 */
nomask void
common_board_check(int last_time)
{
    string file;
    int note_time;
    string post;

    /* Give the player a message about his mail-status. But don't bother with
     * wizards who quickly cloned themselves a mail reader.
     */
    post = this_object()->query_def_post();
    if (stringp(post) && !present(READER_ID))
    {
        catch(post->query_mail());
    }

    /* Sanity check. */
    if (catch(COMMON_BOARD->teleledningsanka()))
    {
	return;
    }

    file = COMMON_BOARD->query_latest_note();
    if (!strlen(file) ||
	(sscanf(file, "b%d", note_time) != 1))
    {
	return;
    }

    if (note_time > last_time)
    {
        /* People who start in the tutorial get a custom message. */
        if (wildmatch(TUTORIAL_DIR + "*", query_default_start_location()))
        {
	    catch_tell("\nThe COMMON board contains a new note since you last logged in!\n" +
		"Please visit the Town Hall in the northern parts of Greenhollow\n" +
                "and read the COMMON board for it contains valuable information!\n\n");
        }
	else
	{
	    catch_tell("\nThe COMMON board contains a new note since you last " +
	        "logged in!\nPlease read the COMMON board for it contains " +
	        "valuable information!\n\n");
	}
    }
}

/*
 * Function name: mail_young_player
 * Description  : When a young player reaches 1 hour of game age, he'll
 *                receive a nice message from the keeper. To keep it simple
 *                and allow for the construction of the message with the
 *                name of the player, the text is kept in the code here.
 */
nomask void
mail_young_player()
{
    /* Don't send to linkdead players. */
    if (interactive())
    {
        MAIL_READER->create_mail("Welcome to the realms!", "AoP Team",
        query_real_name(), "", read_file(YOUNG_AGE_MAIL));
    }
}

/*
 * Function name: do_login_commands
 * Description  : Wizards can have some personal commands in a .login file
 *                in their private directory.
 */
static nomask void
do_login_commands()
{
    string file = DOT_LOGIN(query_real_name());
    string *cmds;

    if (file_size(file) < 1)
        return;

    cmds = explode(read_file(file), "\n");
    foreach(string cmd: cmds)
        command(cmd);
}

/*
 * Function name: no_attack_by_player
 * Description  : Small players shouldn't be attacked by other players in the
 *                Tutorial area.
 * Returns      : error message or 0 if allowed to attack
 */
public mixed
no_attack_by_player()
{
    if (!IS_IN_TUTORIAL(this_object()))
    {
	return 0;
    }
    if (interactive(this_player()))
    {
	return "In the Tutorial area it is not possible to attack other players.\n";
    }
    return 0;
}

/*
 * Function name: start_player
 * Descripiton  : When the player logs in, we set some race-specific stuff.
 */
public void
start_player()
{
    int atime;

    /* Add the race-commandsouls. */
    if (!sizeof(query_cmdsoul_list()))
    {
	add_cmdsoul(RACESOULCMD[query_race()]);
	add_cmdsoul(RACEMISCCMD[query_race()]);
    add_cmdsoul(BASE_RACE_SOUL);
    }

    /* Set the weight of this living. That is dependant on the race. */
    if (query_prop(CONT_I_WEIGHT) <= 1)
	add_prop(CONT_I_WEIGHT, RACEATTR[query_race()][1] * 1000);

    /* Set the volume of this living. That is dependant on the race. */
    if (query_prop(CONT_I_VOLUME) <= 1)
	add_prop(CONT_I_VOLUME, RACEATTR[query_race()][4] * 1000);

    /* Set the height of this living. That is dependant on the race. */
    if (query_prop(CONT_I_HEIGHT) <= 1)
	add_prop(CONT_I_HEIGHT, RACEATTR[query_race()][0]);


    configure_racial_bonuses();
    /* Possible Genesis specific commands. */
    genesis_commands();

    /* Inform the player of a new note on the common board. Give the last
     * login time as argument since it will be reset in the inherited
     * start_player routine.
     */
    set_alarm(2.0, 0.0, &common_board_check(query_login_time()));

    /* Default the web permissions to TRUE starting 16-Feb-2015. */
    if (query_login_time() < 1424044800)
    {
        set_option(OPT_WEB_PERMISSION, 1);
    }

    ::start_player();

    if (wildmatch("*jr", query_real_name()))
        add_prop(PLAYER_I_SEE_ERRORS, 1);

    /* People who start in the tutorial get anti-attack protection. */
    if (wildmatch(TUTORIAL_DIR + "*", query_default_start_location()))
    {
	add_prop(OBJ_M_NO_ATTACK, no_attack_by_player);
    }

    /* Login .login customisation commands from the wizard.
       if (SECURITY->query_wiz_rank(query_real_name()) >= WIZ_NORMAL)
       catch(do_login_commands());
     */

    /* Inform the statistics module. */
    catch(WEBSTATS_CENTRAL->player_login(this_object()));

    /* Inform the event master. */
    catch((EVENT_DIR + "event_dispatcher")->player_login(this_object()));

    /* Automatically send a mail to young players. */
    atime = query_age() * F_SECONDS_PER_BEAT;
    if (atime < YOUNG_AGE)
    {
        set_alarm(itof(YOUNG_AGE - atime), 0.0, mail_young_player);
    }
}

/*
 * Function name: query_def_post
 * Description  : This function returns the location of the post office for
 *                people of this race. It might be good to shadow this
 *                function in guild shadows if the post office is supposed
 *                to be located somewhere special for the guild.
 */
public string
query_def_post()
{
    /* People who start in the tutorial get the tutorial post office. */
    if (wildmatch(TUTORIAL_DIR + "*", query_default_start_location()))
    {
	return TUTORIAL_POST;
    }

    return RACEPOST[query_race()];
}

/*
 * Function name: stats_to_acc_exp
 * Description  : Translates the current base stats into acc_exp and take
 *                the race modofiers into account. All stats are added to
 *                the quest experience only. This function is only used
 *                from the default setup in player_sec::new_init()
 */
static nomask void
stats_to_acc_exp()
{
    int il, sum = 0, tmp;

    for (il = SS_STR ; il < SS_NO_STATS ; il++)
    {
        tmp = stat_to_exp(query_base_stat(il)) * 10 / query_statmod(il);
        
        if (tmp > 0)
        {
            set_acc_exp(il, tmp);

	    /* Only count the "real" stats in the total sum. */
	    if (il < SS_NO_EXP_STATS)
                sum += tmp;
        }
        else
            set_acc_exp(il, 0);
    }

    /* Need to have some basic exp per category. */
    set_exp_quest(sum - 2);
    set_exp_combat(1);
    set_exp_general(1);
}

/*
 * Function name: acc_exp_to_stats
 * Description  : Translates the current accumulated exp into stats and
 *                takes the racial modifiers into account.
 */
void
acc_exp_to_stats()
{
    int il;

    for (il = SS_STR ; il < SS_NO_STATS ; il++)
        if (query_base_stat(il) >= 0)
            set_base_stat(il, exp_to_stat(query_acc_exp(il) * query_statmod(il) / 10));
}

/*
 * Function name: update_stat
 * Description  : Convert exp to stat for a single stat and take the racial
 *                modifiers into account. This usually used by a guild that
 *                wants its stat to behave like the normal.
 * Arguments    : int stat - the stat to update.
 */
public nomask void
update_stat(int stat)
{
    if ((stat >= 0) && (stat < SS_NO_STATS))
        set_base_stat(stat, exp_to_stat(query_acc_exp(stat) * query_statmod(stat) / 10));
}

/*
 * Function name: query_statmod
 * Description  : This function returns the racial stat modifier for this
 *                player for a particular stat.
 * Arguments    : int stat - the stat to get the modifier for.
 * Returns      : int - the racial stat modifier for that stat.
 */
public nomask int
query_statmod(int stat)
{
    return stat_modifiers[query_race()][stat];
}

/*
 * Function name: 	intoxicated_max
 * Description:   	Gives the max intoxication level, used as a call
 *			function from the property: LIVE_I_MAX_INTOX
 * Returns:		Max intoxication level.
 */
int intoxicated_max()
{
    if (!HAS_RACIAL_ABILITY(this_object(), STRONG_LIVER))
    {
        return ::intoxicated_max();
    }
    // Allow alcohol to go past our actual maximum.
    if (calling_function(-1) == "drink_alco")
    {
        return F_STRONG_LIVER(::intoxicated_max());
    }
    return ::intoxicated_max();
}

/*
 * Function name: 	eat_max
 * Description:   	Gives the max amount of food that we can hold
 *			function from the property: LIVE_I_MAX_EAT
 * Returns:		Max food level.
 */
int eat_max()
{
    if (!HAS_RACIAL_ABILITY(this_object(), INSATIABLE))
    {
        return ::eat_max();
    }
    // Allow food to go past our actual maximum.
    if (calling_function(-1) == "eat_food" ||
        calling_function(-1) == "query_stuffed")
    {
        return F_INSATIABLE(::eat_max());
    }
    return ::eat_max();
}

/*
 * Function name:       has_extended_stuffed_levels
 * Description:         Determines whether to show a higher stuffed
 *                      message if stuffed > max_stuffed
 * Returns:             True if the extra messaging should be shown.
 */
public string
query_extended_stuffed()
{
    if (HAS_RACIAL_ABILITY(this_object(), INSATIABLE))
        return "hardly eat another bite";
    return 0;
}

/*
 * Function name:       has_extended_intoxicated_levels
 * Description:         Determines whether to show a higher intox
 *                      message if intox > max_intox
 * Returns:             True if the extra messaging should be shown.
 */
public string
query_extended_intoxicated()
{
    if (HAS_RACIAL_ABILITY(this_object(), STRONG_LIVER))
        return "hammered";
    return 0;
}


public void add_exp_combat(int exp)
{
    if (HAS_RACIAL_ABILITY(this_object(), TENACIOUS))
    {
        if (query_max_exp() > query_exp() + exp && exp > 0
            && random(100) < TENACIOUS_PERCENTAGE)
        {
            this_object()->catch_msg("You feel this combat experience " + 
                "was particularly rewarding.\n");
            exp = F_TENACIOUS_BOOST(exp);
        }
    }
    ::add_exp_combat(exp);
}
