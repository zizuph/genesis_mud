/*
  Shopkeeper of the trap store.
    by Udana, 06/06
*/

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../bhunters.h"

inherit STDMONSTER;

public mapping *query_components()
{
	return ({});
}

void create_keeper()
{}

string living_name()
{
	return "";
}
	
void create_terel_monster()
{
	create_keeper();
	set_alignment(random(30) - random(30));
	set_hp(query_max_hp());
	add_ask(({"trap", "traps"}), "@@trap_answer");
	add_ask("components", "@@components_answer");
	add_name("_bhkeeper_");
	set_race_name("human");
	
	enable_intro();
	set_act_time(20 + random(10));
  
}

public void init_living()
{
	::init_living();
	add_action("list", "list");
	add_action("buy", "buy");
}

string prelong_line(string line)
{
	int length = 38;
	if(strlen(line) > length)
		return "error\n";
	while(strlen(line) < length)
		line += " ";
	return "|" + line + "|\n";
}

int list(string a)
{
	notify_fail("List what?\n");
	if(strlen(a) && a != "components")
		return 0;
	write("_______________________________________\n");
	write(prelong_line(""));
	for(int i = 0; i < m_sizeof(query_components()[0]); ++i)
	{
		string name = m_indexes(query_components()[0])[i];
		int prize = query_components()[1][m_indexes(query_components()[0])[i]];
		write(prelong_line(" " + name + " - " + prize + " blood " + (prize == 1 ? "coin" : "coins")));
	}
	write(prelong_line(""));
	write("---------------------------------------\n");
	return 1;
}

int buy(string a)
{
	FIX_EUID;
	if(query_components()[0][a] == 0)
	{
		notify_fail("Buy what? Use 'list' to see available components.\n");
		return 0;
	}
	object component = clone_object(query_components()[0][a]);
	if(query_components()[0][a] == TRAP_COMPONENTS + "ball")
	{
		string size = explode(a, " ")[0];
		component->set_size(size);
	}
	if(!TP->pay_coins(component->query_component_value()))
	{
		notify_fail("You don't have enough blood coins to pay the price.\n");
		return 0;
	}
	component->move(TP);
	write("Shopkeeper hands you a " + a + ".\n");
	return 1;
}

public void attacked_by(object attacker)
{
	::attacked_by(attacker);
	if(attacker->query_guild_name_lay() == BHNAME)
	{
		attacker->cleanup_hunter();
		attacker->catch_msg("You broke the rules of bounty hunters' brotherhood. You have been expelled!\n");
	}
}

