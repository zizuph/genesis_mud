/*
 * Conclave command object
 * by Aridor, 11/94
 */

/**
 * Navarre: December 10th 2007
 * Added extra checks to present 0 strings
 * on a few commands that didn't have those checks.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"

#include "../guild.h"
#include <ss_types.h>
#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#define  MAX_ACTIONS          6
#define KNIGHT_S_CONCLAVE_SUCCESSOR "_knight_s_conclave_successor"
#define WIZARD_AS_DIRPATH   "_wizard_as_dirpath"
#define WIZARD_S_LAST_DIR   "_wizard_s_last_dir"
#define WIZARD_S_TAIL_PATH  "_wizard_s_tail_path"
#define WIZARD_I_TAIL_LIMIT "_wizard_i_tail_limit"
#define TAIL_READ_CHUNK (800)

int
do_help(string str)
{
    string name = E(TO)->query_name(), command;

    if (!str)
	return 0;

    if (str == "conclave")
    {
	if (ADMIN->is_conclave(name) || ADMIN->is_grandmaster(name) ||
	    member_array(name, GUILDMASTERS) != -1)
        {
  	    write("Available commands of the Knight Conclave:\n"+
                  "------------------------------------------\n" +
		  "creview      - Review the Conclave Log\n"+
      		  "cdegrade     - Degrade the rank of a Knight\n" +
		  "cupgrade     - Upgrade the rank of a Knight\n" +
   	          "caward       - Award someone for a good deed\n" +
	          "cban         - Ban a Knight from the guild\n" +
		  "cpardon      - Pardon a banned Knight\n" +
		  "cdemote      - Demote a Knight from the Conclave\n"+
		  "cpromote     - Promote a Knight to the Conclave\n"+
		  "cresign      - Resign your Conclave position\n"+
		  "csuccessor   - Name a successor to your position\n"+
		  "cdisgrace    - Disgrace a Knight\n"+
		  "cforgive     - Forgive a disgraced Knight\n" +
		  "cappoint     - Appoint an assistant\n" +
                  "ccheck       - Check the list of assistants\n" +
  	          "cremove      - Remove an assistant or yourself as an assistant\n" +
		  "leaveapprove - Approve an extended leave request\n"+
		  "leavecancel  - Cancel an extended leave request\n"+
  	          "leavelist    - List the approved and requested extended leaves\n"+
		  "leaverequest - Request an extended leave of 28 days\n"+
  	          "knlist       - A detailed list of active Knights\n" +
	          "knightinfo   - Get detailed information on a certain Knight\n\n"+
	          "For more information no a command, use 'help conclave <command>'.\n");
	}
	else
	{
  	    write("Available commands of the Knight Conclave:\n"+
                  "------------------------------------------\n"+
              "caward       - Award someone for a good deed\n" +
	      "cforgive     - Forgive a disgraced Knight\n" +
              "ccheck       - Check the list of assistants\n" +
	      "cremove      - Remove an assistant or yourself as an assistant\n" +
  	      "leavelist    - List the approved and requested extended leaves\n"+
  	      "knlist       - A detailed list of active Knights\n" +
	      "knightinfo   - Get detailed information on a certain Knight\n\n"+
	      "For more information on a command, use 'help conclave <command>'.\n");
	}

        return 1;
    }

    NF("Use 'help conclave' or 'help conclave <command>'.\n");
    if (sscanf(str, "conclave %s", command) != 1)
        return 0;

    switch (command)
    {
	case "leavecancel":
	    write("leavecancel - 'leavecancel <who>'\n"+
		  "               cancel your request or cancel your approval of a request\n");
	    break;
	case "leaverequest":
	    write("leaverequest - 'leaverequest <reason>'\n"+
		  "               request an extended leave of 28 days\n");
	    break;
	case "leaveapprove":
	    write("leaveapprove - 'leaveapprove <who>'\n"+
		  "               approve leave of someone who has requested it\n");
	    break;
	case "leavelist":
	    write("leavelist - 'leavelist'\n"+
		  "            list all leave requests and approved leaves\n");
	    break;
	case "creview":
	    write("creview   - 'creview [actions]'\n"+
		  "           Review the Private Conclave Log in its entirety, or review\n"+
		  "           all actions of a certain type by specifying [actions]. The\n"+
		  "           possible choices are: appointments, awards, banishments,\n"+
		  "           degradations, demotions, disgraces, forgive, leave, pardons,\n"+
		  "           orders, promotions, and upgrades.\n");
	    break;
	case "cdegrade":
	    write("cdegrade  - 'cdegrade [n] <who> because <reason>'\n" +
		  "            Possible choices are [rank/full/half/quarter/tenth/squire/black]\n"+
		  "	       Rank will always lower the Knight to the next lower level\n"+
		  "            The others are approximations based on the current\n"+
		  "            prestige level. Note: 'Full' will usually be more than\n"+
		  "            'rank', because rank gives only the prestige necessary\n"+
		  "            to lower the Knight one rank.\n"+
	          "            Squire or Black will lower the Knight to those levels.\n");
	    break;
	case "cupgrade":
	    write("cupgrade  - 'cupgrade [how] <who> because <reason>'\n" +
		  "            Possible choices are [rank/full/half/quarter/tenth]\n"+
		  "	       Rank will always raise the Knight to the next level\n"+
		  "            The others are approximations based on the current\n"+
		  "            prestige level. Note: 'Full' will usually be more than\n"+
		  "            'rank', because rank gives only the prestige necessary\n"+
		  "            to advance the Knight one rank.\n");
	    break;
	case "cban":
	    write("cban      - 'cban <who> because <reason>' Ban a knight from the Knighthood! " +
      "			  Only black knights may be banished.\n");
	    break;
	case "cpardon":
            write("cpardon   - 'cpardon <who> because <reason>'\n" +
      "           Pardon a former knight who was cast out of the knighthood. <Who>\n" +
      "           must be logged on. <Who> must usually prove worthiness to rejoin.\n");
	    break;
	case "cdisgrace":
	    write("cdisgrace - 'cdisgrace <who> because <reason>'\n" +
      "           Disgrace a knight, disallow training, team leading and armory room\n" +
      "           access for 2 days playing time.\n");
	    break;
	case "cpromote":
	    write("cpromote  - 'cpromote <player> to crown|sword|rose conclave'\n"+
      "           Promote a Knight to Conclave member, requires two votes.\n");
	    break;
	case "cdemote":
	    write("cdemote   - 'cdemote <player> from crown|sword|rose conclave'\n"+
      "           Demote a Conclave member, requires two votes.\n");
	    break;
	case "csuccessor":
	    write("csuccessor- 'csuccessor <player>'\n"+
      "           Name a successor. This person will take your place on the Conclave\n"+
      "           when you resign.\n");
	    break;
	case "cresign":
	    write("cresign   - 'cresign'\n"+
      "           Resign your position. If successor has been used previously, the\n"+
      "           named Knight will take the newly vacated position.\n");
	    break;
	case "cappoint":
	    write("cappoint  - 'cappoint assistant <who>'\n" +
      "           Appoint an assistant. Trying to add someone from another order or\n" +
      "           of a lower sublevel than 10 won't have any effect.\n");
	    break;
	case "ccheck":
	    write("ccheck    - 'ccheck assistants'\n" +
      "           List all assistants of the orders. Assistants may only see\n" +
      "           assistants of their own order.\n");
	    break;
	case "cremove":
	    write("cremove   - 'remove assistant [<who> | me]'\n" +
      "           Remove an appointed assistant. By giving 'me' as argument an\n" +
      "           assistant can remove him/herself.\n");
	    break;
	case "caward":
	    write("caward    - 'caward <who> with <what> because <reason>'\n" +
      "           <what> = [braid | ribband | rose | sword | crown]\n" +
      "           Award a member of the guild. The award is a small object to show\n" +
      "           special contribution to the guild. An award stays with a player\n" +
      "           player for 2 days playing time.\n");
	    break;
	case "cforgive":
	    write("cforgive  - 'cforgive <who>'\n" +
      "           Forgive a knight the killing of a player or remove a disgrace\n" +
      "           applied to a knight.\n");
	    break;
	case "knlist":
	    write("knlist   - 'knlist'\n" +
      "           A special list of the knights currently logged on.\n");
	    break;
        case "knightinfo":
	    write("knightinfo - 'knightinfo <who>'\n" +
      "           Give info about a knight, even when s/he is not logged on.\n");
	    break;
	default:
	    write("No help available for the conclave command "+command+".\n");
	    break;
    }

    return 1;
}

void
create_object()
{
    setuid();
    seteuid(getuid());

    set_long("The conclave object. Use 'help conclave' to see a list of "+
	"commands, or 'help conclave <command>' for help on a specific "+
	"command.\n");
    set_name("conclave object");
    add_name("commands");
    add_name("object");
    add_name("conclave");
    add_name(CONCLAVE_OBJ);

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_MAGIC, 1);
    add_prop(OBJ_M_NO_TELEPORT, 1);
}

void
init()
{
    ADA("kteam");
    ADA("cpardon");
    ADA("cdegrade");
    ADA("cupgrade");
    ADA("cban");
    ADA("cdisgrace");
    ADA("cforgive");
    ADA("cappoint");
    ADA("caward");
    ADA("cpromote");
    ADA("cdemote");
    ADA("csuccessor");
    ADA("cresign");
    ADD("cancel_vacation", "leavecancel");
    ADD("request_vacation", "leaverequest");
    ADD("approve_vacation", "leaveapprove");
    ADD("list_vacation", "leavelist");
    ADD("no_assist","cremove");
    ADD("check_lists","ccheck");
    ADD("do_list","knlist");
    ADD("do_knightinfo","knightinfo");
    ADD("tail_file", "creview");
    ADD("do_help", "help");

    ::init();
}
/***************************************************************************
 * valid user check
 **************************************************************************/
int
check_owner_assistant()
{
    if (E(TO)->query_knight_sublevel() == 11 ||
      (ADMIN)->is_assistant(E(TO)->query_real_name()) ||
      member_array(E(TO)->query_name(), GUILDMASTERS) > -1)
	return 1;
    set_alarm(0.1,0.0,"remove_object");
    return 0;
}

int
check_owner_no_assistant()
{
    if (E(TO)->query_knight_sublevel() == 11 ||
      member_array(E(TO)->query_name(), GUILDMASTERS) > -1)
	return 1;

    //Hack
    return 0;
}

/****************************************************************************
 * add/remove a member from the knight teams
 ***************************************************************************/
public int
kteam(string str)
{
    string who, me, team;
    object targ;

    if (!check_owner_no_assistant())
    {
	return 0;
    }

    if (!str)
    {
	return NF("Syntax: kteam <appoint|remove> <who> <to|from> <team> "+
		"[as leader]\n");
    }

    me = this_player()->query_name();

    if (sscanf(str, "appoint %s to %s as leader", who, team) == 2)
    {
	if (!(targ = find_player(who)) ||
	    !present(targ, environment(this_player())))
	{
	    write("The appointee needs to be present.\n");
	    return 1;
	}

	if (targ->query_knight_sublevel() < 8)
	{
	    write("The appointee is not of an appropriate level.\n");
	    return 1;
	}

	if ((ADMIN)->add_knight_team(team, who, me, 1))
	{
	    write("You appoint "+ C(who) +" as the leader of "+
		"the team '"+ team +"'.\n");
	    tell_object(targ, QCTNAME(this_player()) +" has appointed "+
		"you the leader of the team '"+ team +"'.\n");
	}
	else
	{
	    write("You fail to appoint "+ C(who) +" to the team "+
		"'"+ team +"'.\n");
	}
    }
    else if (sscanf(str, "appoint %s to %s", who, team) == 2)
    {
	if (!(targ = find_player(who)) ||
	    !present(targ, environment(this_player())))
	{
	    write("The appointee needs to be present.\n");
	    return 1;
	}

	if (targ->query_knight_sublevel() < 8)
	{
	    write("The appointee is not of an appropriate level.\n");
	    return 1;
	}

        if ((ADMIN)->add_knight_team(team, who, me, 0))
        {
	    write("You appoint "+ C(who) +" to "+
		"the team '"+ team +"'.\n");
	    tell_object(targ, QCTNAME(this_player()) +" has appointed "+
		"you to the team '"+ team +"'.\n");
        }
	else
	{
	    write("You fail to appoint "+ C(who) +" to the team "+
		"'"+ team +"'.\n");
	}
    }
    else if (sscanf(str, "remove %s from %s", who, team) == 2)
    {
        if ((ADMIN)->rem_knight_team(team, who, me))
        {
	    write("You remove "+ C(who) +" from "+
		"the team '"+ team +"'.\n");
	    tell_object(targ, QCTNAME(this_player()) +" has removed "+
		"you from the team '"+ team +"'.\n");
        }
	else
	{
	    write("You fail to remove "+ C(who) +" from the team "+
		"'"+ team +"'.\n");
	}
    }
    else
    {
        return NF("Syntax: kteam <appoint|remove> <who> <to|from> <team> "+
                "[as leader]\n");
    }
    return 1;
}

/****************************************************************************
 * pardon a knight who has been banished and allow him back into the knights
 ***************************************************************************/
int
cpardon(string str)
{
    int i;
    if (!check_owner_no_assistant())
	return 0;
    NF("Pardon who? because what?\n");
    if (!str)
	return 0;
    return (ADMIN)->do_pardon(str);
}


/****************************************************************************
 * degrade a knight who has misbehaved
 ***************************************************************************/
int
cdegrade(string str)
{
    int i, times = 1;
    if (!check_owner_no_assistant())
	return 0;
    NF("Degrade [how] <who> because <reason>?\n"+
	"Use 'rank/full/half/quarter/tenth/squire/black' for [how].\n");
    if (!str)
	return 0;
    return (ADMIN)->do_degrade(str);
}

/****************************************************************************
 * upgrade a knight who has done a good deed
 ***************************************************************************/
int
cupgrade(string str)
{
    int i, times = 1;
    if (!check_owner_no_assistant())
	return 0;
    NF("Upgrade [how] <who> because <reason>?\n"+
	"Use 'rank/full/half/quarter/tenth' for [how].\n");
    if (!str)
	return 0;
    return (ADMIN)->do_rewarding(str);
}

/****************************************************************************
 * ban a black knight from the knighthood!
 ***************************************************************************/
int
cban(string str)
{
    if (!check_owner_no_assistant())
	return 0;
    NF("Ban who because what? (Note: only Black Knights will be banned).\n");
    if (!str)
	return 0;
    return (ADMIN)->do_banish(str);
}

/****************************************************************************
 * appoint a knight as assistant
 ***************************************************************************/
int
cappoint(string str)
{
    int i, x;
    object who;
    string str1, old;

    NF("You are not allowed to use this command.\n");
    if (!check_owner_no_assistant())
    {
	return 0;
    }

    if(!str)
    {
        NF("Appoint an assistant or teammember?\n");
        return 0;
    }
    if (!TP->query_wiz_level() && TP->query_knight_sublevel() != 11)
    {
	return 0;
    }
    
    old = str;

    x = sscanf(old,"%s to team %s as head",str1,str);
    if (x != 2)
    {
        x = sscanf(old,"%s to team %s",str1, str);
        if (x == 2)
            x = 1;
        else
            x = 0;
    }
    else if (x == 1)
    {
	x = 0;
    }

    NF("Appoint an assistant or teammember?\n");
    if (!x && (sscanf(old,"assistant %s",str1) != 1))
	return 0;

    who = find_player(L(str1));
    NF(C(str1) + " is not a good candidate for the position of your conclave " +
      "assistant.\n");
    if (!who || who->query_knight_level() != TP->query_knight_level() ||
      who->query_knight_sublevel() < 8)/* || who->query_wiz_level()*/
	return 0;
    NF(C(str1) + " is not present in this room.\n");
    if (E(who) != E(TP))
	return 0;
    if (!x)
    {
    NF("Failed to appoint " + C(str1) + " as assistant. You may only have a " +
      "max of 2 assistants at any time.\n");
    i = (ADMIN)->add_assistant(TP, who);
    if (i)
    {
	write("You have appointed " + C(L(str1)) + " as assistant of the " +
	  "conclave.\n");
	who->catch_msg("You have been appointed assistant to the " +
	  "conclave.\n");
    }
    }
    else
    {
        i = (ADMIN)->add_knight_team(str, L(str1), x, TP->query_name());
        if (i)
        {
            write("You have appointed "+ C(str1) +" "+ (x == 2 ?
                "as the head of " : "to ") +"team '"+str+"'.\n");
            who->catch_tell("You have been appointed "+ (x == 2 ?
                "head of " : "to ") + "team '"+str+"'.\n");
        }
        else
        {
            NF("Failed to appoint "+ C(str1) +" to the team '"+ str +"'.\n");
        }
    }
    return i;
}

/****************************************************************************
 * remove a knight as assistant
 ***************************************************************************/
int
no_assist(string str)
{
    int i, x;
    string str1, old;
    object who;

    if (!check_owner_assistant())
	return 0;
    NF("Remove an assistant or teammember?\n");
    if (!str)
	return 0;

    old = str;

    x = sscanf(old,"%s from team %s",str1,str);

    if (sscanf(old,"assistant %s",str1) != 1 && x != 2)
	return 0;

    str1 = L(str1);
    if (str1 == "me")
	str1 = TP->query_real_name();

    if (x != 2)
    {
    NF(C(str1) + " is not of your knight order.\n");
    if ((ADMIN)->is_assistant(str1) != TP->query_knight_level())
	return 0;
    i = (ADMIN)->remove_assistant(TP, str1);
    if (i)
    {
	if (str1 == TP->query_real_name())
	    write("You have resigned from the position of assistant to the " +
	      "Knight conclave.\n");
	else
	{
	    write("You have removed " + C(str1) + " from the position of " +
	      "assistant of the Knight conclave.\n");
	    who = find_player(L(str1));
	    if (who)
		who->catch_msg("You have been removed from the position of " +
		  "assistant to the Knight conclave.\n");
	}
    }
    }
    else
    {
        i = (ADMIN)->rem_knight_team(str, str1, TP->query_name());
        if (i)
        {
            if (who == TP)
            {
                write("You remove yourself from the team '"+str+"'.\n");
            }
            else
            {
                write("Removed "+ C(str1) +" from the team '"+str+"'.\n");
                if (who)
                    who->catch_tell("You have been removed from the "+
                        "team '"+str+"'.\n");
            }
        }
        else
        {
            NF("Failed to remove "+C(str1)+" from the team '"+str+"'.\n");
        }
    }
    return i;
}

/**************************************************************************
 * list assistants to the conclave
 *************************************************************************/
static void
list_order(int order)
{
    string *assistants = (ADMIN)->query_assistants(order);
    string order_name = ({"none","black","squire","crown","sword","rose"})[order];
    int i = -1, size = sizeof(assistants);
    write("Assistants to the " + order_name + " conclave are:\n");
    if (assistants && sizeof(assistants))
    {
	while(++i < size)
	    write(sprintf("   %14-s", C(assistants[i])));
	write("\n");
    }
    else
	write("   None\n");
}

int
check_lists(string str)
{
    string str1;
    int subl, lev;

    if (!check_owner_assistant())
	return 0;
    NF("Check your assistants or applicants?\n");
    if (str == "assistants")
    {
	lev = TP->query_knight_level();
	subl = TP->query_knight_sublevel();
	if (subl == 11 || member_array(TP->query_name(), GUILDMASTERS) >= 0)
	{
	    list_order(3);
	    list_order(4);
	    list_order(5);
	}
	else
	    list_order(lev);
	return 1;
    }
    return 0;
}

/**************************************************************************
 * disgrace a knight (thus putting a ban on the 'invite' command and
 *                    training)
 *************************************************************************/
int
cdisgrace(string str)
{
    if (!check_owner_no_assistant())
	return 0;
    NF("Disgrace who because what?\n");
    if (!str)
	return 0;
    return (ADMIN)->do_disgrace(str);
}

/**************************************************************************
 * forgive a knight the act of pkilling (thus lifting the ban on invite
 *                                       and training)
 *************************************************************************/
int
cforgive(string str)
{
    if (!check_owner_assistant())
	return 0;
    NF("Forgive who?\n");
    if (!str)
	return 0;
    return (ADMIN)->do_forgive(str);
}


/**************************************************************************
 * award a knight with an award
 *************************************************************************/
int
caward(string str)
{
    if (!check_owner_assistant())
	return 0;

    /*
    NF("Only conclave may use this command.\n");
    if (!TP->query_wiz_level() &&
	TP->query_knight_sublevel() < 11)
      return 0;
      */
    NF("Award who with what because what?\n");
    if (!str)
	return 0;
    return (ADMIN)->do_award(str);
}


/**************************************************************************
 * a special knightlist for the conclave
 *************************************************************************/
int
is_knight(object ob)
{
    return ob->query_guild_member(GUILD_NAME);
}

/*
int
is_lay_knight(object ob)
{
    return (ob->query_guild_name_lay() == GUILD_NAME_LAY &&
	    ob->query_guild_name_occ() != GUILD_NAME &&
	    !ob->query_invis());
}
*/

int
is_occ_knight(object ob)
{
    return (ob->query_guild_name_occ() == GUILD_NAME &&
      !ob->query_invis());
}

int
level_greater(object ob1, object ob2)
{
    int i1 = ob1->query_knight_level() * 100 + ob1->query_knight_sublevel();
    int i2 = ob2->query_knight_level() * 100 + ob2->query_knight_sublevel();
    if (i1 > i2)
	return -1;
    else if (i1 == i2)
	return 0;
    else
	return 1;
}

int
do_list(string str)
{
    object *list, *occ = ({ }), ti = this_player();
    int    i, j, busy, lev;
    string spon_str, sqr_str, *sqr, ord;

    notify_fail("Only Conclave members can use this command.\n");
    if (!check_owner_assistant())
	return 0;

    list = filter(users(), "is_knight", this_object());
    occ = filter(list,"is_occ_knight", this_object());
    occ = sort_array(occ, "level_greater");
    write("Name         Order Sublevel Sponsor     Squire(s)\n");
    write("---------------------------------------------------------------\n");
    for(i=0;i<sizeof(occ);i++)
    {
	lev = occ[i]->query_knight_level();
	switch(lev)
	{
	case 1: ord = "black";
	    break;
	case 2: ord = "squire";
	    break;
	case 3: ord = "crown";
	    break;
	case 4: ord = "sword";
	    break;
	case 5: ord = "rose";
	    break;
	default: ord = "none";
	}
	spon_str = (ADMIN)->get_knight_squire(occ[i]);
	sqr = (ADMIN)->get_squire_knight(occ[i]);
	sqr_str = "";
	if (spon_str == "none")
	    spon_str = "---";
	for(j=0;j<sizeof(sqr);j++)
	    sqr_str += sqr[j] + " ";
	if (sqr_str == "none ")
	    sqr_str = "---";
	write(sprintf("%-11s %6s     %2d   %-11s %-23s\n",
	    occ[i]->query_name(),ord,occ[i]->query_knight_sublevel(),
	    spon_str, sqr_str));
    }
    write("---------------------------------------------------------------\n");
    return 1;
}

/**************************************************************************
 * a special knightinfo check for the conclave to inform about knights
 * who are not logged in.
 *************************************************************************/

int
do_knightinfo(string str)
{
    string sponsor;
    string *squires;
    string order_s, type;
    int order;

    if (!check_owner_assistant())
	return 0;

    NF("Knightinfo who?\n");
    if (!str)
	return 0;

    order = (ADMIN)->query_knight_status(str);
    sponsor = (ADMIN)->get_knight_squire_s(str);
    squires = (ADMIN)->get_squire_knight_s(str);

    if (!order)
    {
	write(C(str) + " is not a member of the Knights of Solamnia.\n");
	return 1;
    }

    if (order < 10)
	type = "occupational";
    else
	type = "layman";

    if (order % 10 == 1)
	order_s = "Black Knight";
    else if (order % 10 == 2)
	order_s = "Squire";
    else if (order % 10 == 3)
	order_s = "Crown Knight";
    else if (order % 10 == 4)
	order_s = "Sword Knight";
    else if (order % 10 == 5)
	order_s = "Rose Knight";
    else
	order_s = "Bugged Knight";

    write(C(str) + ": " + order_s + " in the " + type + " branch.\n");
    if (order % 10 < 3)
	write("           Sponsor: " + sponsor + ".\n");
    else
	write("           Squires: " + sprintf(" %12@s",squires) +
	  ".\n");
    return 1;
}

/* Functions from the knightroom incorporated to this command object */

/* Promote a conclave member - it takes two conclave votes */
int
cpromote(string str)
{
    NF("Promote <player> to crown|sword|rose conclave.\n");
    if (!str)
	return 0;

    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
    {
	write("You have no such power!\n");
	return 1;
    }

    return ADMIN->do_promote(str);
}

/* Demote a conclave member - it takes two conclave votes */
int
cdemote(string str)
{
    NF("Promote <player> to crown|sword|rose conclave.\n");
    if (!str)
	return 0;

    if (member_array(TP->query_name(),GUILDMASTERS) == -1 && 
	TP->query_knight_sublevel() != 11)
    {
	write("You have no such power!\n");
	return 1;
    }
    
    return (ADMIN)->do_demote(str);
}

/*allows a conclave to name his/her successor in the position */
int
csuccessor(string str)
{
    NF("Try: 'successor <knight>'\n");
    if (!str)
        return 0;

    if (TP->query_knight_sublevel() != 11 && TP->query_name() != "Morrigan")
    {
        NF("You are not a Conclave member!\n");
        return 0;
    }

    seteuid(getuid());

    NF("The Grandmaster is not chosen by way of named successor.\n");
    if (ADMIN->is_grandmaster(E(TO)->query_name()))
 	return 0;

/*
    NF("This command is not available during armageddon.\n");
    if (SECURITY->shutdown_active())
        return 0; 
 */

    NF(C(str)+" is not a Knight of Solamnia.\n");
    if (!ADMIN->query_knight_status(L(str)))
	return 0;

    NF("The player must be of the same order as you.\n");
    if (ADMIN->query_knight_status(L(str)) != E(TO)->query_knight_level())
        return 0;

/*
    NF("Your successor must have enough prestige to become Conclave.\n");
    if (who->query_level_up(who->query_skill(SS_PRESTIGE_ST)) < 11)
        return 0;
*/

    E(TO)->add_prop(KNIGHT_S_CONCLAVE_SUCCESSOR, L(str));

    write("You have selected " + C(str) + " to be your successor as conclave.\n" +
        "Issuing the 'resign' before you log out will result in your chosen "+
	"successor being promoted to your Conclave position.\n");
    say(QCTNAME(TP) + " has selected " + C(str) + " as successor in the Conclave.\n");
    return 1;
}

/* allows a player to resign from the conclave */
int
cresign(string str)
{
    string succ, order;

    if (TP->query_knight_sublevel() != 11)
    {
        NF("You are not a conclave member!\n");
        return 0;
    }

    if ((ADMIN)->is_grandmaster(TP->query_name()))
    {
	(ADMIN)->remove_grandmaster();
	return 1;
    }

    if (TP->query_prop(KNIGHT_S_CONCLAVE_SUCCESSOR))
    {
	succ = TP->query_prop(KNIGHT_S_CONCLAVE_SUCCESSOR);

        if (TP->query_knight_level() == 3)
	    order = "crown";
	else if (TP->query_knight_level() == 4)
	    order = "sword";
	else if (TP->query_knight_level() == 5)
	    order = "rose";
	else // this should never happen!
	    order = "none";

	TP->clear_high(TP->query_knight_level());
        if (find_living(succ))
        {
            (ADMIN)->notify_conclave("ADMIN: "+TP->query_name()+" resigned the Conclave and has "+
		    "named "+C(succ)+" as the successor.");
	    find_living(succ)->set_high(TP->query_knight_level());
        }
	else
        {
	    (ADMIN)->notify_knight(succ, "You have been promoted to the Conclave!");
	    (ADMIN)->notify_conclave("ADMIN: "+TP->query_name()+" resigned the Conclave and has "+
		    "named "+C(succ)+" as the successor.");
	    (ADMIN)->add_conclave(C(succ), order);
	}

        return 1;
    }

    TP->clear_high(TP->query_knight_level());    
    return 1;
}


/* Functions for requesting extended vacation */
public int
request_vacation(string str)
{
    string name = L(TP->query_name());
    NF("Request leave for what reason?\n");    
    if (!str)
	return 0;

    NF("You may not use this command.\n");
    if (!ADMIN->is_conclave(E(TO)->query_name()) &&
	!ADMIN->is_grandmaster(E(TO)->query_name()) &&
	member_array(E(TO)->query_name(), GUILDMASTERS) == -1)
	return 0;

    if (ADMIN->query_extended_leave_excuse(name) != "no")
    {
	write("You have already requested an extended leave "+
	    "because "+ADMIN->query_extended_leave_excuse(name)+". You "+
	    "must cancel that request first.\n");
	return 1;
    }

    ADMIN->request_extended_leave(name, str);
    write("You request an extended leave because "+str+". This request "+
	"must be approved by another Conclave member or the Grand Master "+
	"to be valid.\n");
    return 1;
}

public int
approve_vacation(string str)
{
    string name = L(TP->query_name());

    NF("Approve leave for whom?\n");    
    if (!str)
	return 0;

    str = L(str);

    NF("You may not use this command.\n");
    if (!ADMIN->is_conclave(E(TO)->query_name()) &&
	!ADMIN->is_grandmaster(E(TO)->query_name()) &&
	member_array(E(TO)->query_name(), GUILDMASTERS) == -1)
	return 0;

    if (ADMIN->query_extended_leave_excuse(str) == "no")
    {
	write(C(str)+" has not requested extended leave.\n");
	return 1;
    }

    if (ADMIN->query_extended_leave_approver() != "no")
    {
	write(C(str)+"'s request was already approved by "+
	    ADMIN->query_extended_leave_approver()+".\n");
	return 1;
    }

    if (str == name)
    {
	write("You cannot approve your own request!\n");
	return 1;
    }

    ADMIN->approve_extended_leave(str, name);
    write("You approve "+C(str)+"'s request for extended leave.\n");
    return 1;
}

public int
cancel_vacation(string str)
{
    string name = L(TP->query_name());

    NF("Cancel a leave, or leave request for whom?\n");    
    if (!str)
	return 0;

    str = L(str);

    NF("You may not use this command.\n");
    if (!ADMIN->is_conclave(E(TO)->query_name()) &&
	!ADMIN->is_grandmaster(E(TO)->query_name()) &&
	member_array(E(TO)->query_name(), GUILDMASTERS) == -1)
	return 0;

    if (ADMIN->query_extended_leave_excuse(str) == "no")
    {
	write(C(str)+" has not requested extended leave.\n");
	return 1;
    }

    if (ADMIN->query_extended_leave_approver(str) == "no" &&
	str != name)
    {
	write("Only "+C(str)+" can cancel their own leave request.\n");
	return 1;
    }

    if (ADMIN->query_extended_leave_approver(str) != name &&
	str != name)
    {
	write(C(str)+"'s request may only be cancelled by "+C(str)+ " or "+
	    C(ADMIN->query_extended_leave_approver(str))+".\n");
	return 1;
    }

    ADMIN->remove_extended_leave(str, name);
    write("You remove "+C(str)+"'s request for extended leave.\n");
    return 1;
}

public int
list_vacation(string str)
{
    string tmp;
    int i = 0;

    NF("You may not use this command.\n");
    if (!ADMIN->is_conclave(E(TO)->query_name()) &&
	!ADMIN->is_grandmaster(E(TO)->query_name()) &&
	member_array(E(TO)->query_name(), GUILDMASTERS) == -1)
	return 0;

    if (TP->query_name() == "Morrigan")
    {
        if (ADMIN->query_extended_leave("morrigan") != "no")
 	{
  	    write(" - "+ADMIN->query_extended_leave("morrigan")+"\n");
	    i = 1;
	}
    }

    if (strlen(tmp = ADMIN->query_conclave("crown")))
    {
        if (ADMIN->query_extended_leave(L(tmp)) != "no")
 	{
  	    write(" - "+ADMIN->query_extended_leave(L(tmp))+"\n");
	    i = 1;
	}
    }

    if (strlen(tmp = ADMIN->query_conclave("sword")))
    {
        if (ADMIN->query_extended_leave(L(tmp)) != "no")
 	{
  	    write(" - "+ADMIN->query_extended_leave(L(tmp))+"\n");
	    i = 1;
	}
    }

    if (strlen(tmp = ADMIN->query_conclave("rose")))
    {
        if (ADMIN->query_extended_leave(L(tmp)) != "no")
 	{
  	    write(" - "+ADMIN->query_extended_leave(L(tmp))+"\n");
	    i = 1;
	}
    }

    if (strlen(tmp = ADMIN->query_grandmaster()))
    {
        if (ADMIN->query_extended_leave(L(tmp)) != "no")
 	{
  	    write(" - "+ADMIN->query_extended_leave(L(tmp))+"\n");
	    i = 1;
	}
    }

    if (!i)
        write("There are currently no scheduled leaves, or requests for leaves.\n");

    return 1;
}
  
/* Functions to view the Conclave log in reverse order (tail -r) */

nomask public void
reopen_this_soul()
{
    object ob  = previous_object();
    string fun = calling_function();

    /* Check carefully. */
    /*
    if ((!strlen(REOPEN_SOUL_ALLOWED[fun])) ||
        (file_name(ob) != REOPEN_SOUL_ALLOWED[fun]) ||
        (!interactive(this_object())))
    {
        return;
    }
    */

    ob->open_soul(0);
    export_uid(ob);
    ob->open_soul(1);
    call_other(ob, "tail_knight_log_reloaded");
    ob->open_soul(0);
}

/*
 * Function name: tail_input_player
 * Description  : Input function for the "tail -r" command. We call the
 *                function reload_soul in the player to get an euid into
 *                the soul again and then display more text.
 * Arguments    : string str - the input-argument.
 */
nomask void
tail_knight_log(string str)
{
    str = (strlen(str) ? lower_case(str) : "u");

    switch(str[0])
    {
    case 'q':
    case 'x':
        /* Clean up after ourselves. */
        this_interactive()->remove_prop(WIZARD_S_TAIL_PATH);
        this_interactive()->remove_prop(WIZARD_I_TAIL_LIMIT);
        return;

    case 'u':
        call_other(TO, "reopen_this_soul");
        return;

    default:
        write("Invalid command. \"q/x\" to quit or RETURN to continue --- ");
        input_to(tail_knight_log);
        return;
    }

    write("Impossible end of tail_input_player() in the apprentice soul.\n" +
      "Notify the administration.\n");
}

/*
 * Function name: tail_lines
 * Description  : This function will actually print a part of the file that
 *                the wizard wants to tail.
 */
private void
tail_knight_lines()
{
    string path  = this_interactive()->query_prop(WIZARD_S_TAIL_PATH);
    int    size  = file_size(path);
    int    limit = this_interactive()->query_prop(WIZARD_I_TAIL_LIMIT);
    int    begin = limit - TAIL_READ_CHUNK;
    string text;
    string *lines;

    /* If we reach the begin of the file, stop. */
    if (begin <= 0)
    {
        text = read_bytes(path, 0, limit);
        write(text + "BOF\n");
        this_interactive()->remove_prop(WIZARD_S_TAIL_PATH);
        this_interactive()->remove_prop(WIZARD_I_TAIL_LIMIT);
        return;
    }

    text = read_bytes(path, begin, TAIL_READ_CHUNK);
    lines = explode(text, "\n");

    /* If there is at least one line, only print the complete lines. */
    if (sizeof(lines) > 1)
    {
        text = implode(lines[1..], "\n");
    }

    write(text + "\n");
    limit -= (strlen(text) + 1);
    write("TAIL " + limit + "/" + size + " (" + (100 * limit / size) + "%)" +
      " --- \"q/x\" to quit, RETURN to continue --- ");

    this_interactive()->add_prop(WIZARD_I_TAIL_LIMIT, limit);
    input_to(tail_knight_log);
}

/*
 * Function name: tail_input_player_reloaded
 * Description  : When the euid of this object has been set to the euid
 *                of the wizard again, print more of the file.
 */
public nomask void
tail_knight_log_reloaded()
{

    if ((previous_object() != this_object()) ||
      (calling_function() != "reopen_this_soul"))
    {
        write("Illegal call to tail_input_player_reloaded().\n");
        return;
    }

    tail_knight_lines();
}

nomask int
tail_file(string str)
{
    int reverse;
    int size;
    string path;


    NF("You may not use this command.\n");
    if (!ADMIN->is_conclave(E(TO)->query_name()) &&
	!ADMIN->is_grandmaster(E(TO)->query_name()) &&
	member_array(E(TO)->query_name(), GUILDMASTERS) == -1 &&
	!check_owner_assistant())
	return 0;

    if (!str)
        path = KLOG + "allactions";
    else if (str == "appointments")
        path = KLOG + "appointments";
    else if (str == "awards")
        path = KLOG + "award";
    else if (str == "banishments")
        path = KLOG + "banishment";
    else if (str == "degradations" || str == "degrades")
        path = KLOG + "degradation";
    else if (str == "demotions")
	path = KLOG + "demotion";
    else if (str == "disgraces")
        path = KLOG + "disgrace";
    else if (str == "forgive")
	path = KLOG + "forgive";
    else if (str == "leave")
	path = KLOG + "leave";
    else if (str == "pardons")
	path = KLOG + "pardon";
    else if (str == "promotions")
        path = KLOG + "promotion";
    else if (str == "upgrades")
	path = KLOG + "upgrade";
    else if (str == "orders")
	path = KLOG + "order";
    else
        path = "";

    if (!stringp(path))
    {
        notify_fail("Syntax: creview [which-log]\n");
        return 0;
    }

    reverse = sscanf(path, "-r %s", path);

    if (!strlen(path))
    {
        notify_fail("Invalid log to review: " + str+ ". See 'help conclave creview'.\n");
        return 0;
    }

    if (!(SECURITY->valid_read(path, geteuid(), "tail")))
    {
        notify_fail("You have no read access to: " + path + "\n");
        return 0;
    }

    size = file_size(path);
    if (size <= 0)
    {
        notify_fail("Invalid log to review: " + str + ". See 'help conclave creview'.\n");
        return 0;
    }

    /* The normal tail command without the -r argument. */
    /*
    if (!reverse)
    {
        if (tail(path))
        {
            return 1;
        }

        notify_fail("No such file: " + path + "\n");
        return 0;
    }
    */

    /* If the file is too small, print the whole file. */
    if (size <= TAIL_READ_CHUNK)
    {
        cat(path);
        return 1;
    }

    /* Add the relevant information to the player in properties. */
    this_interactive()->add_prop(WIZARD_S_TAIL_PATH, path);
    this_interactive()->add_prop(WIZARD_I_TAIL_LIMIT, size);
    tail_knight_lines();    
    return 1;
}
