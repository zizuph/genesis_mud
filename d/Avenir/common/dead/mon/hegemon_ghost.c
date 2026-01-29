// /d/Avenir/common/dead/mon/hegemon_ghost.c
// creator(s): Lilith
// last update: Created May 2021
// purpose:   Ghost of Hegemon
// note:      Manis-ak dei Ni'stu  father of Tjana
//            mortal consort of Goddess Azauph, 
//            son-in-law of Goddess Mascarvin   
// Updates: Lilith, Sep 2021: fixed syntax error in quest reward sequence  
//             added clone of thief npc when quest ask is done + added logging
// bug(s):
// to-do:    


inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/quest";
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/macros.h"
#include "../dead.h"
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

string do_quest_ask();
string do_masq_ask();
object thief;

void
create_monster()
{
    ::create_monster();

    set_name("hegemon");
    add_name(({"manis","ak","high lord", "ghost", "spirit", "elf", "shadow-elf"}));
    set_adj(({"haughty", "enraged"}));
    set_race_name("shadow-elf ghost");
    set_gender(G_MALE);
    set_living_name("Manis-ak");
	set_title("dei Ni'stu the former Lord High Commissioner and "
	    +"Hegemon of Sybarus, the consort of Azauph Maternal the "
		+"daughter of Mascarvin, and father of beloved Tjana");	
    set_long("This is the ghost of one of the most powerful lords "
	    +"ever known in Sybarus.\nEven in death you can see that "
		+"he was once very beautiful of face and well-formed of "
		+"body.\nHe looks like he is very angry.\n"
		+"");

    set_stats(({200,200,200,200,200,200}));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_HEIGHT, 250);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(OBJ_M_NO_ATTACK, 1);
	add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
	add_prop(LIVE_I_SEE_DARK, 20);
	add_prop(LIVE_I_UNDEAD, 1);
    set_alignment(0);
	
	set_act_time(15);
	add_act("emote shouts: That she-gnome will die an ugly death and there "
	    +"will be no rebirth for her.");
	add_act("emote says: Who disturbs a dead man's rest?");
	add_act("emote says: The scepter and the wand must be returned to me.");
	add_act("emote murmurs to himself: Mascarvin will surely deny that "
	    +"servant of Nitikas rebirth.");
	add_act("emote fumes and floats.");
	add_act("emote I seek not rebirth, but rest, and I cannot rest without "
	    +"my scepter of office. It is a part of me.");
	add_act("emote says: I might be willing to reward the one who helps me--"
	    +"with an opportunity to meet Mascarvin. Might...");	
	add_act("emote says: I cannot tell Her that my sarcophagus was robbed "
	    +"by a follower of Nitikas in the House of the Dead. She would do "
		+"terrible things, terrible terrible things. It must be returned "
		+"quietly to me before too long--lest all of Sybarus suffer.");
    add_act("emote says: I spoke to the goblin workers and I hope they "
	    +"understand the urgency of the situation. They certainly ran off "
		+"quickly enough.");
	
	
	set_default_answer("say I need help finding the pieces of my scepter of "
	    +"office--not much else is important to me!", 1);
	
	add_ask(({"[about] [the] [pieces] [of] [the] / [your] [hegemon] 'scepter' [of] [office] "}),
		do_quest_ask);
	add_ask(({"[how] [can] [i] 'help' [you] [find] [your] [scepter]"}), 
	    do_quest_ask);
	add_ask(({"[do] [you] [have] [a] 'task' / 'quest' [for] [me]"}), 
	    do_quest_ask);	
    add_ask(({	"[what] / [why] [are] [you] 'angry' / 'mad' / 'upset' [about]"}),
	    do_quest_ask);	
	add_ask(({"[about] [how] [do] [i] 'meet' 'mascarvin'"}),
		do_masq_ask);
	add_ask(({"[about] [the] 'path' [to] [return] [to] [mascarvin]"}),
		do_masq_ask);
    add_ask(({"[about] [the] 'mascarvin' [quest]"}),
        "say Mascarvin is the goddess of death and rebirth. Her daughter "
		+"Azauph and I had a child together. Should Tjana's statue somehow be "
		+"found, I know the path to return her to her grandmother's embrace.", 1);
    add_ask(({"[about] [placate] 'azauph'"}),
        "say Centuries ago she was so beautiful and happy. She was "
        +"a goddess of the hearth and childbirth. Azauph has been half-mad "
		+"with grief and vengeance ever since Nitikas stole our daughter. "
		+"There is no placating her.\n", 1);	
    add_ask(({"[about] [the] [god] 'nitikas'"}),
        "say Curse him and all who follow him! Nitikas stole my daughter "
       +"from us and broke Azauph's heart.", 1);		
    add_ask(({"[about] [the] [statue] [of] 'tjana' [quest]"}),
        "say It is too sad for me to talk about. If you want to know "
        +"my daughter's story, you can read about it in the library at "
        +"the Bazaar.\n", 1);
    add_ask(({"[about] [your] 'daughter' [tjana]"}),
        "say It is too sad for me to talk about. If you want to know "
        +"my daughter's story, you can read about it in the library at "
        +"the Bazaar.\n", 1);	
    add_ask(({"[about] [the] 'statue' [of] [your] [daughter] [tjana]"}),
        "say Nitikas, the god of wealth and aquisition, coveted my "
		+"daughter Tjana and when she refused his advances, he turned "
		+"her into a statue.\n", 1);		
	add_ask(({"[about] [the] 'catacombs' / 'house' [of] [the] [dead]"}),
	    "say This is where the bodies of dead Sybarites lay. Some "
		+"rest in Mascarvin's embrace, whilst others still have more "
        +"to do in service to the Gods.",1);
	add_ask(({"[about] [the] / [a] 'sarcophagus' / 'sarcophagi'"}),
	    "say This is my sarcophagus. I was laid to rest here.",1);		
	add_ask(({"[about] [the] / [a] [kesoit] [death] 'mask'"}),
	    "say The death masks are interred with the bodies of High Lords "
        +"and Chatelaines in our sarcophagi. We believe that they "
		+"help sustain us in death and speed our rebirth.",1);
		
    setuid();
    seteuid(getuid());
}

string
race_sound()
{
   return "frowns and says";
}

void 
not_wanted(object what, object who)
{
    command("frown "+NAMEQ(who));
    if (!command("give "+NAMEQ(what)+" to "+NAMEQ(who)))
    {
        what->remove_object();  
    }
} 

void
reward_heg_quest(object player)
{
	seteuid(getuid(TO));
    //They've done the first stage of the Mascarvin quest.
	player->set_skill(SS_MASQ_STAGE, STAGE_1_HEG);
    reward_quest("Hegemon's Ghost", player, HEG_GROUP, HEG_BIT, HEG_EXP);	
    SCROLLING_LOG(HEG_LOG, capitalize(player->query_real_name()) +
	    " helped the Hegemon and got "+ HEG_EXP +" exp.\n" );
    STATSERV_LOG_EVENT("crypt", "Quest: Hegemon Ghost helped");
    MONEY_MAKE_PC(1);
	command("give coins to "+ NAMEQ(player));	
    thief = 0;  
}


void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
	
    if (!living(from))
        return;
	
    if (obj->id("sybarun_token"))
	{ 
        command("say I don't have use for these anymore.");
		set_alarm (2.0, 0.0, &not_wanted(obj, from));
	    return;
    }	
	// player already did the quest.
	if (CHECK_QUEST_HEG(from))
	{
		set_alarm (1.0, 0.0, &command("say You've helped me with this already."));
		//If player already did the quest, remove the quest object
        obj->remove_object();
      	return;
	} // player didn't complete the quest yet
	// Is this a scepter piece
	if (obj->id("_Hegemon_Scepter_Top"))
	{
		// player gave me one already
	    if (from->query_prop(HEG_TOP_PROP))	
		{	    
            set_alarm (2.0, 0.0, &command("emote frowns thoughtfully."));
		    set_alarm(3.0, 0.0, &command("say You gave me this just a bit ago..."
			    +"How is it that you have it once again? Are you working for "
				+"Nitikas?"));
            obj->remove_object();				
		    return;
        }
        // Player gave me the wand, too, so now I've got the top--reward them	
        if (from->query_prop(HEG_WAND_PROP))
		{
			from->add_prop(HEG_TOP_PROP, 1);
			command("say With both parts of my scepter of office returned "
			   +"to me, I can rest in peace.");
			command("thank "+ NAMEQ(from));
			set_alarm(2.0, 0.0, &command("whisper to "+ NAMEQ(from) +" I "
			   +"think Mascarvin would look favorably upon meeting with "
			   +"you. Look carefully amongst the bones stacked along "
			   +"the wall. You should see an opening there now."));
		    set_alarm (4.0, 0.0, &reward_heg_quest(from));
		    return;
		}
	    // This is the top but where is the bottom?
		from->add_prop(HEG_TOP_PROP, 1);
		command("thank "+ NAMEQ(from));
		command("say I am happy to be reunited with this part of my scepter. "+
		    "Did you recover the bottom portion from the thief, too?");	
		obj->remove_object();
		return;
	} // Not the scepter top. 
	// Is it the scepter wand?
	if (obj->id("_Hegemon_Scepter_Wand"))
	{
		// yes, player gave me one already
	    if (from->query_prop(HEG_WAND_PROP))	
		{	    
            set_alarm (2.0, 0.0, &command("emote frowns thoughtfully."));
		    set_alarm(3.0, 0.0, &command("say You gave me this just a bit ago..."
			    +"How is it that you have it once again? Are you working for "
				+"Nitikas?"));
            obj->remove_object();				
		    return;
        }
        // Player gave me the top, so now I've got the wand--reward them	
        if (from->query_prop(HEG_TOP_PROP))
		{
			from->add_prop(HEG_WAND_PROP, 1);
			command("say With both parts of my scepter of office returned "
			   +"to me, I can rest in peace.");
			set_alarm(2.0, 0.0, &command("whisper to "+ NAMEQ(from) +" I "
			   +"think Mascarvin would look favorably upon meeting with "
			   +"you. Look carefully amongst the bones stacked along "
			   +"the wall. You should see an opening there now."));
		    set_alarm (4.0, 0.0, &reward_heg_quest(from));
		    return;
		}
	    // This is the wand but where is the top?
		from->add_prop(HEG_WAND_PROP, 1);
		command("thank "+ NAMEQ(from));
		command("say I am happy to be reunited with this part of my scepter. "+
		    "Did you recover the top portion from the thief, too?");	
		obj->remove_object();
		return;
	} // Not the scepter wand, either.
	// There isn't anything else that I want.
    set_alarm(0.1, 0.0, &not_wanted(obj, from));
	return;
}

string
do_quest_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote frowns and looks around.");
        return "";
    }
	if (!CHECK_QUEST_HEG(TP))	
	{
		// Quest is being given out, lets clone the npc with the scepter pieces.
		if (!thief)
		{	
	        thief = clone_object("/d/Avenir/common/dead/mon/scepter_thief");
		    thief->move_living("M", CRYPT+"crypt"+(19+random(30)));
		    STATSERV_LOG_EVENT("crypt", "Quest: Scepter thief cloned");
        }
		command("say My peaceful slumber has been disturbed again.");
		command("say Nitikas has sent another follower to steal my "
		    +"scepter of office. It is beautiful and unique, two "
	        +"things he covets.");
	    set_alarm(2.0, 0.0, &command("say When I died it was ceremoni"
    		+"ally broken and interred with my body in my sarcophagus, "
			+"but now it is gone."));
		set_alarm(4.0, 0.0, &command("say When I woke I saw a female "
            +"gnome running away with the pieces of my scepter in "
            +"her hands."));
        set_alarm(6.0, 0.0, &command("say Please return my scepter to "
            +"me and you will be rewarded."));		
        return "";
	}
}


string
do_masq_ask()
{
    if (IS_INFIDEL(TP))
    {
        command("emote screams something that sounds like: INFIDEL!");
        command("$kill "+ NAMEQ(TP));
        return "";
    }
    if (!CAN_SEE(TO, TP))
    {
        command("emote frowns and looks around.");
        return "";
    }
	if (!CHECK_QUEST_HEG(TP))	
	{
		command("say I'm far more concerned with finding my scepter.");
        return "";
	}
	if (!CHECK_QUEST_MASQ(TP))	
	{
		command("say If you are certain, I can show you the way "
		    +"to Mascarvin...");
		command("say Meeting her is a privilege at any time, "
	        +"especially outside of death's door.");
        set_alarm(3.0, 0.0, &command("say Look you to the bones "
		    +"stacked here in my chamber and your eyes will see "
			+"what others cannot."));		
        return "";
	}
	command("say You may go that way just the once. If you wish to "
	    +"see her again -- you must die first.\n");
	return "";
}


