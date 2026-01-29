/*
 * R I C H   M E N S   C L U B
 * 
 * THE RICH PURSE
 *
 * History
 *
 * 95-01-01: Created, Conan and Valeria
 * 95-02-02: Some more emotes added, Valeria
 * 95-02-08: Purse OK, Tintin 
 * 95-02-13: Some wiz titles added, Conan
 * 95-02-15: Account functions added, Valeria 
 * 95-02-17: More active emotes, Valeria
 * 95-04-03: Fixed the richlist and added some emotes, Conan
 * 95-04-18: Removed the leave_inv(), it now resets the weight, Conan
 * 95-04-18: Added rlook emote, Conan
 * 95-05-28: Changed the rpick, Valeria  
 * 95-11-30: Moved the emtoes to richsoul.c, Conan
 * 05-11-14: Updated and Prepared for Sparkle domain move, Lunatari
 * 06-01-31: counthi was moved out to rmcsoul.c, Lunatari
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>

#define LONG "This is " + LANG_ADDART(implode(query_adj(1), " ")) + " "\
	   + query_name() +" "+\
	   "that the members of The Rich Men's Club have. It is " +\
       "used to hold the huge amount of platinum coins that " +\
       "the members of this club have. There is an inscription " +\
       "on one side reading: Use 'rc help' to get the " +\
       "club emotes.\n"

#define BROKENLONG "This is " + LANG_ADDART(implode(query_adj(1), " ")) + " " +\
	     query_name() + " that the "+\
	     "members of The Rich Men's Club have. It is " +\
	     "used to contain the huge amount of platinum coins that " +\
	     "the members of this club have. There is an inscription " +\
	     "on one side reading: Use 'rc help' to get the " +\
	     "club emotes. There is a hole in the purse, as from a sharp " +\
	     "object. It needs repair.\n"

mixed *id;
int hole = 0;

mixed *pursetypes =
({
    ({ "purse", "leather", "small", 100, 10000, 150, 10000, 0 }),
    ({ "purse", "silver-ornamented", "nice", 200, 15000, 500, 15000, 0 }),
    ({ "purse", "gold-shimmering", "expensive", 50, 20000, 500, 20000, 0 }),
    ({ "money-sack", "diamond-speckled", "expensive", 700, 40000, 700, 40000, 1500 }),
    ({ "money-sack", "ruby-speckled", "impressive", 1000, 50000, 1000, 10000, 2500 }),
    ({ "money-sack", "amazing", "priceless", 700, 100000, 700, 100000, 5000 }),
    ({ "money-sack", "valuable", "terribly", 710, 100010, 710, 100010, 5000 }),
    ({ "something", "nauseaus", "broken", 50000, 50000, 100, 100, 0 })
});

string
query_auto_load()
{
    return MASTER;
}

void
get_me_soul(object ob)
{
    ob->add_cmdsoul(RMCSOUL);
    ob->update_hooks();
}

void
coins_thru_hole(object ob)
{
    if (hole)
    {
    	if (present("coin", TO))
	        say("Some coins falls out of " + QTNAME(ob) + "'s " + query_name() + ".\n");
    
    	while (present("coin", TO))
            present("coin", TO)->move(ENV(ob));

    	set_alarm( 600.0, 0.0, &coins_thru_hole(ob));
    }
}

void
make_hole()
{
    hole = 1;
    set_long(BROKENLONG);

    (RMCMASTER)->set_purse_hole(TP->query_real_name());
    set_alarm( 600.0, 0.0, &coins_thru_hole(TP));
}

void
unset_hole()
{
    hole = 0;
    
    set_long(LONG);
}

void
create_container()
{
    mixed *purse;
    int level;

    seteuid(getuid(TO));
    
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_NO_STEAL,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
     
    level = RMCMASTER->query_level(TP->query_real_name());

    switch (level)
    {
    case 1:
	purse = pursetypes[0];
	break;
    case 2..3:
	purse = pursetypes[1];
	break;
    case 4..7:
	purse = pursetypes[2];
	break;
    case 8..15:
	purse = pursetypes[3];
	break;
    case 16..32:
	purse = pursetypes[4];
	break;
    case 33:
	purse = pursetypes[5];
	break;
    case 34:
	purse = pursetypes[6];
	break;
    default:
	purse = pursetypes[7];
	set_alarm(2.0, 0.0, &remove_object());
    }
    
    set_name(purse[0]);
    add_name(PURSE_ID);
    set_adj(purse[1]);
    add_adj(purse[2]);
    set_short(purse[2] + " " + purse[1] + " " + purse[0]);
    set_long(LONG);

    if (purse[0] == "money-sack")
	add_name("moneysack");

    add_prop(CONT_I_WEIGHT, purse[3]);
    add_prop(CONT_I_MAX_WEIGHT, purse[4]);
    add_prop(CONT_I_VOLUME, purse[5]);
    add_prop(CONT_I_MAX_VOLUME, purse[6]);

    if (purse[7])
	add_prop(CONT_I_REDUCE_WEIGHT, purse[7]);

    hole = (RMCMASTER)->query_purse_hole(TP->query_real_name());

    if (hole)
    {
	    set_long(BROKENLONG);
    	set_alarm(60.0, 0.0, &coins_thru_hole(TP));
    }
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    remove_name(PURSE_ID);
    if (present(PURSE_ID, ENV(TO)))
    {
	tell_room(ENV(TO),
		  "The purse melts together in some mysterious way.\n");
	set_alarm(1.0,0.0, &remove_object());
	return;
    }
    add_name(PURSE_ID);
    if (living(ENV(TO)))
	dest->add_subloc(RMCSUBLOC, this_object());

    set_alarm(2.0,0.0, "greetings");
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc(RMCSUBLOC);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!(wildmatch("/std/coins*", file_name(ob)) == 1) &&
	!(FIND_STR_IN_OBJECT(" gem ", ob)))
	set_alarm(1.0, 0.0, "resist", ob);
    else
    {
	if (!hole)
	{
	    if (function_exists("set_pen", ob) == "/std/weapon" ||
		function_exists("set_ac", ob) == "/std/armour")
		make_hole();
	}
    }
}

public string 
show_subloc(string subloc, object on, object for_obj)
{
    string data, title, how;

    if (!(RMCMASTER)->query_visible(on->query_real_name()))
        return "";
  
    if ((RMCMASTER)->query_level(on->query_real_name()) < 8)
        how = " fastened on the belt";
    else
        how = " over the shoulder";
    
    if (for_obj == on)
        data = "You are gallantly carrying a " + query_name() + how +
	    ", which indicates that you are";
    else
        data = capitalize(environment(this_object())->query_pronoun()) +
	    " is gallantly carrying a " + query_name() + how +
	    ", which indicates that "+
            capitalize(environment(this_object())->query_pronoun()) + " is";

    seteuid(getuid(TO));
    title = (RMCMASTER)->query_art_title(on->query_real_name()) +
	" of the Rich Men's Club.";
    
    if ((RMCMASTER)->query_humble(on->query_real_name()))
        return data+" a Humble Member of the Rich Men's Club.\n";
    
    return data + " " + title + "\n";
}

void
init()
{
    ::init();
        
    set_alarm( 1.0, 0.0, &get_me_soul(TP));
}

int
resist(object ob)
{
    if (ob != TO)
    {
      write("The "+query_name()+" says: Nah, I don't want "+ob->short()+"!\n");
      ob->move(ENV(TO));
    }
}

/* 
 * WELCOME MESSAGE 
 */
int 
greetings()
{
    write("Time for business again, distinguished member of The Rich Men's Club!\n");

    if (TP->query_wizlevel() && (RMCMASTER)->query_level(TP->query_real_name()) < 32)
    	(RMCMASTER)->set_level(TP->query_real_name(), 32);

    if ((RMCMASTER)->query_news_status(TP->query_real_name()))
        write("<RMC> New things in the club, please check the 'rc news' command.\n");

    if (!RMCMASTER->query_visible(TP->query_real_name()))
    {
        write("You smile wealthily, but not so that anyone could see it.\n");
    }
    else if (RMCMASTER->query_humble(TP->query_real_name()))
    {
        write("You smile generously.\n");
        say(QCTNAME(TP)+" smiles generously.\n");
    }
    else
    {
        write("You smile wealthily.\n");
        say(QCTNAME(TP)+" smiles wealthily.\n");
    }

    RMCMASTER->change_account(TP->query_real_name());

    if (!random(10)) /* Don't check every time */
    	RMCMASTER->update_president();

    RMCMASTER->notificate(TP->query_real_name());

    return 1;
}