/*
 * /d/Gondor/guilds/militia/room/join.c
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
 * The join room for the militia.
 * 
 * Coded by Auberon and Gwyneth on 19 February 2001
 *
 * Modifications:
 * 08/23/02 - Gwyneth, allowed for occupational members with no change
 *            in abilities -- i.e. two layman guilds.
 * 10/13/03 - Gwyneth, Changed ALIGN_MIN to MILITIA_ALIGN_MIN so it doesn't
 *            conflict with the mud-standard alignment.h
 * 1/8/04   - Gwyneth, Added guild item restoration support.
 */
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs2";

#include "../militia.h"
#include <files.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <options.h>
#include <stdproperties.h>

/* Four Months to get off the banished list */
#define CLEANUP_TIME	4838400
#define DESK_NAME	"small wooden desk"
#define DESK_NUM	1
#define CHAIR_NAME	"well-worn chair"
#define CHAIR_NUM	1
#define PLAYER_I_JOINED_THORNLIN	"_player_i_joined_thornlin"

/* Global Variables */
static string gConfirm = "";
object gRecruiter;
string *gMembers = ({ });
mapping gNotAllowed = ([ ]);
mapping gWarned = ([ ]);

/* Prototypes */
public void cleanup_list();
int militia_only();

int
militia_only()
{
    if (!this_player()->query_guild_member("Thornlin Militia"))
    {
        write ("The recruiter keeps you from entering the members' areas.\n");
        return 1;
    }

    check_sitting();
    return 0;
}            

public void
reset_room()
{
    if (!objectp(gRecruiter))
    {
        gRecruiter = clone_object(MNPC + "recruiter");
        gRecruiter->arm_me();
        gRecruiter->move_living("with a confident stride.", this_object());
        gRecruiter->command("sit at desk");
    }
}

public string
see_chair()
{
    return ("The chair is meant for visitors and potential recruits. It is " +
        "well-worn, but still comfortable.\n" +
        sitting_on_chair(CHAIR_NAME, this_player(), 0, 0));
}

public string
see_desk()
{
    return ("The desk is just large enough to be functional. It has papers " +
        "neatly stacked on the desk next to a pot of ink and feather quill.\n" +
        sitting_on_chair(DESK_NAME, this_player(), 0, 0));
}

public string
read_rules()
{
    string txt = ("You read over the rules of the Thornlin Militia.\n" +
        "       RULES OF THE THORNLIN MILITIA\n" +
        "\n" +
        "1. Do no harm to those who assist us against the lidless eye: fellow\n" +
        "   Militia, Gondorian soldiers or citizens, Rangers, or Heralds of the\n" +
        "   Valar.\n" +
        "\n" +
        "2. Do not regularly associate with those of black heart or evil reputation.\n" +
        "\n" +
        "3. For obvious reasons, the following may not be Militia members: orcs,\n" +
        "   servants of the East, minions of the foul dragon Takhisis, or others\n" +
        "   who cannot be trusted.  Trustworthy though they may be, Knights of\n" +
        "   Solamnia do not have the necessary time to assist in our defence,\n" +
        "   and so are also forbidden from being members.\n" +
        "\n" +
        "4. Please refrain from spitting or using profanity in the guildhouse,\n" +
        "   and try to treat each other courteously.  Try not to post anything\n" +
        "   on the board which might be considered unnecessarily rude to another\n" +
        "   member, class of members, or allies.  We are not bickering orcs, we\n" +
        "   have to be able to count on our fellow Militia to guard our backs.\n" +
        "\n");

    if (IS_MILITIA(this_player()))
    {
        txt += "In fine print at the bottom, you read that one may 'list members', " +
            "'list banished' and 'list warned', as well as being able to 'enlist' or " +
            "'resign' (at a small penalty) here.\n";
    }

    return txt;
}

public void
create_gondor()
{
    set_short("the recruitment center for the Militia");
    set_long("A bare and spartan room, the only furniture here is a small wooden " +
        "desk, where the recruiter signs up new members for the Thornlin Militia, " +
        "and a well-worn chair. On the wall a piece of parchment has been very " +
        "visibly posted.\n");
    
    add_item(({"parchment", "piece of parchment", "rules"}), &read_rules());
    add_cmd_item(({"parchment", "piece of parchment", "rules"}), "read", 
        &read_rules());
    add_item(({"floor", "ground", "straw"}), "The straw that has been strewn across " +
        "the floor is fresh and clean, with a few herbs mixed in to repel fleas.\n");
    add_item(({"wall", "walls", "bare walls", "ceiling", "brick"}),
        "The walls and ceiling are made of good quality brick, and the " +
        "workmanship appears to be that of local mason who took great " +
        "pride in his work and making the buildings of his town look nice. A " +
        "piece of parchment on the wall lists the rules that all members of the " +
        "Thornlin Militia must obey.\n");
    add_item(({"desk", "small desk", "wooden desk", "small wooden desk", "quill", 
        "feather quill", "papers", "pot", "ink pot"}), &see_desk());
    add_item(({"chair", "well-worn chair", "wooden chair"}), &see_chair());

    add_chair(CHAIR_NAME, 
        "[down] [on] / [in] [the] [well-worn] [wooden] [worn] 'chair'", CHAIR_NUM,
        "in");
    add_chair(DESK_NAME, "[down] [behind] / [at] [the] [small] [wooden] 'desk'",
        DESK_NUM, "behind");

    add_prop(ROOM_I_INSIDE, 1);
    restore_object(MASTER);
    reset_room();
    cleanup_list();
    add_exit(MROOM + "start.c", "north", &militia_only(), 1, 0);
    add_exit(MROOM + "train.c", "east", &militia_only(), 1, 0);
    add_exit(MROOM + "board_room.c", "west", &militia_only(), 1, 0);
    add_exit(THORN_DIR + "guardhouse.c", "south", 0, 1, 0);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1); 
}

/*
 * Function name: query_member
 * Description  : Queries if a name is on the member list.
 * Arguments    : string name - the name to query 
 */
public int
query_member(string name)
{
    name = capitalize(name);

    return (member_array(name, gMembers) != -1);
}

/*
 * Function name: add_member
 * Description  : Adds a name to the member list.
 * Arguments    : string name - the name to add
 */
public void
add_member(string name)
{
    name = capitalize(name);

    if (!query_member(name))
    {
        gMembers += ({ name });
        save_object(MASTER);
    }
}

/*
 * Function name: remove_member
 * Description  : Removes a name from the member list.
 * Arguments    : string name - the name to remove
 */
public void
remove_member(string name)
{
    name = capitalize(name);

    if (query_member(name))
    {
        gMembers -= ({ name });
        save_object(MASTER);
    }
}

/*
 * Function name: query_warned
 * Description  : queries if the name is on the warned list
 * Arguments    : string name - the name to query
 * Returns      : The time they were warned
*/
public int
query_warned(string name)
{
    name = capitalize(name);

    if (member_array(name, m_indexes(gWarned)) != -1)
        return gWarned[name];
    else
        return 0;
}

/*
 * Function name: add_warned
 * Description  : Add a militia-member's name to the warned list
 * Arguments    : string name - the member's name
 * Returns      : 0 if never warned before, the time of the last warning
 *                if already warned once.
 */
public int
add_warned(string name)
{
    int warned_time;
    name = capitalize(name);

    if (!query_warned(name))
    {
        gWarned += ([ name : time() ]);
        save_object(MASTER);
        return 0;
    }
    else
    {
        warned_time = gWarned[name];
        gWarned[name] = time();
        save_object(MASTER);
        return warned_time;
    }
}

/*
 * Function name: remove_warned
 * Description  : Removes a name from the warned list
 * Arguments    : string name - the name to remove
*/
void
remove_warned(string name)
{
    name = capitalize(name);

    if (query_warned(name))
    {
        gWarned = m_delete(gWarned, name);
        save_object(MASTER);
    }
}

/*
 * Function name: query_not_allowed
 * Description  : Queries if a name is on the not allowed list
 * Arguments    : string name - the name to remove
 * Returns      : int - the time they were last bad
 */
public int
query_not_allowed(string name)
{
    name = capitalize(name);

    if (member_array(name, m_indexes(gNotAllowed)) != -1)
        return gNotAllowed[name];
    else
        return 0;
}

/*
 * Function name: add_not_allowed
 * Description  : Adds a name to the not allowed list.
 * Arguments    : string name - the name to add
 *                int end - the end of the punishment
 */
public varargs void
add_not_allowed(string name, int end)
{
    name = capitalize(name);

    if (!query_not_allowed(name))
    {
        if (!end)
            end = time() + CLEANUP_TIME;

        gNotAllowed += ([ name : end ]);
        save_object(MASTER);
    }
    else
    {
        if (!end)
            end = time() + CLEANUP_TIME;

        gNotAllowed[name] = end;
        save_object(MASTER);
    }
}

/*
 * Function name: remove_not_allowed
 * Description  : Removes a name from the not allowed list.
 * Arguments    : string name - the name to remove
 */
public void
remove_not_allowed(string name)
{
    name = capitalize(name);

    if (query_not_allowed(name))
    {
        gNotAllowed = m_delete(gNotAllowed, name);
        save_object(MASTER);
    }
}

/*
 * Function name: cleanup_list
 * Description  : Remove not allowed from list after 4 months
 *                Remove names of non-existant players
 */
public void 
cleanup_list()
{
    int i, size, current_time = time();
    string *names;

    /* Remove the players not allowed who have served their punishment. */
    names = m_indexes(gNotAllowed);
    for (i = 0, size = sizeof(names); i < size; i++)
    {
        if (current_time - gNotAllowed[names[i]] > 0)
        {
            remove_not_allowed(names[i]);
        }
    }

    /* Remove non-existant players from the list. */
    for (i = sizeof(gMembers) - 1; i >= 0; i--)
    {
        if (!SECURITY->exist_player(gMembers[i]))
            remove_member(gMembers[i]);
    }
}

public int
enlist(string str)
{
    int ret, mswitch = 0;
    string reason, full_part;
    object shadow, who = this_player();

    if (!strlen(str) || (!parse_command(lower_case(str), ({}), 
      "[in] [the] [thornlin] [militia] / [guild] %w 'time'", full_part)))
    {
        notify_fail("Enlist in the militia full/part time?\n");
        return 0;
    }
    else if (!present(gRecruiter, this_object()))
    {
        notify_fail("The recruiter is not here to enlist you.\n");
        return 0;
    }
    else if (who->query_race() == "goblin")
    {
        /* This will give for example, Hobgoblins aren't welcome here! */
        notify_fail(LANG_PWORD(capitalize(who->query_race_name())) +
            "aren't welcome here!\n");
        return 0;
    }
    else if (who->query_alignment() < MILITIA_ALIGN_MIN)
    {
        notify_fail("You don't seem to be welcome here.\n");
        return 0;
    }
    else if (who->query_wiz_level())
    {
        notify_fail("Wizards must add the shadow and soul to themselves.\n");
        return 0;
    }
    else if (query_not_allowed(who->query_real_name()))
    {
        notify_fail("The Thornlin Militia has not forgiven you yet.\n");
        return 0;
    }
    else if (!IS_MILITIA(who) && who->query_prop(PLAYER_I_JOINED_THORNLIN))
    {
        notify_fail("The recruiter ignores you, as you have joined " +
            "too recently.\n");
        return 0;
    }

    if (full_part == "part")
    {
        if(who->query_guild_member("layman"))
        {
            notify_fail("You already have a layman guild. Perhaps you " +
                "would like to 'enlist full time'?\n");
            return 0;
        }
        else if (who->query_guild_name_lay() == MILITIA_NAME)
        {
            notify_fail("You are already enlisted part time. If you want, " +
                "you can 'enlist full time'.\n");
            return 0;
        }

        if (who->query_guild_name_occ() == MILITIA_NAME)
        {
            who->remove_lay_militia(who, "switch", 1);
            mswitch = 1;
        }

        shadow = clone_object(MSHADOW);
        ret = shadow->shadow_me(who, "layman", MILITIA_STYLE,
            MILITIA_NAME);
    }
    else if (full_part == "full")
    {
        if(who->query_guild_member("occupational"))
        {
            notify_fail("You already have an occupational guild. Perhaps " +
                "you would like to 'enlist part time'?\n");
            return 0;
        }
        else if (who->query_guild_name_occ() == MILITIA_NAME)
        {
            notify_fail("You are already enlisted full time. If you want, " +
                "you can 'enlist part time'.\n");
            return 0;
        }

        if (who->query_guild_name_lay() == MILITIA_NAME)
        {
            who->remove_lay_militia(who, "switch", 1);
            mswitch = 1;
        }

        shadow = clone_object(OCCSHADOW);
        ret = shadow->shadow_me(who, "occupational", MILITIA_STYLE,
            MILITIA_NAME);
    }

    switch(ret)
    {
    case 1:
        /* The player has been successfully shadowed. */
        gRecruiter->command("say to " + OB_NAME(who) + " Welcome " +
            "to the Thornlin Militia!");
        say(QCTNAME(gRecruiter) + " hands " + QTNAME(who) + " a pair of " +
            "standard issue boots as " + who->query_pronoun() + " marks " +
            who->query_possessive() + " name on the roster.\n", who);
        who->catch_tell(gRecruiter->query_The_name(who) + " hands you " +
            "a pair of standard issue boots as you mark your name on " +
            "the roster.\n");
        /* Only new recruits get a gold coin. */
        if (!mswitch)
        {
            if (!MONEY_MOVE(1, "gold", 0, gRecruiter))
            {
                gRecruiter->command("give gold coin to " + OB_NAME(who));
            }
            else
            {
                if (!MONEY_MOVE(1, "gold", 0, this_object()))
                {
                    gRecruiter->command("say to " + OB_NAME(who) + 
                        " You can't carry your gold coin, so I will just " +
                        "leave it here for you.");
                    gRecruiter->command("emote drops a gold coin.");
                }
            }
        }

        
        log_file(MILITIA_LOG, extract(ctime(time()), 4, 15) + " " +
            capitalize(who->query_real_name()) +
            " joined " + full_part + " time.\n", 500000);
        /* Avoid abuse to get lots of gold coins. */
        who->add_prop(PLAYER_I_JOINED_THORNLIN, 1);
        return 1;
    case -4:
        /* The player has the wrong type of guild already, or */
        /* one of his existing guilds has blocked this one. */
        write("Your other guilds prohibit you from joining this one!\n");
        break;
    default:
        /* Shadowing error */
        write("You were unable to enter the militia due to " +
            "a problem in the fabric of space. Contact " +
            "the guildmaster or make a bug report.\n");
    }

    /* We couldn't shadow the player, so remove the shadow. */
    shadow->remove_shadow();
    log_file(MILITIA_LOG, extract(ctime(time()), 4, 15) + " " +
        " tried to join the guild, but couldn't.\n", 500000);
    return 1;
}

public int
resign(string str)
{
    object who = this_player();

    if (strlen(str) && lower_case(str) != "from the militia")
    {
        notify_fail("Resign from the militia?\n");
        return 0;
    }
    else if (!present(gRecruiter, this_object()))
    {
        notify_fail("The Recruiter is not present to receive your " +
            "resignation.\n");
        return 0;
    }
    else if (!IS_MILITIA(who))
    {
        gRecruiter->command("say You cannot resign. You aren't in the " +
            "Militia!");
        return 1;
    }
    else if (gConfirm != who->query_real_name())
    {
        write("Are you sure you wish to resign from the Thornlin Militia? " +
            "Resign again if you are sure.\n");
        gConfirm = who->query_real_name();
        return 1;
    }

    write("You resign from the Thornlin Militia.\n");
    say(QCTNAME(who) + " resigns from the Thornlin Militia.\n");

    /* The shadow will catch the rest. */
    who->remove_lay_militia(who, "left");
    return 1;
}

public int
query_boot_recover(object player)
{
    /* Restore boots to militia members who don't have them already. */
    if (!IS_MILITIA(player) || present(MITEM_ID, player))
        return 0;
    else
        return 1;
}

public int
restore_boots(object player)
{
    object mitem;
    int res;

    mitem = clone_object(MITEM);
    res = mitem->move(player, 1);
    mitem->set_militia_name(player->query_name());
    return (!res);
}

public int
new_item(string str)
{
    object mitem;

    if (!strlen(str) || (!parse_command(lower_case(str), ({}),
      " [a] [new] [guild] 'item' / 'object' / 'boots' ")))
    {
        notify_fail("Request what? New boots?\n");
        return 0;
    }
    else if (!present(gRecruiter))
    {
        notify_fail("The recruiter is not present to give you new " +
            "boots.\n");
        return 0;
    }
    else if (!IS_MILITIA(this_player()))
    {
        gRecruiter->command("say You aren't enlisted!");
        return 1;
    }
    else if (present(MITEM_ID, this_player()))
    {
        gRecruiter->command("say You already have a pair of boots!");
        return 1;
    }

    mitem = clone_object(MITEM);
    mitem->move(this_player(), 1);
    mitem->set_militia_name(this_player()->query_name());
    write("You receive a new " + mitem->short() + " from " +
        gRecruiter->query_the_name(this_player()) + ".\n");
    say(QCTNAME(this_player()) + " receives a new " + mitem->short() +
        " from " + QTNAME(gRecruiter) + ".\n");
    return 1;
}

public string
format_output(string *output)
{
    int size, i, scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string *output2, formatted = "";
 
    size = sizeof(output);
 
    if (!size)
    {
        return "";
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

public int
list_all(string str)
{
    if (!IS_MILITIA(this_player()))
        return 0;

    if (!strlen(str))
    {
        notify_fail("List members? List banished? List warned?\n");
        return 0;
    }

    str = lower_case(str);

    if (str == "members")
    {
        if (sizeof(gMembers) > 0)
        {
            write("Enlisted in the Thornlin Militia:\n" + 
                format_output(gMembers));
            return 1;
        }
        else
        {
            write("There is nobody enlisted in the Thornlin Militia.\n");
            return 1;
        }
    }
    else if (str == "banished")
    {
        if (sizeof(m_indexes(gNotAllowed)) > 0)
        {
            write("Banished from enlisting in the Thornlin Militia:\n" +
                format_output(m_indexes(gNotAllowed)));
            return 1;
        }
        else
        {
            write("There is nobody banished from joining the Thornlin " +
                "Militia.\n");
            return 1;
        }
    }
    else if (str == "warned")
    {
        if (sizeof(m_indexes(gWarned)) > 0)
        {
            write("The following people have a warning on their record:\n" +
                format_output(m_indexes(gWarned)));
            return 1;
        }
        else
        {
            write("Nobody has a warning on their record right now.\n");
            return 1;
        }
    }

    return 0;
}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

void
remove_militia_members(object who)
{
    who->catch_tell("A stern looking guard escorts you out of the " +
        "barracks.\n");
    tell_room(this_object(), QCTNAME(who) + " is escorted out of the " +
        "barracks by a stern looking guard.\n", who);
    tell_room(THORN_DIR + "r2a", QCTNAME(who) + " is escorted out from " +
        "the barracks by a stern looking guard.\n");
    who->move_living("M", THORN_DIR + "r2a", 1, 0);
}

int
did_spit(string str)
{
    remove_militia_members(this_player());
    return 1;
}

public void
init()
{
    ::init();

    init_room_chairs();
    add_action(enlist,   "enlist");
    add_action(did_spit, "spit");
    add_action(list_all, "list");
    add_action(new_item, "new");
    add_action(new_item, "request");
    add_action(resign,   "resign");
}
