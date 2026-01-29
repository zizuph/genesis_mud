/*
 * The Rich Men's Club Joining Room
 *
 * Coded by Conan Jan -95
 * Assisted by Valeria
 *
 * Changes:
 * 95-02-08: Unknown
 * + Edited.
 * 99-08-17: Tintin
 * + Major recoding.
 * 05-12-14: Lunatari
 * + Typo Fixes to add_cmd_item and moved all the MASTER code out to the
 *   new lib/master.c as a preparation for the RMC move to /d/Sparkle/clubs
 * 06-02-01: Lunatari
 * + Moved a couple of functions and some unused variables from here to
 *   the new master object under lib/ and I also rewrote the repair 
 *   function in this room as well as removed notif command.
 */
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/trade";

static int leava = 0;

#include "defs.h"

int
unset_purse_hole(object ob)
{
    string name = ob->query_real_name();
    object purse = present(PURSE_ID, ob);

    FIXEUID;
    
    if (purse)
    {    
    	if (RMCMASTER->query_purse_hole(name))
	    {
            /* check if the player has enough money */
            if (can_pay(17280 , ob) == 0)
    	    {
	        	ob->catch_msg("You don't have the money to repair it! The cost is "+
			      "10 platinum coins.\n");
        		return 1;
	        }

            /* let the player pay */
    	    pay(17280, ob, "", 0, 0, "", 1); 

    	    RMCMASTER->add_pursepay(10);
	    
    	    purse->unset_hole();
            RMCMASTER->unset_purse_hole(name);

    	    write("Your " + purse->short() + " is " +
    		  "repaired, take more care of it now.\n");

    	    return 1;
	    }

    	write("There's nothing wrong with your " + purse->short() + "!\n");
    	return 1;
    }

    write("You have no purse/sack to repair!\n");
    return 1;
}

string
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
	"|    If your purse has holes in it, we can also repair      |\n"+
	"|              it for you. Type <repair purse>.             |\n"+
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
    setuid();
    seteuid(getuid());
    
    set_short("The Rich Men's Club");
    set_long(break_string(
	"This is a huge room with impressive tapestry and furniture. "+
	"Everything is shining with gold and gemstones; in other words, "+
	"this is the home for 'The Rich Men's Club.' A set of stairs "+
	"leads up to the upper floor where the private rooms are. A sardonyx "+
	"sign is hanging on one of the walls."+
	"\n",60));
  
    INSIDE;
    add_item("tapestry", "Really an impressive tapestry made of purple coloured fabrics.\n");
    add_item("furniture", "Impressive furniture made of oak.\n");
    add_item("sign", "@@sign");
    add_cmd_item("sign","read", "@@sign");
    
    add_exit(RMCROOMS+"private1", "up", "@@check");
    add_exit(RMCROOMS+"pier", "south");
    
    config_default_trade();
}

void
init()
{
    ::init();
  
    add_action("join"      , "consider");
    add_action("rpay"      , "pay");
    add_action("cost"      , "cost");
    add_action("leave"     , "leave");
    add_action("newpurse"  , "newpurse");
    add_action("suspension", "suspend");
    add_action("regain"    , "regain");
    add_action("repair"    , "repair");
}

int
check()
{
    if (TP->query_wiz_level() > 0)
    {
      write("You are a wizard and may pass.\n");
      return 0;
    }

    if ((RMCMASTER->query_member(TP->query_real_name())) && 
        (!RMCMASTER->query_suspension(TP->query_real_name()))) 
	    return 0;

    if (RMCMASTER->query_suspension(TP->query_real_name()))
    {
		write("Uhm, You have suspended our membership, perhaps you should regain it first.\n");
		return 1;
    }
    
    write("Uhm, no, you don't dare to climb the stairs. Maybe you could slip "+
	  "and hurt yourself.\n");
    return 1;
}

int
join()
{
    write(break_string(
	"It is quite easy to join this club. All you have to "+
	"do is to pay the entry fee of 100 platinum coins. To do this, "+
	"type <pay entry>, and you will receive the first title of this "+
	"club. To enhance your title, type <cost title> to find out how "+
	"much money you will have to pay for it, and <pay title> to get "+
	"the higher title. Note that the higher the title is, the "+
	"greater the cost will be.\n",60));
    say(QCTNAME(TP)+" asks about how to join this exclusive club.\n");
  
    return 1;
}

int
repair(string str)
{
    NF("Repair what? The purse/sack/money-sack?\n");

    if (str == "purse" || str == "sack" || str == "money-sack")
	    return unset_purse_hole(TP);

    return 0;
}

int
cost(string str)
{
    int fee, level;
    string title;
    
    notify_fail("Cost for what? Title?\n");

    if (str == "title" && (RMCMASTER)->query_member(TP->query_real_name()))
    {
    	level = (RMCMASTER)->query_level(TP->query_real_name());

    	if (level < 16)
    	{
    	    fee = level * 200;
    	    title = (RMCMASTER)->query_num_title(level * 2);
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
    int cost, level, ban;
    string name, title, stitle;
    object ob, purse;
    name = TP->query_real_name();

    if (!(RMCMASTER)->query_member(name))
    {

    	if (str == "entry")
    	{
    	    if (TP->query_wiz_level())
    	    {
    	    	write("Ahhh...a wizard that wants to join this club.\nWell, we feel "+
    		      "honoured by that so you will be able to join without paying "+
    		      "anything!\n");
		
        		title = (RMCMASTER)->query_num_title(32);
		
    	    	TP->catch_msg("You pay the entry fee to join The Rich Men's Club.\n");
	    	    TP->catch_msg("You have the title '"+title+"' in this club. If you want "+
    			      "to leave it some day, type <leave rich club>.\n");
        		say(QCTNAME(TP)+" joined The Rich Men's Club.\n");
		
    	    	(RMCMASTER)->add_wizard_member(name);
		
    		    (RMCMASTER)->logger("joined the club");
		
        		ob = clone_object(RMCPURSE);
        		ob->move(TP);
		    
	    	    return 1;
    	    }      
	        else
	        {
        		cost = 172800;
	    
                /*check if the player has enough money */
    	    	if (!can_pay(cost, TP))
        		{
        		    TP->catch_msg("You're a poor one! You lack the money needed to join us!\n");
    	    	    return 1;
        		}
		
	        	title = (RMCMASTER)->query_num_title(1);
		
    	    	pay(cost, TP, "", 0, 0, "", 1); /* let the player pay */
	    	    (RMCMASTER)->add_howmuch(100);
		
    		    TP->catch_msg("You pay the entry fee to join The Rich Men's Club.\n");
        		TP->catch_msg("You have the title '"+title+"' in this club. If you want "+
		    	      "to leave it some day, type <leave rich club>.\n");
    		    say(QCTNAME(TP)+" joined The Rich Men's Club.\n");
		
        		(RMCMASTER)->add_member(name);
		
        		(RMCMASTER)->logger("joined the club");
		
    	    	ob = clone_object(RMCPURSE);
    		    ob->move(TP);
		
    	    	return 1;
	        }
    	}
       	return 0; // Not member, and not entry as param
    }
    else
    {
    	if (str ="title") // This is a member
	    {
    	    level = (RMCMASTER)->query_level(name);
	        if (level >= 16)
    	    {
    	    	TP->catch_msg("You already have the highest title in this club.\n");
	        	return 1;
    	    }
	    
	        cost = level * 345600;
	    
    	    if (!can_pay(cost,TP))
    	    {
        		TP->catch_msg("Ha! You haven't got that kind of money!\n");
    	    	return 1;
	        }
	    
            title = (RMCMASTER)->query_num_title(level * 2);
	    
	        pay(cost, TP);
	        (RMCMASTER)->add_howmuch(level * 200);
	    
    	    TP->catch_msg("You pay the price to enhance your title in the club.\n");
	        TP->catch_msg("You have the title '"+title+"' in this club.\n");
    	    say(QCTNAME(TP)+" increased "+TP->query_possessive()+" title in this "+
        		"club to '"+title+"'.\n");
	    
    	    (RMCMASTER)->set_level(name, 2 * ((RMCMASTER)->query_level(name)));
	    
	        ob = clone_object(RMCPURSE);           /* clone a new club object */
	        /* Before getting rid of the old purse, move everything to the new
    	     * purse. Otherwise we get rather disgruntled members.
	         */
    	    purse = present("rich_club_obj", TP);
	        if (objectp(purse))
    	    {
        		all_inventory(purse)->move(ob, 1);
	        	purse->remove_object();
    	    }

            // The move must happen after we destroy the old purse!
    	    ob->move(TP, 1);
	    
    	    (RMCMASTER)->logger("improved to " + level*2);
	    
    	    return 1;
	    }
    } 
}

int
leave(string str)
{
    int level, member;
    object purse;
    
    if (str == "rich club" && (RMCMASTER)->query_member(TP->query_real_name()))
    {
    	if (leava == 0)
    	{
    	    TP->catch_msg("Sure you want to leave this club? In that case "+
    			  "type <leave rich club again>.\n");
    	    leava = 1;
    	    return 1;
    	}
	
    	purse = present(PURSE_ID, TP);

    	if (purse)
    	{
    	    all_inventory(purse)->move(TP, 1);
    	    purse->remove_object();
    	}
	
    	TP->catch_msg("You leave 'The Rich Men's Club'. The purse is "+
    		      "disintegrated by some magic force.\n");
    	say(QCTNAME(TP)+"'s purse is disintegrated by some magic force.\n");
	
    	(RMCMASTER)->remove_member(TP->query_real_name());
	
    	(RMCMASTER)->logger("left the club");
	
    	leava = 0;

    	return 1;
    }
    
    return 0;
}

int
newpurse()
{
    object ob;
    int level, s;
    
    level = (RMCMASTER)->query_level(TP->query_real_name());
    
    NF("You are not member of this club!\n");
    if (level != 0)
    {
	NF("You have already got a purse!\n");
	if (!present(PURSE_ID,TP))
	{
	    s = (RMCMASTER)->query_suspension(TP->query_real_name());
	    NF("Your membership is suspended!\n");
	    if (!s)
	    {
		ob = clone_object(RMCPURSE);
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
  
    NF("Suspend what? Membership?\n");
    if (str == "membership")
    {
        NF("You're not member of this club!\n");
        if ((RMCMASTER)->query_level(TP->query_real_name()))
        {
            ob = present(PURSE_ID,TP);
            NF("Your membership is already suspended.\n");
            if (!(RMCMASTER)->query_suspension(TP->query_real_name()))
            {
                all_inventory(ob)->move(TP, 1);
                ob->remove_object();
                write("You suspend your membership in the Rich Men's Club. "+
                      "You can regain it anytime by typing <regain membership> "+
                      "in this room.\n");
                say(QCTNAME(TP)+" suspends "+TP->query_possessive()+" member"+
                    "ship in the Rich Men's Club.\n");
                (RMCMASTER)->set_suspension(TP, 1);
                (RMCMASTER)->logger("suspended mship");
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
    
    level = (RMCMASTER)->query_level(TP->query_real_name());

    NF("Regain what? Membership?\n");
    if (str == "membership")
    {
        NF("You are not a member! You must pay the entry fee first!\n");
        if (level != 0)
        {
            s = (RMCMASTER)->query_suspension(TP->query_real_name());
            NF("You are an active member!\n");
            if (s)
            {
                write("Welcome back to the Rich Men's Club. May your life "+
                      "be long and prosperous!\n");
                say(QCTNAME(TP)+" regains "+TP->query_possessive()+" member"+
                    "ship of the Rich Men's Club.\n");
                (RMCMASTER)->set_suspension(TP,0);
                ob = clone_object(RMCPURSE);
                ob->move(TP);
                (RMCMASTER)->logger("regained mship");
                return 1;
            }
        }
    }
    return 0;
}
