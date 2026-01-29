#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/properties.h"

#include "/d/Khalakhor/sys/basic.h"

private string query_adject();
string _ADJ = query_adject();

private string
query_adject()
{
	string *adjectives = ({
		"smoothly", "seductively", "sexily", "quietly", "tenderly",
		"softly", "huskily", "gently", "enticingly", "lovingly",
		});
		return adjectives[random(sizeof(adjectives))];
}

string
ask_help()
{
	command("emote "+ _ADJ +" purrs: I do not need any help right "+
	"now. But I can try to help you, if you desire help?");
	return ""; 
}
string
ask_desire_help()
{
	command("emote "+ _ADJ +" purrs: I know many helpful things.");
	command("emote "+ _ADJ +" purrs: Such as the Otherworld, "+
	"Temptresses, this temple and so forth.");
	command("emote "+ _ADJ +" purrs: Ask me whatever you like and "+
	"I will do my best to answer.");
	return ""; 
}

string
ask_temptress()
{
	command("emote "+ _ADJ +" purrs: Temptresses serve the god of "+
	"love, Oenghus. He allows us to come here and worship in this "+
	"small temple.");
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
ask_bangles()
{
	command("emote glances about "+ _ADJ +".");
	if (IS_MEMBER(TP))
	{
		command("emote "+ _ADJ +" purrs: Aye, I bear the "+
		"symbol of the temptresss. My home is yours.");
		command("emote "+ _ADJ +" purrs: You may exchange "+
		"your bangles if you wish to a new or different pair.");
		return "";
	}
	command("whisper " + OB_NAME(TP) + " The bangles are a symbol "+
	"of being a temptress.");
	return "";
}
public string
ask_change_bangles()
{
	command("emote "+ _ADJ +" purrs: We can change our bangles at "+
	"the entrance of the temple.");
	return "";
}

public string
ask_khalakhor()
{
	command("emote "+ _ADJ +" purrs: Khalakhor is a wondrous land "+
	"filled with mystery.");
	return "";
}

public string
ask_otherworld()
{
	command("emote "+ _ADJ +" purrs: The Otherworld...");
	command("emote smiles "+ _ADJ +"");
	command("emote "+ _ADJ +" purrs: It is the most delightful land "+
	"of all that are under the sun; the trees are stooping down "+
	"with fruit and with leaves and with blossom. Honey and wine "+
	"are plentiful here.");
	return "";
}

public string
ask_temple()
{
	command("emote "+ _ADJ +" purrs: The temple is a blessing from "+
	"Oenghus.");
	return "";
}
public string
ask_oenghus()
{
	command("emote "+ _ADJ +" purrs: Oenghus, God of love.");
	command("emote sighs "+ _ADJ +"");
	command("emote "+ _ADJ +" purrs: Oenghus is the offspring of "+
	"the Dagda and Boann. Oenghus often intervenes on the behalf "+
	"of lovers in peril.");
	return "";
}

public string
ask_boann()
{
	command("emote "+ _ADJ +" purrs: Boann is the goddess of the "+
	"river Boyne.");
	return "";
}

public string
ask_dagda()
{
	command("emote "+ _ADJ +" purrs: Dagda is Father, which some "+
	"call the Good God, but others know Him as the Hammer God.");
	return "";
}

public string
ask_lovers()
{
	command("emote "+ _ADJ +" purrs: Lovers in peril is where you "+
	"will find Oenghus intervening.");
	return "";
}

public void
create_history()
{
	TO->add_ask(({"help"}), VBFC_ME("ask_help"), 1);
	TO->add_ask(({"desire help"}), VBFC_ME("ask_desire_help"), 1);
	TO->add_ask(({"temptresses", "temptress"}),
	VBFC_ME("reply_temptress"), 1);
	TO->add_ask(({"magic"}), VBFC_ME("ask_magic"), 1);
	TO->add_ask(({"bangles"}), VBFC_ME("ask_bangles"), 1);
	TO->add_ask(({"change bangles"}),
	VBFC_ME("ask_change_bangles"), 1);
	TO->add_ask(({"khalakhor"}), VBFC_ME("ask_khalakhor"), 1);
	TO->add_ask(({"otherworld"}), VBFC_ME("ask_otherworld"), 1);
	TO->add_ask(({"temple"}), VBFC_ME("ask_temple"), 1);
	TO->add_ask(({"oenghus"}), VBFC_ME("ask_oenghus"), 1);
	TO->add_ask(({"boann"}), VBFC_ME("ask_boann"), 1);
	TO->add_ask(({"dagda"}), VBFC_ME("ask_dagda"), 1);
	TO->add_ask(({"lover", "lovers", "lovers in peril"}),
	VBFC_ME("ask_lovers"), 1);
		
}



public void
init_history()
{

}