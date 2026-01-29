/* This is the master room of the cabal of Hiddukel.
 *
 * All data of the guild members plus data for/of the Ringleader
 * are handled and stored here. 
 *
 * ~Aridor 02/96
 *
* Removed council support which hasn't been used... forever.
 * Louie Dec 2005
 *
 */
#pragma no_inherit
#pragma no_clone
#pragma save_binary


#include <language.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include "guild.h"
#define SAVE_FILE       LOG + "master"
#define JOIN_FILE       LOG + "next_join"

inherit ROOM_BASE

mixed* actions = ({});
mapping thieflist = ([]);
/* format: name:({ layman(0), guildstat, guildexp, reserved }) */
string tmaster = "kilrayne";
string* right_hand = ({});
static string header = 0;
mapping punishlist = ([]);
int next_join;

void
create_thief_room()
{
    set_short("an empty cell");
    set_long("You are in an empty room, actually more like a cell and the " +
	     "only option you have is to leave out again, unless of course, you " +
	     "intend to 'stay'.\n");
    add_exit(GUILDR + "start","out");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    restore_object(SAVE_FILE);
    set_alarm(10.0,0.0,"check_members");
}

void
init()
{

    ADA("stay");
    ADA("tpunish");
    ADA("texpel");
    ADA("tpass");
    ADA("righthand");
    ADA("nextjoin");
    ADA("allthieves");
    ADA("thieflist");
    ADA("masternote");
    ADA("rread");
    ADA("rsend");

    ::init();
}

void
check_members()
{
    /* In this function we need to get rid of all members who have been deleted from the game. */
    int i;
    string *namelist = m_indexes(thieflist);
    
    if (!namelist || !sizeof(namelist))
      return;
    
    for(i=0;i<sizeof(namelist);i++)
      if (!(SECURITY->exist_player(namelist[i])))
	thieflist = m_delete(thieflist, namelist[i]);
}


public nomask int
is_master(object who)
{
    if (!objectp(who))
      return 0;
    return (who->query_real_name() == tmaster ||
	    member_array(who->query_name(), GUILDMASTERS) >= 0);
}

public nomask string
query_master_thief()
{
    return tmaster;
}

public nomask int
query_right_hand(object who)
{
    if (member_array(who->query_name(),right_hand) >= 0)
      return 1;
    else
      return 0;
}

public nomask int
query_member_number()
{
    return m_sizeof(thieflist);
}

public nomask int
stay(string str)
{
    NF("What?\n");
    if (!is_master(TP))
      return 0;

    write("You decide to stay here for a while.\n" +
	  "These are the commands you can use here:\n" +
	  " rread         - Read mail to 'Ringleader' from guildmembers.\n" +
	  " rsend         - Write a mail to someone as 'Ringleader'.\n" +
	  " masternote    - Write a note as 'Ringleader' on the guild board.\n" +
	  " tpunish       - Punish a member of the guild (malus on steal for\n" +
	  "                 2 days + reduction of the guild level).\n" +
	  " texpel        - Expel a member from the guild (will result in death of member).\n" +
	  " tpass         - Pass the Ringleader position onto someone else!\n" +
	  "                 Please do not just retire from the master position\n" +
	  "                 (by leaving the guild/game) without selecting a successor.\n" +
	  " righthand     - Select a Right Hand for your support or remove. The member\n" +
	  "                 receives the official title of \"Right Hand\".\n" +
	  " nextjoin      - Show the time after which the next person can join.\n" +
	  " allthieves    - Will give a list of all members of the guild.\n" +
	  " thieflist     - Give a list of the members currently logged in.\n" +
	  " You can remove any notes from the guild board\n" +
	  "     (use the remove command at the board).\n" +
	  " You can use the tpunish and texpel command, even when the thief is not logged in.\n" +
	  " For the tpass command, however, your successor must be logged in at the time.\n" +
	  " Note that your position as Ringleader is secret! No member of the Cabal, nor anyone\n" +
	  " else for that matter, should ever know your identity. Especially watch out when\n" +
	  " writing a note or a mail with 'rsend', or when you enter this room for people can\n" +
	  " see you take the special exit!\n" +
	  " Rejoining the guild is possible by doing one of the two contact persons (wandering\n" +
	  " merchants) of the guild which walk the realm a small favor.\n" +
	  "If you have any questions or suggestions, contact the guildmaster via mail.\n");

    return 1;
}

int
nextjoin(string str)
{
    NF("What?\n");
    if (!is_master(TP))
      return 0;
    
    save_object(SAVE_FILE);
    restore_object(JOIN_FILE);
    write("The next new member can join after: " + ctime(next_join) + ".\n");
    restore_object(SAVE_FILE);
    return 1;
}

string
check_wizard(string th)
{
    return th+(SECURITY->query_wiz_rank(th) ? "(wizard)" : "");
}

int
allthieves(string str)
{
    string to_write;
    string *thlist;
    int size;
    int scrw;
    
    NF("What?\n");
    /* test here if allowed to use*/
    if (!is_master(TP))
      return 0;
    
    size = m_sizeof(thieflist);
    if (size == 0)
      to_write = "There are no members at all in this guild.\n";
    else if (size == 1)
      to_write = "There is one member:\n";
    else
      to_write = "There are " + LANG_WNUM(size) + " members:\n";
    
    scrw = TP->query_option(OPT_SCREEN_WIDTH);
    scrw = (scrw ? scrw - 3 : 77);
    if (size > 0)
    {
	thlist = m_indexes(thieflist);
	thlist = map(thlist,check_wizard);
	if (scrw == -4) /* handle OPT_SCREEN_WIDTH == -1 correctly */
	  to_write += sprintf("%*#s\n",100000,implode(thlist,"\n"));
	else
	  to_write += sprintf("%-*#s\n",scrw,implode(thlist,"\n"));
    }
    write(to_write);
    return 1;
}

int
is_thief(object ob)
{
    return ob->query_guild_member(GUILD_NAME) &&
      !ob->query_wiz_level();
}

int
is_lay_thief(object ob)
{
    return ob->query_guild_name_lay() == GUILD_NAME;
}

int
guildstat_greater(object ob1, object ob2, int stat)
{
    if (ob1->query_stat(stat) > ob2->query_stat(stat))
      return -1;
    else if (ob1->query_stat(stat) == ob2->query_stat(stat))
      return 0;
    else
      return 1;
}

int
guildstat_greater_lay(object ob1, object ob2)
{
    return guildstat_greater(ob1,ob2,8);
}

int
thieflist(string str)
{
    object *list, *lay = ({ }), *occ = ({ }), ti = this_player();
    int    i, j, busy;
    function fun;
    
    notify_fail("What?\n");
    if (!is_master(TP))
      return 0;
    
    list = filter(users(), "is_thief", this_object());
    fun = &is_lay_thief();
    lay = filter(list,fun);
    lay = sort_array(lay, "guildstat_greater_lay");
    write("Name        Level  Rank\n");
    write("----------------------------\n");
    for(i=0;i<sizeof(lay);i++)
    {
	write(sprintf("%-11s  %3d   %3d\n",
		      lay[i]->query_name(), lay[i]->query_thief_level(), i+1));
    }
    return 1;
}

public nomask int
masternote(string str)
{
    NF("What?\n");
    /* test here if allowed to use*/
    if (!is_master(TP))
      return 0;

    NF("Note must have a header!\n");
    if (!str || str == "")
      return 0;
    NF("Header must have at least 10 characters.\n");
    if (strlen(str) < 10)
      return 0;

    write("This note will be written by 'Ringleader'. You should _never_ " +
	  "sign this note with your own name!\n");
    
    header = str;
    seteuid(getuid());
    clone_object(EDITOR_OBJECT)->edit("done_editing");
    return 1;
}

public nomask int
done_editing(string message)
{
    object board = START_ROOM->query_board();
    
    /* test here if allowed to use*/
    if (!is_master(TP))
      return 0;
    if (!header)
      return 0;

    if (!board->create_note(header,"Ringleader",message))
    {
	write("ERROR posting the note.\n");
	return 0;
    }
    header = 0;
    write("Note posted.\n");
    return 1;
}

int
rread(string str)
{
    int num;
    mixed flag;

    if (!is_master(TP))
      return 0;
      
    NF("Rread what?\n");
    if (!str || str == "")
      return POSTMASTER->check_mail(TP,1);

    if (sscanf(str,"%d %s",num,flag) == 2)
      return POSTMASTER->read_mail(TP,num,flag,1);
    
    if (sscanf(str,"%d",num) == 1)
      return POSTMASTER->read_mail(TP,num,0,1);

    return 0;
}

int
rsend(string str)
{
    if (!is_master(TP))
      return 0;

    NF("Rsend to who?\n");
    if (!str || str == "")
      return 0;
    NF("No such guildmember.\n");
    if (!thieflist[L(str)])
      return 0;
    return POSTMASTER->send_mail(TP,L(str),1);
}

int
do_punish_now(object who, string reason)
{
    object ob;
    int val;
    
    if (ob = present(THIEF_OBJ_ID, who))
    {
	val = who->query_acc_exp(SS_LAYMAN);
	val /= 5; /* -80% */
	who->set_guild_stat(SS_LAYMAN, val);
	punishlist += ([ who->query_real_name():REALAGE(who) + 172800 ]);
	who->catch_msg("You are being punished because " + reason + "!\n");
	who->catch_msg("The punishment will mean a malus on your stealing " +
		       "abilities for two days of your playing time and " +
		       "a reduction of your guild level.\n");
	save_object(SAVE_FILE);
	return 1;
    }
    NF(who->query_name() + " is not a valid candidate for punishment.\n");
    return 0;
}

int
do_expel_now(object who, string reason)
{
    JOIN_ROOM->expel_member_from_guild(who->query_real_name(),reason);
    return 1;
}

int
do_action_now(object who, string action, string reason)
{
    int rslt = call_other(TO,"do_" + action + "_now",who,reason);
    
    if (rslt)
      write_file(ACTION_LOG, ctime(time())[4..15] + " " + C(action) +
		 " success for " + C(who->query_name()) + " because " + 
		 reason + ".\n");
    else
      write_file(ACTION_LOG, ctime(time())[4..15] + " " + C(action) +
		 " failed for " + C(who->query_name()) + " because " +
		 reason + ".\n");
    return rslt;
}

void
do_action_later(string who, string action, string reason)
{
    actions += ({ ({ who,action,reason }) });
    save_object(SAVE_FILE);
    write(C(who) + " was put in the " + action + " list because " +
	  reason + ".\n");
    write_file(ACTION_LOG, C(who) + " was put in the " + action +
	       " list because " + reason + ".\n");
}

int
try_action_now(string action, string str)
{
    object who;
    int rslt;
    string tname, reason;

    NF("T" + C(action) + " who because what?\n");
    if (!str)
      return 0;
    if (sscanf(str,"%s because %s",tname,reason) != 2)
      return 0;

    NF(C(tname) + " is not a valid candidate for punishment.\n");
    if (member_array(tname, m_indexes(thieflist)) == -1)
      return 0;

    who = find_player(tname);
    if (who)
    {
      rslt = do_action_now(who,action,reason);
      if (rslt)
	write("You have " + action + "ed " + C(tname) + " because " +
	      reason + ".\n");
      return rslt;
    }

    do_action_later(tname,action,reason);
    return 1;
}

int
tpunish(string str)
{
    NF("What?\n");
    if (!is_master(TP))
      return 0;

    return try_action_now("punish",str);
}

int
texpel(string str)
{
    NF("What?\n");
    if (!is_master(TP))
      return 0;
    
    return try_action_now("expel",str);
}

int
tpass(string str)
{
    object newmaster;

    NF("What?\n");
    if (!is_master(TP))
      return 0;
    NF("Pass the Ringleader position onto who? Your successor must currently be logged in.\n");
    if (!str)
      return 0;

    newmaster = find_player(str);
    if (!newmaster || !LAYMAN(newmaster) || newmaster == TP || !interactive(newmaster))
      return 0;

    tmaster = newmaster->query_real_name();
    write("You have transferred the Ringleader position over the Cabal of Hiddukel to " + C(tmaster) + "!\n");
    write("All you have left to do is type 'out' and leave this room.\n");
    newmaster->catch_msg(C(TP->query_real_name()) + " has transferred the Ringleader position over the Cabal of Hiddukel to you!\n");
    newmaster->catch_msg("Use the exit 'hiddukel' in the boardroom to get to the Master room.\n");
    save_object(SAVE_FILE);    
    log_file("guild/thief/master",ctime(time())[4..15] + ", " +
	     TP->query_name() + " -> " + C(tmaster) + "\n",50000);
    return 1;
}

int
righthand(string str)
{
    string func,name;

    NF("Righthand [a|d <name>].\n");

    if (!str)
    {
	write("Your Right Hand is currently:\n" +
	      (sizeof(right_hand) ? sprintf("%@#12s", right_hand) : "---") +
	      ".\nUse 'righthand a <name>' to add a Right Hand\n" +
	      "and 'righthand d <name>' to delete.\n");
	return 1;
    }

    if (sscanf(str,"%s %s",func,name) != 2)
      return 0;

    NF(C(name) + " is not a thief.\n");
    if (member_array(L(name),m_indexes(thieflist)) < 0)
      return 0;

    NF("Righthand [a|d <name>].\n");
    if (func == "a")
    {
	right_hand += ({ C(name) });
	write("Ok.\n");
	return 1;
    }
    else if (func == "d")
    {
	right_hand -= ({ C(name) });
	write("Ok.\n");
	return 1;
    }
    else
      return 0;
}

void 
check_actions(object who)
{
    int i;
    float f = 1.0;
    mixed *doneactions = ({});
    mixed* entry = thieflist[who->query_real_name()];

    /* first update the thieflist */
    if (!entry || sizeof(entry) < 4)
      thieflist += ([who->query_real_name():({0,0,0,0,})]);
    thieflist[who->query_real_name()][1] = who->query_stat(SS_LAYMAN);
    thieflist[who->query_real_name()][2] = who->query_acc_exp(SS_LAYMAN);
    
    /* then check pending actions */
    for (i=0;i<sizeof(actions);i++)
    {
	if (!who)
	  return;
	if (actions[i][0] == who->query_real_name())
	{
	    set_alarm(f,0.0,"do_action_now", who,
		      actions[i][1],actions[i][2]);
	    f += 0.2;
	    doneactions += ({ actions[i] });
	}
    }
    actions -= doneactions;
    save_object(SAVE_FILE);
}

void
add_thief(string member)
{
    thieflist += ([ L(member):({ 0,0,0,0 }) ]);
    save_object(SAVE_FILE);
}

void
remove_thief(string member)
{
    thieflist = m_delete(thieflist, L(member));
    punishlist = m_delete(punishlist, L(member));
    POSTMASTER->remove_thief(member);
    save_object(SAVE_FILE);
}

int
is_punished(object who)
{
    int p = punishlist[who->query_real_name()];
    
    /* Not in list */
    if (p == 0)
      return 0;
    
    /* In list but punishment expired */
    if (REALAGE(who) > p)
    {
	punishlist = m_delete(punishlist, who->query_real_name());
	save_object(SAVE_FILE);
	return 0;
    }
    
    return 1;
}

