/*
*
* The Rich Men's Club
*
* Coded by Conan Jan -95
* Assisted by Valeria
*
* Edited 95-02-08
*/

#pragma save_binary

inherit "/std/room";
inherit "/lib/trade";

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

mixed *rdata;
static int leava = 0;
static int mbwealth;
int howmuch;
int president, vicepres;

string query_title(object ob);
string query_num_title(int n, object ob);
void set_member_tot_wealth();

int
query_member(object ob)
{
  int i,member;
  string person;
  
  person = ob->query_real_name();
  member = -1;
  
  for (i = 0; i < sizeof(rdata); i++)
  {
    if (RMC_MEMBER(i) == person)
      member = i;
  }
  
  return member;
}

int
query_level(object ob)
{
  int no,paid;
  
  seteuid(getuid(TO));
  no = query_member(ob);
  
  if(no != -1)
  {
    paid = RMC_PAID(no);

    return paid;
  }
  
  return 0;
}

/* ACCOUNT FUNKTIONS */
int
bank_account(object ob)
{
  mapping acc = ACCOUNTS->query_account(ob->query_real_name());
  int tot;
  object account_list = find_object(ACCOUNTS);
  
  if (m_sizeof(acc) < 6)
      return 0;
  return (acc["pc"] + acc["gc"]/12 + acc["sc"]/144 + acc["cc"]/1728);
}

int
level_account(object ob)
{
  int level,tot;

  level = query_level(ob); 
  tot = (200 * level) - 100;
  return tot;
}

int
inv_account(object ob)
{
  int tot;

  tot = TOTAL_MONEY(ob);
  tot = tot/1728;
  return tot;
}

int
total_account(object ob)
{
  int tot;
  tot = level_account(ob) + inv_account(ob) + bank_account(ob);
  return tot;
}

int
change_account(object ob)
{
    int member, plats;
    string person;

    member = query_member(ob);
    if (member == -1)
        return 0;

    plats = bank_account(ob) + inv_account(ob);

    RMC_ACCOUNT(member) = plats;
    save_object(RICH_OBJ);
}

int
query_suspension(object ob)
{
  int no,s;
  
  seteuid(getuid(TO));
  no = query_member(ob);
  
  if(no != -1)
  {
    s = RMC_SUSPEND(no);
    
    return s;
  }
  
  return 0;
}

int
add_howmuch(int hm)
{
  seteuid(getuid(TO));

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

  ws += str + "\t\t"+extract(ctime(time()),4,15);

  if (TP->query_wiz_level())
    ws += " (*)";

  ws += "\n";

  write_file(RICHLOG, ws);

  return 1;
}

int
mverrmes()
{
  write("Sorry you have too much in you inventory. Drop some stuff and try "+
    "the command 'newpurse'.\n");
  return 1;
}

sign()
{
  return "The sign reads:\n\n"+
      "+-----------------------------------------------------------+\n"+
      "| o                                                       o |\n"+
      "|                        Welcome to:                        |\n"+
      "|                                                           |\n"+
      "|           T H E   R I C H   M E N ' S   C L U B           |\n"+
      "|                                                           |\n"+
      "|          The club for people with lots of money.          |\n"+
      "|                                                           |\n"+
      "| To join this exclusive club, type <consider> in this room |\n"+
      "|                and follow the instructions.               |\n"+
      "|                                                           |\n"+
      "|       If you are a member, but have lost your purse       |\n"+
      "|                      type <newpurse>.                     |\n"+
      "|                                                           |\n"+
      "|  If you want to make a delay in your membership, simply   |\n"+
      "|  type <suspend membership>, to regain it you'll have to   |\n"+
      "|                 type <regain membership>.                 |\n"+
      "| o                                                       o |\n"+
      "+-----------------------------------------------------------+\n\n";
}

public void
create_room()
{
  object depos;

  seteuid(getuid(TO));

  set_short("The Rich Men's Club");
  set_long(break_string(
    "This is a huge room with impressive tapestry and furniture. "+
    "Everything is shining of gold and gemstones; in other words, "+
    "this is the home for 'The Rich Men's Club.' A set of stairs "+
    "leads up to the upper floor where the private rooms are. A sardonyx "+
    "sign is hanging on one of the walls."+
    "\n",60));
  
  INSIDE;
  add_item("tapestry","Really a impressive tapestry made of purpur coloured fabrics.");
  add_item("furniture","Impressive furniture made of oak.");
  add_item("sign","@@sign");
  add_cmd_item("sign","read","@@sign");

  add_exit(RICHCLUB+"richprivate1","up","@@check");
  add_exit(GOLD+"pier","south");
  
  rdata = ({});

  restore_object(RICH_OBJ);
  set_member_tot_wealth();
  config_default_trade();
}

void
init()
{
  ::init();
  
  add_action("join" ,   "consider");
  add_action("rpay" ,        "pay");
  add_action("cost" ,        "ask");
  add_action("leave",      "leave");
  add_action("newpurse","newpurse");
  add_action("suspension","suspend");
  add_action("regain"  ,  "regain");
  add_action("ask_notification","notif");
/*  add_action("painting",     "exa");
  add_action("painting", "examine");
  add_action("painting",    "look");*/
}

int
check()
{
  int member;
  
  member = query_member(TP);
  
  if (member != -1 || TP->query_wiz_level()>0) return 0;
  
  write("Uhm, no, you don't dare to enter the stairs. Maybe you could slip "+
    "and hurt yourself.\n");
  return 1;
}

public int
query_humble(object ob)
{
  int no,hum;
  
  no = query_member(ob);
  if (no != -1)
  {
      hum = RMC_HUMBLE(no);
      return hum;
  }
  return 0;
}

public void
toggle_humble(object ob)
{
  int no,hum;
  
  no = query_member(ob);
  if (no != -1)
  {
      hum = RMC_HUMBLE(no);
      
      if (hum == 0)
          RMC_HUMBLE(no) = 1;
      else if (hum == 1)
          RMC_HUMBLE(no) = 0;
      
      save_object(RICH_OBJ);
  }
}

void
clear_news(object ob)
{
  int no,hum;
  
  no = query_member(ob);
  if (no != -1)
  {
    RMC_NEWS(no) = 0;
    save_object(RICH_OBJ);
  }
}

int
query_news_status(object ob)
{
  int no,nws;
  
  no = query_member(ob);
  if (no != -1)
  {
    nws = RMC_NEWS(no);
    return nws;
  }
  return 0;
}

void
set_all_news()
{
  int i;

  for (i = 0; i < sizeof(rdata); i++)
    RMC_NEWS(i) = 1;

  save_object(RICH_OBJ);
}

int
query_member_vars(string s, object to)
{
    int no,nws,i;
  
    no = (-1);

    for (i = 0; i < sizeof(rdata); i++)
    {
        if (RMC_MEMBER(i) == s)
            no = i;
    }
    if (no != -1)
    {
        to->catch_msg("\n--- RMC MEMBER VARS ---\n* Name:         "+
                      capitalize(RMC_MEMBER(no))+
                      "\n* Paid:         "+RMC_PAID(no)+
                      "\n* Humble:       "+RMC_HUMBLE(no)+
                      "\n* News status:  "+RMC_NEWS(no)+
                      "\n* Account:      "+RMC_ACCOUNT(no)+
                      "\n* Suspension:   "+RMC_SUSPEND(no)+
                      "\n* Notification: "+RMC_NOTE(no)+
                      "\n* Purchased:    "+RMC_PURCHASE(no)+"\n\n");
        return 1;
    }
    return 0;
}

int
add_member(object ob)
{
  string name;
  int plats,lv = 1;

  name = ob->query_real_name();
  if (pointerp(rdata))
  {
      rdata += (({ ({ name, lv, 0, 1, 0, 0, 1, 0, 0}) }));
  }
  else
  {
      rdata = (({ ({ name, lv, 0, 1, 0, 0, 1, 0, 0}) }));
  }
  
  save_object(RICH_OBJ);
  return 1;
}

int
add_wizard_member(object ob)
{
  string name;
  int lv = 32;
    
  name = ob->query_real_name();
  
  if (pointerp(rdata))
  {
      rdata += (({ ({ name, lv, 0, 0, 0, 0, 1, 0, 0}) }));
  }
  else
  {
      rdata += (({ ({ name, lv, 0, 0, 0, 0, 1, 0, 0}) }));
  }
  
  save_object(RICH_OBJ);
  return 1;
}

int
add_level(object ob)
{
  string name;
  int no,level;
  
  no = query_member(ob);
  name = ob->query_real_name();
  
  level = RMC_PAID(no) * 2;
  
  RMC_PAID(no) = level;

  save_object(RICH_OBJ);
  return 1;
}

int
set_level(string name, int level)
{
  int no, i;

  no = (-1);

  for (i = 0; i < sizeof(rdata); i++)
  {
      if (RMC_MEMBER(i) == name)
          no = i;
  }
  
  if (no != -1)
  {
      RMC_PAID(no) = level;

      save_object(RICH_OBJ);
      return 1;
  }
  return 0;
}

int
remove_member(object ob)
{
  int no;
  string *hmm;
    
  no = query_member(ob);
  
  rdata = exclude_array(rdata,no,no);
  ob->remove_cmdsoul(RICHSOUL);
  ob->update_hooks();
  save_object(RICH_OBJ);
  return 1;
}  

int
set_suspension(object ob,int s)
{
  int no,level;
  
  no = query_member(ob);
  
  RMC_SUSPEND(no) = s;

  save_object(RICH_OBJ);
  return 1;
}

void
set_notification(object ob, int n)
{
    int no;
    
    no = query_member(ob);
    
    RMC_NOTE(no) = n;
    save_object(RICH_OBJ);
}

public int
query_notification(object ob)
{
    int n,no;
    
    no = query_member(ob);
    if (no != -1)
        return RMC_NOTE(no);
    else
        return 1;
}

public int
query_purchased(object ob)
{
    int n,no;
    
    no = query_member(ob);
    if (no != -1)
        return RMC_PURCHASE(no);
    else
        return 1;
}

void
add_purchased(object ob, int n)
{
    int no;
    
    no = query_member(ob);

    if (no != -1)
    {
        RMC_PURCHASE(no) += n;
        save_object(RICH_OBJ);
    }
}

void
set_visible(object ob, int n)
{
    int no;
    
    no = query_member(ob);
    
    if (no != -1)
    {
        RMC_VISIBLE(no) = n;
    }
    save_object(RICH_OBJ);
}

public int
query_visible(object ob)
{
    int n,no;
    
    no = query_member(ob);
    if (no != -1)
        return RMC_VISIBLE(no);
    else
        return 0;
}

int
ask_notification()
{
    int i;
    
    if (TP->query_wiz_level())
    {
        for (i=0; i<sizeof(rdata);i++)
        {
            write(RMC_MEMBER(i)+": "+RMC_NOTE(i)+".\n");
        }
        return 1;
    }
    return 0;
}

void
set_member_tot_wealth()
{
    int i,tb,pr;

    for (i = 0; i < sizeof(rdata); i++)
    {
        tb += RMC_ACCOUNT(i);
        pr += RMC_PURCHASE(i);
    }
    mbwealth = tb - pr - howmuch;
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
	p = query_real_name(players[i]);
        if ( l )
        {
            t += "| " + capitalize(RMC_MEMBER(p));
            if (strlen(RMC_MEMBER(p)) > 5)
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
        "| Total no of members : "+sizeof(rdata)+"\t| President     :  "+
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

    
public int
purge_member(object who, object by)
{
  string wb,ww;

  remove_member(who);
  wb = capitalize(by->query_real_name());
  ww = capitalize(who->query_real_name());

  if (strlen(wb)>8) wb += "\t";
  else wb += "\t\t";
  if (strlen(ww)>8) ww += "\t";
  else ww += "\t\t";

  wb += "purged " + ww + extract(ctime(time()),4,15);

  wb += "\n";

  write_file(RICHLOG, wb);
  return 1;
}

int
join()
{
  write(break_string(
    "It is quite easy to join this club. All you have to "+
    "do is to pay the entry fee of 100 platinum coins. To do this, "+
    "type <pay entry>, and you will receive the first title of this "+
    "club. To enhance your title, type <ask title> to find out how "+
    "much money you will have to pay for it, and <pay title> to get "+
    "the higher title. Note that the higher the title is, the "+
    "greater the cost will be.\n",60));
  say(QCTNAME(TP)+" asks about how to join this exclusive club.\n");
  
  return 1;
}

int
cost(string str)
{
  int member,fee,level;
  string title;
  
  member = query_member(TP);
  
  if (str == "title" && member != -1)
  {
    level = query_level(TP);
    if (level < 16)
    {
      fee = level * 200;
      title = query_num_title(level*2, 0);
      write("The cost for next level is ");
      write(fee);
      write(" platinum coins.\nThe next title is:\n"+title+"\n");
      say(QCTNAME(TP)+" asks about the cost to improve "+
        TP->query_possessive()+" title.\n");
    }
    else
    {
      write("Sorry, you have already obtained the highest title in "+
        "this club.\n");
    }
    return 1;
  }
  return 0;
}

int
rpay(string str)
{
  int cost,level,member,ban;
  string title,stitle;
  object ob,purse;
  
  member = query_member(TP);
  
  if (str == "entry" && member == -1) /* check that the player isn't a member */
  {
    if (TP->query_wiz_level())
    {
      write("Ahhh...a wizard that wants to join this club.\nWell, we feel "+
        "honoured by that so you will be able to join without paying "+
        "anything!\n");

      title = query_num_title(32, 0);

      TP->catch_msg("You pay the entry fee to join The Rich Men's Club.\n");
      TP->catch_msg("You have the title '"+title+"' in this club. If you want "+
        "to leave it some day, type <leave rich club>.\n");
      say(QCTNAME(TP)+" joined The Rich Men's Club.\n");

      add_wizard_member(TP);

      logger("joined the club");

      ob = clone_object(RICHPURSE);
      ob->move(TP);
    
      return 1;
    }      
    else
    {
      cost = 172800;
    
      if (can_pay(cost,TP) == 0) /*check if the player has enough money */
      {
        TP->catch_msg("You're a loser! You are too poor to join us!\n");
        return 1;
      }

      title = query_num_title(1, 0);

      pay(cost,TP,"",0,0,"",1); /* let the player pay */
      add_howmuch(100);

      TP->catch_msg("You pay the entry fee to join The Rich Men's Club.\n");
      TP->catch_msg("You have the title '"+title+"' in this club. If you want "+
        "to leave it some day, type <leave rich club>.\n");
      say(QCTNAME(TP)+" joined The Rich Men's Club.\n");

      add_member(TP);
    
      logger("joined the club");

      ob = clone_object(RICHPURSE);
      ob->move(TP);
    
      return 1;
    }
  }
  else if (str ="title" && member != -1)
  {
    level = query_level(TP);
    if (level >= 16)
    {
       TP->catch_msg("You already have the highest title in this club.\n");
       return 1;
    }
    
    cost = level * 345600;
    
    if (can_pay(cost,TP) == 0)
    {
      TP->catch_msg("Ha! You haven't got that kind of money!\n");
      return 1;
    }

    title = query_num_title(level * 2, 0);

    pay(cost,TP);
    add_howmuch(level * 200);

    TP->catch_msg("You pay the price to enhance your title in the club.\n");
    TP->catch_msg("You have the title '"+title+"' in this club.\n");
    say(QCTNAME(TP)+" increased "+TP->query_possessive()+" title in this "+
      "club to '"+title+"'.\n");

    add_level(TP);
    
    purse = present("rich_purse",TP);       /* delete the old club object */
    if (purse)
      purse->remove_object();

    ob = clone_object(RICHPURSE);           /* clone a new club object */
    ob->move(TP);
    
    logger("improved to " + level*2);

    return 1;
  } 
}

int
leave(string str)
{
  int level,member;
  object purse;
  
  if (str == "rich club" && member != -1)
  {
    if (leava == 0)
    {
      TP->catch_msg("Sure you want to leave this club? In that case "+
        "type <leave rich club again>.\n");
      leava = 1;
      return 1;
    }
    
    purse = present("rich_purse",TP);
    if (purse)
      purse->remove_object();
      
    TP->catch_msg("You leave 'The Rich Men's Club'. The purse is "+
      "disintegrated by some magic force.\n");
    say(QCTNAME(TP)+"'s purse is disintegrated by some magic force.\n");
    
    remove_member(TP);

    logger("left the club");

    leava = 0;
    return 1;
  }
  
  return 0;
}

int
newpurse()
{
  object ob;
  int level,s;

  level = query_level(TP);
  
  NF("You're not member of this club!\n");
  if (level != 0)
  {
    NF("You already got a purse!\n");
    if (!present("rich_club_obj",TP))
    {
        s = query_suspension(TP);
        NF("Your membership is suspended!\n");
        if (!s)
        {
            ob = clone_object(RICHPURSE);
            ob->move(TP);

            write("Something suddenly materializes in front of you and quickly "+
                  "slips down into your inventory.\n");
            say("Something materializes in front of "+QCTNAME(TP)+" and quickly "+
                "slips down into "+HIS_HER(TP)+" pocket.\n");
            return 1;
        }
    }
  }
  return 0;
}

int
suspension(string str)
{
    object ob;
    int level,s;

    level = query_level(TP);
    s = query_suspension(TP);
  
    NF("Suspend what? Membership?\n");
    if (str == "membership")
    {
        NF("You're not member of this club!\n");
        if (level != 0)
        {
            ob = present("rich_club_obj",TP);
            NF("Your membership are already suspended.\n");
            if (!s)
            {
                ob->remove_object();
                write("You suspend your membership in the Rich Men's Club. "+
                      "You can regain it anytime by typing <regain membership> "+
                      "in this room.\n");
                say(QCTNAME(TP)+" suspends "+TP->query_possessive()+" member"+
                    "ship in the Rich Men's Club.\n");
                set_suspension(TP,1);
                logger("suspended mship");
                return 1;
            }
        }
    }
    return 0;
}

int
regain(string str)
{
    int level,s;
    object ob;
    
    level = query_level(TP);

    NF("Regain what? Membership?\n");
    if (str == "membership")
    {
        NF("You're not a member! You must pay the entry fee first!\n");
        if (level != 0)
        {
            s = query_suspension(TP);
            NF("You are an active member!\n");
            if (s)
            {
                write("Welcome back to the Rich Men's Club. May your life "+
                      "be long and prosperous!\n");
                say(QCTNAME(TP)+" regains "+TP->query_possessive()+" member"+
                    "ship of the Rich Men's Club.\n");
                set_suspension(TP,0);
                ob = clone_object(RICHPURSE);
                ob->move(TP);
                logger("regained mship");
                return 1;
            }
        }
    }
    return 0;
}

    

/*int
painting(string str)
{
  object *players,ob;
  int i,hi,tot;
  string desc,race;

  if (str == "painting" || str == "at painting")
  {
    players = users();

    for (i = 0; i<sizeof(players); i++)
    {
      if (present("rich_club_obj",players[i]))
      {
        write("jashdg 1");
        tot = total_account(players[i]);
        write("jashdg 2");
        if (tot>hi)
        {
          hi = tot;
          ob = players[i];
        }
      }
    }
    desc = ob->query_adjs();
    race = ob->query_gender();

    write("You look at the painting which shows the face of the richest "+
      "member of this club. The portrait of the "+desc+" "+race+" has a "+
      "small golden plaque beneath it which reads: "+CAP(ob->query_real_name())+
      ", The Richest of The Richest.\n");
    say(QCTNAME(TP)+" studies the painting closely.\n");
    return 1;
  }
  return 0;
}
*/

void
notificate(object ob)
{
    object *players;
    int i, p, o, l, m, pr;
    
    FIXEUID;

    players = users();
    l = query_level(ob);
    pr = query_purchased(ob);
    
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
    
    for (i = 0; i < sizeof(players); i++)
    {
        p = query_member(players[i]);
        if (p >= 0 && present("rich_club_obj", players[i]) && players[i] != ob && RMC_NOTE(p))
        {
            if (RMC_PAID(p) <4)
                players[i]->catch_msg(RICH_NOTIFY_MSG[0] + ".\n");
            else if (RMC_PAID(p) < 16)
                players[i]->catch_msg(RICH_NOTIFY_MSG[m] + ".\n");
            else
                players[i]->catch_msg(RICH_NOTIFY_MSG[m] + " as "+ob->query_name() +
                                      " enters the world of Genesis.\n");
        }
    }
}

string
query_president()
{
    return RMC_MEMBER(president);
}

string
query_vice_president()
{
    return RMC_MEMBER(vicepres);
}

void
update_president()
{
    int w,c,p,i,v;

    c = 0;

    for (i = 0; i < sizeof(rdata); i++)
    {
        if (RMC_PAID(i) == 16)
        {
            w = (RMC_PURCHASE(i)/175) + (RMC_ACCOUNT(i)/250) + 1;
            if (w > c)
            {
                c = w;
                p = i;
            }
        }
    }

    c = 0;

    for (i = 0; i < sizeof(rdata); i++)
    {
        if (RMC_PAID(i) == 16 && i != president)
        {
            w = (RMC_PURCHASE(i)/175) + (RMC_ACCOUNT(i)/250) + 1;
            if (w > c)
            {
                c = w;
                v = i;
            }
        }
    }
    president = p;
    vicepres = v;
}

int
query_acc(string str)
{
    int i;

    for (i = 0; i < sizeof(rdata); i++)
    {
        if (RMC_MEMBER(i) == str)
            return RMC_ACCOUNT(i) + RMC_PURCHASE(i);
    }
    return -1;
}

string
query_title(object ob)
{
    int no,lv,pr;
    string s;
    
    no = query_member(ob);
    if (no != -1)
    {
        lv = RMC_PAID(no);
        pr = RMC_PURCHASE(no);

        switch(lv)
        {
        case 1:
            s = RMC_TITLE[0];
            break;
        case 2:
            s = RMC_TITLE[1];
            break;
        case 4:
            s = RMC_TITLE[2];
            break;
        case 8:
            s = RMC_TITLE[3];
            break;
        case 16:
            s = RMC_TITLE[4];
            if (pr > 4000)
                s = RMC_TITLE[6];
            else if (pr > 2000)
                s = RMC_TITLE[5];
            if (no == vicepres)
                s = RMC_TITLE[7];
            if (no == president)
                s = RMC_TITLE[8];
            break;
        case 32:
            s = RMC_TITLE[9];
            break;
        case 33:
            s = RMC_TITLE[10];
            break;
        case 34:
            s = RMC_TITLE[11];
            break;
        case 35:
            s = RMC_TITLE[12];
            break;
        default:
            break;
        }
        return s;
    }
    return "Zippo";
}

string
query_art_title(object ob)
{
    int no,lv,pr;
    string s;
    
    no = query_member(ob);
    if (no != -1)
    {
        lv = RMC_PAID(no);
        pr = RMC_PURCHASE(no);

        switch(lv)
        {
        case 1:
            s = "a "+RMC_TITLE[0];
            break;
        case 2:
            s = "an "+RMC_TITLE[1];
            break;
        case 4:
            s = "a "+RMC_TITLE[2];
            break;
        case 8:
            s = "an "+RMC_TITLE[3];
            break;
        case 16:
            s = "an "+RMC_TITLE[4];
            if (pr > 4000)
                s = "a "+RMC_TITLE[6];
            else if (pr > 2000)
                s = "a "+RMC_TITLE[5];
            if (no == vicepres)
                s += " and the "+RMC_TITLE[7];
            if (no == president)
                s += " and the "+RMC_TITLE[8];
            break;
        case 32:
            s = "a "+RMC_TITLE[9];
            break;
        case 33:
            s = "a "+RMC_TITLE[10];
            break;
        case 34:
            s = "the "+RMC_TITLE[11];
            break;
        case 35:
            s ="the "+ RMC_TITLE[12];
            if (pr > 4000)
                s += " and "+RMC_TITLE[6];
            break;
        default:
            break;
        }
        return s;
    }
    return "Nufber Zippo";
}

string
query_num_title(int n, object ob)
{
    string s;
    int pr,no;
    
    if (ob)
    {
        no = query_member(ob);
        pr = RMC_PURCHASE(no);
    }
    
    switch(n)
    {
    case 1:
        s = RMC_TITLE[0] + "\t\t\t";
        break;
    case 2:
        s = RMC_TITLE[1] + "\t\t\t";
        break;
    case 4:
        s = RMC_TITLE[2] + "\t\t\t";
        break;
    case 8:
        s = RMC_TITLE[3] + "\t";
        break;
    case 16:
        s = RMC_TITLE[4] + "\t";
        if (pr > 4000)
            s = RMC_TITLE[6]+"!\t\t\t";
        else if (pr > 2000)
            s = RMC_TITLE[5] + "\t\t";
        break;
    case 32:
        s = RMC_TITLE[9] + "\t";
        break;
    case 33:
        s = RMC_TITLE[10] + "\t\t\t";
        break;
    case 34:
        s = RMC_TITLE[11] + "\t\t\t";
        break;
    case 35:
        s = RMC_TITLE[12] + "\t\t";
        
        break;
    default:
        break;
    }
    return s;
}

int
query_valuation(object ob)
{
    int no,w,pr,ac,v;
    string s;
    
    no = query_member(ob);
    if (no != -1)
    {
        pr = RMC_PURCHASE(no);
        ac = RMC_ACCOUNT(no);

        v = (pr/175) + (ac/250);

        if (RMC_PAID(no) > 20)
            v = 100 + RMC_PAID(no);
        
        return v + 1;
    }
    return 0;
}

string
query_mypos(object ob)
{
    int no,pos,ma,i,mo, p;
    string *s = ({ }), t;

    pos = 1;
    no = query_member(ob);

    if (no != -1)
    {
        ma = (RMC_PURCHASE(no)/175) + (RMC_ACCOUNT(no)/250) + 1;
        for (i = 0; i < sizeof(rdata); i++)
        {
            p = RMC_PAID(i);
            if (no != i && p > 15 && p < 20)
            {
                mo = (RMC_PURCHASE(i)/175) + (RMC_ACCOUNT(i)/250) + 1;
                if (ma < mo)
                {
                    pos++;
                }
            }
        }

        return "Your position in the RMC is "+pos + ".\n";
    }
    return 0;
}

string
query_pos(string s)
{
    int no,pos,ma,i,v;
    string t;

    pos = 1;

    for (i = 0; i < sizeof(rdata); i++)
    {
        if (RMC_MEMBER(i) == s)
            no = i;
    }

    v = (RMC_PURCHASE(no)/175) + (RMC_ACCOUNT(no)/250) + 1;

    if (RMC_PAID(no) > 20)
        v = 100 + RMC_PAID(no);

    ma = RMC_ACCOUNT(no);
        
    if (no != -1)
    {
        for (i = 0; i < sizeof(rdata); i++)
        {
            if (no != i && RMC_PAID(i)>15 && RMC_PAID(i)<20)
            {
                if (v < ((RMC_PURCHASE(i)/175) + (RMC_ACCOUNT(i)/250) + 1))
                {
                    pos++;
                }
            }
        }

        return "The position for "+capitalize(s)+" in the RMC is "+pos +
            " with account = "+ma+" and valuation = "+v+".\n";
    }
    return 0;
}

string
query_onlogged_members()
{
    object *players,p;
    mixed *list, *sorted;
    int i,j,lvl, no, val, who;
    string title, str, s;

    players = users();
    list = ({ });

    s =  "\n+-------------------------------------------------------+\n";
    s += "| $              Wealthy people working               $ |\n";
    s += "+-------------------------------------------------------+\n";
    for (i = 0; i < sizeof(players); i++)
        if (present("rich_club_obj",players[i]))
            list += ({ ({ players[i], query_level(players[i]),
                          query_valuation(players[i]) }) });

    if (sizeof(list))
    {
        no = sizeof(list);
        s += "| There are "+sizeof(list)+
            " active members right now.   \t        |\n";

        for (i = 150; i > 0; i--)
        {
            for (j = 0; j < no; j++)
            {
                p = list[j][0];
                lvl = list[j][1];
                val = list[j][2];
                
                if (val == i && !p->query_invis())
                {
                    if (p->query_wiz_level()) str = "| (Wiz) ";
                    else if (query_president() == p->query_real_name())
                        str = "| (Prs) ";
                    else if (query_vice_president() == p->query_real_name())
                        str = "| (VPr) ";
                    else str = "| (---) "; 

                    str += p->query_name();

                    if (strlen(str)<=14)
                        str += ",\t\t";
                    else
                        str += ",\t";

                    if (lvl && query_humble(p))
                        str += "Humble Member\t\t\t|";
                    else
                    {
                        str += query_num_title(lvl, p) + "|";
                    }
/*                    if (strlen(str) < 33)
                        str+="\t\t|";
                    else if(strlen(str) < 40)
                        str+="\t|";
                    else
                        str+="|";*/
                    
                    s += str + "\n";
                } 
            }
        }
    }
  s += "+-------------------------------------------------------+\n\n";
  return s;
}

string
force_members(object who)
{
    string s;
    mixed t;
    int i,j;

    s = "\nFORCE\n";
    for (i = 0; i < sizeof(rdata); i++)
    {
        if (!SECURITY->finger_player(RMC_MEMBER(i)))
        {
            s += "Will purge "+RMC_MEMBER(i)+".\n";
            t = "Purged {";
            for (j = 0; j < sizeof(rdata[i]); j++)
            {
                t += rdata[i][j];
                t += ",";
            }
            t += "} .\n";
            write_file(RMC_PURGE_LOG, t);
            rdata = exclude_array( rdata, i, i);
            save_object(RICH_OBJ);
        }
    }
    s += "DONE.\n\n";

    return s;
}
