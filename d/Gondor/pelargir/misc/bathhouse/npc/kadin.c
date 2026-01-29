/*
 * /d/Gondor/pelargir/misc/bathhouse/npc/kadin.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * owner of bathhouse -- pay her to take a bath.
 */

#pragma strict_types


inherit "/d/Gondor/std/monster";
inherit	"/lib/trade";

#include <const.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../bath.h"


/* people who knocked on the door while bath was under construction.
 * this will be removed once we've given each a free bath.
 */
string	*Freebies = ({ "Tharizdun", "Thalis", "Bromoru", });
string	FirstCustomer = "";
mapping	Banned = ([ ]);

/* prototypes in order of appearance */
public void	create_gondor_monster();
public void	init_living();
public string	ask_bath();
public int	parse_pay(string arg);
public void	pay_for_bath();
public void	greet(object pl, string vb);
public void	add_banned(string name, string reason);
public string	query_banned(string name);
public void	remove_banned(string name);
public void	add_freebie(string name);
public void	remove_freebie(string name);
public void	remove_first(string name);


/*
 * Function name:	create_gondor_monster
 * Description	:	set up the npc
 */
public void
create_gondor_monster()
{
    
    FIX_EUID;

    restore_object(OWNER_FILE);

    set_name( ({ "kadin", "woman", "owner", "attendant", }) );
    set_living_name("kadin");
    set_gender(G_FEMALE);
    set_adj( ({ "calm", "black-haired", }) );
    set_race_name("human");
    GONDOR_MASTER->npcsize(TO, "tall", "normal");
   
    set_stats( ({ 60, 60, 60, 60, 60, 60 }) );
    set_alignment(500);
   
    config_default_trade();

    add_prop(PLAYER_I_BATH, I_AM_DRY_AND_CLEAN);
    (BATH_DIR + "bath")->short();
    add_subloc(WET_SUBLOC, (BATH_DIR + "bath"));


    set_chat_time(15);
    add_chat("A hot bath will wash away cares, as well as dirt.");
    add_chat("You'll feel much more fresh after a hot bath.");
    add_chat("There's nothing more relaxing than a nice hot bath.");
    add_chat("Ahhh, the pleasure of soaking in a tub of hot water.");
    add_chat("You'll be much more attractive to that certain someone " +
	"after you've bathed.");
    add_chat("It only costs " + BATH_PRICE_STRING +
	" for a nice hot bath. That will be money well-spent.");
    add_chat("You can soon be soaking chin-deep in a nice soothing " +
	"tub of hot water.");

    add_prop(OBJ_M_NO_ATTACK, "This does not seem wise.\n");

    set_dont_answer_unseen(1);
    set_default_answer( ({ ({ "peer @@query_player_name@@",
	"I'm afraid I can't help you with that." }) }) );
    add_ask_item( ({ "bath", "bathing", "baths", "cost", "price",
	"cost of bath", "cost of a bath", "price of bath",
	"price of a bath" }),
	VBFC_ME("ask_bath"));
    add_ask_item( ({ "job", "work", "task", "assignment", "chore",
	"quest", "help" }),
	({ "say I'm sorry, but I don't have any task for you at present.",
	   "say I don't believe I have any jobs just now.",
	   "say Thank you, but I don't need any help today.",
	}) );

} /* create_gondor_monster */


/*
 * Function name:	init_living
 * Description	:	add verbs for paying for bath
 */
public void
init_living()
{
    add_action(parse_pay, "pay");
} /* init_living */


/*
 * Function name:	ask_bath
 * Description	:	respond to request for bath
 * Returns	:	null str (response given via command())
 */
public string 
ask_bath()
{
    string resp;

    if (TP->query_prop(PLAYER_I_PAID))
    {
	resp = "say You've already paid for a bath, " +
	    (TP->query_met(TO) ?
		 TP->query_name() : TP->query_nonmet_name())
	    + ". ";
	switch (TP->query_gender())
	{
	case G_FEMALE:
	    resp += "If you'll just step through the doorway " +
		"to the east, the attendant will help you.";
	    break;
	case G_MALE:
	    resp += "If you'll just step through the doorway " +
		"to the west, the attendant will help you.";
	    break;
	default:
	    resp = "If you'll just step through the east or " +
		"the west doorway, the attendant will help you.";
	    break;
	}
    }
    else
    {
	resp = 
	    ({ "say A bath costs " + BATH_PRICE_STRING +
		    ", including soap and towels. ",
	       "say It's only " + BATH_PRICE_STRING + " for a bath. ",
	       "say I charge only " + BATH_PRICE_STRING + 
		    " for a bath. ",
	    })[random(3)] + PAY_ME;
    }
    command(resp);
    return "";
}

/*
 * Function name:	parse_pay
 * Description	:	parse attempts to pay for a bath
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	int -- 1 if we understand the arg, 0 if not
 */
public int
parse_pay(string arg)
{
    string	tmpstr;
    if (!CAN_SEE_IN_ROOM(TP) ||
	!CAN_SEE(TP, TO))
    {
	NF0("You can't see anyone to pay.\n");
    }
    if (!strlen(arg))
    {
	pay_for_bath();
	return 1;
    }
    arg = LOW(arg);
    if (parse_command(arg, ({}), "%s 'for' [a] 'bath'", tmpstr))
    {
	if (!strlen(tmpstr))
	{
	    pay_for_bath();
	    return 1;
	}
	arg = tmpstr;
    }
    if (id(arg) ||
	parse_command(arg, ({}), "[calm] [black-haired] [female] 'human'"))
    {
	pay_for_bath();
	return 1;
    }
    NF0("Pay whom?\n");
} /* parse_pay */


/*
 * Function name:	pay_for_bath
 * Description	:	if they can afford it, remove the coins and
 *			set the paid-for-bath prop
 */
public void
pay_for_bath()
{
    int		*money,
		n;
    string	coin_pay_text,
		coin_get_text,
		ob_name,
		tp_name;

    if (!CAN_SEE_IN_ROOM(TO) ||
	!CAN_SEE(TO, TP))
    {
	command("say What? Who's that? I can't see you!");
	return;
    }

    ob_name = OB_NAME(TP),
    tp_name = (TP->query_met(TO) ?
		   TP->query_name() : TP->query_nonmet_name());

    if (strlen(Banned[TP->query_name()]))
    {
	command("scowl " + ob_name);
	return;
    }

    money = pay(BATH_PRICE_COPPERS, TP, 0, 0, 0, 0);
    if (sizeof(money) == 1)
    {
	command("say to " + ob_name +
	    " I'm afraid you cannot afford a bath, " + tp_name + ".");
	return;
    }

    n = sizeof(MONEY_TYPES);
    coin_pay_text = text(exclude_array(money, n, n*2-1));
    coin_get_text = text(exclude_array(money, 0, n-1));
    write("You pay " + coin_pay_text + " to " + 
	process_string(QCTNAME(TO)) + ".\n");
    tell_room(ENV(TO),
	QCTNAME(TP) + " pays some coins to " + QTNAME(TO) + ".\n",
	TP);

    if (coin_get_text)
    {
        write("You get " + coin_get_text + " back.\n");
    }
    TP->add_prop(PLAYER_I_PAID, 1);

    switch (TP->query_gender())
    {
    case G_FEMALE:
	command("smile " + ob_name);
	command("say to " + ob_name +
	    " The women's bath is to the east.");
	break;
    case G_MALE:
	command("smile " + ob_name);
	command("say to " + ob_name +
	    " The men's bath is to the west.");
	break;
    default:
	command("peer worriedly " + ob_name);
	command("say Well, the women's bath is to the east and the " +
	   "men's is to the west.");
	command("say Choose whichever you like, I suppose.");
	command("confused");
	break;
    }
    command("say to " + ob_name + " Enjoy your bath, " + tp_name + "!");
} /* pay_for_bath */


/*
 * Function name:	greet
 * Description	:	greet customers
 * Arguments	:	object pl -- the customer
 *			string vb -- verb s/he used to enter
 */
public void
greet(object pl, string vb)
{
    string	ob_name,
		pl_name,
		tmpstr;

    if (!interactive(pl) ||
	ENV(pl) != ENV(TO) ||
	!CAN_SEE_IN_ROOM(TO) ||
	!CAN_SEE(TO, pl))
    {
	return;
    }

    ob_name = OB_NAME(pl);
    pl_name = (pl->query_met(TO) ?
		   pl->query_name() : pl->query_nonmet_name());

    if (vb == "east" ||
        vb == "west")
    {
	if (pl->query_prop(PLAYER_I_BATH) == I_AM_DRY_AND_CLEAN)
	{
	    command("smile warmly " + ob_name);
	    command("say to " + ob_name + 
		({ " Did you enjoy your bath, " + pl_name + "?",
		   " You're looking very clean, " + pl_name + ".",
		   " I hope your bath was pleasant, " + pl_name + ".",
		})[random(3)]);
	}
    }
    else if (!strlen(FirstCustomer) &&
	     !pl->query_wiz_level() &&
	     (tmpstr = pl->query_name()) != "Xyzzy" &&
	     !sscanf(tmpstr, "%sjr", tmpstr))
    {
	FirstCustomer = pl->query_name();
	/* don't give 'em two freebies
	 * remove_freebie() will call save_object
	 */
	remove_freebie(FirstCustomer);

	command("bow warmly " + ob_name);
	command("introduce me to " + ob_name);
	command("say Welcome to the Pelargir Baths!");
	command("say Since you are our very first customer, " +
	    "there is no charge for your bath.");
	command("emote gestures invitingly toward the " + 
	   (pl->query_gender() == G_FEMALE ? "east" : "west") +
	   " door.");
	pl->add_prop(PLAYER_I_PAID, 1);
    }
    else if (member_array(TP->query_name(), Freebies) >= 0)
    {
	command("bow warmly " + ob_name);
	command("introduce me to " + ob_name);
	command("say to " + ob_name + 
	   " The builders told me that you came by before " +
	   "we opened. ");
	command("say to " + ob_name + " I'm so sorry you had to wait.");
	command("say to " + ob_name +
	   " Please, let your first bath here be my treat.");
	command("emote gestures invitingly toward the " + 
	   (pl->query_gender() == G_FEMALE ? "east" : "west") +
	   " door.");
	pl_name = pl->query_name();
	remove_freebie(pl_name);
	pl->add_prop(PLAYER_I_PAID, 1);
    }
    else
    {
	command("say to " + ob_name + " Would you like to try a " +
           "nice relaxing bath, " + pl_name + "?");
	command("smile encouragingly " + ob_name);
    }
} /* greet */


/*
 * Function name:	add_banned
 * Description	:	add player to list of persona non grata
 * Arguments	:	string name -- name
 *			string reason -- why the eviction
 */
public void
add_banned(string name, string reason)
{
    if (strlen(name))
    {
	name = CAP(name);
	if (strlen(reason))
	{
	    reason = CAP(reason);
	}
	else
	{
	    reason = "Troublemakers";
	}
	Banned[name] = reason;
	save_object(OWNER_FILE);
    }
} /* add_banned */


public string query_banned(string name)  { return Banned[CAP(name)]; }
public void remove_banned(string name)
{
    Banned = m_delete(Banned, CAP(name));
    save_object(OWNER_FILE);
}




/* code for freebies will all be removed as soon as array is emptied */
public void
add_freebie(string name)
{
    Freebies += ({ CAP(name) });
    save_object(OWNER_FILE);
}
public void
remove_freebie(string name)
{
    Freebies -= ({ CAP(name) });
    save_object(OWNER_FILE);
}
public void
remove_first(string name)
{
    FirstCustomer = "";
    save_object(OWNER_FILE);
}
