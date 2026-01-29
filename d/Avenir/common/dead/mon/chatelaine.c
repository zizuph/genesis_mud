// /d/Avenir/common/dead/mon/chatelaine.c
// creator(s): Lilith Created May 2021
// last update: Lilith, Sep 2021: added name gatekeeper, added undead prop.
// purpose:   Gatekeeper of the Catacombs
// note:      She rewards players who make their way
//            through the catacombs with permanent access.
//            Catacomb Gate quest npc         
//
// bug(s):
// to-do:    


inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"

#include "../dead.h"
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#define GATEROOM       CRYPT+"crypt_entr.c"
#define CHECK_QUEST(x) (x)->test_bit("Avenir", Q_GROUP, GATE_BIT)

string
do_open()
{
    //Three ways to qualify for exit.
    object player = this_player();
    // Did the gate quest
    if (CHECK_QUEST(player))
    {	
	command("say to "+ NAMEQ(player) +" I remember your face. ");
	command("say You made it out alive, again. Amazing.");
	command("say Go soak that filth off at Melchior's Baths "
	  +"before you try going home.");
	(GATEROOM)->test_gate();
	return "";
    }
    // wearing a death mask
    if (player->query_prop(DMASK_PROP))
    {	
	command("say to "+ NAMEQ(player) +" I remember your face. ");
	command("say May you please the Gods in all you do, High One.");
	command("curtsey to "+ NAMEQ(player));
	(GATEROOM)->test_gate();
	return "";
    }
    // came via the banshee, needs to give me a token
    if (player->query_prop(ABDM))
    {			
	command("say to "+ NAMEQ(player) +" A new face. Hmm. The "
	  +"Banshee sent you, did she?");
	command("emote puts a pale, nearly-immaterial hand out.");
	command("say Do you have something for me?"); // sybarun coin please
	return "";
    }
    // You. Shall. Not. Pass!   But I'll give you some hints.		
    command("say to "+ NAMEQ(player) +" The banshee didn't send you, "
      +"so unless you're a High Lord with a death mask in your "
      +"pocket, you're not leaving.");
    return "";
}


void
create_monster()
{
    ::create_monster();

    set_name("chatelaine");
    add_name(({"_Avenir_Catacombs_Chatelaine", "ghost", "spirit", "gatekeeper"}));
    set_adj(({"patient", "skeletal"}));
    set_race_name("spirit");
    set_gender(G_FEMALE);

    set_long("This is the ghost of a once-powerful "
      +"chatelaine of one of the great Houses of "
      +"Sybarus.\nShe is a tall and skeletal spirit "
      +"wearing a chatelaine's chain around her waist. "
      +"Upon it hangs numerous keys and pouches.\n");

    set_stats(({200,200,200,200,200,200}));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_HEIGHT, 500);
    add_prop(CONT_I_WEIGHT, 56000);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
    add_prop(LIVE_I_UNDEAD, 1);
    set_alignment(0);

    set_default_answer("say I serve to keep the gate, not to answer questions. Move along!", 1);

    add_ask(({"[about] [the] 'gate' "}),
      "say Only I can open this gate.", 1);
    add_ask(({"[about] [the] 'key' "}),
      "say I am the sole bearer of the key to the Catacombs.", 1);
    add_ask(({"'open' [the] / [this] 'gate' "}), do_open);
    add_ask(({"[about] [the] 'catacombs' / 'house' [of] [the] [dead]"}),
      "say This is where the bodies of dead Sybarites lay. Some "
      +"rest in Mascarvin's embrace, whilst others still have more "
      +"to do in service to the Gods.",1);
    add_ask(({"[about] [the] / [a] 'sarcophagus' / 'sarcophagi'"}),
      "say There are a half-dozen places in the catacombs where "
      +"they can be found. If you're looking for one, be careful "
      +"not to get lost. It's like a maze down there.",1);		
    add_ask(({"[about] [the] / [a] [death] 'mask'"}),
      "say The death masks are interred with the bodies of High Lords "
      +"and Chatelaines in their sarcophagi.",1);
    add_ask(({"[about] [the] / [a] 'kesoit' [death] 'mask'"}),	
      "say The kesoit masks are made exclusively for the Hegemons of "
      +"Sybarus.", 1);
    add_ask(({"'what' [do] [you] 'want' [to] [open] [gate]"}),
      "say I want what nearly all gatekeepers in Sybarus collect.",1);
    add_ask(({"[what] [do] [you] 'collect'"}),
      "say I collect those tokens of the God's approval: sybarun coins.", 1);	
    add_ask(({"[about] [who] [is] [you] 'mascarvin' [quest]"}),
      "say You jest! Surely you know that Mascarvin is the goddess of "
      +"death and rebirth? She has a resting place down in the "
      +"catacombs some place I don't know. I wouldn't dare to "
      +"intrude even if I did.", 1);	
    add_ask(({"[for] 'help'"}), "say What kind of help do you need, child? "
      +"There is only so much I can do for you.", 1);
}

string
race_sound()
{
    return "slowly says";
}

void 
not_wanted(object what, object who)
{
    command("frown "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
	+who->query_real_name()))
	what->remove_object();  
} 

void
reward_gate_quest(object player)
{
    seteuid(getuid(TO));
    reward_quest("Catacomb Gate", player, Q_GROUP, GATE_BIT, GATE_EXP);	
    SCROLLING_LOG(GATE_LOG, capitalize(player->query_real_name()) +
      " made it through the Catacombs and got "+ GATE_EXP +" exp.\n" );
    STATSERV_LOG_EVENT("crypt", "Gate quest done");
    say(QCTNAME(player) + " got a nice reward.\n");

}


void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (obj->id("_sybarun_token"))
    {
	if (CHECK_QUEST(from))
	{
	    set_alarm (1.0, 0.0, &command("say Yes, you've given me one already."));
	    set_alarm (3.0, 0.0, &command("say There is no need to do so again."));
	    set_alarm (4.0, 0.0, &command("say You need only ask me to open the "
		+"gate, or knock from the other side."));
	    set_alarm (4.0, 0.0, &not_wanted(obj, from));
	    return;
	}
	else
	{
	    //make sure player came from above
	    if (from->query_prop(ABDM))
	    {	
		set_alarm (2.0, 0.0, &command("emote stashes the sybarun coin in "+
		    "a pouch on her golden chatelaine's belt."));
		set_alarm(3.0, 0.0, &command("say You can ask me to open the gate "+
		    "and I will. If you want back in, just knock. "));
		set_alarm (4.0, 0.0, &reward_gate_quest(from));
		return;
	    }
	}

	set_alarm (2.0, 0.0, &command("say Who are you and how did you get here?!"));
	set_alarm (2.0, 0.0, &command("say The Guardians did not grant you passage, "
	    +"so neither can I."));		
	set_alarm (2.0, 0.0, &not_wanted(obj, from));
	return;
    }
    set_alarm(0.1, 0.0, &not_wanted(obj, from));
    return;
}
