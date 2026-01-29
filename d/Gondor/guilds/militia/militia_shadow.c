/*
 * /d/Gondor/guilds/militia/militia_shadow.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis' 
 * called 'legal', and they do not forfeit any of their intellectual 
 * property rights as that document supposes they would.  They are the 
 * sole and complete owners of this code, which as of April 2001 they are 
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Autoloading shadow for the Militia of Thornlin
 *
 * Gwyneth and Auberon, March 4, 2001
 *
 * Modification log:
 * 06/12/01 - Impale F_PENMOD changed to weight dex instead of statavg,
 * and weight guild exp more heavily.  
 * 06/17/01 - Fixed a bug that allowed people to become evil and get
 * kicked out and immediately join again.
 * 06/27/01 - Two more ranks added to the list, now 14 ranks total.
 * 02/04/02 - Cut down damage and reset of impale by 1/3 to reduce the
 * potential for (ab)using it as an offensive special.
 * 10/13/03 - Changed ALIGN_MIN to MILITIA_ALIGN_MIN so it doesn't
 *            conflict with the mud-standard alignment.h
 * 08/12/06 - Palmer - created impale_obj.c to prevent a player from being 
 *            auto-impaled by multiple Militia at once as per AoD request.
 * 05/26/14 - Removed exp penalty for leaving/expulsion. (Gorboth)
 */
    //Prevents a player from being auto-impaled by more than one Militia at a time
inherit "/std/guild/guild_lay_sh";

#include <const.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Gondor/guilds/militia/militia.h"
#include "/d/Gondor/guilds/militia/wep_find.c"
#include "/d/Gondor/defs.h"

/* (skill(max of 50) * 3 + ((int + wis) / 4)) */
#define TASK_LIST	({ SKILL_WEIGHT, 300, SS_MILITIA, SKILL_WEIGHT, 50, \
			SKILL_AVG, TS_INT, TS_WIS, SKILL_END })

/* ((int + wis + dis) * 2 / 3) */
#define VICTIM_LIST	({ SKILL_WEIGHT, 200, SKILL_AVG, TS_INT, TS_WIS, \
			TS_DIS, SKILL_END })

#define MAX_GUILD_LEVEL	14
#define MILITIA_AS_ATTACKED_BY	"_militia_as_attacked_by"
#define PLAYER_I_IMPALE_TIME	"_player_i_impale_time"

#define IMPALE_ABILITY      (MILITIA_DIR + "specials/impale_attack")

private int gTeamAlarm = 0;

/* Testing purposes, real titles need adding */
private string *male_titles = ({ "Raw Recruit", "Loyal Sentry", 
	"Trustworthy Night Watch", "Watchful Sentinel", "Vigilant Watchman",
	"Confident Patroller", "Courageous Protector", "Bold Pikeman", 
	"Iron-willed Defender", "Toughened Veteran", "Warg's Bane", 
	"Vengeful Orc Stalker", "Relentless Goblinbane", "Folk Hero",
        "Legend" });
private string *fem_titles = ({ "Raw Recruit", "Loyal Sentry", 
	"Trustworthy Night Watch", "Watchful Sentinel", "Vigilant Watchwoman", 
	"Confident Patroller", "Courageous Protector", "Bold Pikewoman", 
	"Iron-willed Defender", "Toughened Veteran", "Warg's Bane", 
	"Vengeful Orc Stalker", "Relentless Goblinbane", "Folk Heroine",
        "Legend" });

/*
 * Function name: query_guild_tax_lay
 * Description  : Standard function that returns the amount of
 *                tax the guild charges.
 * Returns      : int - The tax amount
 */
nomask public int
query_guild_tax_lay()
{
    return MILITIA_TAX;
}
/*
 * Function name : query_guild_style_lay
 * Description  : Standard function to return the guild style for this
 *                guild - fighter, magic, cleric, thief or ranger.
 * Returns       : string - the style
 */
nomask public string
query_guild_style_lay()
{
    return MILITIA_STYLE;
}
 
/*
 * Function name : query_guild_name_lay
 * Description  : Standard function that returns the guild name.
 *                This will be used in such things as listing
 *                your guilds while meditating.
 * Returns       : string - the guild name
 */
nomask public string
query_guild_name_lay()
{
    return MILITIA_NAME;
}

/* Function name : query_militia_level
 * Description   : Unique militia function that gives the level of
 *                 the member.
 * Returns       : int - the level of the member
 */
public nomask int
query_militia_level()
{
    return min(MAX_GUILD_LEVEL, shadow_who->query_stat(SS_LAYMAN) / 10);
}

/* Function name : query_guild_title_lay
 * Description   : Standard function that returns the title the
 *                 mortal player has for this guild.
 * Returns       : string - the title
 */
nomask public string
query_guild_title_lay()
{
    if (shadow_who->query_wiz_level() && shadow_who->query_prop(LIVE_I_UNDEAD))
        return "Elf Lover of the Thornlin Militia";

    return ((shadow_who->query_gender() == G_MALE ? 
        male_titles[query_militia_level()] : 
        fem_titles[query_militia_level()]) + " of the Thornlin Militia");
}

/* Function name: query_militia_title
 * Description  : Gives the militia title
 * Returns      : string - the title
 */
nomask public string
query_militia_title()
{
    return query_guild_title_lay();
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
    if (shadow_who->query_default_start_location() == MSTART)
        return MPOST;
    else
        return shadow_who->query_def_post();
}

/*
 * Function name : query_guild_trainer_lay
 * Description  : Standard function that returns one or more references
 *                to the object that defines sk_train_max for the player.
 *                The returned reference can be a string reference, an
 *                object pointer or an array of those. Prevents skill decay.
 * Returns       : string * - an array of paths to the guild's trainers.
 */
nomask public mixed
query_guild_trainer_lay()
{
    return MTRAIN;
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
    if (type == SS_MILITIA)
        return "militia tactics";

    if (type == SS_MILITIA_IMPALE)
        return "impale";

    return 0;
}

/*
 * Function name : query_guild_not_allow_join_lay
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
query_guild_not_allow_join_lay(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not layman. */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    if (name == "Morgul Mages")
    {
        player->catch_tell("We don't want servants of the East around here!");
        return 1;
    }

    if (name == "Dragonarmy")
    {
        player->catch_tell("Your type isn't welcome here!\n");
        return 1;
    }

    return 0;
} 

/*
 * Function name : remove_lay_militia
 * Description   : Unique militia function to remove a guild member with
 *                 all the proper clearing of skills/guild stat/soul/
 *                 shadow/guild object etc.
 * Arguments    : object who    - the member to expel
 *                string reason - the reason they are to be expelled
 *                int mswitch   - optional argument to indicate the member is
 *                                just switching from lay to occ
 * Returns       : 1 - success,  0 - fail
 */
public varargs int
remove_lay_militia(object who, string reason = "unknown", int mswitch = 0)
{
    int ret, prev_exp;
    object emblem;
 
    if (!objectp(who))
        return 0;
 
    prev_exp = shadow_who->query_acc_exp(SS_LAYMAN);

    /* Clear the player's layman guild stat */
    shadow_who->clear_guild_stat(SS_LAYMAN);
 
    /* They are leaving, not switching */
    if (!mswitch)
    {
        /* Penalty for leaving if not switching from occ-lay or lay-occ: 
         * lose 1/8 of total combat exp.
         *   - Let's not do this anymore. In the modern game, this sort of
               punishment for guild-switching is very much obsolete, and
               unfriendly. (Gorboth - May 2014)
        who->add_exp(-(who->query_exp_combat()) / 8, 1);
         */

        /* Remove special skills */
        who->remove_skill(SS_MILITIA);
 
        /* Reset start location */
        if (!mswitch && who->query_default_start_location() == MSTART)
            who->set_default_start_location(who->query_def_start());
 
        /* Give a message before removing the guild emblem. */
        emblem = present(MITEM_ID, shadow_who);
        if(objectp(emblem))
        {
            who->catch_tell("Your " + emblem->short() + " cracks into " +
                "a million pieces and falls to the ground.\n");
            emblem->remove_object();
        }
 
        if (extract(reason, 0, 3) == "evil")
            MJOIN->add_not_allowed(shadow_who->query_real_name());

        /* Remove the militia from the guildhouse if he's there. */
        environment(shadow_who)->remove_militia_members(shadow_who);
 
        /* Keep a cycling log of those removed from the guild. */
        log_file("militia", extract(ctime(time()), 4, 15) + " " +
            capitalize(shadow_who->query_real_name()) + " removed because of " +
            reason + ".\n", 500000);
    }
    else
    {
        emblem = present(MITEM_ID, shadow_who);
        if(objectp(emblem))
            emblem->remove_object();

        shadow_who->set_guild_stat(SS_OCCUP, prev_exp);

        log_file("militia", extract(ctime(time()), 4, 15) + " " +
            capitalize(shadow_who->query_real_name()) + " switched from " +
            "layman to occupational.\n");
    }

    /* Update the member list. */
    MJOIN->remove_member(shadow_who->query_real_name());
 
    /* Remove the guild soul and update the commands. */
    shadow_who->remove_cmdsoul(MSOUL);
    shadow_who->update_hooks();
 
    /* Remove the guild shadow last.  This also resets tax to 0. */
    ret = remove_guild_lay();

    return ret;
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
    string race, reason = "";
 
    setuid();
    seteuid(getuid());
 
    /* Wizards are exempt. */
    if (who->query_wiz_level())
        return 1;

    align = who->query_alignment();
    /* Give an alignment warning, but don't kick out. */
    if (align < ALIGN_WARN)
        who->catch_tell("\nYou're getting dangerously close to being " +
            "expelled for sympathizing with evil!\n\n");

    /* Throw out militia with alignment more evil than the min */
    if (align < MILITIA_ALIGN_MIN)
    {
        reason = ("evil: " + align);
        who->catch_tell("You are too evil to be trusted in Thornlin!\n");
    }

    /* Throw out all sorts of goblins. */
    if (who->query_race() == "goblin")
    {
        race = who->query_race_name();
        reason = ("goblin kind: " + race);
        who->catch_tell("A " + race + "! The Thornlin Militia has no use " +
            "for " + LANG_PWORD(race) + ".\n"); 
    }

    /* Make sure the admin room is loaded */
    MJOIN->teleledningsanka();

    if (MJOIN->query_not_allowed(who->query_real_name()))
    {
        reason = ("not-allowed list");
        who->catch_tell("You have betrayed the Thornlin Militia!\n");
    }

    /* Return 1 here so we can make a few adjustments of our own. */
    if (strlen(reason))
        set_alarm(1.0, 0.0, &remove_lay_militia(who, reason));
 
    return 1;
}

/*
 * Function name : init_militia_lay_member
 * Description   : Add necessary guild items to the player and
 *                 do any other kind of initialization necessary
 *                 after a 1 second alarm to make sure that login
 *                 was completed.
 */
public nomask void
init_militia_lay_member()
{
    object mitem;

    if (!objectp(shadow_who))
        return;

    setuid();
    seteuid(getuid());
    
    /* Clone the guild emblem and move it to the player. */
    if (objectp(mitem = clone_object(MITEM)))
    {
        mitem->move(shadow_who, 1);
        mitem->set_militia_name(shadow_who->query_name());
    }

    /* Make sure the member list is updated minus wizards and juniors. */
    MJOIN->teleledningsanka();

    if (!shadow_who->query_wiz_level() && 
      extract(shadow_who->query_real_name(), -2) != "jr")
        MJOIN->add_member(shadow_who->query_real_name());

    /* Add the guild's soul to the player. */
    shadow_who->add_cmdsoul(MSOUL);
    shadow_who->update_hooks();
}

/*
 * Function name : add_lay_shadow
 * Description   : Shadow an object with this shadow
 * Arguments     : object who - the object to shadow
 * Returns       : as shadow_me in /std/guild/guild_base.c
 */
int
add_lay_shadow(object who)
{
    int ret;
    ret = shadow_me(who, "layman", MILITIA_STYLE, MILITIA_NAME);

    if (ret == 1)
        init_militia_lay_member();

    return ret;
}

/*
 * Function name: init_lay_shadow
 * Description  : This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments    : The argument string sent to autoload_shadow.
 */
void
init_lay_shadow(string arg)
{
    /* delay so that player completes login before we continue */
    set_alarm(1.0, 0.0, &init_militia_lay_member());
}

/*
 * Function name: change_attacked_prop
 * Description  : adds to or subtracts from the prop that keeps track 
 *                of who attacked the player
 * Arguments    : string attacker - the attacker
 *                int togg - 0 remove, 1 add
 */
void
change_attacked_prop(string attacker, int togg)
{
    string *names = shadow_who->query_prop(MILITIA_AS_ATTACKED_BY);

    attacker = lower_case(attacker);

    if (togg)
    {
        if (!sizeof(names))
            names = ({ attacker });
        else if (member_array(attacker, names) == -1)
            names += ({ attacker });
        else
            return;
    }
    else
    {
        if (!sizeof(names))
            return;
        else
            names -= ({ attacker });
    }

    shadow_who->add_prop(MILITIA_AS_ATTACKED_BY, names);
    return;
}

/*
 * Function name: attacked_by
 * Description  : Keeps track of who attacked the player if a pc,
 *                to avoid punishment if the attacker is then killed
 *                and a member of a protected guild.
 * Arguments    : object ob - the attacker
 */
void
attacked_by(object ob)
{
    string *names;

    shadow_who->attacked_by(ob);

    if (!ob->query_npc())
    {
        /* We must do this to prevent abuses of a player using a special
           such as 'taunt' or 'rknee' that causes another player to
           attack them and get impaled. Let's also keep track of who
           does it... */
        if (!objectp(this_interactive()) || this_interactive() != ob)
        {
            log_file("militia_impale", extract(ctime(time()), 4, 15) + " " +
                capitalize(shadow_who->query_real_name()) + " made the player " +
                capitalize(ob->query_real_name()) + " attack.\n");
            return;
        }
        
        if (IS_RANGER(ob) || IS_MILITIA(ob) || 
          ob->query_guild_name_lay() == "Heralds of the Valar")
        {
            change_attacked_prop(ob->query_real_name(), 1);
        }

        object oldtp = this_player();
        set_this_player(shadow_who);
        setuid();
        seteuid(getuid());
        IMPALE_ABILITY->do_ability("");
        set_this_player(oldtp);
    }
}

/*
 * Function name: punish_teaming
 * Description  : Punish teaming after a few minutes
 * Arguments    : object who - the questioned team member
 */
int
punish_teaming(object who, int warned)
{
    int success, align, mil_align;

    if (!objectp(who) || !objectp(shadow_who))
        return 1;

    switch(warned)
    {
    case 0:
        shadow_who->catch_tell("You feel very uneasy about " +
            "being around " + who->query_the_name(shadow_who) + ".\n");

        if (!gTeamAlarm)
            gTeamAlarm = set_alarm(60.0, 0.0, &punish_teaming(who, 1));

        break;

    case 1:
        if (objectp(who) && 
            member_array(who, shadow_who->query_team_others()) != -1)
        {
            shadow_who->catch_tell("Your feeling of uneasiness deepens as " +
                "you remain on the team of " + 
                who->query_the_name(shadow_who) + ".\n");
            gTeamAlarm = set_alarm(90.0, 0.0, &punish_teaming(who, 2));
        }
        else
        {
            gTeamAlarm = 0;
        }
        break;

    case 2:
        if (objectp(who) && 
            member_array(who, shadow_who->query_team_others()) != -1)
        {
            shadow_who->catch_tell("An evil presence invades your mind, " +
                "calling to you to abandon yourself to evil.\n");
            align = who->query_alignment();

            if (align < -250)
            {
                mil_align = shadow_who->query_alignment();
                align /= 3;
                mil_align += align;
                shadow_who->set_alignment(mil_align);
                log_file("militia", extract(ctime(time()), 4, 15) + " " +
                    capitalize(shadow_who->query_real_name()) + " had alignment " +
                    "adjusted by " + align + " to " + mil_align + " for " +
                    "being on " + capitalize(who->query_real_name()) + "'s " +
                    "team.\n");
            }
        }

        gTeamAlarm = 0;
        break;

    default:
        break;
    }
}

/*
 * Function name:    set_leader
 * Description  :    Sets this living as a member in a team
 *                   It will fail if this living is a leader itself
 * Arguments    :    leader: The objectpointer to the leader of the team
 * Returns      :    True if successfull
 */
public int
set_leader(object leader)
{
    int success, mil_align;
    string gname;

    success = shadow_who->set_leader(leader);
    if (leader->query_wiz_level() || shadow_who->query_wiz_level())
        return success;

    gname = leader->query_guild_name_occ();
    if (success && member_array(gname, BANNED_GUILDS) != -1)
    {
        punish_teaming(leader, 0);
    }

    return success;
}

/*
 * Function name: team_join
 * Description  : Sets this living as the leader of another
 *                Fails if we have a leader, then we can't lead others.
 * Arguments    : member: The objectpointer to the new member of my team
 * Returns      : True if member accepted in the team
 */
public int
team_join(object member)
{
    int success, mil_align;
    string gname;

    success = shadow_who->team_join(member);
    if (member->query_wiz_level() || shadow_who->query_wiz_level())
        return success;

    gname = member->query_guild_name_occ();
    if (success && member_array(gname, BANNED_GUILDS) != -1)
    {
        punish_teaming(member, 0);
    }

    return success;
}

/*
 * Function name: punish_player
 * Description  : Punishes a player for killing the wrong thing
 */
int
punish_player()
{
    if (MJOIN->add_warned(shadow_who->query_real_name()) > 0)
    {
        write("You've been warned before! You are stripped of your " +
            "membership in the Thornlin Militia!\n");
        MJOIN->remove_warned(shadow_who->query_real_name());
        MJOIN->add_not_allowed(shadow_who->query_real_name());
        set_alarm(1.0, 0.0, &remove_lay_militia(shadow_who, "second warning"));
        return 1;
    }
    return 0;
}

/*
 * Function name: notify_you_killed_me
 * Description  : Checks that the thing being killed is ok.
 * Arguments    : object killed
 */
void
notify_you_killed_me(object killed)
{
    string *names;

    shadow_who->notify_you_killed_me(killed);

    if (killed->query_npc())
    {
        /* Check for thornlin citizens. */
        if (killed->id("_thornlin_mili"))
        {
            if (!punish_player())
            {
                shadow_who->catch_tell("You just killed a defender of " +
                "Thornlin! Let this be a warning that killing those of " +
                "Thornlin is not acceptable to the Thornlin Militia!\n");
            }
        }
        else if (killed->id("_thornlin_citizen"))
        {
            if (!punish_player())
            {
                shadow_who->catch_tell("You just killed a citizen of Thornlin! " +
                    "Let this be a warning that killing those of Thornlin " +
                    "is not acceptable to the Thornlin Militia!\n");
            }
        }
        else if (killed->id("_gondor_guard"))
        {
            if (!punish_player())
            {
                shadow_who->catch_tell("You just killed a defender of Gondor! " +
                    "Let this be a warning that killing the free people of " +
                    "Middle Earth is not acceptable to the Thornlin Militia!\n");
            }
        }
        else if (killed->id("rohirrim"))
        {
            if (!punish_player())
            {
                shadow_who->catch_tell("You just killed a Rohirrim!\n" +
                    "Let this be a warning that killing the free people of " +
                    "Middle Earth is not acceptable to the Thornlin Militia!\n");
            }
        }
        else if (killed->id("ranger"))
        {
            if (!punish_player())
            {
                shadow_who->catch_tell("You just killed a Ranger!\n" +
                    "Let this be a warning that killing the free people of " +
                    "Middle Earth is not acceptable to the Thornlin Militia!\n");
            }
        }
        /* Commenting this out for the moment. Hobbits might exist in other lands too.
        else if (killed->id("hobbit"))
        {
            if (!punish_player())
            {
                shadow_who->catch_tell("You just killed one of the Shirefolk!\n" +
                    "Let this be a warning that killing the free people of " +
                    "Middle Earth is not acceptable to the Thornlin Militia!\n");
            }
        }
        */
    }
    else
    {
        names = shadow_who->query_prop(MILITIA_AS_ATTACKED_BY);
        if (sizeof(names))
        {
            /* The player was attacked first by the one they just killed. */
            if (member_array(killed->query_real_name(), names) != -1)
            {
                change_attacked_prop(killed->query_real_name(), 0);
                shadow_who->catch_tell(capitalize(killed->query_real_name()) +
                    " died, but attacked you first.\n");
                return;
            }

            if (IS_RANGER(killed))
            {
                if (!punish_player())
                {
                    shadow_who->catch_tell("You just killed a Ranger!\n" +
                        "Let this be a warning that killing the free people of " +
                        "Middle Earth is not acceptable to the Thornlin " +
                        "Militia!\n");
                }
            }

            if (IS_MILITIA(killed))
            {
                shadow_who->catch_tell("You just killed one of your " +
                    "guildmates!\n");
                MJOIN->add_not_allowed(shadow_who->query_real_name());
                set_alarm(1.0, 0.0, &remove_lay_militia(shadow_who, 
                    "killed guildmate " +
                    capitalize(killed->query_real_name())));
            }
            else if (killed->query_guild_name_lay() == "Heralds of the Valar")
            {
                if (!punish_player())
                {
                    shadow_who->catch_tell("You just killed a Herald of " +
                        "the Valar!\nLet this be a warning that killing the " +
                        "free people of Middle Earth is not acceptable to the " +
                        "Thornlin Militia!\n");
                }
            }
        }
    }
}


