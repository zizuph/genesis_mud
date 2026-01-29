#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
   set_name(({"traveller"}));
   set_race_name("human"); 
   set_short("traveller");
   set_long(BSN("A wizened old man, slumped over by age. "+
         "His eyes sparkle with life and he looks as if he wishes to share "+
         "his knowledge with others."));
   default_config_npc(15 + random(10));
   set_alignment((random(2)*2-1)*(125 + random(100)));
   set_skill(SS_WEP_KNIFE,25 + random(10));
   set_skill(SS_DEFENCE,30 + random(10));
   set_whimpy(25);
   set_random_move(15 + random(16));
   set_chat_time(30);
   add_chat("In my day we feared the Corsairs of Umbar.");
   add_chat("Have you been to Pelargir?");
   add_chat("I would love to have a grasshopper for dinner.");
   add_chat("I was once a guard of Pelargir, but now I am too old and weak.");
   add_chat("Explore, my young friend, that is my message to the youth.");
   add_chat("Poor me, I am so hungry- I would like a grasshopper to eat.");
   set_default_answer(VBFC_ME("default_answer"));
   add_ask(({"help","for help","about help"}), VBFC_ME("inform_help"));
   add_ask(({"about lebennin","lebennin",}), VBFC_ME("inform_lebennin"));
   seq_new("do_things");
   add_ask(({"pelargir","about pelargir","city"}), VBFC_ME("inform_pelargir"));
   add_ask(({"gondor","minas tirith","about gondor"}), VBFC_ME("inform_gondor"));
   add_ask(({"umbar","about umbar","corsairs"}), VBFC_ME("inform_umbar"));
   add_ask(({"ithilien","about ithilien","rangers"}), VBFC_ME("inform_ithil"));
   add_ask(({"grasshopper","dinner"}), VBFC_ME("inform_ghopper"));
   add_ask(({"harbormaster","harbourmaster","master","master of advice"}), 
	   VBFC_ME("inform_master"));
   add_ask(({"mordor","dark tower","nameless one"}), VBFC_ME("inform_mordor"));
   add_ask(({"riders","riders of rohan"}), VBFC_ME("inform_riders"));
   add_ask(({"orcs","orc","haradrim"}), VBFC_ME("inform_orc"));
}

public void
arm_me()
{
    FIX_EUID;
   
    clone_object(WEP_DIR + "knife")->move(TO);
    command("wield knife");
    clone_object(MINAS_DIR + "obj/ltunic")->move(TO);
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
    command("say it's still infested by corsairs from Umbar and even by orcs from the Black Land.");
   return "";
}

string 
inform_pelargir()
{
   command("emote smiles wistfully.");
   command("say Ah, yes, my beloved town. So fortunate that it");
   command("say does not fall directly under the shadow of that");
   command("say awful black tower as Minas Tirith does, not that");
   command("say if Minas Tirith falls we will last long, no I don't");
   command("say mean to say that, but our main problem is those");
   command("say damnable Corsairs from Umbar.");
   command("emote blushes profusely.");
   command("say I'm sorry, you asked about Pelargir, didn't you? Well,");
   command("say I think Pelargir is about the best place around.");
   command("say The Admiral sure runs a tight ship there, and");
   command("say as it's the oldest surviving city in Gondor, you");
   command("say really get to see how the Men of Old made things.");
   command("emote sighs happily.");
   command("say It really is a nice place, you should visit.");
    command("say If you are there, go and talk to Carastur, the Lord Councillor.");
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
   command("say To me they are not so scary- I fought them for decades.");
   command("say But still they continue to harass us here in the South.");
   command("say If the King should return, he will no doubt destroy them.");
   return "";
}

string 
inform_ithil()
{
   command("say The herbgarden of Gondor, that's what Ithilien is!");
   command("say We have herbs here in this part of Gondor, but");
   command("say nothing like there.");
   command("emote sighs sadly.");
   command("say But Ithilien is also where the orcs and harads");
   command("say make their camps in preparation for war.");
   command("say Only the Rangers and Riders of Rohan can save us.");
   return "";
}

string 
inform_master()
{
   command("say The Master of Advice is Hunthor in Minas Tirith.");
   command("say The Harbourmaster may be found in the Harlond.");
   command("emote smiles helpfully.");
   return "";
}

string 
inform_ghopper()
{
   command("say Grasshoppers are plentiful in Lebennin.");
   command("say I wouldn't mind eating one right now, though.");
   return "";
}

string 
inform_mordor()
{
   command("emote takes a deep breath.");
   command("say You shouldn't ask about them, it's bad luck.");
   command("say But I will tell you this:");
   command("emote looks around suspiciously.");
   command("say The forces of the Evil One are more numerous than");
   command("say the forces of Gondor and Rohan.");
   command("say But never dismiss the difference between goblins");
   command("say and the other races- men are braver in battle.");
   command("say That is Gondor's hope.");
   return "";
}

string 
inform_riders()
{
   command("say The riders of Rohan are skilled in fighting from");
   command("say horseback, and though they are few, they may do great deeds.");
   command("emote turns to the northwest, and sighs despondently.");
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
