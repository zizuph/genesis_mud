/*
 * /d/Gondor/guilds/rangers/soul/admin.c
 *
 * Included in the soul. This contains the commands for the council
 * of the Rangers in order to run the guild.
 * Commands included:
 *
 * Entrust <command> <name>   : Any of the following commands may be
 *                              entrusted to a Lieutenant or a Sergeant
 *                              by the Captain.
 * Restrict <command> <name>  : Any of the following commands may be
 *                              restricted from a Sergeant or a Lieutenant
 *                              by the Captain.
 * Approve [of] <name>        : Approve an apprentice to become a Ranger.
 * Reward <name> <amnt> <why> : Reward a Ranger. Amount options are;
 *                              slightly, moderately, generously
 * Promote <name> [to] <rank> : Promote a Ranger. Rank options are;
 *                              Ranger, Sergeant, Lieutenant
 * Demote <name> [to] <rank>  : Demote a Ranger. Rank options are;
 *                              Ranger(from Sgt or Lt), Apprentice(from Ranger)
 * Punish <name> <type> <why> : Type options are: no spells, no brawl, no skills
 * Unpunish <name>            : Lift a Ranger's punishment
 * Expel <name> <why>         : Expel a Ranger from the guild.
 * Unexpel <name>             : If a Ranger hasn't logged in yet after they
 *                              have been marked to be expelled, it can be
 *                              lifted, but not after.
 * Ban(ish) <name> <why>      : Ban a non-Ranger from joining the Rangers.
 * Unban(ish) <name>          : Unbanish a previously banished non-Ranger.
 * Outlaw <name> <reason>     : Outlaw a non-Ranger.
 * Notorious <name> <reason>  : Make a non-Ranger a Notorious Outlaw.
 * Pardon <name>              : Pardon an outlaw or notorious outlaw.
 * Passage <name>             : Grant/ungrant passage into the hideout to
 *                              a visitor
 * Assign <name> <specialty>  : Assign a Ranger a specialty.
 * Assign <name> master       : Assign a specialist to a master position.
 * Advance <name>             : Advance a specialist
 * Unassign <name>            : Unassign a specialist.
 *
 * Original Rangers coded by Elessar
 * Recode by Gwyneth 4/13/01
 *
 * Modification log:
 *   Gwyneth, 20 July 2004: Master/specialist assign, unassign, advance added.
 *   Finwe, 7 March 2005: Added GM to has_access() list
 */
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <language.h>
#include "../rangers.h"
#include "/d/Gondor/defs.h"

#define ADMIN_COMMANDS ({ "advance", "approve", "assign", "ban", "banish", \
   "demote", "entrust", "expel", "notorious", "outlaw", "pardon", "passage", \
    "promote", "punish", "reward", "unassign", "unban", "unban", "unbanish", \
    "unexpel", "unpunish" })
/*
 * Function name: has_access
 * Description  : Checks if the player is allowed to execute this command.
 * Returns      : 1/0 Can execute/cannot execute
 */
int
has_access()
{
    object key;
    string name = capitalize(this_interactive()->query_real_name());

    key = present("_council_key", this_interactive());

    /* Allow wizards to perform commands */
    if ( (this_interactive()->query_wiz_level() &&
        SECURITY->query_wiz_dom(name) == "Gondor") ||
        SECURITY->query_guild_is_master(RANGERS_GUILD_NAME, name)  )
        return 1;

    /* Mortals must have the council key. */
    if (!objectp(key))
        return 0;

    /* If they have rcommands turned off, fail the command. */
    if (!key->query_rcommands())
        return 0;

    /* Captains or GM may perform any admin command */
    if (MANAGER->query_council(name) == CAPTAIN_POSITION ||
        SECURITY->query_guild_is_master(RANGERS_GUILD_NAME, name))
        return 1;

    /* Allow commands entrusted by the Captain to be done. */
    return (member_array(lower_case(query_verb()),
      MANAGER->query_admin_cmds(name)) != -1);
}

/*
 * Function name: valid_target
 * Description  : Checks if the command executer and the target are
 *                in the same company and if the executer is lower
 *                rank than the target.
 * Arguments    : string target - The target of the command
 *                string officer - The executor of the command
 * Returns      : 1/0 Same company and valid rank/Different companies
 *                or invalid
 */
int
valid_target(string target, string officer)
{
    int tlevel = MANAGER->query_ranger_level(target);

    /* Wizards can do all. */
    if (SECURITY->query_wiz_rank(this_interactive()->query_real_name()) > 0)
        return 1;

    /* Target is not a full Ranger, commands allowed. */
    if (tlevel <= APPROVED_APP_LEVEL)
        return 1;

    /* Not in the same company */
    if (MANAGER->query_ranger_level(officer) != tlevel)
    {
        write(capitalize(target) + " is not in your company.\n");
        return 0;
    }

    /* Lower rank council trying command on higher rank council. */
    if (MANAGER->query_council(officer) >= MANAGER->query_council(target) &&
      MANAGER->query_council(target) != -1)
    {
        write(capitalize(target) + " is of higher rank than you.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: approve
 * Description  : Approve an apprentice to become a Ranger.
 * Arguments    : string str - As entered by the user, should consist of
 *                [of] <name>, where name is the one being approved.
 * Returns      : 1/0 Success/Failure
 */
int
approve(string str)
{
    object target_ob;
    string name;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "[of] %w", name))
    {
        notify_fail("Approve of who?\n");
        return 0;
    }

    name = capitalize(name);

    /* Can't add the Ranger to the list of Approved Apprentices. */
    if (!MANAGER->add_ranger(name, "approved"))
    {
        notify_fail(capitalize(name) + " is not an apprentice or has already " +
            "been approved.\n");
        return 0;
    }

    write("You approve of " + name + " as a future Ranger.\n");

    /* If the target is in the realms, send a message to them. */
    target_ob = find_player(lower_case(name));
    if (objectp(target_ob))
    {
        target_ob->catch_tell(this_interactive()->query_name() +
            " approves of you as a future Ranger. You are no " +
            "longer under the time constraints of an Apprentice.\n");
    }

    return 1;
}

/*
 * Function name: banish
 * Description  : Banish a non-Ranger from joining the Rangers. Can be
 *                performed by a Captain or an entrusted officer.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <why> where name is the name of the person to
 *                banish and why is the reason for the banishment.
 * Returns      : 1/0 Success/Failure
 */
int
banish(string str)
{
    string name, reason;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w 'for' %s", name,
      reason))
    {
        notify_fail("Banish <who> for <reason>?\n");
        return 0;
    }

    if (!strlen(reason))
    {
        notify_fail("You must give a reason for banishment.\n");
        return 0;
    }

    name = capitalize(name);

    /* Failed to add the target to the banished list. */
    if (!MANAGER->add_banished(name))
    {
        notify_fail(name + " cannot be banished. They are " +
            "either a Ranger, already banished or do not exist.\n");
        return 0;
    }

    /* Banishment successful */
    write("You banish " + name + " from joining the Rangers.\n");

    return 1;
}

/*
 * Function name: demote
 * Description  : Demotes a Ranger from one rank to another. The Ranger's
 *                current rank must be higher than the designated rank.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> [to] <rank> where name is the name of the Ranger
 *                and rank is one of Ranger or Apprentice.
 * Returns      : 1/0 Success/Failure
 */
int
demote(string str)
{
    int level;
    object target_ob, councilkey;
    string rank, name;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w [to] %w", name, rank))
    {
        notify_fail("Demote who to what rank (ranger or apprentice)?\n");
        return 0;
    }

    name = capitalize(name);
    rank = lower_case(rank);
    level = MANAGER->query_ranger_level(name);

    /* Not listed as a Ranger in the MANAGER */
    if (!level)
    {
        write(name + " is not a Ranger.\n");
        return 1;
    }

    /* Apprentice is the lowest level possible. */
    if (level == APPRENTICE_LEVEL)
    {
        write(name + " cannot be demoted any more, but can be expelled.\n");
        return 1;
    }

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_interactive()->query_real_name()))
        return 1;

    switch(rank)
    {
    case "apprentice":
        /* Demote target to Apprentice rank. */
        MANAGER->add_ranger(name, rank);

        write("You demote " + name + " to the rank of Apprentice.\n");

        /* Send message to target if target is in the realms. */
        target_ob = find_player(lower_case(name));
        if (objectp(target_ob))
        {
            target_ob->catch_tell("You have been demoted to the rank of " +
                "Apprentice!\n");
            target_ob->change_emblem("apprentice");
        }

        break;
    case "ranger":
        /* Captain cannot be demoted normally. */
        if (MANAGER->query_council(name) == CAPTAIN_POSITION)
        {
            write("You cannot demote " + name + " to that rank.\n");
            return 1;
        }

        /* Demote the Lieutenant or Sergeant. */
        MANAGER->remove_council(name);

        write("You demote " + name + " to the rank of Ranger.\n");

        /* Send message to target if target is in the realms. */
        target_ob = find_player(lower_case(name));
        if (objectp(target_ob))
        {
            target_ob->catch_tell("You have been demoted to the rank of " +
                "Ranger!\n");

            /* Remove the council key if present */
                councilkey = present("_Council_Key", target_ob);
                if (objectp(councilkey))
                    {
                    target_ob->catch_tell("Your " + councilkey->short() +
                        " suddenly disappears in a cloud of smoke.\n");
                    councilkey->remove_object();
                    }
        }

        break;

    default:
        /* The rank given by the executor is not an option. */
        notify_fail("That is not a valid rank " + rank + ".\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: entrust
 * Description  : Entrust a command to a Lieutenant or Sergeant so that
 *                they can perform the command in your steed.
 * Arguments    : string str - As entered by the user, should consist of
 *                <command> <name> where command is the name of an officer
 *                command, and name is the name of the officer to give it to.
 * Returns      : 1/0 Success/Failure
 */
int
entrust(string str)
{
    object target_ob;
    string cmd, target;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w [to] %w", cmd, target))
    {
        notify_fail("Entrust which command to who?\n");
        return 0;
    }

    cmd = lower_case(cmd);

    /* The command given by the executor is not an option for entrusting. */
    if (member_array(cmd, ADMIN_COMMANDS) == -1)
    {
        notify_fail("There is no such command or that command is " +
            "not one you can entrust. See the council help page for " +
            "a list of commands.\n");
        return 0;
    }

    target = capitalize(target);

    /* If you have access to this command, you have access to all. */
    if (target == capitalize(this_interactive()->query_real_name()))
    {
        notify_fail("You don't need to entrust commands to yourself.\n");
        return 0;
    }

    /* Check for wiz or council executor, approved- target or */
    /* same company target. Checks for rank superiority. */
    if (!valid_target(target, this_interactive()->query_real_name()))
        return 1;

    /* Only council can have entrusted commands. */
    if (!MANAGER->query_is_council(target))
    {
        notify_fail(target + " is not on council.\n");
        return 0;
    }

    /* Checks pass, add the command to the target's entrusted list. */
    MANAGER->add_admin_cmd(target, cmd);
    write("You entrust the " + cmd + " command to " + target + ".\n");

    /* Send the target a message if in the realms. */
    target_ob = find_player(lower_case(target));
    if (objectp(target))
    {
        target->catch_tell("You have been entrusted with the " + cmd +
            " command.\n");
    }

    return 1;
}

/*
 * Function name: expel
 * Description  : Expel a Ranger from the guild. One can only expel an
 *                Apprentice or member of their company. If the expelled
 *                is an apprentice, no penalty will be inflicted. If it
 *                is a full Ranger, they will feel the full penalty as if
 *                they had left the guild on their own. One may expel the
 *                Ranger 'regretfully' to avoid this punishment.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> [regretfully] <why>, where name is the name of
 *                the Ranger to expel and why is the reason for doing so.
 * Returns      : 1/0 Success/Failure
 */
int
expel(string str)
{
    int soft = 0;
    object target_ob;
    string name, reason;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w %s", name, reason))
    {
        notify_fail("Expel who [regretfully] for what reason?\n");
        return 0;
    }

    if (!strlen(reason))
    {
        notify_fail("Expel who [regretfully] for what reason?\n");
        return 0;
    }

    name = capitalize(name);

    /* Don't expel non-Rangers. */
    if (!MANAGER->query_ranger_level(name))
    {
        notify_fail(name + " is not a Ranger.\n");
        return 0;
    }

    /* Check for wiz or council executor, approved- target or */
    /* same company target. Checks for rank superiority. */
    if (!valid_target(name, this_interactive()->query_real_name()))
        return 1;

    /* Check for withholding of punishment. */
    if (extract(reason, 0, 10) == "regretfully")
        soft = 1;

    /* Expel target directly if they are in the realms. */
    target_ob = find_player(lower_case(name));
    if (objectp(target_ob))
    {
        target_ob->expel_ranger(reason, soft);
        write("You expel " + name + " " + reason + ".\n");
    }
    else
    {
        /* Mark the target for expelling next time they log in. */
        MANAGER->add_to_be_expelled(name, reason, soft);
        write("You mark " + name + " to be expelled.\n");
    }

    return 1;
}

/*
 * Function name: unexpel
 * Description  : If a Ranger hasn't logged in yet after they have been
 *                marked to be expelled, it can be lifted with this
 *                command, but not after.
 * Arguments    : string name - As entered by the user, should consist of
 *                <name> where name is the name of the person to lift the
 *                expel from.
 * Returns      : 1/0 Success/Failure
 */
public int
unexpel(string name)
{
    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No argument entered */
    if (!strlen(name))
    {
        notify_fail("Unexpel <name>?\n");
        return 0;
    }

    /* Capitalize the name */
    name = capitalize(name);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_interactive()->query_real_name()))
        return 1;

    if (!MANAGER->remove_to_be_expelled(name))
    {
        notify_fail(name + " has not been marked to be expelled.\n");
        return 0;
    }

    write("You remove " + name + " from the list of Rangers to be " +
        "expelled.\n");
    return 1;
}

/*
 * Function name: notorious
 * Description  : Make a non-Ranger a Notorious Outlaw. Notorious Outlaws
 *                are not subject to a time limit. However, it is suggested
 *                that one-time offenders be removed after a period of time.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <reason> where name is the name of the person to
 *                make a notorious outlaw and reason is the reason for it.
 * Returns      : 1/0 Success/Failure
 */
int
notorious(string str)
{
    string name, reason;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w %s", name, reason))
    {
        notify_fail("Mark who as a notorious outlaw for what reason?\n");
        return 0;
    }

    if (!strlen(reason))
    {
        notify_fail("Mark who as a notorious outlaw for what reason?\n");
        return 0;
    }

    name = capitalize(name);

    if (!MANAGER->add_notorious_outlaw(name))
    {
        /* Failed to mark the target as a notorious outlaw, */
        /* target does not exist or is a Ranger. */
        notify_fail(name + " cannot be marked as a notorious outlaw.\n");
        return 0;
    }

    /* Target marked successfully. */
    write("You mark " + name + " as a notorious outlaw.\n");
    return 1;
}

/*
 * Function name: outlaw
 * Description  : Outlaw a non-Ranger. Outlaw status is subject to a time
 *                limit. After a set amount of time, they will be removed
 *                from the list.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <why> where name is the person to be outlawed and
 *                why is the reason.
 * Returns      : 1/0 Success/Failure
 */
int
outlaw(string str)
{
    string name, reason;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w %s", name, reason))
    {
        notify_fail("Mark who as an outlaw for what reason?\n");
        return 0;
    }

    if (!strlen(reason))
    {
        notify_fail("Mark who as an outlaw for what reason?\n");
        return 0;
    }

    name = capitalize(name);

    if (!MANAGER->add_outlaw(name))
    {
        /* Failed to mark the target as an outlaw, */
        /* target does not exist or is a Ranger. */
        notify_fail(name + " cannot be marked as an outlaw.\n");
        return 0;
    }

    /* Target marked successfully as an outlaw. */
    write("You mark " + name + " as an outlaw.\n");
    return 1;
}

/*
 * Function name: pardon
 * Description  : Pardon an outlaw or notorious outlaw.
 * Arguments    : string name - As entered by the user, should consist of
 *                <name> where name is the (notorious) outlaw to pardon.
 * Returns      : 1/0 Success/Failure
 */
int
pardon(string name)
{
    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No target given. */
    if (!strlen(name))
    {
        notify_fail("Pardon who?\n");
        return 0;
    }

    name = capitalize(name);

    /* Is the target a notorious outlaw? */
    if (MANAGER->query_notorious_outlaw(name))
    {
        /* Remove the target from the notorious outlaw list. */
        MANAGER->remove_notorious_outlaw(name);
        write("You remove " + name + " from the notorious outlaw list.\n");

        /* Two pardons must be given to remove from NO AND outlaw lists. */
        if (MANAGER->query_is_outlaw(name))
        {
            write("You will have to grant one more pardon to " + name +
                " for them to be removed from the normal outlaw list.\n");
        }

        return 1;
    }

    /* Is the target on the outlaw list only? */
    if (MANAGER->query_is_outlaw(name))
    {
        /* Remove the target from the outlaw list. */
        MANAGER->remove_outlaw(name);
        write("You remove " + name + " from the outlaw list.\n");
        return 1;
    }

    /* Target not on either list. */
    write("No such outlaw or notorious outlaw.\n");
    return 1;
}

/*
 * Function name: passage
 * Description  : Grant passage into the hideout to a visitor.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name>, where name is the one being granted passage.
 * Returns      : 1/0 Success/Failure
 */
int
passage(string str)
{
    object entrance;
    string name, company, *list;

    /* Check for wiz, captain or entrusted. */
    if (!has_access() && !SECURITY->query_guild_is_master("rangers", name))
        return 0;

    FIX_EUID;

    if (!strlen(str))
    {
        company = TI->query_company();

        if (company == "ithilien" || TI->query_wiz_level())
        {
            LOAD_ERR(RANGERS_ITH_DIR + "entrance.c");
            entrance = find_object(RANGERS_ITH_DIR + "entrance");

            list = entrance->query_all_allowed();
            if (!sizeof(list))
                write("Nobody currently is allowed passage to the " +
                    "Ithilien guildhall.\n");
            else
                write("The following are allowed passage to the " +
                    "Ithilien guildhall.\n" + COMPOSITE_WORDS(list) + ".\n");
        }

        if (company == "north" || TI->query_wiz_level())
        {
            LOAD_ERR(RANGERS_NOR_DIR + "stairs");
            entrance = find_object(RANGERS_NOR_DIR + "stairs");

            list = entrance->query_all_allowed();
            if (!sizeof(list))
                write("Nobody currently is allowed passage to the " +
                    "Northern guildhall.\n");
            else
                write("The following are allowed passage to the " +
                    "Northern guildhall.\n" + COMPOSITE_WORDS(list) + ".\n");
        }

        return 1;
    }

    if (TI->query_wiz_level())
    {
        if (!parse_command(str, ({}), "[for] %w [to] [the] %w",
          name, company) ||
          (company != "north" && company != "ithilien"))
        {
            notify_fail("Passage for who to which company?\n");
            return 0;
        }
    }
    else
    {
        if (!parse_command(str, ({}), "[for] %w", name))
        {
            notify_fail("Passage for who?\n");
            return 0;
        }

        company = this_interactive()->query_company();
    }

    if (!SECURITY->exist_player(lower_case(name)))
    {
        write(name + " does not exist.\n");
        return 1;
    }

    name = CAP(name);
    switch(company)
    {
        case "north":
            (RANGERS_NOR_DIR + "stairs")->teleledningsanka();
            entrance = find_object(RANGERS_NOR_DIR + "stairs.c");
            break;

        case "ithilien":
            (RANGERS_ITH_DIR + "entrance")->teleledningsanka();
            entrance = find_object(RANGERS_ITH_DIR + "entrance.c");
            break;

        default:
            write("Something went wrong, please make a bugreport.\n");
            return 1;
    }

     if (entrance->query_allowed(name))
    {
        entrance->rem_allowed(name);
        write("You remove passage to the guildhouse for " + name + ".\n");
        return 1;
    }

    entrance->add_allowed(name);
    write("You grant passage into your hideout to " + name + ".\n");
    return 1;
}

/*
 * Function name: promote
 * Description  : Promote to Ranger, Sergeant or Lieutenant. By promoting
 *                an approved Apprentice to Ranger, they will become part
 *                of your company. Only the Captain can promote a Ranger
 *                to Sergeant or Lieutenant.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> [to] <rank> where name is the person to promote
 *                and rank is the rank to promote to (ranger, sergeant or
 *                lieutenant).
 * Returns      : 1/0 Success/Failure
 */
int
promote(string str)
{
    string name, rank, company = "";
    object target_ob, councilkey;

    setuid();
    seteuid(getuid());

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* Only wizards can choose which company to promote someone to. */
    if (this_interactive()->query_wiz_level())
    {
        /* No match */
        if (!strlen(str) || !parse_command(str, ({}),
          "%w [to] [a] %w [of] [the] [rangers] [of] [the] %w [company]",
          name, rank, company))
        {
            notify_fail("Promote who to what rank of which company?\n");
            return 0;
        }

        name = capitalize(name);
        company = lower_case(company);
    }
    else
    {
        /* No match */
        if (!strlen(str) || !parse_command(str, ({}), "%w 'to' %w", name, rank))
        {
            notify_fail("Promote who to what rank?\n");
            return 0;

        }

        /* Company defaults to the company of the command executor. */
        company = lower_case(this_interactive()->query_company());
        name = capitalize(name);

        /* Check for wiz or council executor, approved- target or same */
        /* company target. Checks for rank superiority. */
        if (!valid_target(name, this_interactive()->query_real_name()))
            return 1;
    }

    switch(lower_case(rank))
    {
    case "ranger":
        /* Person must be an Approved Apprentice to be promoted to Ranger. */
        if (MANAGER->query_ranger_level(name) != APPROVED_APP_LEVEL)
        {
            write(name + " is not an Approved Apprentice.\n");
            return 1;
        }

        switch(company)
        {
        case "ithilien":
        case "north":
            /* Promote the target to Ranger of the selected company. */
            MANAGER->add_ranger(name, company);
            write("You promote " + name + " to a Ranger of the " +
                capitalize(company) + " company!\n");
            break;

        default:
            /* Wizard gave a bad company option. */
            write("No such company.\n");
            break;
        }

        /* Send message to target if target is in the realms. */
        target_ob = find_player(lower_case(name));
        if (objectp(target_ob))
        {
            target_ob->catch_tell("You have been promoted to the rank of "
                + "Ranger of the " + capitalize(company) + " company. "
                + "Congratulations!\n");
            switch(company)
            {
            case "ithilien":
                target_ob->change_emblem("ithilien");
                break;
            case "north":
                target_ob->change_emblem("north");
                break;
            }
        }

        return 1;

    case "sergeant":
        switch(company)
        {
        case "ithilien":
        case "north":
            if (!MANAGER->add_council(name, SERGEANT_POSITION, company))
            {
                /* Non Ranger or not a full Ranger. */
                write("Failed to add " + name + " as Sergeant.\n");
                return 1;
            }

            /* Promotion successful. */
            write("You promote " + name + " to Sergeant " +
                "of the " + capitalize(company) + " company!\n");

            target_ob = find_player(lower_case(name));
            if (objectp(target_ob))
            {
                target_ob->catch_tell("You have been promoted to the " +
                    "rank of Sergeant!\n");

                /* Add the council key if not present */
                    councilkey = present("_Council_Key", target_ob);
                    if (!objectp(councilkey))
                        {
                        target_ob->catch_tell("A gold key" +
                            " suddenly appears in your hand.\n");
                        councilkey = clone_object(RANGERS_COUNCILKEY);
                        councilkey->move(target_ob, 1);
                        }
            }

            return 1;

        default:
            /* Wizard gave invalid company. */
            write("No such company.\n");
            return 1;
        }

    case "lieutenant":
        switch(company)
        {
        case "ithilien":
        case "gondor":
        case "north":
            if (!MANAGER->add_council(name, LIEUTENANT_POSITION, company))
            {
                /* Non Ranger or not a full Ranger. */
                write("Failed to add " + name + " as Sergeant.\n");
                return 1;
            }

            /* Promotion successful. */
            write("You promote " + name + " to Lieutenant " +
                "of the " + capitalize(company) + " company!\n");

            target_ob = find_player(lower_case(name));
            if (objectp(target_ob))
            {
                target_ob->catch_tell("You have been promoted to the " +
                    "rank of Lieutenant!\n");

                /* Add the council key if not present */
                    councilkey = present("_Council_Key", target_ob);
                    if (!objectp(councilkey))
                        {
                        target_ob->catch_tell("A gold key" +
                            " suddenly appears in your hand.\n");
                        councilkey = clone_object(RANGERS_COUNCILKEY);
                        councilkey->move(target_ob, 1);
                        }
            }

            return 1;

        default:
            /* Wizard gave invalid company. */
            write("No such company.\n");
            return 1;
        }

    case "captain":
        if (!this_interactive()->query_wiz_level())
        {
            write("You aren't allowed to do that.\n");
            return 1;
        }
        switch(company)
        {
        case "ithilien":
        case "north":
            if (!MANAGER->add_council(name, CAPTAIN_POSITION))
            {
                /* Non Ranger or not a full Ranger. */
                write("Failed to add " + name + " as Captain.\n");
                return 1;
            }

            /* Promotion successful. */
            write("You promote " + name + " to Captain " +
                "of the " + capitalize(company) + " company!\n");
            return 1;

        default:
            /* Wizard gave invalid company. */
            write("No such company.\n");
            return 1;
        }

    default:
        /* Rank given not an option. */
        notify_fail("There is no such rank, " + rank + ".\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: punish
 * Description  : Punish a Ranger with no spells, no brawl or noskills.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <type> <why> where name is the Ranger to punish,
 *                type is one of no spells, no brawl or noskills and why
 *                is the reason for the punishment.
 * Returns      : 1/0 Success/Failure
 */
int
punish(string str)
{
    object target;
    string name, punish, why;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w [with] %w [for] %s",
      name, punish, why))
    {
        notify_fail("Punish <name> with <punishment> for <reason>.\n");
        return 0;
    }

    name = lower_case(name);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_player()->query_real_name()))
        return 1;

    /* If target is not in the realms, mark them for punishment next login. */
    target = find_player(name);
    if (!objectp(target))
    {
        /* Target is not a Ranger or punishment doesn't exist. */
        if (!MANAGER->add_to_be_punished(name, punish, why))
        {
            notify_fail("That person is not a Ranger or that " +
                "punishment is not an option.\n");
            return 0;
        }

        write("You mark " + capitalize(name) + " to be punished with " +
            punish + " for " + why + ".\n");
    }
    else
    {
        if (!MANAGER->punish_ranger(name, punish, why))
        {
            /* Failed to punish the target. */
            notify_fail("That person is not a Ranger, or that " +
                "punishment is not an option.\n");
            return 0;
        }

        /* Punishment given. */
        write("You punish " + capitalize(name) + " with " + punish +
            " for " + why + ".\n");

        if (environment(target) == environment(this_player()))
            target->catch_tell(this_player()->query_The_name(target) +
                " punishes you with " + punish + " for " + why + ".\n");
        else
            MANAGER->send_message(target, "You have been punished with " +
                punish + " for " + why + ".\n");

    }

    return 1;
}

/*
 * Function name: restrict
 * Description  : Restrict an admin command from a Sergeant or Lieutenant.
 * Arguments    : string str - As entered by the user, should consist of
 *                <command> [from] <name> where command is the command to
 *                restrict and name is the person to restrict it from.
 * Returns      : 1/0 Success/Failure
 */
int
restrict(string str)
{
    object target_ob;
    string cmd, target;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w [from] %w", cmd, target))
    {
        notify_fail("Restrict which command from who?\n");
        return 0;
    }

    cmd = lower_case(cmd);

    /* Command input is not an option. */
    if (cmd != "all" && member_array(cmd, ADMIN_COMMANDS) == -1)
    {
        notify_fail("No such command to restrict, " + cmd + ". See the " +
            "council help page for a list.\n");
        return 0;
    }

    /* Don't restrict from oneself. */
    if (lower_case(target) == this_interactive()->query_real_name())
    {
        notify_fail("What, don't you trust yourself?\n");
        return 0;
    }

    target = capitalize(target);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(target, this_interactive()->query_real_name()))
        return 1;

    /* Entrusted commands can only be entrusted to council. So no
       way to have an entrusted command to remove on a non-council. */
    if (!MANAGER->query_is_council(target))
    {
        notify_fail(target + " is not an officer.\n");
        return 0;
    }

    /* Remove all of the entrusted commands for the target. */
    if (cmd == "all")
    {
        if (MANAGER->remove_all_admin_cmds(target))
        {
            /* Removal of entrusted commands successful. */
            write(target + " no longer has access to any Ranger admin " +
                "command.\n");
        }
        else
        {
            write(target + " didn't have any entrusted commands in the " +
                "first place.\n");
        }

        return 1;
    }

    if (MANAGER->remove_admin_cmd(target, cmd))
    {
        /* Command removed from entrusted list successfully. */
        write(target + " no longer has access to " + cmd + ".\n");
    }
    else
    {
        write(target + " does not have that command in the first place.\n");
    }

    return 1;
}

/*
 * Function name: reward
 * Description  : Reward a Ranger slightly, moderately or generously.
 *                Rewarding a Ranger slightly is like a pat on the back
 *                for a job well done. Rewarding a Ranger moderately is
 *                for tasks assigned and completed successfully. A generous
 *                reward should be given out only very rarely. It is the
 *                exception, not the rule.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <amnt> <why> where name is the Ranger to reward,
 *                amnt is one of slightly, moderately or generously and
 *                why is the reason for the reward.
 * Returns      : 1/0 Success/Failure
 */
int
reward(string str)
{
    object target;
    string name, reward, why;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str))
    {
        notify_fail("Reward <name> <slightly/moderately/generously> for " +
            "<reason>.\n");
        return 0;
    }

    if(!parse_command(str, ({}), "%w %w [for] %s", name, reward, why))
    {
        notify_fail("Reward <name> <slightly/moderately/generously> for " +
            "<reason>.\n");
        return 0;
    }

    /* This shouldn't ever happen, but just to be sure. */
    if (!strlen(name))
        return 0;

    /* This shouldn't ever happen, but just to be sure. */
    if (!strlen(reward))
        reward = "moderately";

    /* This might happen. */
    if (!strlen(why))
        why = "meritorious deeds!";

    /* Get rid of the . since parse_command doesn't like filtering it out. */
    if (extract(why, -1) == ".")
        why = extract(why, 0, strlen(why) - 2);

    if (extract(why, -1) != "!")
        why += "!";

    name = capitalize(name);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_interactive()->query_real_name()))
        return 1;

    switch(lower_case(reward))
    {
    case "slightly":
    case "moderately":
    case "generously":
        break;
    default:
        notify_fail("No such reward amount, " + reward + ".\n");
        return 0;
    }

    target = find_player(lower_case(name));
    if (!objectp(target))
    {
        if (!MANAGER->add_to_be_rewarded(name, reward, why))
        {
            notify_fail(name + " is not a Ranger.\n");
            return 0;
        }

        write("You mark " + name + " to be rewarded " + reward +
            " for " + why + "\n");
    }
    else
    {
        if (!MANAGER->reward_ranger(name, reward))
        {
            notify_fail("No such reward, " + reward + ". Options are - " +
                "slightly, moderately or generously.\n");
            return 0;
        }

        write("You reward " + name + " " + reward + " for " + why + "\n");
        MANAGER->reward_ranger(name);

        if (environment(target) == environment(this_interactive()))
            target->catch_tell(this_interactive()->query_The_name(target) +
                " rewards you " + reward + " for " + why + "\n");
        else
            MANAGER->send_message(target, "You have been rewarded " +
                reward + " for " + why + "\n");

    }

    MANAGER->rlog(MANAGER->query_ranger_company(name),
        capitalize(this_interactive()->query_real_name()) + " rewarded " +
        name + " with " + reward + " for " + why);
    return 1;
}

/*
 * Function name: unbanish
 * Description  : Unbanish a previously banished non-Ranger.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> where name is the person to unbanish.
 * Returns      : 1/0 Success/Failure
 */
int
unbanish(string name)
{
    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    if (!strlen(name))
    {
        notify_fail("Unbanish who?\n");
        return 0;
    }

    name = capitalize(name);

    /* Try to remove target from the banished list. */
    if (!MANAGER->remove_banished(name))
    {
        /* Target wasn't banished in the first place. */
        write(name + " is not banished.\n");
        return 1;
    }
    else
    {
        /* Unbanishment successful. */
        write("You remove " + name + " from the banished list.\n");
        return 1;
    }
}

/*
 * Function name: unpunish
 * Description  : Remove a punishment from a Ranger. The same type options
 *                as punish apply.
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <type> where name is the Ranger to remove the
 *                punishment from and type is the type of punishment to lift.
 * Returns      : 1/0 Success/Failure
 */
int
unpunish(string str)
{
    object target;
    string name, punish, why;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "%w [for] %w", name, punish))
    {
        notify_fail("Unpunish <name> for <punishment>.\n");
        return 0;
    }

    name = lower_case(name);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_player()->query_real_name()))
        return 1;

    /* If target is not in the realms, mark them for unpunishment next login. */
    target = find_player(name);
    if (!objectp(target))
    {
        /* Target is not a Ranger or already is marked to be unpunished. */
        if (!MANAGER->add_to_be_unpunished(name))
        {
            notify_fail("That person is not a Ranger or has already " +
                "been marked to have their punishment lifted.\n");
            return 0;
        }

        write("You mark " + capitalize(name) + " to have their punishment " +
            "lifted.\n");

        /* Punishment removal logged to be acted on next login. */
        MANAGER->rlog(MANAGER->query_ranger_company(name), capitalize(name) +
            " marked to have punishment lifted by " +
            capitalize(this_interactive()->query_real_name()));
        return 1;
    }
    else
    {
        MANAGER->add_to_be_unpunished(name);
        if (!MANAGER->unpunish_ranger(name))
        {
            /* Failed to unpunish the target. */
            notify_fail("That person is not a Ranger or is not punished.\n");
            return 0;
        }

        /* Punishment lifted. */
        write("You lift the punishment for " + capitalize(name) + ".\n");

        if (environment(target) == environment(this_player()))
        {
            target->catch_tell(this_player()->query_The_name(target) +
                " lifts your punishment!\n");
            return 1;
        }

        return 1;
    }
}

/*
 * Function name: assign
 * Description  : Assign a ranger to a specialty or to a master position
 * Arguments    : string str - As entered by the user, should consist of
 *                <name> <specialty>/master where name is the Ranger to
 *                specialize, and specialty is the particular specialty,
 *                or the word master, which assigns a specialist to master.
 * Returns      : 1/0 Success/Failure
 */
public int
assign(string str)
{
    string name, specialty;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    if (!strlen(str) || !parse_command(str, ({}), "%w [as] %w", name, specialty))
    {
        notify_fail("Assign <name> <specialty>/master?\n");
        return 0;
    }

    name = lower_case(name);
    specialty = capitalize(specialty);

    if (MANAGER->query_is_council(name))
    {
        notify_fail("Council members cannot specialize.\n");
        return 0;
    }

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_player()->query_real_name()))
        return 1;

    if (specialty == "Master")
    {
        specialty = MANAGER->query_specialist_specialty(name);
        if(!strlen(specialty))
        {
            write(capitalize(name) + " is not a specialist.\n");
            return 1;
        }
        else if (MANAGER->query_is_master(name))
        {
            write(capitalize(name) + " is already a master.\n");
        }
        else if (!MANAGER->add_master(name))
        {
            write("Something has gone wrong and " + capitalize(name) +
                "is unable to be made a master.\n");
            return 1;
        }
        else
        {
            reward(name + " generously for becoming a Master " +
                MANAGER->query_master_specialty(name));
            write("You make " + capitalize(name) + " a Master " +
                specialty + ".\n");
            return 1;
        }
    }

    if (!MANAGER->add_specialist(name, specialty))
    {
        write(capitalize(specialty) + " is not a valid specialty, " +
            capitalize(name) + " is not a Ranger or they are not " +
            "experienced enough to specialize.\n");
        return 1;
    }
    else
    {
        write("You assign " + capitalize(name) + " as " + specialty + ".\n");
        return 1;
    }
}

/*
 * Function name: unassign
 * Description  : Unassign a specialist or master
 * Arguments    : string str - the name of the ranger to unassign
 * Returns      : 1/0 - success, failure
 */
public int
unassign(string str)
{
    string name, specialty;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    if (!parse_command(str, ({}), "%w", name))
    {
        notify_fail("Unassign <name>?\n");
        return 0;
    }

    name = lower_case(name);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_player()->query_real_name()))
        return 1;

    if (MANAGER->query_is_master(name))
    {
        specialty = MANAGER->query_master_specialty(name);
        MANAGER->remove_master(name);
        write("You unassign " + capitalize(name) + " as a Master " +
            specialty + ".\n");
        return 1;
    }

    if (MANAGER->query_is_specialist(name))
    {
        specialty = MANAGER->query_specialist_specialty(name);
        MANAGER->remove_specialist(name);
        write("You unassign " + capitalize(name) + " as a " +
            specialty + ".\n");
        return 1;
    }

    write(capitalize(name) + " is neither a master nor a specialist.\n");
    return 1;
}

/*
 * Function name: advance
 * Description  : Advances a specialist's rank.
 * Arguments    : string name - the specialist to advance
 * Returns      : 1/0 success/failure
 */
public int
advance(string name)
{
    string specialty;

    /* Check for wiz, captain or entrusted. */
    if (!has_access())
        return 0;

    if (!strlen(name))
    {
        notify_fail("Advance whom?\n");
        return 0;
    }

    name = lower_case(name);

    /* Check for wiz or council executor, approved- target or same */
    /* company target. Checks for rank superiority. */
    if (!valid_target(name, this_player()->query_real_name()))
        return 1;

    if (MANAGER->advance_specialist(name))
    {
        specialty = MANAGER->query_specialist_specialty(name);
        write("You advance " + capitalize(name) + " as a " + specialty + ".\n");
        reward(name + " moderately for advancing as " + LANG_ADDART(specialty));
        return 1;
    }

    if (MANAGER->query_is_master(name))
    {
        write(capitalize(name) + " is a master and cannot be " +
            "advanced.\n");
        return 1;
    }

    if (MANAGER->query_specialist_rank(name) >= 5)
    {
        write(capitalize(name) + " is already of the highest rank.\n");
        return 1;
    }

    write(capitalize(name) + " is not a specialist.\n");
    return 1;
}
