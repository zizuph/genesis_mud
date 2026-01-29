/*
 *  council.c
 *
 *  The meeting room of the Council of the Hin Warriors. This room
 *  uses functions defined in HIN_DIR + "shire_council.c".
 *  Helpfiles are stored in HINROOM_DIR + "councilhelp/".
 *
 *                                                       Tricky, may 1994
 */

/*
 * TODO:
 *  - Allow the Council to set the hailing message.
 */
inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/secure/std.h"
#include "defs.h"

/* The text to use for: */
#define V_YEA    "yea"
#define V_NAY    "nay"
#define V_BLANK  "blank"

/* Global variables */
string *voters, *votes, reason;
mixed target;                      /* Sometimes string, sometimes int */
int action;

/* Global variables that do not have to be saved */
static int alarm_id;
static int proposed_max;    /* Proposed new Council size */

void
create_room()
{
    set_short("Council meeting room");
    set_long(break_string(
       "This is the meeting room of the Council of the Hin Warrior guild. "
     + "The floor is made of oak, just like the furniture. "
     + "There is a certain scent in the air that indicates that important "
     + "decisions are made here. Some words have been scribbled on a "
     + "blackboard.\n", 70));

    add_item("floor", "The floor is not interesting.\n");

    add_item("furniture", break_string("The furniture provides place for "
     + "some books and for the members of the Council. It is not stylish "
     + "or fashionable, simply functional.\n", 70));

    /* Make it that only members of the Council can read this... */
    add_item(({"blackboard"}), "@@board_desc");

    add_exit(HINROOM_DIR + "hguild","south");
    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    clone_object(HIN_DIR + "bull_council")->move(this_object());
}

int
not_member(object ob)
{
    if (!living(ob))
        return 0;

    return !SHIRE_COUNCIL->is_council_member(ob->query_real_name());
}

void
init()
{
    ::init();

    /* Give the Council members extra commands */
    if (!not_member(this_player()))
    {
        add_action("do_accept", "accept", 0);
        add_action("do_applications", "applications", 0);
        add_action("do_back", "back", 0);
        add_action("do_cancel", "cancel", 0);
        add_action("do_deny", "deny", 0);
        add_action("do_expell", "expell", 0);
        add_action("do_help", "help", 0);
        add_action("do_relieve", "relieve", 0);
        add_action("do_resign", "resign", 0);
        add_action("do_resize", "resize", 0);
        add_action("do_restore", "restore", 0);
        add_action("do_status", "status", 0);
        add_action("do_summon", "summon", 0);
        add_action("do_test", "test", 0);
        add_action("do_vote", "vote", 0);
        add_action("do_warn", "warn", 0);
    }
}

string
board_desc()
{
    string str;

    if (!not_member(this_player()))
    {
        str =
           "The blackboard has some instructions on it:\n\n"
         + "Topics:\n\n"
         + "     accept, applications, deny, expell, relieve, resign, resize,\n"
         + "     restore, rules, status, summon, test, vote, warn\n\n"
         + "More extensive help is available with `help <topic>'\n\n"
         + "The current maximum number of members is "
         + SHIRE_COUNCIL->query_council_max() + ".\n";
    }
    else
    {
        str = break_string("The blackboard is hard to decipher, for the "
         + "members of the Council have a very bad handwriting. You think "
         + "you see your name mentioned on it, though.\n", 70);
    }

    if (SHIRE_COUNCIL->sizeof_council() == 1)
    {
        str += "The only current member of the Council is "
         + SHIRE_COUNCIL->council_members() + ".\n";
    }
    else
    {
        str += "Current members of the Council are:\n"
         + SHIRE_COUNCIL->council_members() + ".\n";
    }

    return str;
}

/*
 * Function name:   tell_council
 * Description:     The same as tell_room, but only for Council members.
 */
void
tell_council(object room, string str, mixed who_not)
{
    object *no_member;

    no_member = filter(all_inventory(this_object()), "not_member",
                       this_object());

    tell_room(room, str, who_not + no_member);
}

/*
 * Function name:   start_vote
 * Description:     Set up the voting stuff, and start counting down the
 *                  time.
 * Arguments:       act: An action number; why are we voting?
 *                  tar: The name of the person we are voting on.
 * Return:          "" if all went well, otherwise the errormessage.
 */
string
start_vote(int act, mixed tar)
{
    if (strlen(reason))
        return "Another vote has already been issued on the " + reason + ".\n";

    /* Reset everything */
    voters = ({ });
    votes = ({ });
    target = tar;
    action = act;

    /* Determine the reason for the vote */
    switch (action)
    {
    case ACTION_NOTHING:
        reason = "test";
        break;

    case ACTION_WARN:
        reason = "warning of " + capitalize(target);
        break;

    case ACTION_EXPELL:
        reason = "expelling of " + capitalize(target);
        break;

    case ACTION_RESTORE:
        reason = "restoration of " + capitalize(target);
        break;

    case ACTION_SUMMON:
        reason = "summoning of " + capitalize(target);
        break;

    case ACTION_RESIZE:
        reason = "resizing of the Council to a maximum of " + target
         + " members";
        break;

    case ACTION_RELIEVE:
        reason = "relieving " + capitalize(target) + " from membership "
         + "of the Council";
        break;
    }

    alarm_id = set_alarm(180.0, 0.0, "end_vote");
    tell_room(this_object(), "A vote has been initiated by "
     + QCTNAME(this_player()) + ".\n"
     + "The Council can now vote on the " + reason + ".\n"
     + "The vote will be closed in three minutes.\n");

    if (reason != "test")
    {
        log_file(COUNCIL_LOG, ctime(time()) + " Vote called by "
         + this_player()->query_name() + " on the " + reason + ":\n");
    }
}

/*
 * Function name:   end_vote
 * Description:     The voting procedure has come to an end, now all votes
 *                  have to be counted, and the action has to be taken.
 */
void
end_vote()
{
    int size, voted_for, voted_against, voted_blank, i;
    string failure;

    tell_room(this_object(), "The vote on the " + reason
     + " has been closed.\n");

    size = SHIRE_COUNCIL->sizeof_council();
    voted_for = 0;
    voted_against = 0;
    voted_blank = 0;

    /* Count the votes */
    for (i = 0; i < sizeof(votes); i++)
    {
        if (votes[i] == V_YEA)
            voted_for++;
        else if (votes[i] == V_NAY)
            voted_against++;
        else
            voted_blank++;
    }
    /* Inform everyone of the outcome */
    tell_room(this_object(), "The outcome:\n     "
      + V_YEA + ": " + voted_for + ", " + V_NAY + ": " + voted_against
      + ", " + V_BLANK + ": " + voted_blank + ".\n");

    if (voted_for >= VOTES_NEEDED[size])
    {
        tell_room(this_object(), "The proposal has been accepted.\n");

        if (reason != "test")
            log_file(COUNCIL_LOG, "                   Proposal accepted.\n");

        /* Take the necessary action */
        failure = SHIRE_COUNCIL->take_action(action, target, 1);

        /* Tell about errors */
        if (strlen(failure))
        {
            tell_room(this_object(), failure);

            if (reason != "test")
                log_file(COUNCIL_LOG, "                   Error: " + failure);
        }
        else
        {
            switch (action)
            {
            case ACTION_EXPELL:
                tell_room(this_object(), "Effective immediately, "
                 + capitalize(target) + " is declared to be a persona non "
                 + "grata, and therefore expelled from the guild.\n");
                 break;

            case ACTION_WARN:
                tell_room(this_object(), capitalize(target)
                 + " will receive a warning at the first opportunity.\n");
                 break;

            case ACTION_RESTORE:
                tell_room(this_object(), "Effective immediately, "
                 + capitalize(target) + " is restored from being a persona "
                 + "non grata.\n");
                 break;

            case ACTION_RESIZE:
                tell_room(this_object(), "Effective immediately, the Council "
                 + "size will be set to " + target + ".\n");
                 break;

            case ACTION_RELIEVE:
                tell_room(this_object(), "Effective immediately, "
                 + capitalize(target) + " is removed from the Council.\n");
            }
        }
    }
    else
    {
        tell_room(this_object(), "The proposal has been rejected.\n");

        if (reason != "test")
            log_file(COUNCIL_LOG, "                   Proposal rejected.\n");
    }

    /*
     * And clear the reason, to close the vote
     * and to allow starting up a fresh one.
     */
    reason = "";
}

int
do_vote(string str)
{
    int index;
    object tp;

    if (not_member(this_player()))
        return 0;

    /* Is there something to vote about? */
    if (!strlen(reason))
    {
        notify_fail("There is nothing to vote about.\n");
        return 0;
    }

    /* Voted something weird */
    if (str != V_YEA && str != V_NAY && str != V_BLANK)
    {
        notify_fail("Vote `" + V_YEA + "', `" + V_NAY + "' or `" + V_BLANK
         + "' to bring out your vote.\n");
        return 0;
    }

    tp = this_player();
    index = member_array(tp->query_real_name(), voters);

    /* Already voted on this */
    if (index >= 0)
    {
        notify_fail("You have already voted " + votes[index] + "on the "
         + reason + ".\n");
        return 0;
    }

    /* Okay, register the vote */
    if (voters)
    {
        voters += ({ tp->query_real_name() });
        votes += ({ str });
    }
    else
    {
        voters = ({ tp->query_real_name() });
        votes = ({ str });
    }

    /* And let everyone know */
    if (tp->query_get_echo())
    {
        if (str == V_YEA)
            write("You have voted for the " + reason + ".\n");
        else if (str == V_NAY)
            write("You have voted against the " + reason + ".\n");
        else
            write("You have voted blank on the " + reason + ".\n");
    }

    tell_room(this_object(), QCTNAME(tp) + " has voted on the matter.\n",
              ({ tp }));

    /* Log vote if necessary */
    if (reason != "test")
    {
        if (str == V_YEA)
            log_file(COUNCIL_LOG, "                   " + tp->query_name()
             + " voted for.\n");
        else if (str == V_NAY)
            log_file(COUNCIL_LOG, "                   " + tp->query_name()
             + " voted against.\n");
        else
            log_file(COUNCIL_LOG, "                   " + tp->query_name()
             + " voted blank.\n");
    }

    /* Perhaps this was the last vote? */
    if (sizeof(voters) == SHIRE_COUNCIL->sizeof_council())
    {
        remove_alarm(alarm_id);
        end_vote();
    }

    return 1;
}

int
do_test(string str)
{
    string err;

    if (not_member(this_player()))
        return 0;

    if (str != "vote")
    {
        notify_fail("Use `test vote' to test the voting procedure.\n");
        return 0;
    }

    err = start_vote(ACTION_NOTHING, "");

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_back(string str)
{
    if (not_member(this_player()))
        return 0;

    return 0;
}

int
do_status(string str)
{
    if (not_member(this_player()))
        return 0;

    return SHIRE_COUNCIL->give_status(str);
}

int
do_summon(string str)
{
    string err;
    object who;

    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Summon who?\n");
        return 0;
    }

    who = find_player(str);

    if (!who)
    {
        write("That person is not in the game at the moment.\n");
        return 1;
    }

    if (environment(who) == this_object())
    {
        write("That person is already here.\n");
        return 1;
    }

    err = start_vote(ACTION_SUMMON, str);

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_warn(string str)
{
    string err;

    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Warn who?\n");
        return 0;
    }

    str = lower_case(str);

    if (!SECURITY->exist_player(str))
    {
        write("No such person exists.\n");
        return 1;
    }

    err = start_vote(ACTION_WARN, str);

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_expell(string str)
{
    string err;

    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Expell who?\n");
        return 0;
    }

    str = lower_case(str);

    if (!SECURITY->exist_player(str))
    {
        write("No such person exists.\n");
        return 1;
    }

    /* You cannot expell members of the Council! */
    if (SHIRE_COUNCIL->is_council_member(str))
    {
        write("Council members cannot be expelled. They must resign or be "
         + "relieved first.\n");
        return 1;
    }

    /* You cannot expell wizards! */
    if (SECURITY->query_wiz_level(str) > WIZLEV_APPRENTICE)
    {
        write("Immortals cannot be expelled.\n"
         + "Ask them politely to leave the guild.\n");
        return 1;
    }

    err = start_vote(ACTION_EXPELL, str);

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_relieve(string str)
{
    string err;

    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Relieve who of her membership of the Council?\n");
        return 0;
    }

    str = lower_case(str);

    if (!SECURITY->exist_player(str))
    {
        write("No such person exists.\n");
        return 1;
    }

    if (!SHIRE_COUNCIL->is_council_member(str))
    {
        write(capitalize(str) + "is not a member of the Council.\n");
        return 1;
    }

    err = start_vote(ACTION_RELIEVE, str);

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_resign(string str)
{
    string err;

    if (not_member(this_player()))
        return 0;

    if (!str || (str != "council" && str != "Council"))
    {
        notify_fail("If you want to resign as a member of the Council, type:\n"
         + "   resign Council\n");
        return 0;
    }

    if (not_member(this_player()))
    {
        notify_fail("Now if only you were a member of the Council...\n");
        return 0;
    }

    SHIRE_COUNCIL->remove_council_member(this_player()->query_real_name());
    log_file(COUNCIL_LOG, ctime(time()) + " " + this_player()->query_name()
     + " has resigned as a member of the Council.\n");
    say(QCTNAME(this_player())
     + " has resigned as a member of the Council.\n");
    write("You have resigned as a member of the Council.\n");
    return 1;
}

int
do_resize(string str)
{
    string err;
    int new_size;

    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Resize the Council to how many members?\n");
        return 0;
    }

    str = lower_case(str);
    if (sscanf(str, "council to %d members", new_size) == 0)
    {
        notify_fail("Resize the Council to how many members?\n");
        return 0;
    }

    if (new_size < MIN_MEMBERS || new_size > MAX_MEMBERS)
    {
        notify_fail("The Council must have between "
         + MIN_MEMBERS + " and " + MAX_MEMBERS + " members.\n");
        return 0;
    }

    err = start_vote(ACTION_RESIZE, new_size);

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_restore(string str)
{
    string err;

    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Restore who?\n");
        return 0;
    }

    str = lower_case(str);

    if (!SECURITY->exist_player(str))
    {
        write("No such person exists.\n");
        return 1;
    }

    if (!SHIRE_PIPE->is_expelled(str))
    {
        write(capitalize(str) + " is not expelled; no need to restore.\n");
        return 1;
    }

    err = start_vote(ACTION_RESTORE, str);

    if (err)
        write(err);
    else
        write("Ok.\n");    

    return 1;
}

int
do_help(string str)
{
    if (not_member(this_player()))
        return 0;

    if (!str)
    {
        notify_fail("Give help on what?\n");
        return 0;
    }

    str = lower_case(str);

    if (file_size(HINROOM_DIR + "councilhelp/" + str) > 0)
    {
        cat(HINROOM_DIR + "councilhelp/" + str);
        return 1;
    }

    notify_fail("No help on topic `" + str + "' available.\n");
    return 0;     /* Allow people to do help on something else as well */
}

int
do_accept(string str)
{
    if (not_member(this_player()))
        return 0;

    return SHIRE_COUNCIL->accept_application(str);
}

int
do_deny(string str)
{
    if (not_member(this_player()))
        return 0;

    return SHIRE_COUNCIL->deny_application(str);
}

int
do_applications(string str)
{
    if (not_member(this_player()))
        return 0;

    if (str)
    {
        notify_fail("Simply type applications.\n");
        return 0;
    }

    write("There are pending applications for "
     + SHIRE_COUNCIL->application_list() + ".\n");
    return 1;
}
