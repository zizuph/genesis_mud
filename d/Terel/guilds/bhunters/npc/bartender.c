#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <stdproperties.h>
#include <ss_types.h>

inherit STDMONSTER;

void create_terel_monster()
{
	set_name("bartender");
	set_adj(({"fat", "bald"}));
	set_short("fat bartender");
	set_race_name("human");
	set_long("Tall, fat human standing before you is an owner of the 'Hook & Dagger' tavern. He's well known in "+
		"town for his relations with bounty hunters.\n");
	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_gender(0);
	default_config_npc(70 + random(10));

	set_skill(SS_UNARM_COMBAT, 60);
	set_skill(SS_DEFENCE, 60);
	set_skill(SS_AWARENESS, 50);
	set_skill(SS_BLIND_COMBAT, 100);
  
	set_hp(query_max_hp());

	set_act_time(40 + random(10));
	add_act("emote picks his nose.");
	add_act("scratch");
	
	add_ask(({"hunters", "bounty hunters"}), "@@hunters_answer");
	add_ask("rumours", "@@rumours_answer");
}

public void init_living()
{
	::init_living();
	add_action("rumours", "ask");
}

int rumours(string a)
{
	string name;
	if(!strlen(a))
		return 0;
	if(!parse_command(a, ({}), " [bartender] 'for' / 'about' 'rumours' 'of' / 'about' %w ", name))
		return 0;
	if(!TP->query_guild_member(BHNAME))
	{
		command("say I'm just a bartender. I know how to pour beer in cups, and that's all you can learn from me.\n");
		return 1;
	}
	(OFFICE)->telegnigasanka();
	string *bounties = (OFFICE)->get_bounties();
	if(member_array(name, bounties) == -1)
	{
		command("say Sorry I know nothing about this one.\n");
		return 1;
	}
	object target = find_player(name);
	if(!objectp(target))
	{
		command("say From what I've heared he's in hiding right now, better go after someone else.");
		return 1;
	}
	command("say I've heared someone saw " + target->query_objective() + " in " + E(target)->query_domain() +
		" not so long ago. I know nothing more.");
	return 1;
}

string rumours_answer()
{
	if(TP->query_guild_member(BHNAME))
		command("say Ask about rumours of a person you're looking for, I might know something.");
	command("say You want a drink or not? I know nothing about anything.");
}

string hunters_answer()
{
	FIX_EUID;
	if(TP->query_guild_member(BHNAME))
	{
		command("smirk");
		command("say You tell me, you're one of them I've heared.");
		command("say Unless you wonna sign out. You'd loose some, but if that's what you really want..");
		return "";
	}
	(OFFICE)->telegnigasanka();
	string *hunters = (OFFICE)->get_hunters();
	command("say Yeah, you heared right, they are back in town, they're even accepting new members.");
	if(member_array(TP->query_real_name(), hunters) == -1)
	{
		
		command("say But you'd have to prove yourself first, you know claim a bounty.\n");
		command("grin broad");
		return "";
	}
	command("say I, on the other hand, heard you're quite capable...");
	command("I've been told to just let sign in ones as yourself. Go ahead if you feel like it.\n");
	return "";
}
	