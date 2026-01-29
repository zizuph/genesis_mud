/*
 * Mercernaries Guild Server
 *
 * Created from the join.c and crest_room.c rooms by Morrigan.
 * 
 * Creation by Lunatari
 */
#pragma no_clone

#include "../merc.h"

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

string *colors = ({ "black", "white", "red", "orange", "yellow", 
		"green", "blue", "purple", "pink", "gold", "silver", 
		"bronze" });
string *emblems = ({ "dragon", "tiger", "sword", "crown", "helmet", "dagger", 
		"club", "axe", "sun", "moon", "griffon", "wyvern", "lion",
		"snake", "purse", "glove", "torch", "claw", "talon", "rose",
		"flame", "fire", "star", "tree", "eye", "leaf", "tear",
		"lightning bolt", "polearm", "unicorn" });

/*
 * Structure:
 *    lords = ([ "merc_name" : ({ a, b, c, d, ({ e }) }) ]), ])
 *       merc_name = the mercenary
 *       a = foreground
 * 	 b = background
 * 	 c = emblem
 *       d = gender
 *	 e = array of sub-lords
 *    members = ([ "merc_name" : "lord_name", ])
 *       merc_name = the mercenary 
 *       lord_name = the lord he has joined
 *    applications = ([ "merc_name" : "lord_name", ])
 *       merc_name = the mercenary
 *       lord_name = the lord he wishes to join
 *    notifications = ([ "merc_name" : ({ "notification1", "notification2", .. }), ])
 */

mapping lords = ([ ]);
mapping members = ([ ]);
mapping applications = ([ ]);
mapping notifications = ([ ]);
mapping private_racks = ([ ]);

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
    save_object(MERC_SERVER);
    return 1;
}

public int
remove_from_banish_list(string str)
{
    str = C(str);

    if (member_array(str, gBanish_list) == -1)
	return 0;

    gBanish_list -= ({ str });
    save_object(MERC_SERVER);
    return 1;
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
        save_object(MERC_SERVER);
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
        save_object(MERC_SERVER);
    }
    else
    {
        end = time() + CLEANUP_TIME;

        gWarned[name] = end;
        save_object(MERC_SERVER);
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
        save_object(MERC_SERVER);
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
        save_object(MERC_SERVER);
    }
    else
    {
        if (!end)
            end = time() + CLEANUP_TIME;

        gNotAllowed[name] = end;
        save_object(MERC_SERVER);
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
        save_object(MERC_SERVER);
    }
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
 * Function   : set_private_rack_transfer
 * Description: Sets the private rack transfer value for a lord
 * Arguments  : name : the name of the lord
 *            : val : the new value to set
 */
int set_private_rack_transfer(string name, int value)
{
    string lord;

    lord = capitalize(name);

    if (member_array(lord, m_indexes(lords)) == -1)
    return 0;

    private_racks[lord] = value;
    save_object(MERC_CREST);

    return 1;
}

/*
 * Function   : query_private_rack_transfer
 * Description: Get the transfer value for a lord
 * Arguments  : name - the name of the lord
 * Returns    : the transfer value
 */
int query_private_rack_transfer(string name)
{
    string lord;

    lord = capitalize(name);

    if (member_array(lord, m_indexes(lords)) == -1)
        return 0;

    if (member_array(lord, m_indexes(private_racks)) == -1)
        return 0;

    return private_racks[lord];
}

/*
 * Function   : add_colour()
 * Description: Add a colour to the crestlist
 * Arguments  : str: the colour to add
 * Returns    : 1 if it is added, 0 if it is not
 */
int add_colour(string str)
{
    if (member_array(str, colors) == -1)
    {
	colors += ({ lower_case(str) });
        save_object(MERC_CREST);
        return 1;
    }

    return 0;
}

/*
 * Function   : add_emblem()
 * Description: Add an emblem to the crestlist
 * Arguments  : str: the emblem to add
 * Returns    : 1 if it is added, 0 if it is not
 */
int add_emblem(string str)
{
    if (member_array(str, emblems) == -1)
    {
	emblems += ({ lower_case(str) });
        save_object(MERC_CREST);
        return 1;
    }

    return 0;
}

/*
 * Function   : remove_colour()
 * Description: Remove a colour from the crestlist
 * Arguments  : str: the colour to remove
 * Returns    : 1 if it is removed, 0 if it is not
 */
int remove_colour(string str)
{
    if (member_array(str, colors) != -1)
    {
	colors -= ({ lower_case(str) });
        save_object(MERC_SERVER);
        return 1;
    }

    return 0;
}

/*
 * Function   : remove_emblem()
 * Description: Remove an emblem from the crestlist
 * Arguments  : str: the emblem to remove
 * Returns    : 1 if it is removed, 0 if it is not
 */
int remove_emblem(string str)
{
    if (member_array(str, emblems) != -1)
    {
	emblems -= ({ lower_case(str) });
        save_object(MERC_SERVER);
        return 1;
    }

    return 0;
}

/*
 * Function   : query_need_notification()
 * Description: Does this merc need notification of anything?
 * Arguments  : merc: the name to check
 * Returns    : 1 if yes, 0 if no
 */
public int query_need_notification(string merc)
{
    if (member_array(merc, m_indexes(notifications)) == -1)
	return 0;

    return 1;
}

/*
 * Function   : get_notifications()
 * Description: Get all notifications for this person
 * Arguments  : merc: the name to get notifications for
 * Returns    : an array of all the notifications
 */
public string *get_notifications(string merc)
{
    string *not;
    if (member_array(merc, m_indexes(notifications)) == -1)
	return 0;

    not = notifications[merc];

    notifications = m_delete(notifications, merc);
    save_object(MERC_SERVER);

    return not;
}

/*
 * Function   : add_notification()
 * Description: Add a notification for a mercenary
 * Arguments  : merc: the mercenary to add a notification for
 *              text: the notification to add
 * Returns    : void
 */
public void add_notification(string merc, string text)
{
    if (find_living(lower_case(merc)))
    {
        find_living(lower_case(merc))->catch_tell("A messenger from the "+
	    "halls of the Mercenaries "+
	    "comes and relays the following information:\n"+text);
        return;
    }

    if (member_array(merc, m_indexes(notifications)) == -1)
	notifications += ([ merc : ({ text }) ]);
       else
	notifications[merc] += ({ text });

    save_object(MERC_SERVER);
}

/*
 * Function   : query_number_followers()
 * Description: How many followers does this lord have?
 * Arguments  : lord: the name of the lord
 * Returns    : an integer of how many followers this lord has
 */
public int query_number_followers(string lord)
{
    int i = 0, size, counter = 0;    

    lord = capitalize(lord);

    if (member_array(lord, m_indexes(lords)) == -1)
	return 0;

    size = sizeof(m_indexes(members));

    while (i < size)
    {
        if (members[m_indexes(members)[i]] == lord && 
	    lord != m_indexes(members)[i])
        {
 	    counter++;
        }

        i++;
    }

    return counter;
}

/*
 * Function   : query_followers()
 * Description: Who are the followers of this lord?
 * Arguments  : lord: the name of the lord
 * Returns    : an array of names
 */
public string *query_followers(string lord)
{
    int i, size;
    string *followers = ({ });

    lord = capitalize(lord);

    if (member_array(lord, m_indexes(lords)) == -1)
	return ({ "none" });

    size = sizeof(m_indexes(members));

    while ( i < size)
    {
        if (members[m_indexes(members)[i]] == lord && 
	    lord != m_indexes(members)[i])

	followers += ({ m_indexes(members)[i], });

	i++;
    }

    return followers;
}

/*
 * Function   : query_have_applicants()
 * Description: Does this lord have applicants?
 * Arguments  : lord: the name of the lord
 * Returns    : 1 if yes, 0 if no
 */
public int query_have_applicants(string lord)
{
    if (member_array(lord, m_values(applications)) == -1)
	return 0;

    return 1;
}

/*
 * Function   : query_members_lord()
 * Description: Who is this member's lord?
 * Arguments  : member: the name of the member
 * Returns    : the name of this member's lord, or 'none' if no lord is found
 */
public string query_members_lord(string member)
{
    member = capitalize(member);

    if (member_array(member, m_indexes(members)) == -1)
        return "none";

    return members[member];
}

/*
 * Function   : query_has_sublords()
 * Description: Does this lord have sublords?
 * Arguments  : member: the name of the member
 * Returns    : 1 if yes, 0 if no
 */
public int query_has_sublords(string member)
{
    member = capitalize(member);

    if (member_array(member, m_indexes(lords)) == -1)
	return 0;

    if (sizeof(lords[member]) < 5)
	return 0;

    return 1;
}

/*
 * Function   : query_sublords()
 * Description: Who are the sublords of this lord?
 * Arguments  : lord: the name of the lord
 * Returns    : the sublords of this lord, or 'none' 
 */
public string *query_sublords(string lord)
{
    lord = capitalize(lord);

    if (member_array(lord, m_indexes(lords)) == -1)
	return ({ "none" });

    if (sizeof(lords[lord]) < 5)
	return ({ "none" });

    return lords[lord][4];
}
    
/*
 * Function   : query_max_sublords()
 * Description: How many sublords can this lord have?
 * Arguments  : lord: the name of the lord
 * Returns    : the number of sublords this lord can have
 */
public int query_max_sublords(string lord)
{
    int i;

    lord = capitalize(lord);

    if (lord == "Morrigan")
	return 2;

    if (member_array(lord, m_indexes(lords)) == -1)
	return 0;

    i = query_number_followers(lord);

    if (i < 5)
	return 0;

    i = i - 2;

    return (i / 3);
}

/*
 * Function   : add_sublord_member()
 * Description: add a sublord
 * Arguments  : str: the name of the member to add, lord: the lord to add him to
 * Returns    : 1 if successful, 0 if fail
 */
public int add_sublord_member(string str, string lord)
{
    lord = capitalize(lord);
    str = capitalize(str);

    if (member_array(str, m_indexes(members)) == -1)
	return 0;

    if (lord != capitalize(members[str]))
	return 0;

    if (lord == str)
	return 0;

    if (!sizeof(lords[lord]))
	return 0;

    if (sizeof(lords[lord]) < 5)
        lords[lord] += ({ ({ str, }) });
       else if (member_array(str, lords[lord][4]) == -1)
        lords[lord][4] += ({ str, });
       else
	return 0;

    add_notification(str, lord+" has bestowed lordship upon you.\n");

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " bestowed lordship upon "+str+"\n");

    save_object(MERC_SERVER);
    return 1;
}

/*
 * Function   : remove_sublord_member()
 * Description: remove a sublord of a lord
 * Arguments  : member: the name of the member to remove, lord: the lord he serves
 * Returns    : 1 if successful, 0 if not
 */
public int remove_sublord_member(string str)
{
    string lord;
    str = capitalize(str);

    if (member_array(str, m_indexes(members)) == -1)
	return 0;

    lord = capitalize(members[str]);

    if (lord != capitalize(members[str]))
	return 0;

    if (!sizeof(lords[lord]))
        return 0;

    if (sizeof(lords[lord]) < 5)
	return 0;

    if (member_array(str, lords[lord][4]) == -1)
	return 0;

    if (sizeof(lords[lord][4]) > 1)
	lords[lord][4] -= ({ str });
       else
        lords[lord] = lords[lord][0..3];

   add_notification(str, lord+" has stripped you of your lordship.\n");

   write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " stripped "+str+" of lordship.\n");

    save_object(MERC_SERVER);
    return 1;
}

public int manual_remove_sublord(string lord, string sublord)
{
    if (!sizeof(lords[lord]))
        return 0;

    if (sizeof(lords[lord]) < 5)
        return 0;

    if (member_array(sublord, lords[lord][4]) == -1)
        return 0;

    if (sizeof(lords[lord][4]) > 1)
        lords[lord][4] -= ({ sublord });
       else
        lords[lord] = lords[lord][0..3];

    save_object(MERC_SERVER);
    return 1;
}


/*
 * Function   : query_registered_lord()
 * Description: Is this lord registered on the list?
 * Arguments  : lord: the name
 * Returns    : 1 if yes, 0 if no
 */
public int query_registered_lord(string lord)
{
    if (member_array(lord, m_indexes(lords)) == -1)
	return 0;

    return 1;
}


/*
 * query_lord_status()
 * Returns: 0 for not a lord
 *          1 for an aspiring lord
 *          2 for lord level
 *          3 for warlord level
 */
public int query_lord_status(string lord)
{
    lord = capitalize(lord);

    if (lord == "Morrigan")
	return 3;

    if (member_array(lord, m_indexes(members)) == -1)
	return 0;

    /* If this member is a sublord, make him appear as a lord */
    if (member_array(lord, m_indexes(lords)) == -1)
        if (member_array(lord, query_sublords(query_members_lord(lord))) != -1)
        return 2;

    if (member_array(lord, m_indexes(lords)) == -1)
	return 0;

    if (query_number_followers(lord) < LORD_FOLLOWING)
	return 1;

    if (query_number_followers(lord) < WARLORD_FOLLOWING)
	return 2;

    if (query_number_followers(lord) >= WARLORD_FOLLOWING)
	return 3;

    return 0;
}

/*
 * Function   : query_lord_gender()
 * Description: What is the gender of this lord?
 * Arguments  : str: the name of the lord
 * Returns    : 'lady', 'lord', or 'none'
 */
public string query_lord_gender(string str)
{
    str = capitalize(str);

    if (member_array(str, m_indexes(lords)) == -1)
	return "none";

    if (sizeof(lords[str]) < 4)
        return "none";

    return lords[str][3];
}

/*
 * Function   : set_lord_gender()
 * Description: Set the gender of a lord
 * Arguments  : str: the lord, gender: which gender?
 * Returns    : 1 if successful, 0 if not
 */
public int set_lord_gender(string str, string gender)
{
    str = capitalize(str);
    gender = lower_case(gender);

    if (member_array(str, m_indexes(lords)) == -1)
	return 0;

    if (gender != "lord" && gender != "lady")
        return 0;

    if (sizeof(lords[str]) < 4)
        lords[str] += ({ gender });
       else
        lords[str][3] = gender;

    save_object(MERC_SERVER);
    return 1;
}

/*
 * Function   : query_crest_description()
 * Description: Get a description of the crest for this lord
 * Arguments  : str: the name of the lord
 * Returns    : a string with the crest description
 */
public string query_crest_description(string str)
{
    string *vowels = ({ "a", "e", "i", "o", "u" });
    str = capitalize(MCREST->query_members_lord(str));

    if (member_array(str, m_indexes(lords)) == -1)
	return "none";

    if (member_array(extract(lords[str][2], 0, 0), vowels) != -1)
        return "a "+lords[str][0]+" "+lords[str][1]+" on an "+
            lords[str][2]+" background";

    return "a "+lords[str][0]+" "+lords[str][1]+" on a "+
	lords[str][2]+" background";
}

/*
 * Function   : query_crest_lord()
 * Description: Is this a crest lord? (seems to be identical to the
 *              function query_registered_lord())
 * Arguments  : str: the name to check
 * Returns    : 1 if yes, 0 if no
 */
public int query_crest_lord(string str)
{
    str = capitalize(str);

    if (member_array(str, m_indexes(lords)) == -1)
	return 0;

    return 1;
}

/*
 * Function   : query_crest_member()
 * Description: Is this mercenary a member of a cause? Including lords
 * Arguments  : str: the name to check
 * Returns    : 1 if yes, 0 if no
 */
public int query_crest_member(string str)
{
    str = capitalize(str);

    if (member_array(str, m_indexes(members)) == -1)
	return 0;

    return 1;
}

/*
 * Function   : remove_crest_member()
 * Description: remove a member of a cause
 * Arguments  : str: the name of the person
 * Returns    : 1 if removed, 0 if not
 */
public int remove_crest_member(string str)
{
    string lord;
    str = capitalize(str);

    if (member_array(str, m_indexes(members)) == -1)
	return 0;

    lord = capitalize(members[str]);

    if (members[str] != str)
       add_notification(lord, str+" renounced his loyalty to you.\n");

    if (member_array(TP->query_name(), query_sublords(lord)) != -1)
	remove_sublord_member(str);

    members = m_delete(members, str);

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " renounced loyalty to "+
	lord+" by quitting\n");

    save_object(MERC_SERVER);
    return 1;
}

/*
 * Function   : remove_crest_lord()
 * Description: Remove a crest lord, his members, notifications, and applicants
 * Arguments  : str: the lord's name
 * Returns    : 1 if successful, 0 if not
 */
public int remove_crest_lord(string str)
{
    int i;
    string *ind;

    str = capitalize(str);
    lords = m_delete(lords, str);

    /* Clean out members of this house before erasing it */
    ind = m_indexes(members);

    for (i = 0; i < sizeof(ind); i++)
    {
	if (members[ind[i]] == str)
        {
	    members = m_delete(members,ind[i]);

            if (ind[i] != str)
               add_notification(ind[i], str+" is no longer a Mercenary "+
		   "Lord.\n");
	}
    }

    /* Clean up unresolved applications for this house before erasing it */
    ind = m_indexes(applications);
    
    for (i = 0; i < sizeof(ind); i++)
    {
       if (applications[ind[i]] == str)
          applications = m_delete(applications, ind[i]);
	  add_notification(ind[i], str+" is no longer a "+
	      "Mercenary Lord, your application has been removed.\n");
    }

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " dissolved "+ POSSESSIVE(TP)+" following "+
	"by quitting\n");

    save_object(MERC_SERVER);
    return 1;
}