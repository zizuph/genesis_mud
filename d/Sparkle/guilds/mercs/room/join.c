/*
 * Mercenaries join room, by Morrigan 11/2001
 *
 * Adapted from code by Auberon and Gwyneth on 19 February 2001
 */
inherit "/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs2";
#include "../merc.h"
#include "room.h"

/* 30 days to get off the banished list, 14 days to get off the warn list */
#define CLEANUP_TIME	2592000
#define WARN_CLEANUP_TIME    1209600
#define DESK_NAME	"small wooden desk"
#define DESK_NUM	1
#define PLAYER_I_JOINED_MERC	"_player_i_joined_merc"

/* Global Variables */
static string gConfirm = "";
object gRecruiter;
string *gBanish_list = ({ });
string *gAvailable = ({ });
mapping gMembers = ([ ]);
mapping gNotAllowed = ([ ]);
mapping gWarned = ([ ]);

/* Prototypes */
public void cleanup_list();
int merc_only();

public int
query_on_banish_list(string str)
{
    str = C(str);

    if (member_array(str, gBanish_list) == -1)
	return 0;

    return 1;
}

public int
add_to_banish_list(string str)
{
    str = C(str);

    if (member_array(str, gBanish_list) != -1)
	return 0;

    gBanish_list += ({ str });
    save_object(MERC_MASTER);
    return 1;
}

public int
remove_from_banish_list(string str)
{
    str = C(str);

    if (member_array(str, gBanish_list) == -1)
	return 0;

    gBanish_list -= ({ str });
    save_object(MERC_MASTER);
    return 1;
}

/*
 * Function name: no_guards()
 * Description  : don't allow guards to pass
 * Returns      : 1 if they don't pass, 0 if they do
 */
int no_guards()
{
    if (this_player()->id("_mercenary_guild_guard_"))
        return 1;

    return 0;
}

/*
 * Function name: merc_only()
 * Description  : only allow mercs to pass, or mortals led by a merc
 * Returns      : 1 if they do not pass, 0 if they do
 */
int merc_only()
{
    if (this_player()->id("_mercenary_guild_guard_"))
	return 0;

    if (this_player()->query_merc_dog())
	return 0;

    if (this_player()->query_wiz_level())
	return 0;

    if (!IS_MERC(this_player()) && objectp(this_player()->query_leader()))
    if (IS_MERC(this_player()->query_leader()) && 
        extract(file_name(environment(this_player()->query_leader())), 0, 22) == MERC_DIR)
    {
        write("A guard says: I will allow you to pass in "+
        this_player()->query_leader()->query_name()+"'s company.\n");
        this_player()->query_leader()->catch_msg("The guards permit "+
            this_player()->query_name()+" to enter in your company.\n");
        return 0;
    }

    if (!this_player()->query_guild_member(MERC_NAME))
    {
        write ("Several guards prevent you from going that way.\n");
        return 1;
    }

    write(GREAT_HALL_ENTER);
    check_sitting();
    return 0;
}            

/*
 * Function name: leave_building()
 * Description  : print a pretty message when a merc leaves the guild hall
 * Returns      : nothing
 */
int leave_building()
{
   if (IS_MERC(TP))
	write("You step out of the Mercenary Halls, ready for another "+
	    "adventure.\n");
       else
	write("You leave the rustic building.\n");
}

public void
reset_room()
{
    if (!objectp(gRecruiter))
    {
        gRecruiter = clone_object(MNPC + "gnimpsh");
        gRecruiter->arm_me();
        gRecruiter->move_living("with a weary smile.", this_object());
        gRecruiter->command("sit at desk");
    }
}

public string
see_desk()
{
    return ("The desk is small in size. Upon it rest a black leather-"+
	"bound book with a red dragon on the front, a quill, and a bottle of "+
	"ink.\n" +
        sitting_on_chair(DESK_NAME, this_player(), 0, 0));
}

public string
long_desc()
{
    return ("This is the entrance to a large building. "+BUILDING_DESC+
	" Facing the door sits a small "+
	"wooden desk"+(objectp(gRecruiter) ? ", at which "+
	gRecruiter->query_the_name(TP)+
        " is seated." : ".") + " A poster has been hung on the wall behind "+
	"the desk. Beyond the desk, the room opens up into a great "+
	"chamber.\n");
}

public string
read_rules()
{
    string txt = ("You read the poster.\n" +
        "       RULES\n" +
        "\n" +
        "1. Do not kill my guards or hired persons\n"+
	"   without my permission!\n"+
	"2. Do not kill the small and helpless in\n"+
	"   the nearby town of Sparkle unless you\n"+
	"   absolutely have to. If you aren't sure\n"+
	"   whether or not you absolutely have to,\n"+
	"   you don't!\n"+
	"3. Do not kill this gnome!\n\n"+
	"Maligant\n\n");

    if (!IS_MERC(this_player()))
    {
        txt += "In fine print at the bottom, you read that one may 'mjoin' or "+
	    "'mleave' (at a penalty) the mercenaries here. You may also "+
	    "'list mercenaries' here to find out which mercenaries have "+
	    "made themselves 'available' to be hired.\n";
    }   

    if (IS_MERC(this_player()))
    {
        txt += "In fine print at the bottom, you read that one may 'list members',"+
            " 'list banished' and 'list warned', as well as being able to 'mjoin' "+
	    "or 'mleave' (at a penalty) here.\n";
    }

    return txt;
}

public void
create_room()
{
    set_short("Entrance to large building");
    set_long("@@long_desc");
    
    add_item(({"poster", "sign", "rules"}), &read_rules());
    add_cmd_item(({"poster", "sign", "rules"}), "read", 
        &read_rules());
    add_item(({"desk", "small desk", "wooden desk", "small wooden desk", "quill", 
        "feather quill", "papers", "pot", "ink pot"}), &see_desk());

    add_chair(DESK_NAME, "[down] [behind] / [at] [the] [small] [wooden] 'desk'",
        DESK_NUM, "behind");

    add_prop(ROOM_I_INSIDE, 1);
    restore_object(MERC_MASTER);
    gAvailable = ({ });
    reset_room();
    cleanup_list();
    add_exit(MROOM + "great_hall.c", "north", &merc_only(), 1, 0);
    add_exit(MROOM + "center.c", "south", "@@leave_building", 1, 0);
    add_exit(MLIB + "library.c", "east", "@@no_guards", 1, 0);
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

    if (gMembers[name])
      return 1;

    return 0;
}

/*
 * Function name: query_type_member
 * Description  : Queries what type of member the mercenary is.
 * Arguments    : string name - the name to query
 * Returns      : string sword, club, undeclared, or "" if no such merc is
 *                registered with the member list
 */
public string
query_type_member(string name)
{
    name = capitalize(name);

    if (member_array(name, m_indexes(gMembers)) != -1)
        return gMembers[name];

    return "";
}

/*
 * Function name: set_type_member()
 * Description  : Set what type of member this is, club/sword/undeclared
 * Arguments    : name: the merc, type: what type he is
 * Returns      : 1 if successful, 0 if not
 */
public int
set_type_member(string name, string type)
{
    name = capitalize(name);
    type = lower_case(type);

    if (member_array(name, m_indexes(gMembers)) != -1)
    {
        gMembers[name] = type;
        save_object(MERC_MASTER);
        return 1;
    }

    return 0;
}

/*
 * Function name: query_club_member()
 * Description  : Is this a club member?
 * Arguments    : name: the merc
 * Returns      : 1 if yes, 0 if no
 */
public int
query_club_member(string name)
{
    name = capitalize(name);

    if (member_array(name, m_indexes(gMembers)) != -1)
        if (gMembers[name] == "club")
	    return 1;

    return 0;
}

/*
 * Function name: query_sword_member()
 * Description  : is this a sword member?
 * Arguments    : name: the merc
 * Returns      : 1 if yes, 0 if no
 */
public int
query_sword_member(string name)
{
    name = capitalize(name);

    if (member_array(name, m_indexes(gMembers)) != -1)
        if (gMembers[name] == "sword")
	    return 1;

    return 0;
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

    if (member_array(name, m_indexes(gMembers)) == -1)
    {
        gMembers += ([ name : "undeclared" ]);
        save_object(MERC_MASTER);
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
        gMembers = m_delete(gMembers, name);
        save_object(MERC_MASTER);
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
 * Description  : Add a merc-member's name to the warned list
 * Arguments    : string name - the member's name
 * Returns      : 0 if never warned before, the time of the last warning
 *                if already warned once.
 */
public void
add_warned(string name)
{
    int end;
    name = capitalize(name);

    if (!query_warned(name))
    {
        end = time() + WARN_CLEANUP_TIME;

        gWarned += ([ name : end ]);
        save_object(MERC_MASTER);
    }
    else
    {
        end = time() + CLEANUP_TIME;

        gWarned[name] = end;
        save_object(MERC_MASTER);
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
        save_object(MERC_MASTER);
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
        save_object(MERC_MASTER);
    }
    else
    {
        if (!end)
            end = time() + CLEANUP_TIME;

        gNotAllowed[name] = end;
        save_object(MERC_MASTER);
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
        save_object(MERC_MASTER);
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

    /* Remove the players not allowed who have served their punishment. */
    names = m_indexes(gWarned);
    for (i = 0, size = sizeof(names); i < size; i++)
    {
        if (current_time - gWarned[names[i]] > 0)
        {
            remove_warned(names[i]);
        }
    }

    names = m_indexes(gMembers);
    /* Remove non-existant players from the list. */
    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        if (!SECURITY->exist_player(names[i]))
            remove_member(names[i]);
    }
}

/*
 * Function name: join_mercs()
 * Description  : Join the mercenary guild! Woo hoo!
 * Arguments    : str: the string following the verb
 * Returns      : 1 if they joined, 0 if they did not
 */
public int
join_mercs(string str)
{
    int ret;
    string reason;
    object shadow, who = this_player();

    if (!strlen(str) || (!parse_command(lower_case(str), ({}), 
    "[the] [mercenaries] [guild]")))
    {
        notify_fail("Join the mercenaries?\n");
        return 0;
    }
    else if (!present(gRecruiter, this_object()))
    {
        notify_fail("The recruiter is not here to sign you up.\n");
        return 0;
    }
    else if (strlen(str) && str != "the mercenaries" &&
	str != "mercenaries" && str != "the mercenary guild" && 
	str != "the mercenaries guild" && str != "the guild" &&
	str != "guild")
    {
        notify_fail("Join the mercenaries?\n");
        return 0;
    }
    else if (IS_MERC(who))
    {
        gRecruiter->command("say YouAreAlreadyAMercenary!\n");
	gRecruiter->command("emote mumbles something about stupid people.\n");
        return 1;
    }
    else if (who->query_guild_member("occupational"))
    {
        gRecruiter->command("sigh tired");
	gRecruiter->command("say You are too busy with the "+
	    who->query_guild_name_occ()+" to be a mercenary!");
        return 1;
    }
    else if (who->query_wiz_level())
    {
        notify_fail("Wizards must add the shadow and soul to themselves.\n");
        return 0;
    }
    else if (query_not_allowed(who->query_real_name()))
    {
	gRecruiter->command("say GetOut! GetOutImmediately! YouAreNotWelcomeHere!");
	gRecruiter->command("say MaybeMaligantIsn'tHereToRememberYou,ButMyBookDoesn't"+
	    "Lie.");
        return 1;
    }
    /* I want this out for now - (Gorboth)
     *
    else if (who->query_prop(PLAYER_I_JOINED_MERC))
    {
	gRecruiter->command("steam");
	gRecruiter->command("say YouAlreadyJoinedOnceToday! WhatDoYouThinkThisIs,"+
	"MusicalMercenaries?? StopWastingMyTime!");
        return 1;
    }
     */

    if (who->query_real_name() != "gorbyjr")
    {
        gRecruiter->command("sigh");
        gRecruiter->command("say WithMaligantGone ... Well ... TheGuildIsNot"
          + "AcceptingNewMembersAtThisTime ...");
        gRecruiter->command("say I'mNotSureWhatIsGoingToHappen ... Really ...");

        return 1;  
    }

    shadow = clone_object(MSHADOW);
    ret = shadow->shadow_me(who, "occupational", MERC_STYLE,
        MERC_NAME);
    switch(ret)
    {
    case 1:
        /* The player has been successfully shadowed. */
        gRecruiter->command("emote flips open the book and scribbles furiously"+
            "for a few seconds.");
        gRecruiter->command("say to " + OB_NAME(who) + " ThankYouForJoining"+
            "Maligant'sMercenaries! I'mNowOneStepCloserToFinishingMyLifeQuest!");

        say(QCTNAME(gRecruiter) + " reaches into "+POSSESSIVE(gRecruiter)+
            " desk and hands "+QTNAME(who)+" a black leather belt.\n", who);
        who->catch_tell(gRecruiter->query_The_name(who) + " reaches into "+
            "his desk and hands you a black leather belt.\n");

        write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
            capitalize(who->query_real_name()) +
            " joined.\n");
        add_member(who->query_name());
        who->clear_guild_stat(SS_OCCUP);
        who->add_prop(PLAYER_I_JOINED_MERC, 1);
        return 1;
    case -4:
        /* The player has a layman guild already, or */
        /* one of his existing guilds has blocked this one. */
        write("Your other guilds prohibit you from joining this one!\n");
        break;
    default:
        /* Shadowing error */
        write("You were unable to join the mercenaries due to " +
            "a problem in the fabric of space. Contact " +
            "the guildmaster or make a bug report.\n");
    }

    /* We couldn't shadow the player, so remove the shadow. */
    shadow->remove_shadow();
    write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
        " tried to join the guild, but couldn't.\n");
    return 1;
}


/*
 * Function name: leave_mercs()
 * Description  : Leave the guild
 * Arguments    : str: string following verb
 * Returns      : 1 if they left, 0 if they didn't
 */
public int
leave_mercs(string str)
{
    object who = this_player();
    int level = who->query_stat(SS_OCCUP) / 10;

    if (strlen(str) && lower_case(str) != "the mercenaries")
    {
        notify_fail("Leave the mercenaries?\n");
        return 0;
    }
    else if (!present(gRecruiter, this_object()))
    {
        notify_fail("The recruiter is not present to erase your " +
            "name from the book.\n");
        return 0;
    }
    else if (!IS_MERC(who))
    {
	gRecruiter->command("duh "+who->query_name());
        gRecruiter->command("say You'reNotEvenAMercenaryToBeginWith!");
        return 1;
    }
    else if (gConfirm != who->query_real_name())
    {
	gRecruiter->command("say WithMaligantGone, WhoCanBlameYou?");
        write("Are you sure you wish to leave the Mercenaries? " +
            "Repeat command if you are sure.\n");
        gConfirm = who->query_real_name();
        return 1;
    }

    gRecruiter->command("emote sighs heavily and marks through some writing "+
	"in the book.");
    gRecruiter->command("say SometimesIThinkI'llNeverCompleteMyLifeQuest.");
    write("You are no longer a mercenary.\n");
    say(QCTNAME(who) + " is no longer a mercenary.\n");

    /* The shadow will catch the rest. */
    who->remove_occ_merc(who, "left");
    return 1;
}

/*
 * Function name: new_item()
 * Description  : get a new guild item
 * Arguments    : str: string following verb
 * Returns      : 1 if they get a new item, 0 if not
 */
public int
new_item(string str)
{
    object mitem;

    if (!strlen(str) || (!parse_command(lower_case(str), ({}),
      " [a] [new] [guild] 'item' / 'holster' / 'scabbard' / 'belt'")))
    {
        notify_fail("Request a new guild item?\n");
        return 0;
    }
    else if (!present(gRecruiter))
    {
        notify_fail("The recruiter is not present to give you anything.\n");
        return 0;
    }
    else if (!IS_MERC(this_player()))
    {
        gRecruiter->command("scowl angrily");
        gRecruiter->command("say YouAreNotAMercenary!");
        return 1;
    }
    else if (present(MITEM_ID, this_player()))
    {
        gRecruiter->command("rolleyes");
        gRecruiter->command("say YouAlreadyHaveOne! WhatDoYouThinkThisIs,"+
	    "ACharity?!");
        return 1;
    }

    mitem = clone_object(MITEM);
    mitem->move(this_player(), 1);
    write(gRecruiter->query_the_name(this_player())+" looks annoyed as "+
	"he reaches into his desk to replace your lost item. He hands it "+
	"to you with a snort.\n");
    say(QCTNAME(gRecruiter)+" looks annoyed as he reaches into his desk "+
	"and hands something to "+QTNAME(this_player())+" with a snort.\n");
    gRecruiter->command("say ThisTimeDon'tLoseIt!");
    return 1;
}

/*
 * Function name: format_output()
 * Description  : Format an array of strings to one pretty string
 * Arguments    : an array of strings
 * Returns      : one pretty string
 */
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

/*
 * Function name: add_hirelist()
 * Description  : Add someone to the available to be hired list
 * Arguments    : str: the person to add
 * Returns      : void
 */
public void add_hirelist(string str)
{
    str = capitalize(str);

    gAvailable += ({ str });
}

/*
 * Function name: query_hirelist()
 * Description  : Is this person on the available to be hired list?
 * Arguments    : str: the person
 * Returns      : 1 if yes, 0 if no
 */
public int query_hirelist(string str)
{
    str = capitalize(str);

    if (member_array(str, gAvailable) != -1)
	return 1;

    return 0;
}

/*
 * Function name: remove_hirelist()
 * Description  : Remove someone from the available to be hired list
 * Arguments    : str: the person
 * Returns      : 1 if removed, 0 if not
 */
public int remove_hirelist(string str)
{
    str = capitalize(str);

    if (member_array(str, gAvailable) != -1)
    {
	gAvailable -= ({ str });
        return 1;
    }

    return 0;
}

/*
 * Function name: update_hirelist()
 * Description  : Update the hirelist and print it out
 * Returns      : the list of those who are on the available to be hired list
 */
public string *update_hirelist()
{
    int i;
    string *temp_list = gAvailable;

    if (sizeof(temp_list) == 0)
	return 0;

    for (i = 0; i < sizeof(temp_list); i++)
        if (!objectp(find_living(lower_case(temp_list[i]))))
	    gAvailable -= ({ temp_list[i] });

    return gAvailable;
}

/*
 * Function name: available_for_hire()
 * Description  : A merc makes himself available or not for hire
 * Arguments    : str: string following verb
 * Returns      : 1 if successful, 0 if not
 */
public int
available_for_hire(string str)
{
    string name = this_player()->query_name();

    NF("What?\n");
    if (!IS_MERC(this_player()))
        return 0;

    if (!str)
    {
        if (member_array(name, gAvailable) == -1)
	{
	    add_hirelist(name);
	    gRecruiter->command("say OkayIwillAddYourNameToTheListOfMercenaries"+
		"LookingForWork.");
	    gRecruiter->command("emote writes down a name on a list.");
	    return 1;
        }
	else
	{
	    remove_hirelist(name);
	    gRecruiter->command("say IWillEraseYourNameFromTheFor-HireList.");
	    gRecruiter->command("emote erases a name from a list.");
	    return 1;
        }

    }

    if (str == "yes" || str == "on")
    {
        if (member_array(name, gAvailable) != -1)
	{
	    gRecruiter->command("say YouAreAlreadyOnTheList!");
	    return 1;
	}

	add_hirelist(name);
	gRecruiter->command("say OkayIwillAddYourNameToTheListOfMercenaries"+
	    "LookingForWork.");
	gRecruiter->command("emote writes down a name on a list.");
	return 1;
    }
    
    if (str == "no" || str == "off")
    {
        if (member_array(name, gAvailable) == -1)
	{
	    gRecruiter->command("say YouAren'tOnTheListInTheFirstPlace!");
	    return 1;
	}

        remove_hirelist(name);
	gRecruiter->command("say IWillEraseYourNameFromTheFor-HireList.");
	gRecruiter->command("emote erases a name from a list.");
	return 1;
    }

    NF("Use <available [on/off/yes/no]> or just <available> to toggle between "+
	"states.\n");
    return 0;
}

/*
 * Function name: list_all()
 * Description  : List information on something
 * Arguments    : str: the something
 * Returns      : the information
 */
public int
list_all(string str)
{
    string *list = update_hirelist();
    string *member_list = ({ });
    int i;

    if (str == "available mercenaries" || str == "mercenaries for hire" ||
	str == "mercenaries" || str == "hirelings" || str == "for hire")
    {
        if (sizeof(list) == 0)
	{
	    gRecruiter->command("say I'mSorryButIDon'tShowAnyMercenaries"+
		"CurrentlyAvailableForHire.");
	    return 1;
        }

        gRecruiter->command("say LetMeSeeIfICanSayThisSlowlyForYourSlowMind. "+
	    "TheFollowing Mercenaries AreAvailable ToBeHired: "+
	    COMPOSITE_WORDS(list)+".");
	return 1;
    }

    if (!IS_MERC(this_player()) && !this_player()->query_wiz_level())
        return 0;

    if (!strlen(str))
    {
        notify_fail("List members? List banished? List warned?\n");
        return 0;
    }

    str = lower_case(str);

    if (str == "members")
    {
    if(!this_player()->query_wiz_level() &&
        !IS_MERC_WARLORD(this_player()) &&
            !IS_MERC_LORD(this_player()))
    {
        say(QCTNAME(gRecruiter)+" hides his book from "+
           QTNAME(this_player())+", saying: NoneOfYourBusiness!\n");
        write(gRecruiter->query_The_name(this_player())+" hides his "+
            "book from you, saying: NoneOfYourBusiness!\n");
        return 1;
    }

        if (sizeof(m_indexes(gMembers)) > 0)
        {
	    gRecruiter->command("grumble impatiently");
	    say(QCTNAME(gRecruiter)+" shows "+QTNAME(this_player())+" his "+
		"book for a moment.\n");
            write(gRecruiter->query_The_name(this_player())+" shows you "+
		"the list of mercenaries from his book:\n" + 
                format_output(m_indexes(gMembers)));

	    if (TP->query_wiz_level())
		write("Total number of Mercenaries: "+sizeof(m_indexes(gMembers))+
		    "\n");
            return 1;
        }
        else
        {
	    gRecruiter->command("wail");
	    gRecruiter->command("say ThereIsNoOneListedInMyBook! ThereAre"+
		"NoMercenaries!!");
            return 1;
        }
    }
    else if (str == "sword")
    {
        if (!TP->query_wiz_level())
	{
	    gRecruiter->command("say ThatIsn'tForYouToKnow,SoStopAsking!");
	    return 1;
	}

        for (i=0;i<sizeof(m_indexes(gMembers));i++)
            if (gMembers[m_indexes(gMembers)[i]] == "sword")
		member_list += ({ m_indexes(gMembers)[i] });

        if (sizeof(member_list) > 0)
	{
     	    gRecruiter->command("grumble impatiently");
	    say(QCTNAME(gRecruiter)+" shows "+QTNAME(this_player())+" his "+
		"book for a moment.\n");
            write(gRecruiter->query_The_name(this_player())+" shows you "+
		"the list of sword-users from his book:\n" + 
                format_output(member_list));
            write("Total number of sword-users: "+sizeof(member_list)+
		"\n");
            return 1;
        }
	else
	{
	    gRecruiter->command("say ThereAren'tAnySwordUsersYet!\n");
	    return 1;
        }
    }
    else if (str == "club")
    {
        if (!TP->query_wiz_level())
	{
	    gRecruiter->command("say ThatIsn'tForYouToKnow,SoStopAsking!");
	    return 1;
	}

        for (i=0;i<sizeof(m_indexes(gMembers));i++)
            if (gMembers[m_indexes(gMembers)[i]] == "club")
		member_list += ({ m_indexes(gMembers)[i] });

        if (sizeof(member_list) > 0)
	{
     	    gRecruiter->command("grumble impatiently");
	    say(QCTNAME(gRecruiter)+" shows "+QTNAME(this_player())+" his "+
		"book for a moment.\n");
            write(gRecruiter->query_The_name(this_player())+" shows you "+
		"the list of club-users from his book:\n" + 
                format_output(member_list));
            write("Total number of club-users: "+sizeof(member_list)+
		"\n");
            return 1;
        }
	else
	{
	    gRecruiter->command("say ThereAren'tAnySwordUsersYet!\n");
	    return 1;
        }
    }
    else if (str == "undeclared")
    {
        if (!TP->query_wiz_level())
	{
	    gRecruiter->command("say ThatIsn'tForYouToKnow,SoStopAsking!");
	    return 1;
	}

        for (i=0;i<sizeof(m_indexes(gMembers));i++)
            if (gMembers[m_indexes(gMembers)[i]] == "undeclared")
		member_list += ({ m_indexes(gMembers)[i] });

        if (sizeof(member_list) > 0)
	{
     	    gRecruiter->command("grumble impatiently");
	    say(QCTNAME(gRecruiter)+" shows "+QTNAME(this_player())+" his "+
		"book for a moment.\n");
            write(gRecruiter->query_The_name(this_player())+" shows you "+
		"the list of undeclared mercenaries from his book:\n" + 
                format_output(member_list));
            write("Total number of undeclared mercenaries: "+sizeof(member_list)+
		"\n");
            return 1;
        }
	else
	{
	    gRecruiter->command("say ThereAren'tAnySwordUsersYet!\n");
	    return 1;
        }
    }
    else if (str == "banished")
    {
        if (sizeof(m_indexes(gNotAllowed)) > 0)
        {
            gRecruiter->command("glare");
	    gRecruiter->command("say ThoseNoGoodRottenScoundrels. WeRemember"+
		"ThemHere,AndMaligantSaysNotToLetThemBackIn!");
            write(gRecruiter->query_The_name(this_player())+" shows you "+
		"the list of banished persons:\n" +
                format_output(m_indexes(gNotAllowed)));
	    say(QCTNAME(gRecruiter)+" shows "+QTNAME(this_player())+" his "+
		"book for a moment.\n");
            return 1;
        }
        else
        {
            gRecruiter->command("say SoFar,NoOneHasBeenBanished!");
	    gRecruiter->command("smile");
            return 1;
        }
    }
    else if (str == "warned")
    {
        if (sizeof(m_indexes(gWarned)) > 0)
        {
            gRecruiter->command("sigh gravely");
	    gRecruiter->command("say SomePeopleHaveToLearnTheHardWay.");
            write(gRecruiter->query_The_name(this_player())+" shows you "+
		"the list of warned mercenaries:\n" +
                format_output(m_indexes(gWarned)));
	    say(QCTNAME(gRecruiter)+" shows "+QTNAME(this_player())+" his "+
		"book for a moment.\n");
            return 1;
        }
        else
        {
	    gRecruiter->command("say WeHaven'tHadToWarnAnyoneYet!");
	    gRecruiter->command("smile relieved");
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

public int
banish_merc(string str)
{
    object who;
    int i;

    str = capitalize(str);

    if (!TP->query_wiz_level())
	return 0;

    notify_fail("Only arches and higher (or the guildmaster) may use this.\n");
    if (SECURITY->query_wiz_rank(lower_case(TP->query_name())) < 8 &&
	TP->query_name() != "Morrigan")
	return 0;

    if (!strlen(str))
    {
        write("Syntax: 'banish <player>'\n"+
	        "May be used again to remove player from banish list.\n");

        return 1;
    }

    if (objectp(who = find_living(lower_case(str))))
    {
        write(str+" found in the game. Performing banishment...\n");

	/* No experience loss for a banishment */
        who->add_prop(MALIGANT_REMOVED_LEAVE_PENALTY, 1);

        who->catch_tell("You are being banished from the Mercenary guild "+
	    "by powers beyond even Maligant's control.\n");
	i = who->remove_occ_merc(who, "banishment by "+TP->query_name());

        if (i == 0)
	    write("Banishment failed.\n");
	   else
	    write("Banishment completed.\n");

        return 1;
    }

    if (query_on_banish_list(str))
    {
	remove_from_banish_list(str);
        write(str + " removed from banish list.\n");
	return 1;
    }

    add_to_banish_list(str);
    write(str + " added to banish list - will be removed at next login.\n");
    return 1;
}

public void
init()
{
    ::init();

    init_room_chairs();
    add_action(join_mercs,   "mjoin");
    add_action(list_all, "list");
    add_action(new_item, "new");
    add_action(new_item, "request");
    add_action(leave_mercs,   "mleave");
    add_action(banish_merc, "banish");
    add_action(available_for_hire, "available");
}
