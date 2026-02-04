/*
 emotes for bounty hunters guild, 
  by Udana 05/06
 */

#include <cmdparse.h>
#include <macros.h>
#include "./bhunters.h"
#include "/d/Terel/include/Terel.h"

/*
 emote 'bhwarn'

*/
int bhwarn(string a)
{
	mixed *target_list;
	object real_target;
	string *bounties;
	notify_fail("Warn whom?\n");
	if(!strlen(a))
		return 0;
	if(!parse_command(a, E(TP), " %l ", target_list))
		return 0;
	/* first is numeral descriptor */
	if(sizeof(target_list) > 2)
	{
		notify_fail("Warn one person at a time.\n");
		return 0;
	}
	real_target = target_list[1];
	if(real_target == TP)
	{
		notify_fail("Why would you warn yourself?\n");
		return 0;
	}
	/* load the office */
	OFFICE->teleledningsanka();
	bounties = OFFICE->get_bounties();
	if(member_array(real_target->query_real_name(), bounties) == -1)
	{
		actor("You warn", ({real_target}), ", even though there is " +
			"no reward for " + real_target->query_objective() + " you'll hunt "
			+ real_target->query_objective() + " down, just for practice.");
		target(" warns you, even though there is no reward for your head, " +
			TP->query_pronoun() + " will hunt you down, just as an exercise.", ({real_target}));
		all2act(" warns", ({real_target}), " even though there is no reward for " +
			real_target->query_objective() + " " + QNAME(TP) + " will hunt " +
			real_target->query_objective() + " down, just for practice.");
		return 1;
	}
	actor("You warn", ({real_target}), "it's nothing personal. But you'll claim reward for "+
		real_target->query_possessive() + " head.");
	target(" warns you, " + TP->query_pronoun() + " holds no personal grudge for you, but " +
		TP->query_pronoun() + " will claim reward for your head.", ({real_target}));
	all2act(" warns", ({real_target}), " it's nothing personal, but " + TP->query_pronoun() + 
		" will claim reward for " + real_target->query_possessive() + " head.");
	return 1;
}


/* 
 emote 'bhlook'
*/

int bhlook(string a)
{
	mixed *target_list;
	object real_target;

	notify_fail("Look at whom?\n");
	
	if (!strlen(a))
		return 0;

	if(!parse_command(a, E(TP), " [at] %l ", target_list))
		return 0;
	
	if(sizeof(target_list) > 2)
	{
		write("You look around looking for a pray.\n");
		say(QCTNAME(TP) + " as if he was looking for something.\n");
		return 1;
	}
	
	real_target = target_list[1];
	if(real_target == TP)
	{
		notify_fail("You would need a mirror.\n");
		return 0;
	}
	
	actor("You look at", ({real_target}), ", your next prey.");
	target(" looks at you like if " + this_player()->query_pronoun() +
		" owned you.",  ({real_target}));
	all2act(" looks at" ,  ({real_target}), " like if he owned " + (real_target->query_gender() ? "her" : "him") +
		". It wouldn't be wise to step between bounty hunter and " + TP->query_possessive() +
		" prey.");
	return 1;
}

/*
	emote 'bhoffer'
*/
int bhoffer(string a)
{
	mixed *target_list;
	notify_fail("Offer your services to whom?\n");
	
	if (!strlen(a))
		return 0;
	
	if(!parse_command(a, E(TP), " [to] %l ", target_list))
		return 0;
	
	target_list -= ({TP});
	target_list = target_list[1..sizeof(target_list)];
	if(!sizeof(target_list))
		return 0;
	actor("You offer", target_list, " to solve any 'problem', for a nominal fee.");
	target(" offers to get rid of any of your enemies, for a nominal fee.", target_list);
	all2act(" offers ", target_list, ", solve any 'problem', for a nominal fee.");
	return 1;
}

/*
	emote 'bhcoins'
*/
int bhcoins(string a)
{
	object *all_coins = filter(all_inventory(TP), &->id("coin"));
	int coin_amount = 0;
	for(int i = 0; i < sizeof(all_coins); ++i)
		coin_amount += all_coins[i]->num_heap() + random(5);
	if(coin_amount == 0)
	{
		notify_fail("Unfortunately, you don't carry any coins with you.\n");
		return 0;
	}
	write("You take a quick glimpse at your coins, approximating their amount.\n");
	write("You've got about " + coin_amount + " with you.\n");
	say(QCTNAME(TP) + " takes a quick glimpse at his coins, trying to approximate their " +
		"amount. You feel uneasy knowing where that money came from.\n");
	return 1;
}