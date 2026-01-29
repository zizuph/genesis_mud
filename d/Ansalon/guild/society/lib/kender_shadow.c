/* 
 * /d/Ansalon/guild/kender_occ/kender_shadow.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Autoloading shadow for the Secret Society of Uncle Trapspringer
 *
 * Gwyneth, June 1999
 *
 * Modification log:
 * Gwyneth, January 2001 - General cleanup of the code
 */

inherit "/std/guild/guild_occ_sh";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include "../guild.h"

#define TASK_LIST	({SKILL_AVG, SS_CTACT_SPECIAL, TS_OCC, SKILL_END, \
                         TS_DEX})
#define VICTIM_LIST    ({SKILL_AVG, TS_INT, TS_WIS, SKILL_END, \
                         TS_DEX})

#define MAX_GUILD_LEVEL 18

private int gAutosneak_on = 0;
private int gDodge_on = 0;
public int gBrief = 1;
int gLeave_alarm;

/* Guild titles */
static string *titles = ({"Perpetual Inquirer", "Incessant Inquisitor",
        "Neverending Interrogator", "Eager Prankster",
        "Enthusiastic Daredevil", "Stray Wanderer", "Meandering Wanderer",
        "Curious Excursionist", "Roaming Traveller", "Wandering Trekker",
        "Adventurous Voyager", "Spirited Scout", "Daring Pathfinder",
        "Dauntless Pioneer", "Courageous Trail-Blazer", "Bold Adventurer",
        "Inquisitive Map-Maker", "Fervant Cartographer",
        "Irrepressible Rambler"});

public void kender_run_away(); 

/* Because you know, its 2017 ;) */
public int
query_updated_kender_guild()
{
    return 2017;
}

/*
 * Function name: query_guild_tax_occ
 * Description  : Standard function that returns the amount of
 *                tax the guild charges.
 * Returns      : int - The tax amount
 */
nomask public int
query_guild_tax_occ()
{
    return GUILD_TAX;
}

/*
 * Function name : query_guild_style_occ
 * Description  : Standard function to return the guild style for this
 *                guild - fighter, magic, cleric, thief or ranger.
 * Returns       : string - the style
 */
nomask public string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name : query_guild_name_occ
 * Description  : Standard function that returns the guild name.
 *                This will be used in such things as listing
 *                your guilds while meditating.
 * Returns       : string - the guild name
 */
nomask public string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/* Function name : query_kender_level_occ
 * Description   : Unique kender function that gives the level of
 *                 the member.
 * Returns       : int - the level of the member
 */
public nomask int
query_kender_level_occ()
{
    return min(MAX_GUILD_LEVEL, shadow_who->query_stat(SS_OCCUP) /10);
}

/* Function name : query_guild_title_occ
 * Description   : Standard function that returns the title the
 *                 mortal player has for this guild.
 * Returns       : string - the title
 */
nomask public string
query_guild_title_occ()
{
    string new_title;
    new_title = (shadow_who->query_prop("_ken_new_title"));

    /* Return no title if set. */
    if (!new_title)
        return ("");

    /* Return the normal guild title if set. */
    if (new_title == "normal")
        return (titles[query_kender_level_occ()] + " of the Secret " + 
            "Society of Uncle Trapspringer");

    /* Otherwise return the title chosen from a set list. */
    else 
        return (new_title);
}

/* Function name : query_kender_title
 * Description   : Unique kender function to return the member's set
 *                 title or the standard guild title (when normal or 
 *                 not showing). Used in the guild list.
 * Returns       : string - the title
 */
public nomask string
query_kender_title()
{
    string title, race_title, occ_title;

    if (shadow_who->query_wiz_level())
        return (shadow_who->query_title());

    race_title = (shadow_who->query_guild_title_race());

    /* Check to see if there is a title affiliated with a racial guild. */
    if (!strlen(race_title))
    {
        race_title = "";
    }
    else
    {
        race_title = race_title + ", ";
    }

    /* Find the normal guild title. */
    occ_title = titles[query_kender_level_occ()];

    /* Set up the looks of the title to return. */
    title = (race_title + "the " + occ_title + ".");

    return title;
}

/* Function name: query_def_post
 * Description  : Standard function that gives the path to the
 *                guild's post office for mail upon login notification
 *                purposes.
 * Returns      : string - the pathname to the new postoffice
 */
public string
query_def_post()
{
    /* Only use this post office if the start is set here. */
    if (shadow_who->query_default_start_location() == GUILD_STARTLOC)
        return GUILD_POST;
    else
        return shadow_who->query_def_post();
}

/*
 * Function name : query_guild_trainer_occ
 * Description  : Standard function that returns one or more references
 *                to the object that defines sk_train_max for the player.
 *                The returned reference can be a string reference, an
 *                object pointer or an array of those. Prevents skill decay.
 * Returns       : string * - an array of paths to the guild's trainers.
 */
nomask public mixed
query_guild_trainer_occ()
{
    /* The roof trains combat tactics. The train room everything else. */
    return ({ KGROOM + "train", KGROOM + "roof" });
}

/*
 * Function name : query_guild_skill_name
 * Description  : Standard function to return a name for the guild's
 *                special skills in order to print them out nicely
 *                when a player uses the 'skills' command, rather than
 *                seeing 'special'.
 * Arguments     : int type - the number of the skill assigned by the
 *                 liege of the domain
 * Returns       : 0 if no skill of this guild, else the string.
 */
public mixed
query_guild_skill_name(int type)
{
    if (type == SS_TAUNT_SPECIAL)
    {
        return "taunt";
    }
    else if (type == SS_CTACT_SPECIAL)
    {
        return "combat tactics";
    }
    else if (type == SS_HOOPAK_ALTER)
    {
        return "hoopak alteration";
    }

    return 0;
}

/*
 * Function name : query_guild_not_allow_join_occ
 * Description  : Standard function that deals with allowing or not
 *                allowing this member to join another guild. It is
 *                also called each time the player logs on, so race
 *                checks and such can be called here or in the
 *                query_guild_keep_player() function.
 * Arguments    : object player - the player to test
 *                string type   - the guild type
 *                string style  - the guild style
 *                string name   - the guild name
 * Returns      : int 1 - if the player is not allowed
 *                    0 - if the player is allowed
 */
nomask public int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not occupational. */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    /* Kender aren't thieves, they just borrow things ;-) */
    if (type == "thief")
    {
        player->catch_tell("A thief! You disgrace the kender name!\n");
        return 1;
    }

    // Navarre April 5th 2009: Allowing Kenders to Join pirates.
    // Why not make it up to the players to decide if they want
    // a kender in their crew and the kender to decide if he 
    // wants to be a pirate.
    //
    //    if (name == "Pirate of the Bloodsea")
    //    {
    //        player->catch_tell("The life of a pirate is not for kender.\n");
    //        return 1;
    //    }

    return 0;
}

/*
 * Function name : remove_occ_kender
 * Description   : Unique kender function to remove a guild member with
 *                 all the proper clearing of skills/guild stat/soul/
 *                 shadow/guild object etc.
 * Arguments    : object who    - the member to expel
 *                string reason - the reason they are to be expelled
 * Returns       : 1 - success,  0 - fail
 */
public int
remove_occ_kender(object who, string reason)
{
    int ret;
    object emblem;

    if (!objectp(who))
	return 0;

    /* Remove special skills */
    who->remove_skill(SS_TAUNT_SPECIAL);
    who->remove_skill(SS_CTACT_SPECIAL);
    who->remove_skill(SS_RACK_TALLY);
    who->remove_skill(SS_HOOPAK_ALTER);

    /* Penalty for leaving: loose 1/4 of total combat exp */
    who->add_exp(-(who->query_exp_combat()) / 4, 1);

    /* Clear the player's guild stat */
    shadow_who->clear_guild_stat(SS_OCCUP);

    /* Reset start location */
    if (who->query_default_start_location() == GUILD_STARTLOC)
        who->set_default_start_location(who->query_def_start());

    /* Update the member list. */
    (VMASTER)->rem_member(who->query_real_name());

    /* Give a message before removing the guild emblem. */
    emblem = present("kender_guild_emblem", shadow_who);
    if(objectp(emblem))
    {
        who->catch_tell("Your " + emblem->short() + " cracks into " +
            "a million pieces and falls to the ground.\n");
        emblem->remove_object();
    }

    /* Remove no fear. */
    shadow_who->remove_prop(NPC_I_NO_FEAR);
    shadow_who->remove_prop(NPC_I_NO_RUN_AWAY);

    /* Remove the guild soul and update the commands. */
    shadow_who->remove_cmdsoul(GUILD_CMDSOUL_N);
    shadow_who->update_hooks();

    /* Remove the kender from the guildhouse if he's there. */
    environment(shadow_who)->remove_ex_members(shadow_who);

    /* Keep a cycling log of those removed from the guild. */
    log_file(KEN_LOG, extract(ctime(time()), 4, 15) + " " +
        shadow_who->query_name() + " removed because of " + 
        reason + ".\n", 500000);

    /* Remove the guild shadow last.  This also resets tax to 0. */
    ret = remove_guild_occ();
    return ret;
}

/* 
 * Function name: check_valid_kender_race
 * Description  : Unique kender function to test if the player is
 *                a kender or not after a delay to allow all of the
 *                race souls to be properly loaded. Sets an alarm to
 *                remove the member if non-kender.
 * Arguments    : object who - the member to test
 */
public nomask void
check_valid_kender_race(object who)
{
    if((who->query_race_name() != "kender") &&
      (!who->query_wiz_level()) && 
      (!who->query_ghost()))
    {
        who->catch_tell("Only kender can be members of this guild!\n");
        set_alarm(1.0, 0.0, &remove_occ_kender(who, who->query_race_name()));
    }
}

/*
 * Function name : query_guild_keep_player
 * Description   : Standard function to test if we want to keep the
 *                 player in the guild when the shadow is autoloading
 *                 upon login.
 * Arguments     : who - the player to test
 * Returns       : 1 if keeping, 0 if not
*/
public int
query_guild_keep_player(object who)
{
    int align;
    string reason = "";

    setuid();
    seteuid(getuid());

    /* Wizards are exempt. */
    if (who->query_wiz_level())
        return 1;

    /* Set an alarm to be sure the proper souls are loaded, then check race. */
    set_alarm(10.0, 0.0, &check_valid_kender_race(who));

    /* Throw out thieves. */
    if (who->query_guild_style_lay() == "thief")
    {
        reason = "thief layman";
        who->catch_tell("A thief! You disgrace the Kender name!\n");
    }

    align = who->query_alignment();
    /* Give an alignment warning, but don't kick out. */
    if (align < 0)
        who->catch_tell("\nYou'd better watch your step, or other kender " + 
            "won't trust you anymore!\n\n");

    /* Throw out Kender with alignment more evil than untrustworthy. */
    if(align < -239)
    {
        reason = ("evil: " + align);
        who->catch_tell("You are too evil to be trusted in the Secret Society " +
            "Society of Uncle Trapspringer!\n");
    }

    /* Make sure the admin room is loaded */
    VMASTER->teleledningsanka();

    /* Throw out those expelled */
    if(VMASTER->query_expelled(who->query_real_name()))
    {
        reason = "expelled";
        who->catch_tell("You have been expelled from the guild!\n");
    }

    /* Throw out banished */
    if(VMASTER->query_banished(who->query_real_name()))
    {
        reason = "banished";
        who->catch_tell("You have been banished from the guild!\n");
    }

     /* Throw out enemies */ 
    if(VMASTER->query_enemy(who->query_real_name()))
    {
        reason = "enemy";
        who->catch_tell("You have been made an enemy of the guild!\n");
    }     

    /* Return 1 here so we can make a few adjustments of our own. */
    if (strlen(reason))
        set_alarm(1.0, 0.0, &remove_occ_kender(who, reason));

    return 1;
}

/*
 * Function name : init_kender_occ_member
 * Description   : Add necessary guild items to the player and
 *                 do any other kind of initialization necessary
 *                 after a 1 second alarm to make sure that login
 *                 was completed.
 */
public nomask void
init_kender_occ_member()
{
    object guild_emblem, nametag;

    /* Clone the guild emblem and move it to the player. */
    if (objectp(guild_emblem = clone_object(GUILD_EMBLEM)))
        guild_emblem->move(shadow_who, 1);

    /* Clone a nametag to the kender. */
    if (objectp(nametag = clone_object(KGOBJ + "nametag")))
    {
        nametag->set_owner(shadow_who);
        nametag->move(shadow_who, 1);
    }
    /* Add no fear to the kender. */
    shadow_who->add_prop(NPC_I_NO_FEAR, 1);
    shadow_who->add_prop(NPC_I_NO_RUN_AWAY, 1);

    /* Make sure the member list is updated minus wizards and juniors. */
    if (!VMASTER->query_member(shadow_who->query_real_name()) &&
      !shadow_who->query_wiz_level() && 
      (extract(shadow_who->query_real_name(), -2) != "jr"))
    {
        VMASTER->add_member(shadow_who->query_real_name());
    }

    /* Add the guild's soul to the player. */
    shadow_who->add_cmdsoul(GUILD_CMDSOUL_N);
    shadow_who->update_hooks();

    if(VMASTER->query_voting_member(shadow_who))
    {
        if((VMASTER->query_member_voted(shadow_who->query_real_name())) > 0)
        {
            shadow_who->catch_tell("\nThere are " + LANG_WNUM(
                VMASTER->query_member_voted(shadow_who->query_real_name())) +
                " votes for you to vote on!\n");
        }
        else
        {
            shadow_who->catch_tell("\nThere are no votes for you to vote on.\n");
        }
    }
}

/*
 * Function name : add_occ_shadow
 * Description   : Shadow an object with this shadow
 * Arguments     : object who - the object to shadow
 * Returns       : as shadow_me in /std/guild/guild_base.c
 */
int 
add_occ_shadow(object who)
{
    int ret;
    ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
 
    if (ret == 1)
        init_kender_occ_member();
 
    return ret;
}

/*
 * Function name: init_occ_shadow
 * Description  : This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments    : The argument string sent to autoload_shadow.
 */
void
init_occ_shadow(string arg)
{
    /* delay so that player completes login before we continue */
    set_alarm(1.0, 0.0, &init_kender_occ_member());
}

/*
 * Wander code follows. It has been adapted from the
 * Ranger guild with Elessar's permission.
 */

/*
 * Function name: set_autosneak
 * Description  : Sets the global variable to keep track of
 *                autosneak being on or off.
 * Arguments    : int a - the value to set autosneak to
 */
public void
set_autosneak(int a)
{
    gAutosneak_on = a;
}

/*
 * Function name: query_autosneak
 * Description  : Queries the global autosneak variable.
 * Returns      : int - the value of gAutosneak_on
 */
public int
query_autosneak()
{
    return gAutosneak_on;
}

/*
 * Function name: move_living
 * Description  : masks move_living to allow autosneaking
 * Arguments    : string how - The direction of travel, like "north" or
 *                             "X" for teleportation, or
 *                             "M" if you write leave and arrive messages.
 *                mixed to_dest - Destination
 *                int dont_follow - A flag to indicate group shall not
 *                                  follow this move if this_object()
 *                                  is leader.
 *                int no_glance - Don't look after move.
 * Returns      : Result code of move.
 *                      
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int hiding, retval, val, bval, did_sneak;

    if (!shadow_who->query_prop(LIVE_I_SNEAK) &&
      gAutosneak_on &&
      query_verb() &&
      !(shadow_who->query_prop(OBJ_I_LIGHT) && 
        (shadow_who->query_prop(OBJ_I_LIGHT) >
        environment(shadow_who)->query_prop(OBJ_I_LIGHT))) &&
      !(objectp(shadow_who->query_attack())))
    {
        hiding = environment(shadow_who)->query_prop(ROOM_I_HIDE);
        bval = shadow_who->query_skill(SS_SNEAK) * 2 + 
               shadow_who->query_skill(SS_HIDE) / 3;
        bval = (bval - hiding) / 2;

        if (hiding >= 0 && bval > 0)
        {
            val = bval + random(bval);
            shadow_who->add_prop(OBJ_I_HIDE, val);
            shadow_who->add_prop(LIVE_I_SNEAK, 1);
            did_sneak = 1;
        }
        if (!did_sneak)
            tell_object(shadow_who, "You failed to sneak.\n");
    }

    retval = shadow_who->move_living(how, to_dest, dont_follow, no_glance);

    if (!did_sneak)
        return retval;

    hiding = environment(shadow_who)->query_prop(ROOM_I_HIDE);
    bval = shadow_who->query_skill(SS_HIDE);
    bval = (bval - hiding) / 2;

    set_this_player(shadow_who);
    if (hiding < 0 || bval <= 0)
    {
        write("It's too difficult to hide in here, you're visible again.\n");
        shadow_who->reveal_me(0);
    }
    else if (shadow_who->query_prop(OBJ_I_LIGHT) &&
      (shadow_who->query_prop(OBJ_I_LIGHT) >
        environment(shadow_who)->query_prop(OBJ_I_LIGHT)))
    {
        write("You can't hide here, shining like that!\n");
        shadow_who->reveal_me(1);
    }

    val = bval + random(bval);
    shadow_who->add_prop(OBJ_I_HIDE, val);
    return retval;
}

/*
 * Function name: set_kender_dodge
 * Description  : Sets the global dodge variable to on or off
 * Arguments    : int value - value to set
 */
public void
set_kender_dodge(int value)
{
    gDodge_on = value;
}

/*
 * Function name: query_kender_dodge
 * Description  : Queries if dodging is active or not
 * Returns      : the value of gDodge_on
 */
public int
query_kender_dodge()
{
    return gDodge_on;
}

/*
 * Function name: set_dodge_brief
 * Description  : Sets the global dodge brief variable on or off
 *                to indicate long messages or short.
 * Arguments    : int value - the value to set it to
 */
public void
set_dodge_brief(int value)
{
    gBrief = value;
}

/*
 * Function name: query_dodge_brief
 * Description  : Queries the value of the global dodge brief variable.
 * Returns      : int - the value of gBrief
 */
public int
query_dodge_brief()
{
    return gBrief;
}

/*
 * Function name : find_hoopak
 * Description   : Finds if a hoopak is wielded
 * Returns       : 1 if wielding hoopak, 0 if not
 */
public int
find_hoopak()
{
    object *weapons = shadow_who->query_weapon(-1);
 
    switch(sizeof(weapons))
    {
    case 1:
        if (weapons[0]->id("hoopak"))
            return 1;
        return 0;
    case 2:
        if (weapons[0]->id("hoopak") || weapons[1]->id("hoopak"))
            return 1;
        return 0;
    default:
        return 0;
    }
}

/*
 * Function name: hit_me
 * Description  : Masks hit_me for kender specific wimpy.
 */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    int wi;
    mixed res;

    res = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    if (!(wi = shadow_who->query_whimpy()))
        return res;

    if (((100 * shadow_who->query_hp()) / shadow_who->query_max_hp()) < wi)
    {
        if (gLeave_alarm != 0)
            remove_alarm(gLeave_alarm);
        gLeave_alarm = set_alarm(1.0, 0.0, &kender_run_away());
    }

    return res;
}

/*
 * Function name : kender_run_away
 * Description   : Gives different, more appropriate to 
 *                 kender, messages when forced to run. Nothing but the
 *                 messages are changed.
 */
public void
kender_run_away()
{
    mixed *exits;
    object room;
    string old_mout, old_min;

    if (gLeave_alarm != 0)
    {
        remove_alarm(gLeave_alarm);
        gLeave_alarm = 0;
    }

    if (shadow_who->query_ghost())
        return;

    room = environment(shadow_who);
    exits = room->query_exit_cmds();
    if (!sizeof(exits))
        return;   

    old_mout = shadow_who->query_m_out();
    shadow_who->set_m_out("yells off a taunt and runs");
    old_min = shadow_who->query_m_in();
    shadow_who->set_m_in("runs in, flushed with excitement");
    catch(shadow_who->command("$" + one_of_list(exits)));
    shadow_who->set_m_out(old_mout);
    shadow_who->set_m_in(old_min);
    tell_object(shadow_who, "You yell off a taunt and run!\n");
    return;
}
