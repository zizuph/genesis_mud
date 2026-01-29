/*           R I C H   M E N S   C L U B
* 
*                  THE RICH PURSE
*
* OK Tintin 95-02-08
*
* Made by Conan and Valeria 95-01-01
*
*
* Some more emotes added by Valeria 95-02-02
* Some wiz titles added by Conan   95-02-13
* Account funktions added by Valeria 95-02-15
* More active emotes Valeria 95-02-17
* Fixed the richlist and added some emotes Conan 95-04-03
* Removed the leave_inv(), it now resets the weight. Conan 95-04-18
* Added rlook emote. Conan 95-04-18
* Changed the rpick 95-05-28, Valeria
* Recoded 95-11-30 by Conan, moved the emotes to richsoul.c
*/
#pragma save_binary

inherit "/std/receptacle";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>

string type;
string material,adjec;
mixed *id;
int hole = 0;

query_auto_load()
{
  return MASTER;
}

void
get_me_soul(object ob)
{
    ob->add_cmdsoul(RICHSOUL);
    ob->update_hooks();
}

varargs int
stop(string str)
{
    if (query_verb() == "stop")
    {
        update_actions();
        write("You stop counting.\n");
        remove_alarm(id[0]);
        
        return 1;
    }
    else if (str == "done")
    {
        update_actions();
        return 1;
    }
    else if (query_verb() == "say" || query_verb() == "shout" ||
	     query_verb() == "grin")
        return 0;
    else
    {
        write("You are busy counting. You have to stop if you want " +
                "to do something else.\n");
        return 1;
    }
}

void
rcount_up(int *count_arg, object ob, object tp, string what)
{
    int apa, bepa;

    FIXEUID;
    
    count_arg[2] += count_arg[1];
    if (count_arg[2] < ob->num_heap())
    {
	bepa = random(4) + 1;

	if (bepa == 1)
	    tp->command("say I got "+count_arg[2] + " " +what);
	else if (bepa == 2)
	    tp->command("say And "+count_arg[2] + " " +what);
	else if (bepa == 3)
	    tp->command("say Ahh... I got "+ count_arg[2] + " " + what + ".");
	else if (bepa == 4)
	{
	    tp->command("grin greed");
	    tp->command("say  "+capitalize(count_arg[2]) + " " +what+" is what "+
			"I got");
	}
	    
        apa = set_alarm(itof(count_arg[0]), 0.0, &rcount_up(count_arg, ob, tp, what));
        id = get_alarm(apa);
    }
    else
    {
	tp->command("shout YES! I have "+ ob->num_heap() + " " +what);
        stop("done");
    }
}

void
unset_purse_hole()
{
    hole = 0;
    
    set_long("This is a "+adjec+" "+material+" "+type+" that the "+
	     "members of The Rich Men's Club have. It's "+
	     "used to contain the huge amount of plats that "+
	     "the members of this club has. There's an inscription "+
	     "on one side reading: Use 'rc help' to get the "+
	     "club emotes.\n");
}

void
coins_thru_hole(object ob)
{
    if (hole)
    {
	if (present("coin", TO))
	    say("Some coins falls out of "+QTNAME(ob)+"'s "+type+".\n");
    
	while (present("coin",TO))
	    present("coin",TO)->move(ENV(ob));

	set_alarm( 600.0, 0.0, &coins_thru_hole(ob));
    }
}

void
make_hole()
{
    hole = 1;
    set_long("This is a "+adjec+" "+material+" "+type+" that the "+
	     "members of The Rich Men's Club have. It's "+
	     "used to contain the huge amount of plats that "+
	     "the members of this club has. There's an inscription "+
	     "on one side reading: Use 'rc help' to get the "+
	     "club emotes. There is a hole in the purse. Perhaps "+
	     "someone has put something sharp in it...now you have "+
	     "to repair it.\n");

    (RICHROOM)->set_purse_hole(TP);
    set_alarm( 600.0, 0.0, &coins_thru_hole(TP));
}

void
remove_me()
{
  remove_object();
}

int
make_purse()
{
  int level;
  string title;
  
  seteuid(getuid(TO));
  level = (RICHROOM)->query_level(TP);
  title = (RICHROOM)->query_title(TP);
  
  if (level == 1)
  {
    type = "purse";
    material = "leather";
    adjec = "small";
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 150);
    add_prop(CONT_I_MAX_VOLUME, 10000);
  }
  else if (level == 2)
  {
    type = "purse";
    material = "silver-ornamented";
    adjec = "nice";
    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_MAX_WEIGHT, 15000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 15000);
  }
  else if (level == 4)
  {
    type = "purse";
    material = "gold-shimmering";
    adjec = "expensive";
    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_MAX_WEIGHT, 20000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 20000);
  }
  else if (level == 8)
  {
    type = "money-sack";
    material = "diamond-speckled";
    adjec = "expensive";
    add_prop(CONT_I_WEIGHT ,700);
    add_prop(CONT_I_MAX_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_VOLUME, 40000);
    add_prop(CONT_I_REDUCE_WEIGHT,    1500);
  }
  else if (level >= 16 || level != 34 || level != 33)
  {
    type = "money-sack";
    material = "ruby-speckled";
    adjec = "impressive";
    add_prop(CONT_I_WEIGHT, 1000,);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_REDUCE_WEIGHT,    2500);
  }
  else if (level == 34)
  {
    type = "money-sack";
    material = "amazing";
     adjec = "priceless";
    add_prop(CONT_I_WEIGHT ,700);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(CONT_I_REDUCE_WEIGHT,    5000);
  }
  else if (level == 35)
  {
    type = "money-sack";
    material = "terribly";
     adjec = "valuable";
    add_prop(CONT_I_WEIGHT ,710);
    add_prop(CONT_I_MAX_WEIGHT, 100010);
    add_prop(CONT_I_VOLUME, 710);
    add_prop(CONT_I_MAX_VOLUME, 100010);
    add_prop(CONT_I_REDUCE_WEIGHT,    5000);
  }
  else
  {
    type = "something";
    material = "nauseaus";
    adjec = "broken";
    add_prop(CONT_I_WEIGHT ,50000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_VOLUME, 100);
    set_alarm(2.0,0.0,"remove_me");
  }

  set_name(type);
  add_name("rich_club_obj");
  set_adj(material);
  add_adj(adjec);
  set_short(adjec+" "+material+" "+type);
  set_long("This is a "+adjec+" "+material+" "+type+" that the "+
           "members of The Rich Men's Club have. It's "+
           "used to contain the huge amount of plats that "+
           "the members of this club has. There's an inscription "+
           "on one side reading: Use 'rc help' to get the "+
           "club emotes.\n");
  if (type == "money-sack") add_name("moneysack");
}

void
create_container()
{
  seteuid(getuid(TO));

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_I_NO_STEAL,1);
  add_prop(OBJ_M_NO_SELL,1);
  add_prop(CONT_I_HOLDS_COMPONENTS, 1);
  
  make_purse();
}

public void
enter_env(object dest,object old)
{
  ::enter_env(dest,old);
  remove_name("rich_purse");
  if(present("rich_purse",ENV(TO)))
  {
    tell_room(ENV(TO),"The purses melts together in some mysterical way.\n");
    set_alarm(1.0,0.0,"remove_me");
    return;
  }
  add_name("rich_purse");
  if(living(ENV(TO)))
    dest->add_subloc("rich_purse", this_object());

  set_alarm(2.0,0.0,"greetings");
}

public void
leave_env(object from, object to)
{
  this_player()->remove_subloc("rich_purse");
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob,from);

  if (!(wildmatch("/std/coins*",file_name(ob))  == 1) &&
      !(FIND_STR_IN_OBJECT(" gem ", ob)))
      set_alarm(1.0, 0.0, "resist", ob);
  else
  {
      if (!hole)
      {
	  if (function_exists("set_pen",ob)=="/std/weapon" ||
	      function_exists("set_ac",ob)=="/std/armour")
	      make_hole();
      }
  }
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data,title,how;
    int level;

    if (!(RICHROOM)->query_visible(on))
        return "";
  
    level = (RICHROOM)->query_level(on);
    if (level < 8)
        how = " fastened on the belt";
    else
        how = " over the shoulder";
    
    if (for_obj == on)
        data = "You are gallantly carrying a "+type+how+", which indicates that you're";
    else
        data = capitalize(environment(this_object())->query_pronoun()) + " is "+
            "gallantly carrying a "+type+how+", which indicates that "+
            capitalize(environment(this_object())->query_pronoun())+" is";

    seteuid(getuid(TO));
    title = (RICHROOM)->query_art_title(on) + " of the Rich Men's Club.";
    
    if ((RICHROOM)->query_humble(on))
        return data+" a Humble Member of the Rich Men's Club.\n";
    
    return data+" "+title+"\n";
}

void
init()
{
  int level;

  ::init();
  
  level = (RICHROOM)->query_level(TP);

  add_action("rc", "rc");
  add_action("rdest", "rdest");

  set_alarm( 1.0, 0.0, &get_me_soul(TP));
}

int
resist(object ob)
{
    if (ob != TO)
    {
      write("The "+type+" says: Nah, I don't want "+ob->short()+"!\n");
      ob->move(ENV(TO));
    }
}


int
rcounthi(string str)
{
    string *tmp;
    int *count_arg, intg, apa;
    object ob;

    XRICH_ACCESS(16);

    if(!str)
        return 0;

    notify_fail("Count what?\n");

    str += " coin";

    ob = present(str, TP);
    if (!ob) return 0;

    if (!ob->num_heap()) return 0;

    intg = this_player()->query_stat(SS_INT);

    str += "s";

    count_arg = ({ 5 * (60 / intg), 5 * (intg / 10 + 1), 0 });
    apa = set_alarm(itof(count_arg[0]), 0.0, &rcount_up(count_arg, ob, TP, str));
    id = get_alarm(apa);
    
    add_action(stop, "", 1);
    return 1;
}


/* WELCOME MESSAGE */
int 
greetings()
{
    FIXEUID;

    write("Time for business again, distinguished member of The Rich Men's Club!\n");

    if ((RICHROOM)->query_news_status(TP))
        write("<RMC> New things in the club, please check the 'rc news' command.\n");

    if (!(RICHROOM)->query_visible(TP))
    {
        write("You smile wealthily, but not so that anyone could see it.\n");
    }
    else if ((RICHROOM)->query_humble(TP))
    {
        write("You smile generously.\n");
        say(QCTNAME(TP)+" smiles generously.\n");
    }
    else
    {
        write("You smile wealthily.\n");
        say(QCTNAME(TP)+" smiles wealthily.\n");
    }

    (RICHROOM)->change_account(TP);
    (RICHROOM)->update_president();
    (RICHROOM)->notificate(TP);

    hole = (RICHROOM)->query_purse_hole(TP);
    if (hole)
    {
	set_long("This is a "+adjec+" "+material+" "+type+" that the "+
		 "members of The Rich Men's Club have. It's "+
		 "used to contain the huge amount of plats that "+
		 "the members of this club has. There's an inscription "+
		 "on one side reading: Use 'rc help' to get the "+
		 "club emotes. There is a hole in the purse. Perhaps "+
		 "someone has put something sharp in it...now you have "+
		 "to repair it.\n");

	set_alarm( 60.0, 0.0, &coins_thru_hole(TP));
    }
    return 1;
}

/*
 * ADMIN COMMANDS
*/
int
rdest()
{
  write("\n<RMC> Will destruct the money-sack.\n\n");
  set_alarm(1.0,0.0,"remove_me");
  return 1;
}

int
rc(string str)
{
    string *a;
    int b;
    
    FIXEUID;

    if (!str)
	return 0;
    
    a = explode(str, " ");
    if (a[0] == "counthi")
    {
	if (sizeof(a) > 1)
	    b = rcounthi( a[1] );
	else
	    b = rcounthi("");

	if (b)
	    return 1;

	write("Count what hight? Platinum? Gold?\n");
	return 1;
    }
    return 0;
}

	
