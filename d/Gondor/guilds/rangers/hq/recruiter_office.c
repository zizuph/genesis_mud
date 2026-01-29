#pragma save_binary
/*
 *  /d/Gondor/guilds/rangers/hq/recruiter_office.c
 *
 *  The Office of Ranger Central Headquarters
 *  Adapted descriptions etc. for ranger recruitment office
 *    located in the hq of Gondor
 *
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_HQ_DIR + "ch_funcs.c";

#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#define MOREOBJ   "/obj/more"

#include "/d/Gondor/defs.h"
#include "../titles.h"

mapping       gSanctioned = ([]);

// prototypes
public string long_desc();
public int    sanction(string str);
public int    unsanction(string sanctionee);
public int    add_sanction(string sanctionee, string sanctioner);
public int    remove_sanction(string sanctionee);
public string query_sanction(string name);
public string list_sanctioned();
static string exa_sanctioned_list();
public int    lift_tapestry();

public string
print_member_list()
{
    string text, *apprentice_list, *trusted_list;
    int i, j;

    text = "These are presently the members of the Ranger Apprentices:\n\n";

    trusted_list = MANAGER->query_company_members(APPROVED_APP_LEVEL);
    apprentice_list = MANAGER->query_company_members(APPRENTICE_LEVEL);

    i = -1;
    while (++i < sizeof(trusted_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(trusted_list[i], -2) == "jr") &&
          !(TP->query_wiz_level()))
        {
            continue;
        }

        text += "- " + capitalize(trusted_list[i]) + ", of the Trusted "
            + "Ranger Apprentices\n";
    }

    j = -1;
    while (++j < sizeof(apprentice_list))
    {
        /* Don't want a jr's name on the guildlist */
        if ((extract(apprentice_list[j], -2) == "jr") &&
          !(TP->query_wiz_level()))
        {
            continue;
        }

        text += "- " + CAP(apprentice_list[j]) + ", of the Ranger "
            + "Apprentices\n"; 
    }

    return text + "\n";
}


static string 
exa_poster()
{
    write("On the poster you read:\n\n");
    write(print_member_list());
    return "";
}

static string 
exa_note()
{
    write("On the note you read:\n\n");
    write("--You may type <apprentice> here to see " +
        "the activity of the apprentice log, including " +
        "activity for election results, tasks, and rewards.\n\n" +
        "--You may examine the poster to see a list of current " +
        "apprentices and trusted apprentices.\n\n" +
        "--You may also sanction an apprentice here so that they " +
        "may apply to your company. The syntax for this is " +
        "<sanction apprentice name>. You will be held responsible " +
        "for any apprentice that you sanction, so make sure that " +
        "they have passed all tasks first.\n\n" +
        "--In the event that you have made an error, you may " +
        "also <unsanction apprentice name>.\n");
    return "";
}

string
long_desc()
{
    return "This is the office designed for those recruiters who " +
        "take it upon themselves to assist young apprentices " +
        "in their goal to become full rangers. It is comfortable " +
        "yet businesslike. There is a poster on the wall " +
        "where you can read the list of current ranger apprentices, " +
        "and there is a note tacked to it that gives additional " +
        "information about business that can be conducted in this room. " +
        "A list of names is printed on parchment and tacked up next to the " +
        "poster. A stairway leads up to another room above. There is " +
        "a wooden desk and chair in the corner and a red " +
        "woven rug upon the floor. Soft light filters through " +
        "the velvet tapestry hanging over an exit to the east.\n";
}


void
create_gondor()
{
    set_short("Recruiter's Office");
    set_long(&long_desc());
    add_exit(RANGERS_DIR + "library_rec/rec_library", "up", 0);
    hideout_add_items();
    add_item(({"office", "room"}), &long_desc());
    add_item(({"passage", "east passage", "exit"}), "The passage east " +
        "can be reached by lifting the tapestry.\n");
    add_item(({"stairway", "room above"}), "The stairway leads " +
        "to another room above that is warmly lit.\n");
    add_item(({"wall", "walls"}), "The walls, like most things in the "
        + "hideout, are constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. One wall is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");
    add_item(({"desk", "wooden desk"}), "The wooden desk contains " +
        "a stack of papers pertaining to reports on " +
        "apprentices. The command <apprentice> will allow you to " +
        "read the reports.\n");
    add_item(({"chair", "wooden chair"}), "A wooden chair is in " +
        "corner by the desk. It looks rather uncomfortable and " +
        "uninviting, however.\n");
    add_item("corner", "The corner to the southwest holds a " +
        "wooden desk and chair.\n");
    add_item(({"rug", "woven rug", "woven red rug"}), "While " +
        "furnishings in this room are kept to a bare minimum, " +
        "one concession to comfort is a woven woolen red rug " +
        "upon the floor.\n");
    add_item(({"tapestry", "velvet tapestry"}), "A midnight-blue " +
        "velvet tapestry covers the passage to the east. You can lift " +
        "it to exit.\n");
    add_cmd_item(({"tapestry", "velvet tapestry"}), "lift", lift_tapestry);
    add_item(({"rangers","members","poster"}), &exa_poster());
    add_cmd_item(({"rangers","members","poster"}), "read", exa_poster);
    add_item("note", &exa_note());
    add_cmd_item(({"note"}), "read", exa_note);
    add_item(({"list", "sanctioned list", "parchment"}), 
        &exa_sanctioned_list());
    add_cmd_item(({"list", "sanctioned list", "parchment"}),
        "read", exa_sanctioned_list);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    FIX_EUID;
    restore_object(MASTER);

}

/* Function name: apprentice
 * Description  : Allows a council member to read the apprentice activity
 *                log
 * Arguments    : string str - The argument as entered by the player.
 *                             If entered, it should be a line number
 * Returns      : 1 for success, 0 for failure
 */

public int
apprentice(string str)
{
    int i, line_num = 1;

    object more_obj;

    if (strlen(str))
    {
        i = sscanf(str, "%d", line_num);
        if (i != 1)
        {
            notify_fail("apprentice [line number]?\n");
            return 0;
        }
        
        line_num = (line_num < 1 ? 1 : line_num);
    }

    more_obj = clone_object(MOREOBJ);
    if (file_size(RANGERS_LOG_DIR + "apprentice"))
        more_obj->more(RANGERS_LOG_DIR + "apprentice", line_num);
    else
        write("There is currently no activity in the apprentice log.\n");
    return 1;
}
/* Function name: eject_intruder
 * Description  : Removes a player who isn't allowed in the office.
 * Arguments    : object ob - the player, object from - previous location
 */
public void
eject_intruder(object ob, object from)
{
    if (!objectp(ob))
        return;
    tell_object(ob, "You are not allowed to enter this room!\n");
    if (objectp(from))
        ob->move(from, 1);
    else
        ob->move(find_object(ob->query_default_start_location()), 1);

    return;
}

void
init()
{
    ::init();
    add_action(&apprentice(), "apprentice");
    add_action(&sanction(), "sanction");
    add_action(&unsanction(), "unsanction");
}

public int
query_prevent_snoop()
{
    return 1;
}

/* Function name: sanction
 * Description  : Full ranger can sanction for apprentice before
                  Lossefalme allows him/her to apply to 
                  ranger company. sanctioner is full ranger,
                  rather high level ranger that is,
 *                'sanctionee' is the wannabe applicant
 * Arguments    : string: syntax <sanction for name>
 * Returns      : 1/0
 */
public int
sanction(string str)
{
    object sanctioner = this_player();
    string sanctionee_name, sanctioner_name;
    string company;
    int company_num;
    
    
    //tests for sanctioner
    if (!RANGERS_FULL_MEMBER(sanctioner))
    {
        notify_fail("You must be a full ranger to sanction for an " +
            "apprentice candidate.\n");
        return 0;
    }

    sanctioner_name = sanctioner->query_real_name();
    //tests for sanctionee
    if (!strlen(str))
    {
        notify_fail("Sanction for whom?\n");
        return 0;
    }

    if (!parse_command(str, ({}), " [for] %s ", sanctionee_name))
    {
        notify_fail("Sanction whom?\n");
        return 0;
    }

    if (strlen(query_sanction(sanctionee_name)))
    {
        notify_fail(capitalize(sanctionee_name) + " has already " +
            "been sanctioned for application to a company.\n");
        return 0;
    }

    if (!strlen(sanctionee_name))
    {
        notify_fail("Sanction whom?\n");
        return 0;
    }

    if (MANAGER->query_ranger_level(lower_case(sanctionee_name)) != 1)
    {
        notify_fail(capitalize(sanctionee_name) + " is not a Ranger " +
            "Apprentice!\n");
        return 0;
    }
 
    company_num = MANAGER->query_ranger_level(lower_case(sanctioner_name));
    switch(company_num)
    {
    case 3:
        company = "north";
        break;
    case 4:
        company = "ithilien";
        break;
    default:
        notify_fail("You cannot sanction anyone, since you " +
            "are not a Ranger of Ithilien or a Ranger of the North!\n");
        return 0;
        break;
    }

    if (sanctioner->query_ranger_rank() < SPECIALTY_RANK &&
       (MANAGER->query_council(lower_case(sanctioner_name), "ithilien") == -1) &&
       (MANAGER->query_council(lower_case(sanctioner_name), "north") == -1))
    {
        notify_fail("You are not mature enough as a ranger to " +
            "sanction anyone.\n");
        return 0;
    }

    //successful -- add mapping to gSanctioned
    if (!add_sanction(sanctionee_name, sanctioner_name))
    {
        notify_fail("You are unable to sanction for " +
            capitalize(sanctionee_name) + " for some reason.\n");
        return 0;
    }

    MANAGER->rlog(APPRENTICE_LOG, capitalize(sanctioner_name) + 
        " sanctioned " + capitalize(sanctionee_name) + " to allow " +
        "application to the " + capitalize(company) + " company.");
    MANAGER->rlog(RANGERS_LOG, capitalize(sanctioner_name) + 
        " sanctioned " + capitalize(sanctionee_name) + " to allow " +
        "application to the " + capitalize(company) + " company.");
    write(capitalize(sanctionee_name) + " has been added to " +
        "the list of sanctioned applicants for the " +
        capitalize(company) + " company.\n");
    return 1;
}

/* Function name: unsanction
 * Description  : Rangers decides to remove sanctioner for wannabe
 * Arguments    : string: syntax <unsanction [for] name>
 * Returns      : 1/0
 */
public int
unsanction(string sanctionee)
{ 
    string name;
    object tp = this_player();
    string sanctioner_name = capitalize(tp->query_real_name());
    
    if (!strlen(sanctionee))
    {
        notify_fail("Unsanction whom?\n");
        return 0;
    }

    if (!parse_command(sanctionee, ({}), " [for] %s ", name))
    {
        notify_fail("Unsanction whom?\n");
        return 0;
    }

    if (!strlen(name))
    {
        notify_fail("Unsanction whom?\n");
        return 0;
    }

    if (!strlen(query_sanction(name)))
    {
        notify_fail("There is no sanctioner listed for " +
            name + ".\n");
        return 0;
    }

    name = capitalize(name);
    if (sanctioner_name != gSanctioned[name] &&
        !IS_GONDOR_WIZARD(tp))
    {
        notify_fail("Only the ranger who sanctioned for " +
            "the applicant can remove his/her sanction.\n");
        return 0;
    }

    if (!remove_sanction(name))
    {    
        notify_fail("You were unable to remove the sanction " +
            "for some reason.\n");
        return 0;
    }
    MANAGER->rlog(APPRENTICE_LOG, capitalize(sanctioner_name) + 
        " removed the sanction for " + capitalize(name) + ".");
    MANAGER->rlog(RANGERS_LOG, capitalize(sanctioner_name) + 
        " removed the sanction for " + capitalize(name) + ".");
    write("You removed the sanction for " + name + ".\n");
    return 1;

}
/* Function name: add_sanction
 * Description  : adds a couplet of [sanctionee:sanctioner]
 *                to the sanctioner mapping
 * Arguments    : string sanctionee (ranger wannabe),
 *                string sanctioner (full ranger who is
 *                making the sanctioner)
 * Returns      : 1/0
 */
public int 
add_sanction(string sanctionee, string sanctioner)
{
    string sanctionee_name, sanctioner_name;

    if (!strlen(sanctionee) || !strlen(sanctioner))
    {
        return 0;
    }
    sanctionee_name = capitalize(sanctionee);
    sanctioner_name = capitalize(sanctioner);
    gSanctioned += ([ sanctionee_name : sanctioner_name ]);
    save_object(MASTER);
    return 1;
}

/* Function name: remove_sanction
 * Description  : Remove a sanction for a wannabe
 * Arguments    : string: syntax <remove name (of wannabe)>
 * Returns      : 1/0
 */
public int
remove_sanction(string sanctionee)
{
    string name;

    if (!strlen(sanctionee))
        return 0;

    name = capitalize(sanctionee);
    if (member_array(name, m_indexes(gSanctioned)) == -1)
    {
        return 0;
    }

    gSanctioned = m_delete(gSanctioned, name);
    save_object(MASTER);
    return 1;
}

/* Function name: query_sanction
 * Description  : Returns the ranger's name who sanctioned for
 *                wannabe
 * Arguments    : name of wannabe
 * Returns      : name of sanctioner if exists, else empty string
 */
public string    
query_sanction(string name)
{
    string sanctionee;
    sanctionee = capitalize(name);
    if (member_array(sanctionee, m_indexes(gSanctioned)) == -1)
    {
        return "";
    }
    return gSanctioned[sanctionee];
}

/* Function name: list_sanctioned
 * Description  : Returns a list of sanctioned rangers with their
 *                sponsors
 * Arguments    : none
 * Returns      : List
 */
public string
list_sanctioned()
{
    string text = "";
    mixed * sanctioned, sponsors;
    int i;
    
    if (m_sizeof(gSanctioned) == 0)
    {
        return "There are no sanctioned apprentices at " +
            "this time.\n";
    }
    text = "This is the list of sanctioned apprentices:\n\n";
    sanctioned = m_indexes(gSanctioned);
    sponsors = m_values(gSanctioned);
    for (i = 0; i < m_sizeof(gSanctioned); i++)
    {
        text += "-- " + sanctioned[i] + ", sanctioned by " + sponsors[i] + "\n";
    }
    return text + "\n\n";
}

static string
exa_sanctioned_list()
{
    write("Upon the parchment is printed the following:\n\n");
    write(list_sanctioned());
    return "";
}
public int
lift_tapestry()
{
    object tp = this_player();
    write("You lift the tapestry and exit to the east.\n");
    say(QCTNAME(tp) + " lifts the tapestry and exits to the east.\n");
    tp->move_living("M", RANGERS_HQ_DIR+ "cozy", 1, 0);
    tell_room(environment(tp), QCTNAME(tp) + " enters " +
        "silently.\n", tp);
    return 1;
}
