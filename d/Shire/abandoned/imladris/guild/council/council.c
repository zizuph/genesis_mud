/*
 * Those functions I have been granted access to by other domains/guild
 * are commented below here, right above the actual functions.
 * My thanks goes to Glindor (who let me look at the councilcode for kaheda), 
 * Gresolle and Ged who also did the council coding for kaheda, Maniac for letting me
 * take a look at his council code for the calians. The reason for why i had to use some
 * code from the Kaheda is that i didnt know how to do the apply stuff, I have no 
 * experience in using mapping, and I didnt know how to make the vote part either :-/
 * Actually not much there i could do on my own in the first place. I hope to be able to 
 * make my own version of the Imladris council, and thus remove the functions from the 
 * other guilds, not that they are bad, they are excellent.
 * 
 * Sir Odin.
 */

inherit "/d/Shire/room";
#include "cdefs.h"
#include "defs.h"
#include "/secure/std.h"
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>

clean_up_apply();
string list_apply();
//static void create_board();

string 	*council_members = ({ });
//mixed 	new_members;
//mixed	query_new_members();
//void 	add_new_member(string who);
//int 	*chtyp;
int 	council_max;

int *add_council_member(string who);
int *remove_council_member(string who);

mapping apply; 		/* Make a mapping of who is applying for the guild. */
mapping member_map;	/* Members of the council */
mapping apply_map;	/* Mapping who is applying for guild council. */
mixed 	new_members;

query_prevent_snoop()
{
	return 1;
}

public void
create_room()
{
	set_short("The secret council room for the Healers");
	set_long(
			"You are in the heart of Elrond's house. The council room for the Healers\n"+
			"of Imladris. The place is protected by magic put here by the great Shire\n"+
			"wizards and the Guildmaster. Only council members and wizards approved by\n"+
			"the guildmaster is allowed to enter here. On the southern wall you can see\n"+
			"a board where important matters and ideas are discussed. In the middle of\n"+
			"the room is a rather large table with chairs placed around.\n");
	add_prop(ROOM_I_INSIDE, 1);
	add_item("table", "@@table");
	add_exit("/d/Shire/imladris/room/fireroom", "out", 0);

	//banished 		= 	banished_veto = ([]);
	new_members  	=	({});
	apply 			=	([]);
	apply_map		=   ([]);

	restore_object(COUNCIL);
	reset();
}
/*
public void
reset_room()
{
	if (!present("board", TO))
	create_board();
}

static void
create_board()
{
	object board;
	if ((board = clone_object("/d/Shire/imladris/guild/board/council_board"))
	{
		board->set_board_name("/d/Shire/imladris/guild/board/cboard");
		board->set_num_notes(30);
		board->set_anonymous(0);
		board->set_silent(1);
		board->set_show_lvl(1);
		board->set_remove_lvl(16);
		board->set_remove_str("Sorry only for high-leveled wizards and guildmasters!\n");
		board->set_err_log("/d/Shire/imladris/guild/board/board_err");
		board->move(TO);
	}
	return 0;
}
*/
string 
table()
{
	return	
	"There is a list of all available commands carved into the table:\n"+
	"\n"+
	"	- list council		- List all council members\n"+
	"	- list banished		- List all banished players\n"+
	"	- list apply 		- List all applications to the guild\n"+
	"	- accept <name>		- Accept an application to the guild\n"+
	"	- deny <name>		- Deny an application to the guild\n"+
	"	- add <person>		- Add a person to the council\n"+
	"			requires the whole council agreeing on this,\n"+
	"			and please remember to mail your guildmaster\n"+
	"			about this; mail odin,rogon,dunstable\n"+
	"	- banish <name>		- Banish someone from training\n"+
	"	- unbanish <name>	- Remove your banishment on someone\n"+
	"	- veto			- Make an attempt to unbanish a player\n"+
	"				  banished by someone else. Requires 3\n"+ 
	"				  councilmembers to remove the banishment\n\n"+
	"	And the normal postoffice commands are also available here.\n";
}

enter_inv(object to, object from)
{
	string str;
	::enter_inv(to, from);

	if(!strlen(query_ip_number(to)))
	return;

	if	((to->query_wiz_level() &&
		("/secure/master"->query_wiz_dom(to->query_real_name())=="Shire")) 	||
		(to->query_real_name()=="Odin" || to->query_real_name()=="rogon" 	||
		 to->query_real_name()=="Dunstable") || to->query_real_name()=="Rogon")
	{
	if (!present("mailread", to))
		clone_object(MAILREADER)->move(to);
		return;
	}
	to->catch_msg("\nYou are not allowed to enter here. Your actions will be logged!\n\n");
	seteuid(getuid());
	to->move(to->query_def_start());
	log_file("ILLEGAL_MOVE", ctime(time())+": "+to->query_name()+" tried to enter councilroom illegaly.\n");
	return;
}

leave_inv(object ob, object to)
{
	object mailr;

	::leave_inv(ob, to);
	if (mailr = present("mailread", ob))
		mailr->remove_object();
}

string
query_council()
{
	string str;
	int i;

	seteuid(getuid());
	restore_object(COUNCIL);
	if (sizeof(council_members) == 0)
		str = "The Imladris council currently holds no members.\n";
	else if (sizeof(council_members) == 1)
		str = "The Imladris council currently holds the following member: "+
				council_members[0]+".\n";
	else
	{
		str = "The Imladris council hods the following members: ";
		for (i = 0; i < (sizeof(council_members)-1); i++)
		{
			str += council_members[i];
			if (sizeof(council_members) -1 - i > 1)
			str += ", ";
			else
			str += " ";
		}
		str += "and "+ council_members[sizeof(council_members) - 1] +".\n";
	}
	return str;
}

int
is_council_member(string str)
{
	if (!str)
		return 0;
	str = capitalize(lower_case(str));
	seteuid(getuid());
	restore_object(COUNCIL);

	return (member_array(str, council_members) + 1);
}

int
is_guildmaster(object tp)
{
	if("/secure/master"->query_wiz_dom(tp->query_real_name()=="Shire") &&
		(tp->query_real_name()=="Odin" || tp->query_real_name()=="Rogon" ||
		 tp->query_real_name()=="Dunstable"))
	return 1;
	else
	return 0;
}

string
*query_council_members()
{
	seteuid(getuid());
	restore_object(COUNCIL);
	return council_members;
}	

int
add_council_member(string who)
{
	object tp = TP;
	string adder;
	adder = tp->query_name();

	if (!who) return 0;
	who = CAP(lower_case(who));
	seteuid(getuid());	
	restore_object(COUNCIL);
	if (sizeof(council_members) >= MAX_MEMBERS)
	{
		NF("The council is full at the moment.\n");
		return 0;
	}

	if (!(SECURITY->exist_player(lower_case(who))))
	{
		NF("No such player found!\n");
		return 0;
	}
	if (is_council_member(adder) || is_guildmaster(tp))
	{
		council_members += ({ who });
		write(CAP(who)+" has been added to the council.\n");
		who->catch_msg("You are now a mamber of the Imladris council.\n");
		write_file(COUNCIL_LOG, extract(ctime(time()), 4, 15)+" "+ 
		CAP(TP->query_real_name()) +" added "+CAP(who->query_real_name())+" to the council.\n");
		return 1;
	}

	if (is_council_member(who))
	{
		write(CAP(who)+" is already a member of the council.\n");
		return 0;
	}
	
	adder->catch_msg("You do not have authority to do that! You are logged!\n");
	seteuid(getuid());
	log_file("COUNCIL_ILLEGAL", ctime(time())+": "+adder->query_name()+" tried to add "+CAP(who)+" to the council illegaly.\n");
	return 0;		
}

int
remove_council_member(string who)
{
	object tp = TP;
	string remover;

	if(!who) return 0;

	remover = tp->query_name();
	who = CAP(lower_case(who));
	seteuid(getuid());
	restore_object(COUNCIL);

	if(sizeof(council_members) == 0)
	{
		NF("There are currently noon in the council to remove.\n");
		return 0;
	}
	if (!SECURITY->exist_player(lower_case(who)))
	{
		NF("No such player found!\n");
		return 0;
	}

	if (is_council_member(remover) || is_guildmaster(tp))
	{
		if(member_array(who, council_members) > -1)
		{
			council_members -= ({ who });
			save_object(COUNCIL);
			write_file(COUNCIL_LOG, extract(ctime(time()),4,15)+" "+
			CAP(remover->query_real_name())+" removed "+CAP(who->query_real_name())+" from the council.\n");
			tp->catch_msg("Ok.\n");
			return 1;
		}
		else
		{
			NF("No such player currently in the council.\n");
			return 0;
		}	
	
	}
	else
	{
		NF("You do not have authority to do that!\n");
		return 0;
	}
}



/*
 * Functions add_apply(), list_apply(), sorting_fun(), accept_apply(), deny_apply, 
 * clean_up_apply(), remove_apply();
 * is of Roke origin. Thanks to Glindor for letting me have a peek at their council code
 * and also thanks to Ged and Gresolle.
 * Odin.
 */

string
add_apply(string who)
{
	mixed app;

	if (!(app = apply[who]))
	{
		apply = apply + ([who : ({time(), 0, ""})]);
		clean_up_apply();
		save_object(COUNCIL);
		return "Your application has been noted.\n";
	}
	switch (app[APPLY_STATUS])
	{
		case 0:
			app[APPLY_TIME] = time();
			apply[who] = app;
			clean_up_apply();
			save_object(COUNCIL);
			return "Hmm, seems like there already has been put an application by you.\n";
			break;
		case ACCEPT_APPLY:
			return "You have been granted access to the join-room for joining the guild.\n";
			break;
		case DENY_APPLY:
			return "Seems that your application has been denied.\n";
			break;
		}
	
		return "BUG: Please mail odin, rogon, dunstable and report this!\n";
}
		
string
remove_apply(string who)
{
	if (!apply[who])
	return "Shouldn't you make an application before removing it?\n";

	apply = m_delete(apply, who);
	clean_up_apply();
	save_object(COUNCIL);
	return "Your application has now been removed.\n";
}
		
string 
check_apply(string who)
{
	mixed app;

	if(!(app=apply[who]))
		return "You must make an application by typing <apply for guild>.\n";
	
	switch (app[APPLY_STATUS])
	{
		case 0:
			return "There has been no answer yet to your application.\n";
			break;
		case ACCEPT_APPLY:
			return "Your application has been approved by "+ app[APPLY_NAME] +".\n";
			break;
		case DENY_APPLY:
			return "Your application has been denied by "+ app[APPLY_NAME] +".\n";	
	}
	return "BUG: Please mail odin, rogon, dunstable with the line: error checking application.\n";
}

int
check_apply_status(string who)
{
	mixed app;
	
	if (!(app = apply[who]))
	{
		return -1;
	}
	return app[APPLY_STATUS];
}

string 
list_apply()
{
	string 	*apply_arr, result;
	int 	i;
	mixed 	app;
	
	apply_arr = m_indexes(apply_map);
	i = sizeof(apply_arr);

	if (i == 0)
	return "No applications.\n";
	apply_arr = map(apply_arr, "make_cap", TO);
	
	result = "";
	for (i=0; i<sizeof(apply_arr); i++)
	{
		app = apply[apply_arr[i]];
		result += sprintf("%-13s  %s", CAP(apply_arr[i]), ctime(app[APPLY_TIME]));
		switch (app[APPLY_STATUS])
		{
		case 0:
			result += "\n";
			break;
		case ACCEPT_APPLY:
			result += "  : was accepted by "+ app[APPLY_NAME] +".\n";
			break;
		case DENY_APPLY:
			result += "  : was denied by "+ app[APPLY_NAME] +".\n";
		}
	}
	return result;
}

int
sorting_fun(string pl1, string pl2)
{
	int i1, i2;
	i1 = apply[pl1][APPLY_TIME];
	i2 = apply[pl2][APPLY_TIME];
	if (i1 == i2) return 0;
	if (i1 > i2)  return 1;
	else return -1;
}

clean_up_apply()
{
	string *apply_arr;
	int i, tid;
	
	apply_arr = m_indexes(apply);
	tid = time();
	for (i=0; i<sizeof(apply_arr); i++)
	{
		if (tid - apply[apply_arr[i]][APPLY_TIME] > APPLY_KEEP_TIME)
		apply = m_delete(apply, apply_arr[i]);
	}
}

