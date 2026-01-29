#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/properties.h"

#include "/d/Khalakhor/sys/basic.h"

#define LIVE_O_SPOKE_TO_TEMPTRESS "_live_o_spoke_to_temptress"
#define LIVE_O_ASKED_JOIN     "_live_o_asked_to_join_temptress"

private string query_adject();
string _ADJ = query_adject();

private string
query_adject()
{
	string *adjectives = ({
		"smoothly", "seductively", "sexily", "quietly",
		"softly", "huskily", "enticingly",
		});
		return adjectives[random(sizeof(adjectives))];
}

string
ask_help()
{
	command("emote "+ _ADJ +" purrs: If you are worthy, I will "+
	"help you.");
	return ""; 
}
string
ask_eilgalaith()
{
	command("emote "+ _ADJ +" purrs: Perhaps you should seek "+
	"elsewhere.");
	command("emote fluidly gestures to beyond the entrance.");
	return "";
}
string
ask_magic()
{
	command("emote "+ _ADJ +" purrs: Ahh magic. You wish to know "+
	"more of magic?");
	command("emote "+ _ADJ +" purrs: You are within the Otherworld, "+
	"magic abounds around you my dearest.");
	
	command("emote "+ _ADJ +" purrs: There is more to magic than "+
	"meets the eye. You are a bit young, but if you continue along "+
	"your search you will find your way.");
	command("smile "+ _ADJ +"");
	return "";
}

public string
reply_bangles()
{
	command("emote glances about "+ _ADJ +".");
	if (IS_MEMBER(TP))
	{
		command("whisper " + OB_NAME(TP) + " Aye, I bear the "+
		"symbol of the temptresss. My home is yours.");
		return "";
	}
	command("whisper " + OB_NAME(TP) + " The bangles are a symbol "+
	"of being a temptress.");
	return "";
}

public string
reply_temptress()
{
	if (IS_MEMBER(TP))
	{
		command("whisper " + OB_NAME(TP) + " There is nothing "+
		"I can tell you, that you do not already know.");
		return "";
	}
	command("whisper " + OB_NAME(TP) + " The temptresses are a "+
	"society, of sorts that have chosen to live their life according "+
	"to the art of seduction and love. We are the keepers of the "+
	"old ways.");
	tell_room(environment(), QCTNAME(TO) + " glances over " +
	QTNAME(TP) + " carefully.\n", ({TP}));
	TP->catch_msg(QCTNAME(TO) + " glances over you carefully.\n");
	
	command("whisper " + OB_NAME(TP) + " If you choose to become a "+
	"part of this special society then I can help you to learn this "+
	"precious art so that you might make such claim to be a "+
	"temptress, should you wish. Ask me about their rules.");
	TP->add_prop(LIVE_O_SPOKE_TO_TEMPTRESS, TO);
	return "";

}

public string
reply_rules()
{
	if (!TP->query_prop(LIVE_O_SPOKE_TO_TEMPTRESS) ||
	TP->query_prop(LIVE_O_SPOKE_TO_TEMPTRESS) != TO)
	{
		command("whisper " + OB_NAME(TP) + " Rules? What rules?");
		return "";
	}
	command("smile knowingly");
	command("whisper " + OB_NAME(TP) + " The rules are simple to "+
	"being a temptress. Firstly, we follow the god of love, Oenghus, "+
	"whom allows us this temple in the Otherwold. Secondly, we must "+
	"never intrude our temptress ways upon those who do not wish to "+
	"be tempted. Our ways are not to overbear but to enlighten those "+
	"to a higher plane of seduction and love. You may ask to join if "+
	"you'd like?");
	return "";
}

public string
reply_join()
{
	object bangles;
	/* If the player is already a temptress, do nothing. */
	if (IS_MEMBER(TP))
	{
		command("whisper " + OB_NAME(TP) + " You are already "+
		"a temptress.");
		return "";
	}
	if (this_player()->query_gender() == G_MALE)
	{
		command("emote refuses to teach men.");
		return "";
	}
	if (this_player()->query_race_name() == "orc")
	{
		command("emote refuses to teach orcs.");
		return "";
	}
	if (this_player()->query_race() == "goblin")
	{
		command("emote refuses to teach goblins.");
		return "";
	}
	if (this_player()->query_race_name() == "minotaur")
	{
		command("emote refuses to teach minotaurs.");
		return "";
	}
	
	if (!TP->query_prop(LIVE_O_SPOKE_TO_TEMPTRESS) ||
	TP->query_prop(LIVE_O_SPOKE_TO_TEMPTRESS) != TO)
	{
		command("whisper " + OB_NAME(TP) + " There's nothing "+
		"to say about that.\n");
		return "";
	}
	/* A little confirmation check so players don't join by */
	/* accident, they have to ask to join twice. */
	if (!TP->query_prop(LIVE_O_ASKED_JOIN))
	{
		command("whisper " + OB_NAME(TP) + " I can help you if "+
		"you wish, just ask me again and you'll be a temptress.");
		TP->add_prop(LIVE_O_ASKED_JOIN, TO);
		return "";
	}	
	command("smile warmly");
	command("emote "+ _ADJ +" purrs: Let it be known that on this "+
	"day, "+ TP->query_name() + ", has claimed " + HIS(TP) + " "+
	"rightful place among the beloved and has become a temptress!");
	seteuid(getuid());
	clone_object(GUILD_OBJ)->move(this_player());
	if(!(this_player()->add_cmdsoul(SOUL)))
	{
		write("cmdsoul addition problem\n");
	}
	this_player()->update_hooks();
	command("emote "+ _ADJ +" purrs: These bangles are for you to "+
	"wear proudly.\n");
	write_file("/d/Khalakhor/guilds/tempt/log/membership",
	ctime(time()) + " " 
	+ capitalize(this_player()->query_real_name()) +
	" joined (age = " + (this_player()->query_age() / 43200) +
	", avg = " + this_player()->query_average_stat() + ").\n");
	return "";

	TP->remove_prop(LIVE_O_SPOKE_TO_TEMPTRESS);
	TP->remove_prop(LIVE_O_ASKED_JOIN);
}
int
reply_leave(string str)
{
	object ob;
	
	if (!(ob = present(OBJECT_ID, this_player())))
	{
		write("You are not a temptress!\n");
		return 1;
	}
	write_file("/d/Khalakhor/guilds/tempt/log/teaching",
	ctime(time()) + " " + capitalize(this_player()->query_real_name()) +
	" left (age = " + (this_player()->query_age() / 43200) +
	", avg = " + this_player()->query_average_stat() + ").\n");
	
	if (!this_player()->remove_cmdsoul(SOUL))
	{
		command("emote "+ _ADJ +" purrs: It doesn't seem you "+
		"were a temptress anyway.\n");
		return 1;
	}
	if(ob) ob->remove_object();
	this_player()->update_hooks();
	command("emote "+ _ADJ +" purrs: You are no longer a temptress, "+
	"much to my sorrow.\n");
	return 1;
}
public void
create_temptress()
{
	TO->add_ask(({"thistle"}), VBFC_ME("reply_thistle"), 1);
	TO->add_ask(({"temptresses", "temptress"}),
	VBFC_ME("reply_temptress"), 1);
	TO->add_ask(({"rules"}), VBFC_ME("reply_rules"), 1);
	TO->add_ask(({"join", "about joining", "to join", "joining"}),
	VBFC_ME("reply_join"), 1);
	TO->add_ask(({"leave", "about leaving", "to leave", "leaving"}),
	VBFC_ME("reply_leave"), 1);	
	TO->add_ask(({"help"}), VBFC_ME("ask_help"), 1);
	TO->add_ask(({"eilgalaith", "eil-galaith"}),
	VBFC_ME("ask_eilgalaith"), 1);
	TO->add_ask(({"magic"}), VBFC_ME("ask_magic"), 1);
}



public void
init_temptress()
{

}
