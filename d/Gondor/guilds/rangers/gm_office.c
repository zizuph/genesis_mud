/*
 * /d/Gondor/guilds/rangers/gm_office.c
 *
 * This is a room for the GM or other wizard who needs to
 * do administration tasks for the Rangers. It interfaces
 * with the main manager with user-friendly commands, allowing
 * the GM to do away with direct calls for most things.
 * It is a separate room because the manager is already fairly
 * large.
 *
 * Coded by Gwyneth, 4/23/04
 */
#pragma <no_inherit>
#pragma <no_shadow>

inherit "/std/room";

#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <options.h>
#include "rangers.h"
#include "/d/Gondor/defs.h"

string read_list();
private int manage_rangers(string str);
private int list_rangers(string str);

void
create_room()
{
    set_short("the Guildmaster's Office");
    set_long("You are in a fairly messy office. A large " +
        "cherry wood desk takes up most of the space, and " +
        "is covered in papers, books and who knows what else. " +
        "Despite the clutter, it's possible to do a fair number " +
        "of administrative duties for the Rangers here. An " +
        "important looking list has been tacked up on the wall " +
        "here. It seems to contain a summary of the possible " +
        "jobs that can be from here.\n");
    add_item(({"list", "important list", "important looking list"}),
        &read_list());
}

string
read_list()
{
    return ("Each command must be prepended by manager. Thus, " +
           "you can 'manager promote amaron captain ithilien'. " +
           "You can also list various things. The following is a " +
           "summary of all that is possible here:\n\n" +
           "Manage:\n" +
           "question-add <question-name> - Add a new joining question\n" +
           "question-del <question-name> - Delete current joining question\n" +
           "rejoin <name>                - Remove player's no-rejoin " +
           "restriction\n" +
           "key - clone a set of council keys to gain council commands\n" +
           "skills - clone a tool to setup your juniors with skills\n" +
           "List:\n" +
           "apprentice         - All Apprentice Rangers, including Approved\n" +
           "approved           - Only Approved Apprentice Rangers\n" +
           "ithilien           - All Rangers of Ithilien\n" +
           "north              - All Rangers of the North\n" +
           "rangers            - All Rangers\n" +
           "masters            - All Master Rangers\n" +
           "specialists        - All Rangers in a specialty\n" +
           "council            - All Ranger council members\n" +
           "ithilien council   - All Ranger of Ithilien council members\n" +
           "north council      - All Ranger of the North council members\n" +
           "ithilien elections - Current election in Ithilien\n" +
           "north elections    - Current election in the North\n" +
           "apprentice votes   - All apprentices up for vote\n" +
           "rewards            - All rewards on the to-be-rewarded list\n" +
           "punished           - All Rangers currently punished\n" +
           "expelled           - All Rangers on the to-be-expelled list\n" +
           "banished           - All banished from the Rangers\n" +
           "outlaws            - All outlaws of the Rangers\n" +
           "notorious          - All notorious outlaws of the Rangers\n" +
           "no rejoin          - All that can't rejoin for a certain time\n" +
           "elections          - Elections in both companies\n" +
           "logs               - View the logs\n");
}

private int
check_valid(object who)
{
    string name;

    if (!objectp(who))
        return 0;

    name = who->query_real_name();

    return (SECURITY->query_guild_is_master(RANGERS_GUILD_NAME, name) ||
      (SECURITY->query_domain_lord("Gondor") == name) ||
      (SECURITY->query_domain_steward("Gondor") == name) ||
      name == "gwyneth" || name == "finwe" || name == "arman" ||
      name == "carnak");
}

string
digest(string *output)
{
    int size, i, scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string *output2, formatted = "";

    size = sizeof(output);

    if (!size)
    {
        return "\nNone\n";
    }

    output2 = output;

    for (i = 0, size = sizeof(output2); i < size; i++)
    {
        output2[i] = capitalize(output2[i]);
    }

    scrw = ((scrw >= 40) ? (scrw - 3) : 77);
    formatted += (sprintf("%-*#s\n", scrw, implode(output2, "\n")));
    return ("\n" + formatted + "\n");
}

private int
manage_rangers(string str)
{
    string args, action;

    /* A security check. */
/*
    if (!check_valid(this_interactive()))
        return 0;
*/
    if (!strlen(str))
    {
        notify_fail("Manage what?\n");
        return 0;
    }

    str = lower_case(str);
    if (!parse_command(str, ({}), "%w %s", action, args) || !strlen(action))
    {
        notify_fail("Maybe you need to examine the list.\n");
        return 0;
    }

    switch(action)
    {
    case "rejoin":
        break;

    case "keys":
        clone_object(RANGERS_OBJ + "councilkey")->move(TI, 1);
        write("A set of council keys appears in your inventory.\n");
        break;

    case "skills":
        clone_object(RANGERS_OBJ + "raiser")->move(TI, 1);
        write("A skill raiser appears in your inventory.\n");
        break;

    case "question-add":
        find_object(RANGERS_HQ_DIR + "join")->get_name(args);
        break;

    case "question-del":
        find_object(RANGERS_HQ_DIR + "join")->remove_question(args);
        break;

    default:
        write("No such ability available. Maybe you should write it.\n");
        break;
    }

    return 1;
}

private int
list_rangers(string str)
{
    string *arr = ({});
    int election;

    if (!check_valid(this_interactive()))
        return 0;

    if (!strlen(str))
    {
        notify_fail("List what?\n");
        return 0;
    }

    str = lower_case(str);
    switch(str)
    {
    case "ithilien":
        write("Ithilien Rangers:" +
            digest(MANAGER->query_company_members(ITHILIEN_LEVEL)) +
            "\n");
        break;

    case "north":
        write("Northern Rangers:" +
            digest(MANAGER->query_company_members(NORTH_LEVEL)) +
            "\n");
        break;

    case "apprentice":
        write("Approved Apprentices:" +
            digest(MANAGER->query_company_members(APPROVED_APP_LEVEL)) +
            "\n");
        write("Apprentices:" +
            digest(MANAGER->query_company_members(APPRENTICE_LEVEL)) +
            "\n");
        break;

    case "approved":
        write("Approved Apprentices:" +
            digest(MANAGER->query_company_members(APPROVED_APP_LEVEL)) +
            "\n");
        break;

    case "rangers":
        list_rangers("ithilien");
        list_rangers("north");
        list_rangers("apprentice");
        break;

    case "outlaws":
        write("Outlaws:" +
            digest(MANAGER->query_outlaw_members()) + "\n");
        break;

    case "notorious outlaws":
    case "notorious":
        write("Notorious Outlaws:" +
            digest(MANAGER->query_notorious_members()) + "\n");
        break;

    case "masters":
        write("Under construction.\n");
        break;

    case "specialists":
        write("Under construction.\n");
        break;

    case "council":
        list_rangers("ithilien council");
        list_rangers("north council");
        break;

    case "ithilien council":
        write("The council of Ithilien:\n" +
            MANAGER->query_council_name(CAPTAIN_POSITION, "ithilien") +
            ", Captain of Ithilien\n" +
            MANAGER->query_council_name(LIEUTENANT_POSITION, "ithilien") +
            ", Lieutenant of Ithilien\n" +
            MANAGER->query_council_name(SERGEANT_POSITION, "ithilien") +
            ", Sergeant of Ithilien\n");
        break;

    case "north council":
        write("The council of the North:\n" +
            MANAGER->query_council_name(CAPTAIN_POSITION, "north") +
            ", Captain of Ithilien\n" +
            MANAGER->query_council_name(LIEUTENANT_POSITION, "north") +
            ", Lieutenant of Ithilien\n" +
            MANAGER->query_council_name(SERGEANT_POSITION, "north") +
            ", Sergeant of Ithilien\n");
        break;

    case "expelled":
        write("Under construction.\n");
        break;

    case "rewards":
        write("Under construction.\n");
        break;

    case "punished":
        write("Under construction.\n");
        break;

    case "banished":
        write("Under construction.\n");
        break;

    case "no rejoin":
        write("Under construction.\n");
        break;

    case "elections":
        list_rangers("ithilien elections");
        list_rangers("north elections");
        break;

    case "ithilien elections":
        election = MANAGER->query_elections("ithilien");
        if (!election)
            write("There is no current election in Ithilien.\n");
        else if (election == 1)
            write("There is a nomination vote in Ithilien.\n");
        else if (election == 2)
            write("There is a captain election in Ithilien.\n");
        else if (election == 3)
            write("There is an impeachment vote in Ithilien.\n");
        break;

    case "north elections":
        election = MANAGER->query_elections("north");
        if (!election)
            write("There is no current election in the North.\n");
        else if (election == 1)
            write("There is a nomination vote in the North.\n");
        else if (election == 2)
            write("There is a captain election in the North.\n");
        else if (election == 3)
            write("There is an impeachment vote in the North.\n");
        break;

    case "apprentice votes":
    case "votes":
        write("Candidates for membership in the North:" +
            digest(MEMBER_VOTE_NOR->query_candidates()) +
            "\nCandidates for membership in Ithilien:" +
            digest(MEMBER_VOTE_ITH->query_candidates()) + "\n");
        break;

    case "logs":
        write("Under construction.\n");
        break;

    default:
        write("No such listing available. Maybe you should write it.\n");
        break;
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(manage_rangers, "manage");
    add_action(list_rangers, "list");
}

/*
 * Function name: prevent_enter
 * Description  : I'm using this instead of enter_inv, as it actually
 *                prevents entering, and doesn't need to eject after.
 *                Using enter_inv would allow wizards to use At commands
 *                and read the boards.
 * Arguments    : object ob - the object trying to enter
 * Returns      : 1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    string name, txt;
    object *oblist;

    /* Non-livings are allowed in. */
    if (!living(ob))
        return 0;

    name = ob->query_real_name();

    /* wizards of Gondor and arches are allowed in. */

    if (name == "finwe" || SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return 0;

    ob->catch_tell("No matter how hard you try, you just " +
        "can't enter that room! You'd better stop trying before " +
        "you hurt yourself!\n");

    oblist = FILTER_PLAYERS(oblist);

    txt = extract(ctime(time()), 4) + " " + CAP(name) + " attempted to " +
        "enter the Guildmaster's Room.\nPresent: " +
        COMPOSITE_LIVE(oblist) + ".\n";

    log_file("intruder", txt);
    return 1;
}

