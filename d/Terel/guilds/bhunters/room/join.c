/*
 
 */

#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <files.h>
#include <macros.h>
#include <stdproperties.h>


inherit STDROOM;


public void join_guild(object who);
public void leave_guild(object who);

string *paid_hunters = ({});

object bartender;

public void reset_terel_room()
{
	if(!objectp(bartender))
	{
		bartender = clone_object(BHNPC + "bartender");
		bartender->move(TO);
	}
}

public void create_terel_room()
{
	set_short("Hook & Dagger");
	set_long("You're inside 'Hook & Dagger', bustling tavern in Last. This place has horrible opinion, all kinds "+
		"scoundrels, thugs and bounty hunters are said to spend their free time here. Odd enough, there is none "+
		"here right now, except for fat bartender sweeping the floor. Way to the staircase, in the corner, is blocked "+
		"by a steel grate.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_exit(BHROOM + "corridor1", "staircase", "@@members", 1, 0);
	reset_room();
}

int members()
{
	if(!TP->query_guild_member(BHNAME))
		write("The grate is locked.\n");
	else
		write("You take a key from one of your belt's pouches and open the grate..\n");
	return 1 - TP->query_guild_member(BHNAME);
}

public int sign(string a)
{
	notify_fail("Sign in, or sign out?\n");
	if(a == "in")
	{
		join_guild(TP);
		return 1;
	}
	if(a == "out")
	{
		leave_guild(TP);
		return 1;
	}
	return 0;
}
		


public void join_guild(object who)
{    
	FIX_EUID;
	object shadow, belt;
	int flag = 0;
   
	if(!objectp(bartender))
		return 0;
	if(who->query_guild_member("layman"))
        {
		who->catch_msg("You already have a layman guild!\n");
		return;
        }	
	else
	{
		shadow = clone_object(BHSHADOW);
		flag = shadow->shadow_me(who, "layman", BHSTYLE, BHNAME);
	}

	switch(flag)
	{
		case 1:
			/* The player has been successfully shadowed. */
			who->catch_msg("Bartender hands you a leather belt.\n");
			who->set_skill(BHRANK, 1);
			belt = clone_object(BHOBJ + "guild_item");
			belt->move(who);			
			return;
		case -4:
			/* The player has the wrong type of guild already, or */
			/* one of his existing guilds has blocked this one. */
			who->catch_msg("Your other guilds prohibit you from joining this one!\n");
			break;
		default:
			/* Shadowing error */
			who->catch_msg("You were unable to enter the militia due to " +
				"a problem in the fabric of space. Contact " +
				"the guildmaster or make a bug report.\n");
	}

}

public void leave_guild(object who)
{
	who->catch_msg("Farewell.\n");
	who->cleanup_hunter();
}


public void init()
{
	::init();
	add_action(sign, "sign");
}

public void pay_hunter(object hunter)
{
	if(member_array(hunter->query_real_name(), paid_hunters) != -1)
		return;
	paid_hunters += ({hunter->query_real_name()});
	object *coins = ({});
	int count = BASE_PAYMENT + 2 * hunter->query_hunter_rank();
	while(count--)
		coins += ({clone_object(BHOBJ + "blood_coin")});
	coins->move(TP);
	hunter->catch_msg("You get " + LANG_NUM2WORD(sizeof(coins)) + " blood " + 
		(sizeof(coins) == 1 ? "coin" : "coins") + " of your weekly payment.\n");
}