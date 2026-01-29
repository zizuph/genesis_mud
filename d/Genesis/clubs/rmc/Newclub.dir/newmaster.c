/*
 * THE RICH MAN'S CLUB MASTER ROOM
 * Coded by Conan May -97
 *
 * This room handles all contact with the club variables.
 *
 */
#pragma save_binary

inherit "/std/room";

#include "xdefs.h"
#include <std.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <money.h>

mapping rdata;
static int leava = 0;
static int mbwealth;
int howmuch;
string president, vicepres;

/*
 * ------------------------------------------------------------------
 * Functions to handle the variables from alien objects.
 * ------------------------------------------------------------------
 */
int
query_level(mixed player)
{
    object ob;
    mixed *a;
  
    if (objectp(player))
	ob = player->query_real_name();
    else
	ob = player;

    a = rdata[player];
     
    if (a)
	return rdata[player][0];

    return 0;
}

int
set_all_rmc_data(int dt, mixed v)
{
    mixed *a;
    string *names;
    int i;

    names = m_indexes(rdata);

    for (i = 0; i < sizeof(names); i++)
    {
	a = rdata[names[i]];
	a[dt] = v;
	rdata[names[i]] = a;
    }

    save_object(RICH_OBJ);

    return 1;
}  

int
set_rmc_data(mixed player, int dt, mixed v)
{
    mixed *a;
    string name;
    int l;
   
    if (objectp(player))
	name = player->query_real_name();
    else
	name = player;

    l = query_level(name);
    if (!l)
	return 0;

    a = rdata[name];
    a[dt] = v;
    rdata[name] = a;

    save_object(RICH_OBJ);

    return 1;
}  

int
query_rmc_data(mixed player, int dt)
{
    mixed *a;
    string name;
    int l;
   
    if (objectp(player))
	name = player->query_real_name();
    else
	name = player;

    l = query_level(name);
    if (!l)
	return 0;

    return rdata[name][dt];
}  

mixed*
query_member_vars(mixed player)
{
     string name;
     int l;
   
     if (objectp(player))
	 name = player->query_real_name();
     else
	 name = player;

     l = query_level(name);
     if (!l)
	 return 0;

     return rdata[name];
}

/*
 * ------------------------------------------------------------------
 * Special Functions
 * ------------------------------------------------------------------
 */
int
add_howmuch(int hm)
{
    howmuch += hm;
    save_object(RICH_OBJ);
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
    string ws;

    ws = capitalize(TP->query_real_name());

    if (strlen(ws)>8) ws += "\t";
    else ws += "\t\t";

    ws += str + "\t"+extract(ctime(time()),4,15);

    if (TP->query_wiz_level())
	ws += " (*)";

    ws += "\n";

    write_file(RICHLOG, ws);

    return 1;
}

public string
query_member_list()
{
    object *players;
    string s, t, *names, p;
    int i,wz,pm,am,wm,em,om,fr,bs,tb,hm,ns,nv,nt,pr,l;

    players = users();
    names = m_indexes(rdata);
    
    t = "| Name:\t\tPaid:\tAccount\tHu: Vs: Nw: Su: Nt:     Pr:\t|\n";

    for (i = 0; i < sizeof(names); i++)
    {
        if (RMC_HUMBLE(names[i]))
            hm++;
        if (RMC_NOTE(names[i]))
            nt++;
        if (RMC_PAID(names[i]) == 1)
            pm++;
        if (RMC_PAID(names[i]) == 2)
            am++;
        if (RMC_PAID(names[i]) == 4)
            wm++;
        if (RMC_PAID(names[i]) == 8)
            em++;
        if (RMC_PAID(names[i]) > 15 && RMC_PAID(names[i]) < 30)
            if(RMC_PURCHASE(names[i]) > 4000) bs++;
            else if (RMC_PURCHASE(names[i]) > 2000) fr++;
            else om++;
        if (RMC_PAID(names[i]) > 29)
            wz++;
        if (RMC_NEWS(names[i]))
            ns++;
        if (!RMC_VISIBLE(names[i]))
            nv++;
        
        tb += RMC_ACCOUNT(names[i]);
        pr += RMC_PURCHASE(names[i]);
    }

    t += "+---------------------------------------------------------------+\n";
    for (i = 0; i < sizeof(players); i++)
    {
        l = query_level(players[i]);
        if ( l )
        {
	    p = players[i]->query_real_name();
	    t += "| " + capitalize(p);
            if (strlen(p) > 5)
                t += "\t"; 
            else
                t += "\t\t";

            t += " "+RMC_PAID(p)+"\t  "+RMC_ACCOUNT(p)+"\t "+RMC_HUMBLE(p)+
		"   "+RMC_VISIBLE(p)+"   "+RMC_NEWS(p)+"   "+
                RMC_SUSPEND(p)+"   "+RMC_NOTE(p)+"      "+RMC_PURCHASE(p)+"\t|\n";
        }
    }
    t += "+---------------------------------------------------------------+\n\n";

    s = "\n+---------------------------------------------------------------+\n"+
          "| $                   RMC Member Statistics                   $ |\n"+
        "+-------------------------------+-------------------------------+\n"+
        "| Total no of members : "+m_sizeof(rdata)+"\t| President     :  "+
        capitalize(president)+"\t|\n"+
        "|  - Poor Members     : "+pm+"\t| Vice President:  "+
        capitalize(vicepres)+"\t|\n"+
        "|  - Average Members  : "+am+"\t+-------------------------------+\n"+
        "|  - Wealthy Members  : "+wm+"\t| Humble Members      : "+hm+"\t|\n"+
        "|  - E Wealthy Members: "+em+"\t| Hiding purses/sacks : "+nv+"\t|\n"+
        "|  - O Wealthy Members: "+om+"\t| Not read rnews      : "+ns+"\t|\n"+
        "|  - Wizard Members   : "+wz+"\t+-------------------------------+\n"+
        "|  - F. Rich Members  : "+fr+"\t| dWealth since reboot: "+
                                          (tb-howmuch-pr-mbwealth)+"pc\t|\n"+
        "|  - Big Shots        : "+bs+"\t|                               |\n"+
        "+-------------------------------+                               |\n"+
        "| Total Spent on Club :"+howmuch+"pc\t|                               |\n"+
        "| Total Purchased     : "+pr+"pc\t|                               |\n"+
        "| Total in Accounts   :"+(tb-howmuch-pr)+
	"pc\t|                               |\n"+
        "+-------------------------------+-------------------------------+\n";
        
    return s + t;
}

/*
 * ------------------------------------------------------------------
 * Adding / Removing Member Functions
 * ------------------------------------------------------------------
 */
void
add_member(object ob)
{
    string name;
    mixed *a;
    int lv;

    name = ob->query_real_name();
    
    if (ob->query_wiz_level())
    {
	lv = 32;
	a = ({ lv, m_sizeof(rdata), 0, 0, 0, 0, 1, 0, 0});
    }
    else
    {
	lv = 1;
	a = ({ lv, m_sizeof(rdata), 0, 1, 0, 0, 1, 0, 0});
    }
	
    if (pointerp(rdata))
	rdata += ([ name : a ]);
    else
	rdata = ([ name : a ]);
  
    save_object(RICH_OBJ);
    return;
}

int
remove_member(object ob)
{
    int no;
    string name;
    
    name = ob->query_real_name();

    if (!query_level(name))
	return 0;
    
    m_delete(rdata, name);
    
    save_object(RICH_OBJ);
    return 1;
}  

/*
 * ------------------------------------------------------------------
 * Room Functions
 * ------------------------------------------------------------------
 */
public void
create_room()
{
    seteuid(getuid(TO));

    set_short("The Rich Men's Club Master Room");
    set_long(break_string("This is the Rich Man's Club Master Room. Here "+
			"all contact with the huge member array is handled. "+
			"No players will enter this room as it also is "+
			"used as treasure room for the money used in "+
			"the club since reboot.\n",60));
  
    INSIDE;

    restore_object(RICH_OBJ);
    /* set_member_tot_wealth(); */
}

