/*
 * Conclave command object
 * by Aridor, 11/94
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#define  MAX_ACTIONS          6

void
create_object()
{
    set_name("conclave object");
    add_name("commands");
    add_name("object");
    add_name("conclave");
    add_name(CONCLAVE_OBJ);
    set_long("Available commands of the Knight Conclave:\n" +
      "----------------------------------------------------------------------------\n" +
      "degrade  - 'degrade [n] <who> because <reason>'\n" +
      "           Degrade a knight, remove 1 or n sublevel(s) of prestige.\n" +
      "upgrade  - 'upgrade [n] <who> because <reason>'\n" +
      "           Reward a knight, give ~1/3rd sublevel of prestige. For higher\n" +
      "           level knights, this may be as little as 1/6th. For degrade and\n" +
      "           upgrade [n] may be [1.." + MAX_ACTIONS + "], default is 1.\n" +
      "ban      - 'ban <who> because <reason>'\n" +
      "           Ban a knight from the Knighthood! Only black knights may be\n" +
      "           banished.\n" +
      "pardon   - 'pardon <who> because <reason>'\n" +
      "           Pardon a former knight who was cast out of the knighthood. <Who>\n" +
      "           must be logged on. <Who> must usually prove worthiness to rejoin.\n" +
      "disgrace - 'disgrace <who> because <reason>'\n" +
      "           Disgrace a knight, disallow training, team leading and armory room\n" +
      "           access for 2 days playing time.\n" +
      "cforgive  - 'cforgive <who>'\n" +
      "           Forgive a knight the killing of a player or remove a disgrace\n" +
      "           applied to a knight.\n" +
      "appoint  - 'appoint assistant <who>'\n" +
      "           Appoint an assistant. Trying to add someone from another order or\n" +
      "           of a lower sublevel than 8 won't have any effect.\n" +
      "check    - 'check assistants'\n" +
      "           List all assistants of the orders. Assistants may only see\n" +
      "           assistants of their own order.\n" +
      "remove   - 'remove assistant [<who> | me]'\n" +
      "           Remove an appointed assistant. By giving 'me' as argument an\n" +
      "           assistant can remove him/herself.\n" +
      "award    - 'award <who> with <what> because <reason>'\n" +
      "           <what> = [braid | ribband | rose | sword | crown]\n" +
      "           Award a member of the guild. The award is a small object to show\n" +
      "           special contribution to the guild. An award stays with a player\n" +
      "           player for 2 days playing time.\n" +
      "\n" +
      "knlist   - 'knlist'\n" +
      "           A special list of the knights currently logged on.\n" +
      "knightinfo - 'knightinfo <who>'\n" +
      "           Give info about a knight, even when s/he is not logged on.\n" +
      "\n" +
      "Council members can use these commands:\n" +
      "           cforgive, check, remove, award, knlist, knightinfo.\n");
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
    ADA("pardon");
    ADA("degrade");
    ADA("upgrade");
    ADA("ban");
    ADA("disgrace");
    ADA("cforgive");
    ADA("appoint");
    ADA("award");
    ADD("no_assist","remove");
    ADD("check_lists","check");
    ADD("do_list","knlist");
    ADD("do_knightinfo","knightinfo");
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
    return 0;
}

/****************************************************************************
 * pardon a knight who has been banished and allow him back into the knights
 ***************************************************************************/
int
pardon(string str)
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
degrade(string str)
{
    int i, times = 1;
    if (!check_owner_no_assistant())
	return 0;
    NF("Degrade [how often] who because what? (Note: [how often] may only be " +
      "of the interval [1.." + MAX_ACTIONS + "].\n");
    if (!str)
	return 0;
    return (ADMIN)->do_degrade(str);
}

/****************************************************************************
 * upgrade a knight who has done a good deed
 ***************************************************************************/
int
upgrade(string str)
{
    int i, times = 1;
    if (!check_owner_no_assistant())
	return 0;
    NF("Upgrade [how often] who because what? (Note: [how often] may only be " +
      "of the interval [1.." + MAX_ACTIONS + "].\n");
    if (!str)
	return 0;
    return (ADMIN)->do_rewarding(str);
}

/****************************************************************************
 * ban a black knight from the knighthood!
 ***************************************************************************/
int
ban(string str)
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
appoint(string str)
{
    int i, x;
    object who;
    string str1;

    NF("You are not allowed to use this command.\n");
    if (!check_owner_no_assistant())
	return 0;
    if (!TP->query_wiz_level() && TP->query_knight_sublevel() != 11)
	return 0;
    NF("Appoint an assistant or teammember?\n");
    if (sscanf(str,"assistant %s",str1) != 1)
	return 0;

    x = sscanf(str,"%w to team %w as head",str,str1);
    if (x != 2)
    {
	x = sscanf(str,"%w to team %w",str, str1);
	if (x == 2)
	    x = 1;
	else
	    x = 0;
    }
    else
    {
	x = 0;
    }

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
	i = (ADMIN)->add_knight_team(str1, L(str), x, TP->query_name());
	if (i)
	{
	    write("You have appointed "+ C(str) +" "+ (x == 2 ?
		"as the head of " : "to ") +"team '"+str1+"'.\n");
	    who->catch_tell("You have been appointed "+ (x == 2 ?
		"head of " : "to ") + "team '"+str1+"'.\n");
	}
	else
	{
	    NF("Failed to appoint "+ C(str) +" to the team '"+ str1 +"'.\n");
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
    string str1;
    object who;

    if (!check_owner_assistant())
	return 0;
    NF("Remove an assistant?\n");
    if (!str)
	return 0;
    if (sscanf(str,"assistant %s",str1) != 1)
	return 0;

    x = sscanf(str,"%w from team %w",str,str1);

    who = find_player(L(str1));
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
	i = (ADMIN)->rem_knight_team(str1, str, TP->query_name());
	if (i)
	{
	    if (who == TP)
	    {
		write("You remove yourself from the team '"+str1+"'.\n");
	    }
	    else
	    {
		write("Removed "+ C(str) +" from the team '"+str1+"'.\n");
		if (who)
		    who->catch_tell("You have been removed from the "+
			"team '"+str1+"'.\n");
	    }
	}
	else
	{
	    NF("Failed to remove "+C(str)+" from the team '"+str1+"'.\n");
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
disgrace(string str)
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
award(string str)
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
    object *list, *lay = ({ }), *occ = ({ }), ti = this_player();
    int    i, j, busy, lev;
    string spon_str, sqr_str, *sqr, ord;

    notify_fail("Only Conclave members can use this command.\n");
    if (!check_owner_assistant())
	return 0;

    list = filter(users(), "is_knight", this_object());
    lay = filter(list,"is_lay_knight", this_object());
    occ = filter(list,"is_occ_knight", this_object());
    lay = sort_array(lay, "level_greater");
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
    for(i=0;i<sizeof(lay);i++)
    {
	lev = lay[i]->query_knight_level();
	switch(lev)
	{
	case 1: ord = "black";
	    break;
	case 2: ord = "sentry";
	    break;
	default: ord = "none";
	}
	spon_str = (ADMIN)->get_knight_squire(lay[i]);
	sqr_str = "---";
	if (spon_str == "none")
	    spon_str = "---";
	write(sprintf("%-11s %6s     %2d   %-11s %-23s\n",
	    lay[i]->query_name(),ord,lay[i]->query_knight_sublevel(),
	    spon_str, "---"));
    }
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
