/*
 * /d/Genesis/guilds/merc/room/crest_room.c
 *
 * Mercenary Lord Crest Room, by Morrigan 11/2001
 *
 */


inherit "/std/room";

#include "../merc.h"
#include "room.h"

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

public void cleanup_list();
public string query_members_lord(string lord);

mapping lords = ([ ]);
mapping members = ([ ]);
mapping applications = ([ ]);
mapping notifications = ([ ]);
mapping private_racks = ([ ]);

object npc;

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
        save_object(MERC_CREST);
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
        save_object(MERC_CREST);
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
    save_object(MERC_CREST);

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

    save_object(MERC_CREST);
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

    save_object(MERC_CREST);
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

    save_object(MERC_CREST);
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

    save_object(MERC_CREST);
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

    save_object(MERC_CREST);
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

    save_object(MERC_CREST);
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

    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : reset_room()
 * Description: resets the room
 */
reset_room()
{
    if (!npc && !present("bryce", this_object()))
    {
        npc = clone_object(MNPC+"bryce");
	npc->move(TO);
    }
}

/*
 * Function   : create_room()
 * Description: You guessed it, creates a room
 */
create_room()
{
    set_short("A busy room");
    set_long("The room is bustling with activity as seamstresses "+
        "work on tabards of all colors and designs. Several others "+
        "oversee the work, making sure the work is done correctly. "+
    "On the walls are many pictures with various figures on them, "+
    "and in many colours. "+
        "You notice a vacant desk in the center of the room.\n");
     add_item("desk", "A desk sits in the center of the room "+
      "with a large book upon it.\n");
    add_cmd_item("book", "read", "@@book_desc");
    add_cmd_item("poster", "read", "The poster reads: 'request "+
	"tabard' or 'return tabard' here.\n");
    add_item("poster", "The poster reads: 'request tabard' or "+
	"'return tabard' here.\n");
    add_item(({"colors", "colours"}), "@@list_colours");
    add_item(({"emblems", "figures", "pictures"}), "@@list_emblems");
    add_item("book", "@@book_desc");
    add_cmd_item("book", "read", "@@book_desc");
    add_exit(MROOM+"west_hall.c", "north");
    seteuid(getuid(TO));
    reset_room();
    restore_object(MERC_CREST);

    cleanup_list();
}

/*
 * Function   : init()
 * Description: Initializes a room
 */
init()
{
    ::init();

    add_action("announce_successor", "announce");
    add_action("declare_crest", "declare");
    add_action("renounce_lord", "renounce");
    add_action("accept_member", "accept");
    add_action("remove_member", "remove");
    add_action("erase_crest", "erase");
    add_action("list_members", "list");
    add_action("apply_lord", "apply");
    add_action("cancel_application", "cancel");
    add_action("request_tabard", "request");
    add_action("return_tabard", "return");
    add_action("bestow_lordship", "bestow");
    add_action("revoke_lordship", "revoke");
}

string list_colours()
{
    return "You see many colors, including "+COMPOSITE_WORDS(colors)+".\n";
}

string list_emblems()
{
    return "You see several pictures of emblems, such as a "+
	COMPOSITE_WORDS(emblems)+".\n";
}

string
book_desc()
{
    return "The Book of Lords.\n\n"+
    "Lord Mercenaries may:\n"+
    " - <declare> a crest with the following syntax:\n"+
    "     'declare color1 emblem color2' where color1\n"+
    "     is the foreground and color2 the background\n"+
    " - <accept>/<remove> mercenary\n"+
    " - <erase> your crest and rejoin your former lord\n"+
    " - <list> applicants to your cause\n"+
    " - <bestow>/<revoke> lordship to a member\n"+
    " - <announce> a successor to your cause (this means\n"+
    "   you will no longer be lord of the cause)\n"+
    "Mercenaries with a Lord may:\n"+
    " - <renounce> their house\n"+
    "All Mercenaries may:\n"+
    " - <apply> to a lord's cause\n"+
    " - <cancel> their application to a cause\n"+
    " - <list> information on lords with the key words\n"+
    "   'lords', 'crests', 'status', or detailed information\n"+
    "   on a particular lord using that lord's name.\n"+
    " - <request> or <return> a tabard\n";
;
}

/*
 * Function name: cleanup_list
 * Description  : Remove not allowed from list after 4 months
 *                Remove names of non-existant players
 */
public void 
cleanup_list()
{
    int i, size;
    string *names;

    names = m_indexes(notifications);
    /* Remove non-mercenary players from the list. */
    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        if (MJOIN->query_member(names[i]) == 0)
	{
            notifications = m_delete(notifications, names[i]);
	    save_object(MERC_CREST);
	}
    }

    names = m_indexes(members);
    /* Remove non-existant players from the list. */
    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        if (!SECURITY->exist_player(names[i]))
        {
            remove_crest_member(names[i]);

            write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
                (TP->query_name()) + " purged from memberlist\n");
	}
    }

    names = m_indexes(lords);
    /* Remove non-existant players from the list. */
    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        if (!SECURITY->exist_player(names[i]))
	{
            remove_crest_lord(names[i]);

            write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
                (TP->query_name()) + " purged from lordlist\n");
	}
    }
}

/*
 * Function   : return_tabard()
 * Description: Returns a tabard
 * Arguments  : str: the string following the verb 'return'
 * Returns    : 1 if returned, 0 if not
 */
int return_tabard(string str)
{
    object tabard;

    NF("Return what? The tabard?\n");
    if (!str || str != "tabard")
	return 0;

    NF("You have no tabard to return.\n");
    if (!objectp(tabard = present(TABARD_ID, TP)))
	return 0;

    if (tabard->query_draped())
	tabard->undrape_shield_silently();

    write("You return the tabard.\n");
    say(QCTNAME(TP)+" returns the tabard.\n");
    tabard->remove_object();
    return 1;
}    

/*
 * Function   : request_tabard()
 * Description: Request a tabard
 * Arguments  : str: the string following 'request'
 * Returns    : 1 if you get one, 0 if you do not
 */
int
request_tabard(string str)
{
    object tabard;

    NF("Order what? A tabard?\n");
    if (!str || str != "tabard")
	return 0;

    NF("You have a tabard already. You can't have more than one! "+
	"You can return yours, if you no longer want it.\n");
    if (present(TABARD_ID, TP) && 
	!MCREST->query_registered_lord(TP->query_name()))
	return 0;
    
    setuid();
    seteuid(getuid());

    NF("You serve no Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(members)) < 0)
    {
	tabard = clone_object(TABARD);
	tabard->set_lord("Maligant");
	tabard->set_crest("red", "dragon", "black");
	tabard->move(TP);
    }
   else
    {
    tabard = clone_object(TABARD);
    tabard->set_lord(members[TP->query_name()]);
    tabard->set_crest(lords[members[TP->query_name()]][0],
		      lords[members[TP->query_name()]][1],
		      lords[members[TP->query_name()]][2]);
    tabard->move(TP);
    }

    write("You are given a tabard with a crest of a "+
	tabard->query_crest_desc()+".\n");
    say(QCTNAME(TP)+" is given a tabard with a crest of a "+
	tabard->query_crest_desc()+".\n");
    return 1;
}

/*
 * Function   : remove_member()
 * Description: Remove a member by an action from a mortal
 * Arguments  : str: the string following the verb
 * Returns    : 1 if removed, 0 if not
 */
int
remove_member(string str)
{
    str = capitalize(str);

    NF("You are not a Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	return 0;

    NF("Remove which mercenary from your cause?\n");
    if (!str)
	return 0;

    NF(str+" does not serve your cause.\n");
    if (member_array(str, m_indexes(members)) == -1 ||
      members[str] != TP->query_name())
	return 0;

    if (member_array(str, query_sublords(query_members_lord(str))) != -1)
	remove_sublord_member(str);

    add_notification(str, TP->query_name()+" removed you from "+POSSESSIVE(TP)+
	" service.\n");
    members = m_delete(members, str);

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " removed "+str+" from "+POSSESSIVE(TP)+
	" cause\n");

    write("You remove "+str+" from your cause.\n");
    say(QCTNAME(TP)+" erases a name from the book on the desk.\n");
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : apply_lord()
 * Description: Apply to join the cause of a lord
 * Arguments  : str: the string following the verb
 * Returns    : 1 if applied successfully, 0 if not
 */
int
apply_lord(string str)
{

    NF("Apply to serve which mercenary lord?\n");
    if (!str)
	return 0;

    NF("You aren't a mercenary!\n");
    if (!IS_MERC(TP))
        return 0;

    str = capitalize(str);

    NF("You already serve a Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(members)) >= 0)
	return 0;

    NF("There is no Lord named "+str+".\n");
    if (member_array(str, m_indexes(lords)) == -1)
	return 0;

    NF("You are not ready to join a Lord yet.\n");
    if (!CAN_JOIN_LORD(TP))
        return 0;

    if (member_array(TP->query_name(), m_indexes(applications)) >= 0)
    {
        write("Before applying to serve "+str+" you remove your "+
	    "application to "+applications[TP->query_name()]+".\n");
        applications = m_delete(applications, TP->query_name());
    }

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " applied to join "+str+"'s cause\n");

    write("You apply to serve "+str+".\n");
    add_notification(str, TP->query_name()+" applied for service to you.\n");
    applications += ([ TP->query_name() : str ]);
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : cancel_application()
 * Description: Cancel one's application
 * Arguments  : str: the string that follows the verb
 * Returns    : 1 if cancelled, 0 if not
 */
int
cancel_application(string str)
{

    NF("Cancel what? Your application?\n");
    if (!str && str != "application" && str != "my application")
	return 0;

    if (member_array(TP->query_name(), m_indexes(applications)) == -1)
    {
        write("You have no applications pending.\n");
        return 1;
    }

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " removed "+POSSESSIVE(TP)+" application "+
	"to "+applications[TP->query_name()]+"\n");

    add_notification(applications[TP->query_name()], TP->query_name()+
	" cancelled "+POSSESSIVE(TP)+" application to you.\n");
    applications = m_delete(applications, TP->query_name());
    write("You cancel your application to join a cause.\n");
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : accept_member()
 * Description: A lord tries to accept a member to his cause
 * Arguments  : str: string following verb
 * Returns    : 1 if accepted, 0 if not
 */
int
accept_member(string str)
{
    string fam;

    str = capitalize(str);

    NF("You are not a Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	return 0;

    NF("Accept which mercenary?\n");
    if (!str)
	return 0;

    NF(str+" has not applied to join your cause.\n");
    if (member_array(str, m_indexes(applications)) == -1 )
	return 0;

    if (applications[str] != TP->query_name())
	return 0;

    NF(str+" serves another lord already!\n");
    if (member_array(str, m_indexes(members)) >= 0)
    {
        applications = m_delete(applications, str);
        save_object(MERC_CREST);
	return 0;
    }

    applications = m_delete(applications, str);
    members += ([ str : TP->query_name() ]);
    add_notification(str, TP->query_name()+" accepted you into "+
	POSSESSIVE(TP)+" service.\n");

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " accepted "+str+"'s application to join "+
	POSSESSIVE(TP)+" cause\n");

    write("You accept "+str+"'s application to your "+
	"cause.\n");
    say(QCTNAME(TP)+" adds a name to the book on the desk.\n");
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : renounce_lord()
 * Description: A member tries to quit a lord's cause
 * Arguments  : str: string following verb
 * Returns    : 1 if successful, 0 if not
 */
int
renounce_lord(string str)
{
    string name, lord;

    NF("Renounce what? Your Lord?\n");
    if (!str)
	return 0;

    if (str != "loyalty" && str != "lord" &&	
        str != members[TP->query_name()] &&
	str != lower_case(members[TP->query_name()]))
	return 0;

    NF("A mercenary lord may not renounce himself, although he can "+
	"erase his crest.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) != -1)
	return 0;

    NF("You have not pledged loyalty to a Lord.\n");
    if (member_array(TP->query_name(), m_indexes(members)) == -1)
	return 0;

    lord = members[TP->query_name()];

    if (IS_MERC_SUBLORD(TP))
        remove_sublord_member(TP->query_name());

    members = m_delete(members, TP->query_name());
    add_notification(lord, TP->query_name()+" renounced his loyalty to you.\n");

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " renounced loyalty to "+lord+"\n");

    save_object(MERC_CREST);
    write("You renounce your lord.\n");
    say(QCTNAME(TP)+" erases "+POSSESSIVE(TP)+" name from the book "+
	"on the desk.\n");
    return 1;
}

/*
 * Function   : declare_crest()
 * Description: a mercenaries declares his crest
 * Arguments  : str: string following verb
 * Returns    : 1 if successful, 0 if not
 */
int
declare_crest(string str)
{
    int i;
    string fg, em, bg, gender;

    NF("You are not a mercenary.\n");
    if (!IS_MERC(TP) && !TP->query_wiz_level())
	return 0;

    NF("You are not ready to become a mercenary lord.\n");
    if (TP->query_stat(SS_OCCUP) < LORD_LEVEL && !TP->query_wiz_level())
        return 0;

    NF("Declare a crest?\n");
    if (!str)
	return 0;

    i = sscanf(str, "%s %s %s", fg, em, bg);

    NF("The syntax is: declare <foreground_colour> <emblem> "+
	"<background_colour>\n");
    if (i != 3)
        return 0;

    NF("Your foreground colour selection is invalid.\n");
    if (member_array(fg, colors) == -1)
        return 0;

    NF("Your emblem selection is invalid.\n");
    if (member_array(em, emblems) == -1)
        return 0;

    NF("Your background colour selection is invalid.\n");
    if (member_array(bg, colors) == -1)
        return 0;

    NF("Maligant would surely object to you using his crest!\n");
    if (fg == "red" && em == "dragon" && bg == "black")
	return 0;

    NF("You are already a Mercenary Lord, you must erase your crest before "+
	"you can declare another.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) != -1)
	return 0;

    NF("You have chosen to serve the Mercenary Lord "+
	members[TP->query_name()]+" already, you must renounce him "+
	"before you can become a lord yourself.\n");
    if (member_array(TP->query_name(), m_indexes(members)) >= 0)
	return 0;

    gender = (TP->query_gender() == 1 ? "lady" : "lord");
    lords += ([ TP->query_name() : ({ fg, em, bg, gender }) ]);
    members += ([ TP->query_name() : TP->query_name() ]);
    save_object(MERC_CREST);

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " declares "+POSSESSIVE(TP)+" cause!\n");

    write("You declare yourself a Mercenary Lord, with a "+fg+" "+
	em+" on a "+bg+" background as your crest.\n");
    say(QCTNAME(TP)+" fills in the title of a blank page in the "+
      "book.\n");
    return 1;
}

/*
 * Function   : erase_crest()
 * Description: A lord erases his crest and kills his cause
 * Arguments  : str: string following verb
 * Returns    : 1 if successful, 0 if not
 */
int erase_crest(string str)
{
    string *ind;
    int i;

    NF("Erase what? Your crest?\n");
    if (!str)
	return 0;

    if (str != "crest" && str != "my crest")
	return 0;

    NF("You have no crest declared.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	return 0;

    NF("Only the lord may erase his crest.\n");
    if (members[TP->query_name()] != TP->query_name())
	return 0;

    lords = m_delete(lords, TP->query_name());

    /* Clean out members of this house before erasing it */
    ind = m_indexes(members);

    for (i = 0; i < sizeof(ind); i++)
    {
	if (members[ind[i]] == TP->query_name())
        {
	    members = m_delete(members,ind[i]);

            if (ind[i] != TP->query_name())
               add_notification(ind[i], TP->query_name()+" has disolved "+
   		   POSSESSIVE(TP)+" following and status as a Mercenary "+
		   "Lord.\n");
	}
    }

    /* Clean up unresolved applications for this house before erasing it */
    ind = m_indexes(applications);
    
    for (i = 0; i < sizeof(ind); i++)
    {
       if (applications[ind[i]] == TP->query_name())
          applications = m_delete(applications, ind[i]);
	  add_notification(ind[i], TP->query_name()+" is no longer a "+
	      "Mercenary Lord, your application has been removed.\n");
    }

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " dissolves "+POSSESSIVE(TP)+" following\n");

    write("You erase your house, tearing the page out of the book.\n");
    say(QCTNAME(TP)+" tears a page from the book on the desk.\n");
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : format_output()
 * Description: format a list of strings to one string
 * Arguments  : output: an array of strings
 * Returns    : the formatted string
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
 * Function   : list_members()
 * Description: list information
 * Arguments  : str: what information to list
 * Returns    : the information
 */
int list_members(string str)
{
    string text, gender;
    string *ind, *list = ({ });
    int i;

    if (!str)
	str = "lords";

    if (str == "crest" || str == "crests")
    {
	     ind = m_indexes(lords);

        ind = sort_array(ind);

        write("Registered Crests:\n");

        for (i=0;i<sizeof(ind);i++)
        {
            text = query_crest_description(ind[i]);
	         write(sprintf(" %-15s : %-50s",ind[i],text)+"\n");
	     }

	     return 1;
    }

    if (str == "status" || str == "lords by status")
    {
	ind = m_indexes(lords);

        ind = sort_array(ind);

        write("Status of all Lords and aspiring Lords:\n");

        for (i=0;i<sizeof(ind);i++)
        {
            gender = MCREST->query_lord_gender(ind[i]);
            if (gender == "none")
        	gender = "lord";

            if (query_lord_status(ind[i]) == 1)
		text = "Aspiring "+C(gender)+" Mercenary";
	    else if (query_lord_status(ind[i]) == 2)
		text = C(gender)+" of Mercenaries";
	    else if (query_lord_status(ind[i]) == 3)
		text = "War"+gender+" of the Mercenaries";

	    write(sprintf(" %-15s : %-20s",ind[i],text)+"\n");
	}

	return 1;
    }

    if (str == "lords")
    {
	ind = m_indexes(lords);

        if (sizeof(ind) <= 0)
	{
	    write("There are currently no Mercenary Lords other than "+
		"Maligant.\n");
	    return 1;
        }

	ind = sort_array(ind);
	write("Current Mercenary Lords:"+format_output(ind));
	return 1;
    }

    if (str == "applicants")
    {
        NF("You are not a mercenary lord, and thus have no applicants.\n");
        if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	    return 0;

        NF("You have no applicants currently.\n");
        if (member_array(TP->query_name(), m_values(applications)) == -1)
	    return 0;

        ind = m_indexes(applications);

        for (i=0;i<sizeof(ind);i++)
	    if (applications[ind[i]] == TP->query_name())
		list += ({ ind[i] });

        write("The following mercenaries have applied to your cause:"+
	    format_output(list));
	return 1;
    }

    NF("There is no record of a Mercenary Lord named "+capitalize(str)+".\n");
    if (member_array(capitalize(str), m_indexes(lords)) >= 0)
	str = capitalize(str);
       else
	return 0;

    ind = m_indexes(members);
    for (i = 0; i < sizeof(ind); i++)
    {
	if (members[ind[i]] == str)
	    list += ({ ind[i] });
    }

    gender = MCREST->query_lord_gender(str);
    if (gender == "none")
	gender = "lord";

    if (query_lord_status(str) == 1)
	text = "Aspiring "+C(gender)+" Mercenary";
       else if (query_lord_status(str) == 2)
	text = C(gender)+" of Mercenaries";
       else if (query_lord_status(str) == 3)
	text = "War"+gender+" of the Mercenaries";

    say(QCTNAME(TP)+" glances at a page in the book.\n");
    write("\n"+
	  "     Mercenary: "+str+"\n");
    write("        Status: "+text+"\n");
    write("         Crest: "+lords[str][0]+" "+lords[str][1]+" on a "+
	lords[str][2]+" background\n");

    if (query_has_sublords(str))
        write("         Lords: "+COMPOSITE_WORDS(query_sublords(str))+"\n");

    list -= ({ str });
    list -= query_sublords(str);
    list = sort_array(list);

    if (!sizeof(list))
        write("   Mercenaries: No followers.\n");
       else
        write("   Mercenaries: "+format_output(list)+"\n");

    return 1;
}

/*
 * Function   : announce_successor()
 * Description: A lord retires and announces his successor
 * Arguments  : str: the string following verb
 * Returns    : 1 if successful, 0 if not
 */
int announce_successor(string str)
{
    string fg, em, bg;
    string *ind;
    int i;

    str = capitalize(str);

    NF("You are not a Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	return 0;

    NF("Announce whom as your successor?\n");
    if (!str)
	return 0;

    NF(str+" does not serve your cause.\n");
    if (member_array(str, m_indexes(members)) == -1 ||
      members[str] != TP->query_name())
	return 0;

    /* Add the new lord before removing the old lord */

    /* Give the new lord notification of this event */
    add_notification(str, TP->query_name()+" has announced you as "+
	POSSESSIVE(TP)+ " successor, you now govern the cause.\n");

    /* Add his own member entry */
    members[str] = str;

    /* Add his lord entry */
    fg = lords[TP->query_name()][0];
    em = lords[TP->query_name()][1];
    bg = lords[TP->query_name()][2];
    lords += ([ str : ({ fg, em, bg }) ]);
    
    /* Change cause members to new lord */
    ind = m_indexes(members);

    for (i = 0; i < sizeof(ind); i++)
    {
	if (members[ind[i]] == TP->query_name())
        {
	    members[ind[i]] = str;

            if (ind[i] != TP->query_name())
               add_notification(ind[i], TP->query_name()+" has announced "+
		   str+" as "+POSSESSIVE(TP)+" successor to the cause.\n");
	}
    }

    /* Change applicants of the cause to the new lord */
    ind = m_indexes(applications);
    
    for (i = 0; i < sizeof(ind); i++)
    {
       if (applications[ind[i]] == TP->query_name())
          applications[ind[i]] = str;
	  add_notification(ind[i], TP->query_name()+" has announced that "+
	      str+" is "+POSSESSIVE(TP)+" successor. You should contact "+
	      "the new lord for matters relevant to your application.\n");
    }

    /* Remove the old Lord entry */
    lords = m_delete(lords, TP->query_name());

    write_file(MERC_CAUSES, extract(ctime(time()), 4, 15) + " " +
        (TP->query_name()) + " announced "+str+" as "+POSSESSIVE(TP)+
	" successor\n");

    write("You announce "+str+" as your successor and are no longer "+
	"lord of the cause.\n");
    say(QCTNAME(TP)+" announces a successor to "+POSSESSIVE(TP)+
	" cause.\n");
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : bestow_lordship()
 * Description: A lord bestows lordship on a follower
 * Arguments  : str: the string following verb
 * Returns    : 1 if successful, 0 if not
 */
int bestow_lordship(string str)
{
    str = capitalize(str);

    NF("You are not a Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	return 0;

    NF("Bestow lordship upon whom?\n");
    if (!str)
	return 0;

    NF(str+" does not serve your cause.\n");
    if (member_array(str, m_indexes(members)) == -1 ||
      members[str] != TP->query_name())
	return 0;

    NF("Your following is not yet great enough for you to bestow lordship upon another.\n");
    if (query_max_sublords(TP->query_name()) == 0)
	return 0;

    if (query_has_sublords(TP->query_name()) && sizeof(query_sublords(TP->query_name())) >=
	query_max_sublords(TP->query_name()))
    {
	NF("Your following already has the maximum number of lords serving in it.\n");
	return 0;
    }

    NF("You have already bestowed lordship upon "+str+".\n");
    if (member_array(str, query_sublords(TP->query_name())) != -1)
        return 0;

    write("You bestow lordship upon "+str+".\n");
    say(QCTNAME(TP)+" writes something in the book.\n");

    add_sublord_member(str, TP->query_name());
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : revoke_lordship()
 * Description: A lord revokes the status of his sublord
 * Arguments  : str: the string following verb
 * Returns    : 1 if successful, 0 if not
 */
int revoke_lordship(string str)
{
    str = capitalize(str);

    NF("You are not a Mercenary Lord.\n");
    if (member_array(TP->query_name(), m_indexes(lords)) == -1)
	return 0;

    NF("Revoke lordship from whom?\n");
    if (!str)
	return 0;

    NF(str+" does not serve your cause.\n");
    if (member_array(str, m_indexes(members)) == -1 ||
      members[str] != TP->query_name())
	return 0;

    NF("You have not bestowed lordship upon "+str+".\n");
    if (member_array(str, query_sublords(TP->query_name())) == -1)
        return 0;

    write("You revoke the status of lord from "+str+".\n");
    say(QCTNAME(TP)+" erases something from the book.\n");

    remove_sublord_member(str);
    save_object(MERC_CREST);
    return 1;
}

/*
 * Function   : wiz_tell()
 * Description: Let a wizard know how to add/remove colours/emblems
 * Arguments  : ob: the wizard
 * Returns    : void
 */
void wiz_tell(object ob)
{
        ob->catch_tell("As a wizard, you may add and remove colours and "+
	    "emblems to the lists. Use 'Call here add_colour/remove_colour "+
	    "add_emblem/remove_emblem <colour/emblem>'.\n");
}

/*
 * Function   : enter_inv()
 * Description: Enter this inventory
 * Arguments  : of: who is enterring, from: from where are they enterring
 * Returns    : void
 */
void enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_wiz_level())
        set_alarm(1.0, 0.0, "wiz_tell", ob);
}
