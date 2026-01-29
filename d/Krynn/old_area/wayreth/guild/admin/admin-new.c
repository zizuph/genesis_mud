/*
 * The Admin object for the Wizards of High Sorecry
 *
 * by Rastlin 950522
 */

/*
 * gMembers = ([
 *               player name : ([
 *                                ({ INTEGER 1 = Apprentice, 0 = Not.
 *                                   STRING Color on robe (TYPE_*)
 *                                   STRING Starting room
 *                                   MAPPING (["dest" : "filename"])
 *                                   MIXED +/- promotions/demotions, mentor
 *                                   3 more positions reserved
 *                                })
 *                             ])
 *            ])
 *
 * gSponsor = ({ 
 *               ({ Sponsor name,
 *                  Who (name),
 *                  Time
 *               })
 *             })
 *
 */

/*
 * TODO:
 *    Security check in restore_player, not everyone should call that func.
 *    Make restore_player send a mail to Krynn when something has been 
 *      restored?
 *    Check a player against the records when he/she logs on, for now,
 *      check the bits, to see if they are what they are, type of robe etc
 *    Security check in add/remove_conclave_member (only from soul)
 *    Security check in set_wohs_head (only from soul)
 *    Make vote routines, there are dummy ones.
 *    remove_wohs_member: Descriptions for removal of items, security check
 *      log when something goes wrong. (Doesn't seem to work)
 *      Start skill-decay
 *    Make the paralyze object for the accept sequence
 *    Make it possible to do 'say <answer>' when asked questions in the seq.
 *    Make apprentice to real wizard
 *    In restore_player, better debug text, not only a number.
 *    Notify guildmasters of wizards loging on
 *   
 */
#pragma no_clone
#pragma no_inherit
#pragma no_shadow

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "../../local.h"
#include <std.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>

// inherit "/std/object";

string *gConclave_members;
mapping gMembers;
string *gBanned = ({});
string gHead = "";
mixed gSponsors = ({});

private static mapping gTitles = ([TYPE_RED : WIZARD_AS_TITLES("Red "),
		TYPE_BLACK : WIZARD_BLACK_M_AS_TITLES("Black "),
		"black female" : WIZARD_BLACK_F_AS_TITLES("Black "),
		TYPE_WHITE : WIZARD_AS_TITLES("White ")]);
private static int gAccept_alarm, 
                   gAccept_seq,
                   gAccept_last_try,
                   gAccept_answer,
                   gFullwiz_alarm,
                   gFullwiz_seq,
                   gSize_wiz_titles = sizeof(gTitles[TYPE_BLACK]),
                   gSize_appr_titles = sizeof(APPRENTICE_AS_M_TITLES);
private static object gAccept_teacher, gNuitari, gLunitari, gSolinari;

public void save_admin();
public int query_wohs_member(mixed who);

/*
 * Function name: create_object
 * Description:   Create the admin object
 */
/*public void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("cloud");
    set_short("shimmering cloud");

    // Restore the save file
    restore_object(ADMINFILE);
}
*/

public void
create()
{
    setuid();
    seteuid(getuid());

    restore_object(ADMINFILE);
}

public string
short()
{
    return "shimmering cloud";
}

static void
recreate(object old_admin)
{
    setuid();
    seteuid(getuid());

    create();
}

/*********************************************************
 * Internal functions
 *********************************************************/
/*
 * Function name: shadow_player
 * Description:   Give the shadow to the player
 * Arguments:     player - The player in question
 * Returns:       True if shadowed, false otherwise
 */
static varargs int
shadow_player(object player, int new_player = 0)
{
    object shadow = clone_object(GOBJ + "occ_shadow");

    if (shadow->shadow_me(player, "occupational", GUILD_TYPE, 
			  GUILD_NAME) != 1)
    {
	SECURITY->do_debug("destroy", shadow);
	return 0;
    }
    return 1; 
}

static void
set_bits(object player, int group, int *bits)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (!bits[i])
            player->clear_bit(group, BIT_BIT1 + i);
        else
	    player->set_bit(group, bits[i]);
    }
}

/*
 * Function name: set_wohs_bits
 * Description:   Set the right bits in the player.
 * Arguments:     player - The player
 */
static void
set_wohs_bits(object player)
{
    mixed data = gMembers[RNAME(player)];

    if (data[ASM_APPRENTICE])
    {
        set_bits(player, BIT_GROUP, ({ 0, 0, BIT_BIT3 }));
	return;
    }
    
    switch(data[ASM_TYPE])
    {
        case TYPE_BLACK:
            set_bits(player, BIT_GROUP, ({ BIT_BIT1, 0, 0 }));
	    break;
	case TYPE_RED:
            set_bits(player, BIT_GROUP, ({ BIT_BIT1, BIT_BIT2, 0 }));
	    break;
	case TYPE_WHITE:
	    set_bits(player, BIT_GROUP, ({ 0, BIT_BIT2, 0 }));
	    break;
    }

    return;
}

void
manual_update_membership(string name)
{
    if (WIZ_CHECK < WIZ_ARCH) return;
    if (!objectp(find_player(lower_case(name)))) return;
    set_wohs_bits(find_player(lower_case(name)));
}

/*********************************************************
 * Conclave functions
 *********************************************************/
/*
 * Function name: set_wohs_head
 * Description:   Set the head of the orders
 * Arguments:     name - The name of the conclave member
 */
public void
set_wohs_head(string name)
{
    gHead = name;
    save_admin();
}

/*
 * Function name: query_wohs_head
 * Description:   Get the head of the orders
 * Returns:       The name of the player
 */
public string
query_wohs_head()
{
    return gHead;
}

/*
 * Function name: add_conclave_member
 * Description:   Make player a new conclave member.
 * Arguments:     player - The player object
 * Returns:       True if everything went ok, false otherwise
 */
public int
add_conclave_member(object player)
{
    gConclave_members += ({ RNAME(player) });

    player->add_cmdsoul(GOBJ + "wohs_cmd_conclave");
    player->update_hooks();

    save_admin();

    return 1;
}
  
/*
 * Function name: remove_conclave_member
 * Description:   Remove a player from conclave.
 * Arguments:     player - The player object
 * Returns:       True if everything went ok, false otherwise
 */
public int
remove_conclave_member(object player)
{
    int pos;
    string name = RNAME(player);

    if ((pos = member_array(name, gConclave_members)) > -1)
    {
        if (name == gHead)
	    gHead = "";

        gConclave_members -= ({ name });
	player->remove_cmdsoul(GOBJ + "wohs_cmd_conclave");
	player->update_hooks();
	save_admin();
	return 1;
    }

    return 0;
}
  
/*
 * Function name: query_conclave_member
 * Description:   Check and see if the player is a member in the
 *                conclave or return all the conclave members.
 * Arguments:     name - The name of the player to check
 * Returns:       True if the player was found, false otherwise.
 *                If not arg given, all members are returned.
 */
public varargs mixed
query_conclave_member(string name = 0)
{
    if (!stringp(name))
        return secure_var(gConclave_members);

    if (member_array(name, gConclave_members) > -1)
        return 1;

    return 0;
}

/*
 * Function name: query_conclave_head
 * Description:   Return the name of the Head of the Order.
 * Arguments:     order - The order asked for.
 * Returns:       A name or False.
 */
public string
query_conclave_head(string order)
{
    int size = sizeof(gConclave_members);

    while (size--)
    {
        if (gMembers[gConclave_members[size]][ASM_TYPE] == order)
	    return gConclave_members[size];
    }
    return 0;
}

/*********************************************************
 * Vote functions
 *********************************************************/
/*
 * Function name: query_vote_head
 * Description:   Check and see if 'player' has enough votes to become
 *                Head of the Orders.
 * Arguments:     player - The player to check
 * Returns:       True if yes, false otherwise.
 */
public int
query_vote_head(object player)
{
    return 1;
}

/*
 * Function name: query_vote_conclave
 * Description:   Check and see if 'player' has enough votes to become
 *                Head of the Order of 'order' robes.
 * Arguments:     player - The player to check
 *                order - The requested order
 * Returns:       True if yes, false otherwise
 */
public int
query_vote_conclave(object player)
{
    return 1;
}

/*********************************************************
 * Various filter functions
 *********************************************************/
public string
filter_addart(string str)
{
    string tmp;

    if (parse_command(L(str), ({}), "'an' / 'a' %s", tmp) == 1)
        return tmp;

    return str;
}

/**************************/
/*
 * Function name: query_member_type
 * Description:   Get the right member type
 * Arguments:     player - The player to check
 * Returns:       The proper color or 0 if not a member
 */
public string
query_member_type(object player)
{
    int bits;

    if (player->test_bit("Krynn", BIT_GROUP, BIT_BIT1))
        bits |= 1;
    if (player->test_bit("Krynn", BIT_GROUP, BIT_BIT2))
        bits |= 2;
    if (player->test_bit("Krynn", BIT_GROUP, BIT_BIT3))
        bits |= 4;

    switch (bits)
    {
        case 1:
            return TYPE_BLACK;
        case 2:
	    return TYPE_WHITE;
        case 3:
	    return TYPE_RED;
        case 4:
	    return TYPE_APPRENTICE;
	default:
            return 0;
    }
    return 0;
}

/*
 * Function name: query_member_order
 * Description:   Get the right member order
 * Arguments:     name - The player name to check
 * Returns:       The proper color or 0 if not a member
 */
public string
query_member_order(string name)
{
    mixed data = gMembers[name];

    if (!data)
        return 0;

    return data[ASM_TYPE];
}

public int
query_size_wizard_titles()
{
    return gSize_wiz_titles;
}

public int
query_size_apprentice_titles()
{
    return gSize_appr_titles;
}

public string
query_title(string order, int level, int sex)
{
    string *titles;

    if (sex == G_FEMALE)
      {
        titles = APPRENTICE_AS_F_TITLES;
	if (order == TYPE_BLACK)
		order += " female";
      }
    else
        titles = APPRENTICE_AS_M_TITLES;

    return (titles + gTitles[order])[level];
}

public int
query_accept_busy()
{
    return gAccept_alarm;
}

public string
query_wohs_god(object player)
{
    switch(gMembers[RNAME(player)][ASM_TYPE])
    {
        case TYPE_BLACK:
	    return "Nuitari";
        case TYPE_RED:
	    return "Lunitari";
        case TYPE_WHITE:
	    return "Solinari";
    }
}

/*
 * Function name:
 *
public nomask string *
query_order_titles(string order, int sex)
{
    switch (order)
    {
       case TYPE_BLACK:
           return (((sex && sex != G_NEUTER) ? 
		    BLACK_F_TITLES : BLACK_M_TITLES));
       case TYPE_WHITE:
           return (((sex && sex != G_NEUTER) ? 
		    WHITE_F_TITLES : WHITE_M_TITLES));
       case TYPE_RED:
           return (((sex && sex != G_NEUTER) ? 
		    RED_F_TITLES : RED_M_TITLES));
    }
}
*/

public int
query_number_levels()
{
    return gSize_wiz_titles + gSize_appr_titles;
}


/*
 * Function name: check_join_player
 * Description:   Make the additional checks, to see if a player is
 *                ok to allow to join.
 * Arguments:     player - The player to check.
 * Returns:       False if ok, otherwise a string with the reason.
 */
public string
check_join_player(object player)
{
    if (player->query_guild_member_lay())
        return "is member of a layman guild. Magic and magic only.";

    if (player->query_average_stat() > 67)
        return "has too much experience to join this guild.";

    if (player->query_average_stat() < 44)
        return "is not experienced enough to join this guild.";

    return 0;
}

/*
 * Function name: restore_player
 * Description:   Check if something is wrong with the player, if 
 *                so make a restoration.
 * Arguments:     player - The player to check
 * Returns:       1 If everything went ok, 0 if bogus membership, -1
 *                if failed to restore.
 */
public int
restore_player(object player)
{
    string occ_name = player->query_guild_name_occ(),
           pl_name = player->query_real_name();
    mixed pers_arr = gMembers[pl_name];
    string restored ="",
	   mentor;
    object robe;
    int reward;

    if (sizeof(pers_arr) < max(ASM_REWARDER,ASM_REWARD))
      return 0;

    mentor = pers_arr[ASM_REWARDER];
    reward = pers_arr[ASM_REWARD];
    
    /* MAKE SECURITY CHECK HERE */

    if (strlen(occ_name) && (occ_name != GUILD_NAME))
        return 0;

    /* Is it a member? */
    if (!query_wohs_member(pl_name))
        return 0;

    /* Check the bits */
    if (!query_member_type(player))
    {
        set_wohs_bits(player);
        restored = "Player lost or had the wrong bits";
    }

    /* Check the shadow */
    if (occ_name != GUILD_NAME)
    {
        if (!shadow_player(player))
            return -1;

        restored = "Player was missing the shadow";
    }

    /* Check for the robe */
    if (!present(GUILD_OBJECT, player))
    {
        robe = clone_object(WGUILD + gMembers[pl_name][ASM_TYPE] + "/robe");
	robe->move(player);
	robe->force_init(player);
        restored = "Player was missing the robe";
    }

    if (reward != 0)
      {
	if(reward > 0)
	  {
    		if (((query_size_apprentice_titles() <=
			(player->query_wohs_level() + reward)) &&
			(query_member_type(player) == TYPE_APPRENTICE)) ||
			((query_number_levels() -
				 player->query_wohs_level() - 1) < reward))
		  {
			player->catch_msg(C(mentor) +" tried to reward "+
				"you, but was too generous.\n");
    			gMembers[pl_name][ASM_REWARD] = 0;
    			gMembers[pl_name][ASM_REWARDER] = "";
		  }
		else
		  {

 		player->change_level_mod(reward);

    		player->catch_msg("You feel a new and refreshing "+
			"power, power given to you by "+C(mentor)+".\n");
    		gMembers[pl_name][ASM_REWARD] = 0;
    		gMembers[pl_name][ASM_REWARDER] = "";
		find_player("karath")->catch_msg(sprintf("%s was "+
			"rewarded %i levels.\n", pl_name, reward));
		  }
	  }
	else
	  {
		if (player->query_wohs_level() == 0)
		  {
			player->catch_msg(C(mentor)+" tried to punish "+
				"you, but you are to low for it to work.\n");
    			gMembers[pl_name][ASM_REWARD] = 0;
    			gMembers[pl_name][ASM_REWARDER] = "";
		  }
		else
		  {
		player->change_level_mod(reward);
    		player->catch_msg("You feel a weakened and drained of "+
			"power, a punishment from "+C(mentor)+".\n");
    		gMembers[pl_name][ASM_REWARD] = 0;
    		gMembers[pl_name][ASM_REWARDER] = "";
		find_player("karath")->catch_msg(sprintf("%s was "+
			"punished %i levels.\n", pl_name, reward));
		  }
	  }
      }
    find_player("karath")->catch_msg(sprintf("-> %s.\n", restored));
    if (strlen(restored))
        player->catch_msg("Hmmm.. It seems that you have been hit by a bug. " +
			  "The Tower of Wayreth has made an automatic " +
			  "restoration. If there still seems to be a " +
			  "problem regarding this guild you should contact " +
			  "a Krynn-wizard or the 'playerarch' team.\n");
    return 1;
}
/*
 * Function name: query_starting_room
 * Description:   Return the starting room of the player
 * Arguments:     name - The name of the player
 * Returns:       A filename or false
 */
public string
query_starting_room(string name)
{
    mixed arr = gMembers[name];

    if (sizeof(arr))
        return arr[ASM_STARTING_ROOM];

    return 0;
}

/*
 * Function name: add_starting_room
 * Description:   Set the starting room of the player
 * Arguments:     name - The name of the player
 *                room - The filename of the room
 * Returns:       True if everything went ok, false otherwise.
 */
public int
add_starting_room(string name, string room)
{
    if (sizeof(gMembers[name]))
    {
        gMembers[name][ASM_STARTING_ROOM] = room;
        save_admin();
	  return 1;
    }
    return 0;
}

/*
 * Function name: remove_starting_room
 * Description:   Remove the starting room of the player
 * Arguments:     name - The name of the player
 * Returns:       True if everything went ok, false otherwise.
 */
public int
remove_starting_room(string name)
{
    if (sizeof(gMembers[name]))
    {
        gMembers[name][ASM_STARTING_ROOM] = 0;
        save_admin();
	  return 1;
    }
    return 0;
}

public int
make_appr_to_real(object player)
{
    mixed data = gMembers[RNAME(player)];
    object book;

    if (data[ASM_APPRENTICE])
    {
        data[ASM_APPRENTICE] = 0;
        set_wohs_bits(player);
	if ( book = present(SPELL_BOOK, E(player)))
	    book->setup_spells(player->query_wohs_level());
	return 1;
    }
    
    return 0;
}

public int
reward_nonpresent_player(string player, int number, object mentor) 
{
    int a;
    mixed data;

    if(!sizeof(data = gMembers[lower_case(player)]))
	return 0;

    if(data[ASM_REWARD])
	return -1;
    data[ASM_REWARD] = a;
    data[ASM_REWARDER] = mentor->query_real_name();
    return 1;
}

/*
 * Function name: query_wohs_destinations
 * Description:   Return an array with the known destinations.
 * Arguments:     player - The player in question
 * Returns:       An array
 */
public string *
query_wohs_destinations(object player)
{
    mixed arr = gMembers[RNAME(player)];
    mapping dests;

    if (sizeof(arr))
    {
        dests = arr[ASM_DESTINATIONS];

        if (!mappingp(dests))
            dests = ([]);

	return m_indexes(dests);
    }

    return ({});
}

/*
 * Function name: query_wohs_destination
 * Description:   Return the filename for a destination
 * Arguments:     player - The player in question
 *                where - The destination
 * Returns:       A filename, or false of error.
 */
public string
query_wohs_destination(object player, string where)
{
    mixed arr = gMembers[RNAME(player)];
    mapping dests;

    if (sizeof(arr))
    {
        dests = arr[ASM_DESTINATIONS];

        if (!mappingp(dests))
            dests = ([]);

	return dests[where];
    }

    return 0;
}

/*
 * Function name: add_wohs_destination
 * Description:   Add a destination to the list
 * Arguments:     player - The player object
 *                what - What it should be remembered as
 */
public void
add_wohs_destination(object player, string what)
{
    mixed arr = gMembers[RNAME(player)];
    mapping dests;

    dump_array("1");
    if (sizeof(arr))
    {
        dests = arr[ASM_DESTINATIONS];
	dump_array(2);

        if (!mappingp(dests))
            dests = ([]);

	dump_array(3);
	dests[what] = file_name(E(player));

	gMembers[RNAME(player)][ASM_DESTINATIONS] = dests;
	dump_array(4);

        save_admin();
    }
}


/*
 * Function name: remove_wohs_destination
 * Description:   Remove a destination from the list
 * Arguments:     player - The player object
 *                which - Which destination that should be removed
 */
public void
remove_wohs_destination(object player, string which)
{    
    mixed arr = gMembers[RNAME(player)];
    mapping dests;

    if (sizeof(arr))
    {
        dests = arr[ASM_DESTINATIONS];

        if (!mappingp(dests))
            dests = ([]);

	dests = m_delete(dests, which);

	gMembers[RNAME(player)][ASM_DESTINATIONS] = dests;
        save_admin();
    }
}

/*
 * Function name: query_wohs_member
 * Description:   Check is the player is a member of the guild
 * Arguments:     who - The player object or the name to check.
 * Returns:       True if member, false otherwise.
 */
public int
query_wohs_member(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();

    /* Yeah, sure! */
    if (!stringp(who) || !strlen(who))
        return 0;

    return (gMembers[who] ? 1 : 0);
}

/*
 * Function name: add_wohs_member
 * Description:   Add a member to the member list
 * Arguments:     who - The player to add
 * Returns:       True if added, false otherwise
 */
static int
add_wohs_member(object who, object sponsor)
{
    object shadow, item;
    string robe;

    if (query_wohs_member(who))
        return 0;

    /* Get the shadow */
    if (!shadow_player(who))
        return 0;

    /* Make apprentice */
    who->set_bit(BIT_GROUP, BIT_BIT3);
    who->clear_guild_stat(SS_OCCUP);
    who->remove_skill(SS_WOHS_LEVEL_MOD);

    /* Get the right robe */
    if (who->query_alignment() > 400)
        robe = TYPE_WHITE;
    else
        if (who->query_alignment() < -400)
	    robe = TYPE_BLACK;
        else
	    robe = TYPE_RED;

    gMembers += ([RNAME(who) : ({ 1, robe, 0, 0, 0, 0, 0, 0, 0 }) ]);

    item = clone_object(WGUILD + robe + "/robe");
    item->move(who);
    item->force_init(who);

    /* Hand out the scroll */
    clone_object(GOBJ + "scroll")->move(who);

    gSponsors += ({ ({ RNAME(sponsor), RNAME(who), time() }) });

    save_admin();

    return 1;
}

/*
 * Function:    remove_wohs_member
 * Description: Remove a member to the member list
 * Arguments:   who - The player to remove from the guild
 *              reason - The reason to why he/she is removed
 * Returns:     True if removed, false otherwise
 */
public int
remove_wohs_member(object who, int reason)
{
    int result;
    object obj;
    string name = RNAME(who), type = gMembers[name][ASM_TYPE],
           reason_str;

    if (!gMembers[name])
        return 0;

    if ((result = who->remove_guild_occ()))
    {
	who->clear_guild_stat(SS_OCCUP);
        set_bits(who, BIT_GROUP, ({ 0, 0, 0 }));
	who->remove_skill(SS_WOHS_LEVEL_MOD);

	if (IS_CONCLAVE(name))
	{
	    remove_conclave_member(who);
	}

	obj = present(GUILD_OBJECT, who);	
	if (objectp(obj))
	{
	    obj->remove_object();
	}

	obj = present(SPELL_BOOK, who);
	if (objectp(obj))
	{
	    obj->remove_object();
	}

	who->remove_cmdsoul(GOBJ + "wohs_cmd_normal");
	who->remove_cmdsoul(WGUILD + type + "/mage_soul");
	who->update_hooks();

	gMembers = m_delete(gMembers, name);

	who->setup_skill_decay();

	save_admin();

	switch(reason)
	{
	    case 0:
	        reason_str = "Leaving the guild";
		tell_room(E(who), "All of a sudden " + QTNAME(who) +
			  " starts to burn, the flames are hot and " +
			  "intense. " + C(PRONOUN(who)) + " slowly " +
			  "dies.\n", who);
		who->catch_msg("Suddenly, you start to get extremely hot. " +
			       "A few seconds later you are burning " +
			       "in white hot flames.\n");
		who->heal_hp(-who->query_hp());
		who->do_die();
		break;
	    case 1:
		reason_str = "Was expelled";
		tell_room(E(who), "All of a sudden " + QTNAME(who) +
			  " starts to burn, the flames are hot and " +
			  "intense. " + C(PRONOUN(who)) + " slowly " +
			  "dies.\n", who);
		who->catch_msg("Suddenly, you start to get extremely hot. " +
			       "A few seconds later you are burning " +
			       "in white hot flames.\n");
		who->heal_hp(-who->query_hp());
		who->do_die();
		break;
	    case 2:
		reason_str = "Was banished";
		gBanned += ({ name });
		tell_room(E(who), "All of a sudden " + QTNAME(who) +
			  " starts to burn, the flammes are hot and " +
			  "intense. " + C(PRONOUN(who)) + " slowly " +
			  "dies.\n", who);
		who->catch_msg("Suddenly you start to get very hot " +
			       "and a few seconds later you are burning " +
			       "in white hot flammes.\n");
		who->heal_hp(-who->query_hp());
		who->do_die();
		break;
	    case 3:
		reason_str = "Left during free-leave time";
		tell_room(E(who), "Suddenly " + QTNAME(who) +
			" fades into nothingness. " + C(PRONOUN(who)) +
			" has left the ways of magic.\n", who);
		who->catch_msg("Suddenly, you feel your grasp over "+
			"magic slip away and you feel yourself in "+
			"a new place.\n");
		who->move(who->query_def_start(), 1);
		break;
	    default:
		reason_str = "UNKNOWN";
	}

	write_file("/d/Krynn/log/guild/wohs/record", ctime(time()) + " " + 
		   C(name) + " was removed. Reason: " + reason_str + ".\n");
	
	return 1;
    }

    return 0;
}

/*
 * Function name: check_banned
 * Description:   Check if a player/name has been banned from the guild.
 * Arguments:     who - The player to test.
 * Returns:       True if banned, otherwise false.
 */
public int
check_banned(object who)
{
    return ((member_array(RNAME(who), gBanned) == -1) ? 0 : 1);
}

public void
save_admin()
{
    save_object(ADMINFILE);
}

/*
 * Only arches, the domain liege and domain wizards with the rank MAGE
 * or higher may use the commands.
 */
public int
valid_wohs_wiz()
{
    if (WIZ_CHECK >= WIZ_ARCH)
        return 1;
    if (WIZ_CHECK < WIZ_MAGE)
        return 0;

    if (this_interactive() != this_player())
        return 0;

    if (SECURITY->query_wiz_dom(RNAME(this_interactive())) != getuid())
        return 0;

    return 1;
}

public void
get_answer(string answer)
{
    if (!strlen(answer))
    {
        input_to(get_answer);
	return;
    }

    answer = lower_case(answer);

    if (answer == "yes") 
    {
        gAccept_answer = 1;
        return;
    }
    else
        if (answer == "no")
	{
	    gAccept_answer = 1;
	    gAccept_seq = -1;
	    return;
	}
        else
	{
            TP->catch_msg("The voice says: Yes or No, will be perfectly " +
			  "okay. Now, try again.\n");
	    input_to(get_answer);
        }
}

public void
get_teacher_name(string name)
{
    object teacher = find_player(lower_case(name));

    tell_room(E(TP), QCTNAME(TP) + " mumbles something that you can't " +
	      "hear.\n", TP);

    if (!objectp(teacher) || !present(teacher, E(TP)) || (teacher == TP))
    {
        if (gAccept_last_try)
	{
	    gAccept_seq = -1;
	    return;
        }

        TP->catch_msg("A dark voice howls in your mind: Don't mock me " +
		      TP->query_name() + ". I can't locate " + C(name) +
		      " here, don't expect me to search the world either. " +
		      "I will give you one last try to get it right. " +
		      "Who wants to teach you?\n");
        TP->catch_msg("You feel someone grasping your lungs, making you " +
		      "unable to breath.\n");
	TP->command("$choke");
	input_to(get_teacher_name, 0);
        gAccept_last_try = 1;
    }
    else
    {
        if (teacher->query_guild_name_occ() == GUILD_NAME)
	{
	    if (query_member_type(teacher) != TYPE_APPRENTICE)
	    {
	        gAccept_teacher = teacher;
		return;
	    }
	}
	gAccept_seq = -1;
    }
}

/*********************************************************
 * Sequences
 *********************************************************/
static void
do_accept_seq(object master, object appr, object env)
{
    string str;
    int tmp;

    if (!master || !present(master, env) ||
	!appr || !present(appr, env))
        gAccept_seq = -1;

    switch(gAccept_seq++)
    {
        case 0:
            tell_room(env, "The dust starts to swirl, the shadows start " +
		      "to move, and the light grows brighter.\n");
            break;
        case 1: break;
        case 2:
	    tell_room(env, "The dust, the shadows and the light seem to " +
		      "form three humanoid figures out of nowhere.\n");
            break;
        case 3: break;
        case 4:
	    tell_room(env, "After a while, you see that the figures are clad " +
		      "in one-colored robes, white, red and black.\n");

	    gNuitari = clone_object(NPC_NUITARI);
	    gLunitari = clone_object(NPC_LUNITARI);
	    gSolinari = clone_object(NPC_SOLINARI);
	    gNuitari->move_living("M", env);
	    gLunitari->move_living("M", env);
	    gSolinari->move_living("M", env);

	    appr->command("$gasp");
	    appr->catch_msg("You are so amazed by what is happening that " +
			    "all you can do is to stand there, and watch in " +
			    "awe.\n");

	    clone_object(ACCEPT_PARALYZE)->move(appr);

            break;
        case 5:
	    tell_room(env, "The spectral bodies shimmer in and out of " +
		      "your vision as if stirred by hot winds.\n");
            break;
	case 6: break;
        case 7:
	    tell_room(env, "The black robed figure drifts over and stops " +
		      "infront of " + QTNAME(appr) + ", who looks upon the " +
		      "figure with horror in " + POSSESSIVE(appr) + 
		      " eyes.\n", appr);
	    appr->catch_msg("The black robed figure starts to drift over " +
			    "to you and stops in front of you. Your " +
			    "eyes widen as you look inside the hood, and " +
			    "you realize there is nothing there.\n");
            break;
        case 8: break;
        case 9:
	    tell_room(env, "The red-robed spectral starts to speak in a " +
		      "loud calm female voice.\n");
	    tell_room(env, "It says: Thou hast summoned us " +
		      C(RNAME(master)) + ", to grant " + C(RNAME(appr)) + 
		      " the ability to use the ancient powers of magic.\n");
            break;
        case 10: break;
	case 11:
	    tell_room(env, "She continues: Before doing so, we must see if " +
		      "thy choice is wise, " + C(RNAME(master)) + ".\n");
	    break;
	case 12: break;
	case 13:
	    tell_room(env, "The black-robed figure in front of " + 
		      C(RNAME(appr)) + ", moves slightly and seems to " +
		      "be staring into " + POSSESSIVE(appr) + " soul.\n", 
		      appr);
	    appr->catch_msg("The black-robed figure infront of you moves " +
			    "slightly. When looking inside its hood, " +
			    "you can see two red-glowing eyes, staring " +
                      "at you with a penentrating glare.\n");
	    break;
	case 14: break;
	case 15:
	    appr->catch_msg("Suddenly you hear a hissing voice in your " +
			    "mind.\n");

	    switch(appr->query_alignment())
	    {
	        case -400..400:
	            str = "red path, this means that thou hast not cared " +
		          "for good nor evil";
	            break;
		case 401..1200:
		    str = "white path, this means that thy life hast been " +
		          "spent fighting the evil of this world";
		    break;
		case -1200..-401:
		    str = "black path, this means that thou has been " +
		          "following mine, the evil one";
		    break;
	    }
	    appr->catch_msg("It hisses: Thou hast been following the " +
			    str + ".\n"); 
	    break;
	case 16: break;
	case 17:
	    tell_room(env, "The red-robed figure calmly says: Thy choice " +
		      "is a wise one, " + C(RNAME(master)) + ". We shall " +
		      "grant " + C(RNAME(appr)) + " the ability to use " +
		      "the ancient powers.\n");
	    break;
	case 18: break;
	case 19:
	    appr->catch_msg("The voice in your mind hisses: Whom hast thou " +
			    "found that is willing to guide and teach thee " +
			    "the ways of the ancient powers, to teach thee " +
			    "how to behave against fellow users of the " +
			    "ancient powers, and to prepare thee for The " +
			    "Test? Answer me that now!\n");

	    set_this_player(appr);
	    input_to(get_teacher_name);
	    break;
	case 20:
	    if (!gAccept_teacher)
	    {
	        gAccept_seq--;
		break;
	    }

	    gAccept_teacher->catch_msg("The black-robed figure turns " +
				       "its head and looks upon you.\n");
	    tell_room(env, "The black-robed figure turns its head and looks " +
		      "upon " + QTNAME(gAccept_teacher) + ".\n",
		      gAccept_teacher);
	    break;
	case 21: break;
	case 22:
	    tell_room(env, "The red-robed figure calmly says: " +
		      C(RNAME(gAccept_teacher)) + ", " + C(RNAME(appr)) + 
		      " says that thou wilst teach " + OBJECTIVE(appr) +
		      " about the ancient powers and to prepare " +
		      OBJECTIVE(appr) + " for The Test. I ask thee now, " +
		      "dost thou want to do so?\n");

	    set_this_player(gAccept_teacher);
	    input_to(get_answer);
	    break;
	case 23:
	    if (!gAccept_answer)
	    {
	        gAccept_seq--;
		break;
	    }

	    tell_room(env, "The white-robed figure says: So be it then.\n");
	    break;
	case 24: break;
	case 25:
	    switch(appr->query_alignment())
	    {
	        case -400..400:
	            str = "red";
	            break;
		case 401..1200:
		    str = "white";
		    break;
		case -1200..-401:
		    str = "black";
		    break;
	    }

	    tell_room(env, "The white-robed figure produces, out of " +
		      "nowhere, a " + str + " robe, a book and a scroll.\n");
	    break;
	case 26: break;
	case 27:
	    tell_room(env, "It gives the items to " + QTNAME(appr) + ", " +
		      "and says: The robe, " + C(RNAME(appr)) + ", " +
		      "is the only armour thou may wear. The book wilst " +
		      "contain thine spells, that thou wilst learn in the " +
		      "coming days. The scroll is only a brief " +
		      "introduction to thy new world.\n", appr);

	    appr->catch_msg("It gives you the items " +
		      "and says: The robe, " + C(RNAME(appr)) + ", " +
		      "is the only armour thou may wear. The book wilst " +
		      "contain thine spells, that thou wilst learn in the " +
		      "comming days. The scroll is only a brief " +
		      "introduction to thy new world.\n", appr);

	    if (!add_wohs_member(appr, gAccept_teacher))
	    {
	        gAccept_seq = -2; /* This will be -1 at the next run */
		tell_room(env, "The white-robed figure groans. " +
			  "I can't add you to the guild. Make a bug-report " +
			  "and summon us later.\n");
		break;
	    }
	    break;
	case 28: break;
	case 29:
	    appr->catch_msg("Suddenly you start to become aware of a " +
			    "new feeling, the feeling of the magic power " +
			    "that binds the world.\n");

	    tell_room(env, QCTNAME(appr) + " shivers slightly.\n", appr);
	    break;
	case 30: break;
	case 31:
	    tell_room(env, "The white-robed figure says: " + C(RNAME(appr)) +
		      ", thou dost not know the meaning of magic. " +
		      "Follow and obey the more experienced wizards, " +
		      "listen to their wise words. We care not for thee, " +
		      "if thou dost not want to learn.\n");
	    break;
	case 32:
	    tell_room(env, "The white-robed figure says: That was it, " +
		      "thou art now a member of the Wizards of High " +
		      "Sorcery, may the magic aid thee in thy life when " +
		      "so requiers.\n");
	    break;
	case 33: break;
	case 34:
	    tell_room(env, "The three figures start to melt back into " +
		      "the room from where they came.\n");
	    appr->catch_msg("With a sudden jolt you are able to move " +
			    "again.\n");

	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gAccept_alarm);
	    gAccept_alarm = 0;
	    break;

        case -1:
	    tell_room(env, "The three figures disappear with a puff of " +
		      "smoke. Leaving all of you totally confused. Maybe " +
		      "someone managed to insult them?\n");

	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gAccept_alarm);
	    gAccept_alarm = 0;
	    break;
    }

    return;
}

public void
accept_seq(object appr)
{
    object env = E(TP);

    if (!CALL_BY(WOHS_CMD_CONCLAVE))
        return;

    gAccept_seq = 0;

    gAccept_alarm = set_alarm(4.0, 5.0, &do_accept_seq(TP, appr, env));
    return;
}

static void
do_endtest_seq(object master, object appr, object env)
{
    string str;
    int tmp;

    if (!master || !present(master, env) ||
	!appr || !present(appr, env))
        gFullwiz_seq = -1;

    switch(gFullwiz_seq++)
    {
        case 0:
            tell_room(env, "The dust starts to swirl, the shadows start " +
		      "to move, and the light grows brighter.\n");
            break;
        case 1: break;
        case 2:
	    tell_room(env, "The dust, the shadows and the light seem to " +
		      "form three humanoid figures out of nowhere.\n");
            break;
        case 3: break;
        case 4:
	    tell_room(env, "After a while, you see that the figures "+
			"are clad in one-colored robes, white, red "+
			"and black.\n");

	    gNuitari = clone_object(NPC_NUITARI);
	    gLunitari = clone_object(NPC_LUNITARI);
	    gSolinari = clone_object(NPC_SOLINARI);
	    gNuitari->move_living("M", env);
	    gLunitari->move_living("M", env);
	    gSolinari->move_living("M", env);

	    appr->catch_msg("You feel your body still itself in the "+
		"presence of such power.\n");
	    clone_object(ACCEPT_PARALYZE)->move(appr);

            break;
        case 5:
	    tell_room(env, "The spectral bodies shimmer in and out of " +
		      "your vision as if stirred by hot winds.\n");
            break;
	case 6: break;
        case 7:
	    tell_room(env, "The black robed figure drifts over and stops " +
		      "infront of " + QTNAME(appr) + ", who looks upon the " +
		      "figure with horror in " + POSSESSIVE(appr) + 
		      " eyes.\n", appr);
	    appr->catch_msg("The black robed figure starts to drift over " +
			    "to you and stops in front of you. Your " +
			    "eyes widen as you look inside the hood, and " +
			    "you realize there is nothing there.\n");
            break;
        case 8: break;
        case 9:
	    tell_room(env, "The red-robed spectral starts to speak in a " +
		      "loud calm female voice.\n");
	    tell_room(env, "It says: Thou hast summoned us " +
		      C(RNAME(master)) + ", to review the learning " +
			"and experience of this apprentice " +
			C(RNAME(appr)) + ".\n");
            break;
        case 10: break;
	case 11:
	    tell_room(env, "She continues: Before an apprentice is " +
		      "allowed to progress to a full wizard, they must "+
		"pass the Test.\n");
	    break;
	case 12:
	    tell_room(env, "She nods slightly to the black-robed figure "+
		"and says: Proceed.\n");
	    break;
	case 13:
	    tell_room(env, "The black-robed figure in front of " + 
		      C(RNAME(appr)) + ", moves slightly and seems to " +
		      "be staring into " + POSSESSIVE(appr) + " soul.\n", 
		      appr);
	    appr->catch_msg("The black-robed figure in front of you moves " +
			    "slightly. When looking inside its hood, " +
			    "you can see two red-glowing eyes, staring " +
                      "at you with a penentrating glare.\n");
	    break;
	case 14: break;
	case 15:
	    appr->catch_msg("Suddenly you hear a hissing voice in your " +
			    "mind.\n");

	    switch(appr->query_prop(TEST_RESULT))
	    {
	        case 0:
		    appr->catch_msg("It hisses: You must be Tested "+
			"before you may become a full mage!\n");
		    tell_room(env, "The black-robed figure looks a "+
			"little annoyed and backs away.\n");
		    gFullwiz_seq = -2;
	            break;
		case TEST_SUCCESS:
		    appr->catch_msg("It hisses: Ahhhh yes. You have "+
			"suffered much for the Art and you have bent "+
			"it to your will while it has bent you and "+
			"you have not broken.\n");
		    tell_room(env, "The black-robed figure looks "+
			"somehow pleased.\n");
		    gFullwiz_seq++; /* paranoia to make sure we are right */
		    break;
		case TEST_SUCCESS_GIFT:
		    appr->catch_msg("It hisses: Ahhhh yes. Your Test "+
			"was more subtle than most, but you have "+
			"succeeded anyway.\n");
		    tell_room(env, "The black-robed figure looks "+
			"somehow pleased.\n");
		    gFullwiz_seq++; /* paranoia to make sure we are right */
		    break;
		case TEST_FAIL_DEMOTE:
		    appr->catch_msg("It hisses: It seems that you were "+
			"too unprepared for the Test. Deal with this "+
			"setback or your life in Magic will be very "+
			"short-lived.\n");
		    tell_room(env, "The black-robed figure grins "+
			"menacingly.\n");
                    gFullwiz_seq = 49;
		    break;
    		case TEST_FAIL_DIE:
		    appr->catch_msg("It hisses: Your failure has earned "+
			"you DEATH weak one. Perhaps you can recover "+
			"if your spirit is stronger than it was during "+
			"the Test.\n");
		    tell_room(env, "The black-robed figure slowly starts "+
			"to raise it's hand.\n");
		    gFullwiz_seq = 59;
		    break;
    		case TEST_FAIL_BANISH:
		    appr->catch_msg("It hisses: Your failure is complete "+
			"and you have proved yourself unworthy of Magic. "+
			"Embrace the void for it is your final resting "+
			"place.\n");
		    tell_room(env, "The black-robed figure starts to "+
			"raise it's hissing voice to a ghastly shriek!\n");
		    gFullwiz_seq = 69;
		    break;
    		default:
		    appr->catch_msg("It hisses: You are flawed! There is "+
			"something amiss!\n");
		    tell_room(env, "The black-robed figure frowns in "+
			"displeasure.\n");
		    gFullwiz_seq = -2;
		    break;
	    }
	    break;
	case 16:
	    /* Something has gone wrong! */
	    tell_room(env, "The figures look questioningly around as if "+
		"something is wrong.\n");
	    gFullwiz_seq = -2;
	    break;
	case 17:
	    tell_room(env, "The red-robed figure calmly says: This " +
		      "apprentice is now worthy, " + C(RNAME(master)) +
		      ". We shall grant " + C(RNAME(appr)) + " the " +
		      "status and abilities of a full mage.\n");
	    break;
	case 18:
	    if (!make_appr_to_real(appr))
	      {
		tell_room(env, "The red-robed figure frowns and "+
			"says: Something is wrong. I cannot make "+
			C(RNAME(appr)) + " a full mage.\n");
		gFullwiz_seq = -2;
		break;
	      }
            tell_room(env, "The red-robed figure announces: So be "+
		"it! From this day forth, "+ C(RNAME(appr)) + " shall "+
		"be counted among the wielders of Magic and may go "+
		"out into the lands and learn through experience "+
		"more than the teachings of a mentor.\n");
	    appr->catch_msg("The red-robed figure smiles at you and "+
		"you feel the power of Magic coursing through your "+
		"body. Your feeling of control seems more complete "+
		"and the wisdom gained in the Test bolsters your "+
		"confidence to face the world alone.\n");
		break;
	case 19:
	    appr->catch_msg("The white-robed figure nods to you and "+
		"turns to the others.\n");
	    tell_room(env, "The three figures slowly fade away.\n");

	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gFullwiz_alarm);
	    gFullwiz_alarm = 0;
	    break;
	case 21: break;
	case 50:
	    tell_room(env, "The red-robed figure announces: You will "+
		"recieve your punishment for failure.\n");
	    appr->catch_msg("The white-robed figure raises it's hand "+
		"towards you and you feel a sharp pain!\n");
	    tell_room(env, "The red-robed figure announces: Study "+
		"again apprentice. For the next failure may not be "+
		"as easily survived.\n");
	    appr->change_level_mod(-3);
	    break;
	case 51:
	    tell_room(env, "The figures cast one last look around and "+
		"fade into nothingness.\n");
	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gFullwiz_alarm);
	    gFullwiz_alarm = 0;
	    break;
	case 60:
	    tell_room(env, "The red-robed figure announces: You will "+
		"recieve your punishment for failure.\n");
	    appr->catch_msg("The white-robed figure raises it's hand "+
		"towards you and you feel a sharp pain!\n");
	    appr->change_level_mod(-3);
	    break;
	case 61:
	    appr->catch_msg("The black-robed figure reaches it's hand "+
		"towards you and you feel something tearing inside of "+
		"you.\n");
	    appr->command("$choke");
	    appr->catch_msg("You feel your ribs cracking and your heart "+
		"bulge under pressure and suddenly burst!\n");
	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    appr->heal_hp(-appr->query_hp());
	    appr->do_die();
	    tell_room(env, "The black-robed figure withdraws.\n");
	    tell_room(env, "As the white-robed figure nods, the red-robed "+
		"figure announces: It is done. May the spirit of " +
		C(RNAME(appr)) + " learn.\n");
	    break;
	case 62:
	    tell_room(env, "The figures slowly fade away.\n");
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gFullwiz_alarm);
	    gFullwiz_alarm = 0;
	    break;
	case 70:
	    tell_room(env, "The red-robed figure is strangely audable "+
		"over the horrible shriek of the black-robed figure. The "+
		"red-robed figure announces: And thus those too weak to "+
		"carry the burden of Magic are released of it.\n");
	    tell_room(env, "The white-robed figure slowly turns away.\n");
	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    remove_wohs_member(appr, 2);
	    tell_room(env, "The figures softly fade away, leaving a "+
		"deathly void behind.\n");
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gFullwiz_alarm);
	    gFullwiz_alarm = 0;
	    break;
        case -1:
	    tell_room(env, "The three figures disappear with a puff of " +
		      "smoke. Leaving all of you totally confused. You " +
		      "feel something went wrong.\n");

	    present(ACCEPT_PARALYZE_NAME, appr)->remove_object();
	    gNuitari->remove_object();
	    gLunitari->remove_object();
	    gSolinari->remove_object();

	    remove_alarm(gFullwiz_alarm);
	    gFullwiz_alarm = 0;
	    break;
    }

    return;
}

public void
endtest_seq(object appr)
{
    object env = E(TP);
    if (!CALL_BY(WOHS_CMD_CONCLAVE) && !(WIZ_CHECK < WIZ_ARCH) )
	return;

    gFullwiz_seq = 0;

    gFullwiz_alarm = set_alarm(4.0, 5.0, &do_endtest_seq(TP, appr, env));
}




/*****************************************/
save_con()
{
    gConclave_members = ({"rastlin", "aridor", "jeremiah"});
    save_object(ADMINFILE);
}
