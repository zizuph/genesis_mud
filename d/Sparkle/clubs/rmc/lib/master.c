/*
* RMC Master Object
* Moved out from the joining room.
* rooms/richclub.c was the old master, it is now just a simple joining room.
* backup.dir/richclub2005.c is the old original file.
*
* Code History
* 
* Created Conan Jan -95
* Assisted by Valeria
* 
* Changes:
* 95-02-08: Unknown
* + Code edited and update.
* 99-08-17: Tintin
* + Major recode.
* 05-12-14: Lunatari
* + Created from joining.c the old richclub.c, moved and modified for Sparkle.
* 08-01-28: Lunatari
* + Altered the query_account code so it matches Mercades new gem bank.
*/
#pragma strict_types
#pragma save_binary

inherit "/lib/trade";

#include "defs.h"
#include <files.h>

/* saving variables */
mapping member_list, pursehole;
string  president, vicepres;
int     pursepay, howmuch;

/* none saving ints */
static int mbwealth;

string query_title(object ob);
string query_num_title(int n);
void set_member_tot_wealth();

/*
 * This gives us a reference to the member list.
 * Don't modify the contents unless you are _certain_ of what you are doing.
 * If you don't understand this comment, you are not certain.
 */
mapping
all_members()
{
    return member_list;
}

void
gone()
{
    string *names = m_indexes(member_list);
    int i;
    for (i = 0; i < sizeof(names); i++)
	if(!(MASTER->exist_player(names[i])))
	{
	    write(names[i] + "\n");
	    member_list = m_delete(member_list, names[i]);
	}
	FIXEUID;
	save_object(RMCSAVED);
}

int
query_member(string name)
{
    if (member_list[name])
	return 1;
    else
	return 0;
}

int
query_level(string name)
{
    if (member_list[name])
	return RMC_PAID(member_list[name]);
    else
        return 0;
}

int
bank_account(string name)
{
    int *coins = GOG_ACCOUNTS->query_account_coins(name);

    return MONEY_MERGE(coins) / MONEY_VALUES[MONEY_PC_INDEX];
}

int
level_account(string name)
{
    return (200 * query_level(name)) - 100;
}

int
inv_account(string name)
{
    return TOTAL_MONEY(name) / 1728;
}

int
total_account(string name)
{
    return level_account(name) + inv_account(name) + bank_account(name);
}

void
change_account(string name)
{
    mixed *acc = member_list[name];

    if (acc)
    {
    	RMC_ACCOUNT(member_list[name]) = total_account(name) +
    	    RMC_PURCHASE(acc);
    	FIXEUID;
    	save_object(RMCSAVED);
    }
}

void
set_purse_hole(string name)
{
    pursehole[name] = 1;

    FIXEUID;
    save_object(RMCSAVED);
}

int
unset_purse_hole(string name)
{
    pursehole = m_delete(pursehole, name);

    FIXEUID;
    save_object(RMCSAVED);
}

int
query_purse_hole(string name)
{
    return pursehole[name];
}

int
query_suspension(string name)
{
    mixed data = member_list[name];
    if (pointerp(data))
        return RMC_SUSPEND(data);
    else
        return 0;
}

int
add_howmuch(int hm)
{
    howmuch += hm;
    FIXEUID;
    save_object(RMCSAVED);
    return 1;
}

int
add_pursepay(int pp)
{
    pursepay += pp;

    FIXEUID;
    save_object(RMCSAVED);
    return 1;
}

public int
query_howmuch()
{
    return howmuch;
}

int
logger(string str)
{
    write_file(RMC_RLOG,
	       sprintf("%-16s%-20s%-20s%3s\n",
		       capitalize(TP->query_real_name()),
		       str,
		       ctime(time()),
		       (TP->query_wiz_level() ? "(*)" : "   ")));

    return 1;
}

int
mverrmes()
{
    write("Sorry you have too much in you inventory. Drop some stuff and try "+
	  "the command 'newpurse'.\n");
    return 1;
}

public void
create()
{
    object depos;

    setuid();
    seteuid(getuid());
    
    member_list = ([ ]);
    pursehole = ([ ]);
    
    restore_object(RMCSAVED);
    set_member_tot_wealth();
}

public int
query_humble(string name)
{
    return RMC_HUMBLE(member_list[name]);
}

public void
toggle_humble(string name)
{
    mixed *acc = member_list[name];

    if (acc)
    {
	RMC_HUMBLE(acc) = !RMC_HUMBLE(acc);

	member_list[name] = acc;
	FIXEUID;
	save_object(RMCSAVED);
    }
}

void
clear_news(string name)
{
    RMC_NEWS(member_list[name]) = 0;
}

int
query_news_status(string name)
{
    return RMC_NEWS(member_list[name]);
}

mixed *
map_news(mixed *arr)
{
    RMC_NEWS(arr) = 1;
    return arr;
}

void
set_all_news()
{

    member_list = map(member_list, &map_news());
    FIXEUID;
    save_object(RMCSAVED);
}

int
query_member_vars(string s, object to)
{
    mixed *data = member_list[s];

    if (!data)
	return 0;

    to->catch_msg("\n--- RMC MEMBER VARS ---\n* Name:         "+
		  capitalize(RMC_MEMBER(data))+
		  "\n* Paid:         "+RMC_PAID(data)+
		  "\n* Humble:       "+RMC_HUMBLE(data)+
		  "\n* News status:  "+RMC_NEWS(data)+
		  "\n* Account:      "+RMC_ACCOUNT(data)+
		  "\n* Suspension:   "+RMC_SUSPEND(data)+
		  "\n* Notification: "+RMC_NOTE(data)+
		  "\n* Purchased:    "+RMC_PURCHASE(data)+"\n\n");
        return 1;
}

int
add_member(string name, int lv = 1)
{
    member_list[name] = ({ name, lv, 0, 1, 0, 0, 1, 0, 0});
    
    FIXEUID;
    save_object(RMCSAVED);
    return 1;
}

int
add_wizard_member(string name)
{
    return add_member(name, 32);
}

int
set_level(string name, int level)
{
    if (member_list[name] == 0)
	return 0;
    RMC_PAID(member_list[name]) = level;
    
    FIXEUID;
    save_object(RMCSAVED);
    return 1;
}

void
remove_member(string name)
{
    object ob;

    member_list = m_delete(member_list, name);

    FIXEUID;
    save_object(RMCSAVED);
    
    if (ob = find_player(name))
    {
    	ob->remove_cmdsoul(RMCSOUL);
    	ob->update_hooks();
    }
}  

void
set_suspension(object ob, int s)
{
    RMC_SUSPEND(member_list[ob->query_real_name()]) = s;
    
    FIXEUID;
    save_object(RMCSAVED);
}

void
set_notification(string name, int on)
{
    if (member_list[name])
    {
    	RMC_NOTE(member_list[name]) = on;

    	FIXEUID;
    	save_object(RMCSAVED);
    }
}

public int
query_notification(string name)
{
    if (member_list[name])
	    return RMC_NOTE(member_list[name]);

    return 0;
}

public int
query_purchased(string name)
{
    if (member_list[name])
	    return RMC_PURCHASE(member_list[name]);

    return 0;
}

void
add_purchased(string name, int n)
{
    if (member_list[name])
    {	
	RMC_PURCHASE(member_list[name]) += n;
	FIXEUID;
        save_object(RMCSAVED);
    }
}

void
set_visible(string name, int n)
{
    if (member_list[name])
    {
	RMC_VISIBLE(member_list[name]) = n;
	FIXEUID;
        save_object(RMCSAVED);
    }
}

public int
query_visible(string name)
{
    if (member_list[name])
    {
	return RMC_VISIBLE(member_list[name]);
    }
    return 0;
}

void
ask_map(mixed *arr)
{
    write(RMC_MEMBER(arr)+ ": " + RMC_NOTE(arr) + ".\n");
}

int
ask_notification()
{
    int i;
    
    if (TP->query_wiz_level())
    {
	map(member_list, &ask_map());
        return 1;
    }
    return 0;
}

void
set_member_tot_wealth()
{
    mixed arr = m_values(member_list);

    int i,tb,pr;

    for (i = 0; i < sizeof(arr); i++)
    {
        tb += RMC_ACCOUNT(arr[i]);
        pr += RMC_PURCHASE(arr[i]);
    }
    mbwealth = tb - pr - howmuch;
}

public string
query_member_list()
{
    object *playing_members;
    mixed *entry;
    string s,t;
    int i,wz,pm,am,wm,em,om,fr,bs,tb,hm,ns,nv,nt,p,pr;

    mixed *arr = m_values(member_list);
    
    for (i = 0; i < sizeof(arr); i++)
    {
        if (RMC_HUMBLE(arr[i]))
            hm++;
        if (RMC_NOTE(arr[i]))
            nt++;
        if (RMC_PAID(arr[i]) == 1)
            pm++;
        if (RMC_PAID(arr[i]) == 2)
            am++;
        if (RMC_PAID(arr[i]) == 4)
            wm++;
        if (RMC_PAID(arr[i]) == 8)
            em++;
        if (RMC_PAID(arr[i]) > 15 && RMC_PAID(arr[i]) < 30)
            if(RMC_PURCHASE(arr[i]) > 4000) bs++;
            else if (RMC_PURCHASE(arr[i]) > 2000) fr++;
            else om++;
        if (RMC_PAID(arr[i]) > 29)
            wz++;
        if (RMC_NEWS(arr[i]))
            ns++;
        if (!RMC_VISIBLE(arr[i]))
            nv++;
        
        tb += RMC_ACCOUNT(arr[i]);
        pr += RMC_PURCHASE(arr[i]);
    }

	t = sprintf("| %-16s %8s %8s %3s %3s %3s %3s %3s %5s  |\n", 
	"Name:", "Paid:", "Account", "Hu:", "Vs:", "Nw:",
		    "Su:", "Nt:", "Pr:") +
	"+---------------------------------------------------------------+\n";

    playing_members = filter(users()->query_real_name(), &query_member());

    for (i = 0; i < sizeof(playing_members); i++)
    {
	entry = member_list[playing_members[i]];
	t += sprintf("| %-16s %8d %8d %3d %3d %3d %3d %3d %5d  |\n", 
		     capitalize(RMC_MEMBER(entry)),
		     RMC_PAID(entry),
		     RMC_ACCOUNT(entry),
		     RMC_HUMBLE(entry),
		     RMC_VISIBLE(entry),
		     RMC_NEWS(entry),
		     RMC_SUSPEND(entry),
		     RMC_NOTE(entry),
		     RMC_PURCHASE(entry)
	    );
    }
    t += "+---------------------------------------------------------------+\n\n";

    s = "\n+---------------------------------------------------------------+\n"+
          "| $            Rich Men's Club Member Statistics              $ |\n"+
	"+-------------------------------+-------------------------------+\n";

    s += sprintf("| Total no of members : %-7d | President     : %-13s |\n",
		 m_sizeof(member_list), capitalize(president)); 
    s += sprintf("|  - Poor Members     : %-7d | Vice President: %-13s |\n",
		 pm, capitalize(vicepres));

   s += "|  - Average Members  : "+am+"\t+-------------------------------+\n"+
        "|  - Wealthy Members  : "+wm+"\t| Humble Members      : "+hm+"\t|\n"+
        "|  - E Wealthy Members: "+em+"\t| Hiding purses/sacks : "+nv+"\t|\n"+
        "|  - O Wealthy Members: "+om+"\t| Not read rnews      : "+ns+"\t|\n"+
        "|  - Wizard Members   : "+wz+"\t+-------------------------------+\n"+
        "|  - F. Rich Members  : "+fr+"\t| Wealth since reboot: "+
                                          (tb-howmuch-pr-mbwealth)+"pc\t|\n"+
        "|  - Big Shots        : "+bs+"\t|                               |\n"+
        "+-------------------------------+-------------------------------|\n"+
        "| Total Spent on Club : "+howmuch+"pc                               |\n"+
        "| Total Purchased     : "+pr+"pc                                |\n"+
        "| Total in Accounts   : "+(tb-howmuch-pr)+"pc                               |\n"+
        "+-------------------------------+-------------------------------+\n";
        
    return s + t;
}

    
public void
purge_member(string who, string by)
{
    string wb,ww;
    
    remove_member(who);
    
    write_file(RICHLOG,
	       sprintf("%-20s purged %-20s %20s\n", by, who, ctime(time())));
}

void
notificate(string name)
{
    object *members;
    mixed *acc;
    int i, o, l, m, pr;
    
    FIXEUID;

    /* No info on wizards or Jr's. */
    if (wildmatch("*jr", name) || SECURITY->query_wiz_rank(name))
    {
        return;
    }

    
    l = query_level(name);
    pr = query_purchased(name);
    
    switch (l)
    {
    case 1:
        m = 0;
        break;
    case 2:
        m = 1;
        break;
    case 4:
        m = 2;
        break;
    case 8:
        m = 3;
        break;
    case 16..18:
        m = 4;
        if (pr > 4000)
            m = 5;
        else if (pr > 2000)
            m = 6;
        break;
    case 30..34:
        m = 7;
        break;
    case 35:
        m = 8;
        break;
    default:
        m = 0;
    }
    
    members = filter(users(), &query_member() @ &->query_real_name());

    for (i = 0; i < sizeof(members); i++)
    {
	acc = member_list[members[i]->query_real_name()];
        if (present("rich_club_obj", members[i]) &&
	    members[i] != find_player(name) &&
	    RMC_NOTE(acc))
        {
            if (RMC_PAID(acc) <4)
                members[i]->catch_msg(RICH_NOTIFY_MSG[0] + ".\n");
            else if (RMC_PAID(acc) < 16)
                members[i]->catch_msg(RICH_NOTIFY_MSG[m] + ".\n");
            else
                members[i]->catch_msg(RICH_NOTIFY_MSG[m] + " as " +
				      find_player(name)->query_name() +
                                      " enters the world of Genesis.\n");
        }
    }
}

string
query_president()
{
    return president;
}

string
query_vice_president()
{
    return vicepres;
}

void
update_president()
{
    int worth, curr_max = 0, curr_second = 0, i;
    string pres = "Null";
    string vice = "Null";
    mixed *arr = m_values(member_list);


    for (i = 0; i < sizeof(arr); i++)
    {
        if (RMC_PAID(arr[i]) == 16)
        {
            worth = (RMC_PURCHASE(arr[i])/175) +
		((RMC_ACCOUNT(arr[i]) - RMC_PURCHASE(arr[i]))/250) + 1;
            if (worth > curr_max)
            {
		curr_second = curr_max;
                curr_max = worth;
		vice = pres;
                pres = RMC_MEMBER(arr[i]);

            }
	    else if (worth > curr_second)
	    {
		curr_second = worth;
		vice = RMC_MEMBER(arr[i]);
	    }
        }
    }

    president = pres;
    vicepres = vice;
}

int
query_acc(string str)
{
    if(!member_list[str]) return 0;

    return (RMC_ACCOUNT(member_list[str]) + RMC_PURCHASE(member_list[str]));
}

string
query_title(string name)
{
    mixed *acc;
    int pr;
    
    if (!(acc = member_list[name]))
	return "Zippo";

    switch(RMC_PAID(acc))
    {
    case 1:
	return RMC_TITLE[0];
	break;
    case 2:
	return RMC_TITLE[1];
	break;
    case 4:
	return RMC_TITLE[2];
	break;
    case 8:
	return RMC_TITLE[3];
	break;
    case 16:
	if (name == president)
	    return RMC_TITLE[8];
	if (name == vicepres)
	    return RMC_TITLE[7];
	pr = RMC_PURCHASE(acc);
	if (pr > 4000)
	    return RMC_TITLE[6];
	else if (pr > 2000)
	    return RMC_TITLE[5];
	return RMC_TITLE[4];
	break;
    case 32:
	return RMC_TITLE[9];
	break;
    case 33:
	return RMC_TITLE[10];
	break;
    case 34:
	return RMC_TITLE[11];
	break;
    case 35:
	return RMC_TITLE[12];
	break;
    default:
	break;
    }
}

string
query_art_title(string name)
{
    mixed *acc;
    int pr;
    string s;
    
    if (!(acc = member_list[name]))
	return "Zippo";

    pr = RMC_PURCHASE(acc);
    switch(RMC_PAID(acc))
    {
    case 1:
	return "a " + RMC_TITLE[0];
	break;
    case 2:
	return "an " + RMC_TITLE[1];
	break;
    case 4:
	return "a " + RMC_TITLE[2];
	break;
    case 8:
	return "an " + RMC_TITLE[3];
	break;
    case 16:
	s = "an "+RMC_TITLE[4];
	if (pr > 4000)
	    s = "a " + RMC_TITLE[6];
	else if (pr > 2000)
	    s = "a " + RMC_TITLE[5];
	if (name == vicepres)
	    s += " and the " + RMC_TITLE[7];
	if (name == president)
	    s += " and the " + RMC_TITLE[8];
	return s;
	break;
    case 32:
	return "a "+RMC_TITLE[9];
	break;
    case 33:
	return "a "+RMC_TITLE[10];
	break;
    case 34:
	return "the "+RMC_TITLE[11];
	break;
    case 35:
	s ="the "+ RMC_TITLE[12];
	if (pr > 4000)
	    s += " and "+RMC_TITLE[6];
	return s;
	break;
    default:
	break;
    }
}

string
query_num_title(int n)
{
    string s;
    
    switch(n)
    {
    case 1:
        return RMC_TITLE[0];
        break;
    case 2:
        return RMC_TITLE[1];
	break;
    case 4:
        return RMC_TITLE[2];
        break;
    case 8:
        return RMC_TITLE[3];
        break;
    case 16:
	return RMC_TITLE[4];
        break;
    case 32:
        return RMC_TITLE[9];
        break;
    case 33:
        return RMC_TITLE[10];
        break;
    case 34:
        return RMC_TITLE[11];
        break;
    case 35:
        return RMC_TITLE[12];
        break;
    default:
        break;
    }
}

int
query_valuation(string name)
{
    int val;
    mixed *acc;

    if (!(acc = member_list[name]))
	return 0;

    val = (RMC_PURCHASE(acc)/175) +
	((RMC_ACCOUNT(acc) - RMC_PURCHASE(acc))/250);

    if (RMC_PAID(acc) > 20)
	val = 100 + RMC_PAID(acc);
        
    return val + 1;
}

string
query_pos(string s, int own = 0)
{
    mixed *arr, *acc;
    int pos, i, worth;

    pos = 1;

    worth = (RMC_PURCHASE(member_list[s]) / 175) +
	((RMC_ACCOUNT(member_list[s]) -
	  RMC_PURCHASE(member_list[s])) / 250) + 1;

    if (RMC_PAID(member_list[s]) > 20)
        worth = 100 + RMC_PAID(member_list[s]);

    arr = m_indexes(member_list);

    for (i = 0; i < sizeof(arr); i++)
    {
	if (arr[i] == s)
	    continue;
	acc = member_list[arr[i]];
	if (RMC_PAID(acc)>15 && RMC_PAID(acc)<20)
	{
	    if (worth < ((RMC_PURCHASE(acc) / 175) +
		     ((RMC_ACCOUNT(acc) - RMC_PURCHASE(acc)) / 250) + 1))
		pos++;
	}
    }
    
    return (own ?
	    "Your position is " + pos + ".\n"
	    :
	    "The position for "+capitalize(s)+" in the RMC is " + pos +
	    " with account = " + RMC_ACCOUNT(member_list[s]) +
	    " and valuation = "+ worth +".\n");
}

int
pursecheck()
{
    
    if (TP->query_wiz_level())
    {
	write("\n[RMC] : " + pursepay +
	      " platinum coins have been spent on broken purses.\n");

	write(read_file(RMCMASTER + "purse.log"));
	write("[RMC] : End of log.\n\n");
	
	return 1;
    }
    return 0;
}

mixed
query_dump(string name)
{
    return member_list[name];
}
