#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
   set_name(({"farmer"}));
   set_race_name("human"); 
   set_short("farmer");
   set_long("An");
   default_config_npc(15 + random(10));
   set_alignment((random(2)*2-1)*(125 + random(100)));
   set_skill(SS_WEP_KNIFE,25 + random(10));
   set_skill(SS_DEFENCE,30 + random(10));
   set_whimpy(25);
   filter_exits( ({ "east", "west", "north", "south", "northwest",
		      "northeast", "southwest", "southeast", "up", "down",
		      "enter", "exit", "in", "out" }) );
   set_chat_time(30);
   add_chat("It is hard to live on a farm like this.");
   add_chat("It seems like we are going to have a good harvest this year.");
   add_chat("Anyway the oats sales are good now, they give almost double"+
	    " price these days.");
   add_chat("I whish we had more money.");
   add_chat("Work as a farmer is not easy, you must work a lot!");
   set_default_answer(VBFC_ME("default_answer"));
   add_ask(({"help","for help","about help"}), VBFC_ME("inform_help"));
   add_ask(({"about lebennin","lebennin",}), VBFC_ME("inform_lebennin"));
   seq_new("do_things");
   add_ask(({"pelargir","about pelargir"}), VBFC_ME("inform_pelargir"));
   add_ask(({"gondor","minas tirith","about gondor"}), VBFC_ME("inform_gondor"));
   add_ask(({"umbar","about umbar","corsairs"}), VBFC_ME("inform_umbar"));
   add_ask(({"orcs","orc","haradrim"}), VBFC_ME("inform_orc"));
   add_ask(({"linhir","about linhir"}), VBFC_ME("inform_linhir")); 
}

public void
arm_me()
{
    FIX_EUID;
   
    clone_object(WEP_DIR + "knife")->move(TO);
    command("wield knife");
    clone_object(LEB_DIR + "obj/corshirt")->move(TO);
    command("wear tunic");
}

/* solemnian prestige */
int query_knight_prestige()
{
    return (query_alignment() > 0 ? -3 : 250);
}

string 
default_answer()
{
   command("say I do not know what you are talking about.");
   command("say If you would ask me about help, I might be able to offer some.");
   return "";
}

string 
inform_help()
{
   command("say Well I am not in need of help now but you should see ");
   command("say the Harbourmaster in the Harlond if you are young and broke ");
   command("say or perhaps the Master of Advice has a task for you in ");
   command("say Minas Tirith.");
   return "";
}

string 
inform_lebennin()
{
    command("say The land south of the White Mountains and west of the Anduin is called Lebennin.");
    command("say Its capital is Pelargir, Gondor's largest sea port, close to the mouths of the Anduin.");
    command("say It's a wonderful land, but even though the guards at Pelargir fight hard,");
    command("say it's still unsafe for corsairs from Umbar and even for orcs from the Black Land!");
   return "";
}

string 
inform_pelargir()
{
   command("emote smiles wistfully.");
   command("say Pelargir, yes. Thets where all the ships go.");
   command("say Just sad they are not safe from those damnable corsairs!");
   command("say The Admiral runs the place hard, and");
   command("say it is the oldest city in Gondor, so you");
   command("say should go and take a visit there. It is nice despite");
   command("say those corsair attacks.");
   command("emote sighs happily.");
   return "";
}

string 
inform_gondor()
{
   command("say Minas Tirith is the capital of Gondor, where");
   command("say Denethor II rules as Steward, until the King returns.");
   command("say It is fair and beautiful as here in");
   command("say Lebennin, but the shadow of the dark tower falls more heavily upon Anorien.");
   command("say May the Valar be with the Rangers in the fight against");
   command("say the nameless one.");
   command("emote shivers with fear.");
   command("say I would not like to have their duty.");
   return "";
}

string 
inform_umbar()
{
   command("say I despise the Corsairs!");
   command("emote spits on the ground in disgust.");
   command("say They only makes trouble, both for me and others.");
   command("say But still they continue to harass us here in the South.");
   command("say If the King should return, he will no doubt destroy them.");
   command("emote sits down by the fireplace.");
   command("say I have never liked them, and I think noone in Gondor should!");
   command("say They have made great dammage here, but they know that");
   command("say in Pelargir. They have beed robbed quite lately.");
   command("emote rises again and streches his old body.");
   command("emote sighs sadly.");
   return "";
}

string 
inform_orc()
{
   command("say Those foul orcs!");
   command("say They respect nothing but the power of their master.");
   command("say If they come across the Anduin, they will learn to");
   command("say respect the swords of Gondor!");
   return "";
}

string
inform_linhir()
{
   command("say Linhir yes. A nice city.");
   command("emote smiles profoundly.");
   command("say Linhir is an important harbour for the army of Gondor.");
   command("say Those that have command over that city have also");
   command("say command over the Ethir Anduin, the entrance to the");
   command("say old river.");
   command("say If you go there, make shure to take a look at the");
   command("say guarded bridge, it is quite interesting.");
   return "";
}
