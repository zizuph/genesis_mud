/*
 *    entrance_guard.c  
 *
 * The amazon guard, guarding the entrance
 * to the guild.
 *
 * Baldacin@Genesis, Dec 2003   
 *
 */
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
inherit NPC+"std_amazon";
 
void
create_amazon()
{
	string *equipment = ({ARM+"brown_pants",ARM+"camo_cloak",ARM+"leather_armour",ARM+"leather_boots", WEP+"spear"});

    set_name("ophelia");
    add_name("entrance_guard");
    set_adj("courageous");
    add_adj("steadfast");
    set_long("Courageous and steadfast is the first things that come into "+
		"mind when looking at this Amazon warrior. Her duty amongst the "+
		"Amazons is most likely guarding the entrance to the closed "+
		"sections of the settlement, she would probably not let you pass "+
		"without some kind of token to prove your trustworth.\n");
    set_title("the Courageous Amazon of the Silent Forest and "+
      "Watchful Guardian");
    set_gender(G_FEMALE);
    set_stats(({156, 156, 156, 156, 156, 156}));
    
    add_ask(({"join", "join guild", "guild"}), "say "+
      "You need to gain our trust before you can affilate yourself "+
      "with us.", 1);
	add_ask(({"amazon", "amazons"}), "say You can read more about "+
		"us in the book located southeast and north of here.", 1);
    add_ask(({"trust","gain trust","token"}), VBFC_ME("token_answer"));
      
    set_default_answer(VBFC_ME("def_answer"));

	equip_this(equipment);
}

int
can_npc_see(object player)
{
	if (CAN_SEE(TO, player) && CAN_SEE_IN_ROOM(TO))
		return 1;
	return 0;
}

string
def_answer()
{
    if (!can_npc_see(TP))
	{
	    command("say What?! Who's there!");  
		return "";
	}

    command("say to "+TP->query_name()+" I have no idea what you are talking about.");
    command("shrug");
    return "";
}

string
token_answer()
{
	if (!can_npc_see(TP))
	{
	    command("say What?! Who's there!");  
		return "";
	}

    if (IS_MEMBER(TP))
	{
		command("say to "+TP->query_name()+" Since you're an Amazon you should "+
			"know how the tokens work. If you forgot, read about it in the help "+
			"sections for the guild.");
        command("smile help");
		return "";
	}
	if (SERVER->query_amount_member() <= 3)
	{
		command("say to "+TP->query_name()+" Yes, you have to find one "+
			"of the Amazons and convince them that you are worthy to be "+
			"one of us and she will then give you a token. Since there "+
			"are so few of us around at the moment I will give you one.");
        command("smile");
		setuid();
        seteuid(getuid());

		if (present("amazon_race_token", TP))
        {
            command("say to "+TP->query_name()+" But I see that you already "+
				"got a token and I don't see two heads on you!");
		    return "";
        }
 
        if (TP->query_gender() != G_FEMALE)
        {
            command("say to "+TP->query_name()+" But I see that you are "+
				"not a female! Only females are allowed into the closed "+
				"sections.");
		    return "";
        }

		if (TP->query_race_name() != "human")
        {
            command("say to "+TP->query_name()+" But I see that you are "+
				"not a human! Only humans are allowed into the closed "+
				"sections.");
		    return "";
        }

        clone_object(OBJ + "token")->move(TP, 1);
	    say(QCTNAME(TO) + " presents "+ QTNAME(TP) +
	         " with a token.\n",({TP}));
	    TP->catch_msg(QCTNAME(TO) + " presents you with "+
	        "a token.\n");
		return "";
	}
	else
	{
		command("say to "+TP->query_name()+" Yes, you have to find one "+
			"of the Amazons and convince them that you are worthy to be "+
			"one of us. She will then give you a token that you can show "+
			"to me and I will let you pass.");
        command("smile help");
		return "";
	}
}
public void
add_introduced(string name)
{
    command("introduce me to " + name);
}