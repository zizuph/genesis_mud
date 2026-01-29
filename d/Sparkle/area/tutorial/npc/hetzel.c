/*
 *  /d/Sparkle/area/tutorial/npc/hetzel.c
 *
 *  This is the first npc new players will meet in the game. He
 *  is part of the conversation tutorial, and will hand out
 *  coins to players who complete his conversation tree.
 *
 *  Location: /d/Sparkle/area/tutorial/town/road_1.c
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 *
 *  Updated August 2015, by Bart Freeman (Tedare)
 *  Changed the line of questioning to pertain to the main
 *  quest in this area while still teaching conversation skills.
 */
 
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "silverdell_npc2";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_hetzel_asks();
public void	   greenhollow_answer();
public void    silverdell_answer();
public void    conversation_answer();
public void    call_answer();
public void    dire_answer();
public void    mountain_answer();
public void    castle_answer();
public void    summoning_answer();
public void    pox_answer();
public void    mine_answer();
public void    kobold_answer();
public void    demon_answer();
public void    farmer_answer();
public void    help_answer();
public void    vampire_answer();
public void    monarchy_answer();
public void    baron_answer();
public void    mayor_answer();
public void    adventurer_answer();
public void    reward_answer();
public void	   pass_answer();
public void    check_beginner(); 
public void    forget_answer();
/* definitions */

#define        QUEST_OFFER      "_rillian_quest_hetzel_offer"


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("hetzel");
    set_name("hetzel");
    add_name("hetzel fengard");
    set_adj( ({ "friendly", "old" }) );
    set_race_name("elf");
    add_name("_silverdell_innkeeper");

    set_title("Fengard, Silverdell Councilman, Retired Innkeeper");

    set_long("A worried look seems permanently carved into his"
      + " face. His grim visage is completed with pleading eyes"
      + ", which are peering at you expectantly.\n");

    default_config_npc(20);  /* We'll make him mildly impressive */

    set_act_time(2);
    add_act("emote says: I hope the Baron doesn't destroy the town.");
    add_act("emote says: I'm not sure anyone will be safe if"
      + " a horde of demons pours out of the mountains.");
    add_act("emote says: I wonder how many adventurers have"
		+ " answered the Mayor's call for help.");
    add_act("emote says: The Mayor has been looking for"
		+ " someone like you to help us!");
	add_act("emote says: I wish Farmer Brown had finished off the"
		+ " Baron last time he attacked the town.");

    add_hetzel_asks();
    set_job_response("I have been commissioned to recruit young"
      + " adventurers to help the Mayor save the town from Baron"
      + " von Krolock and his demon army.");

    remove_prop(LIVE_I_NEVERKNOWN);
	add_prop(LIVE_I_ALWAYSKNOWN, 1);

    setuid();
    seteuid(getuid());
} /* create_silverdell_npc */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("smile . "+this_player()->query_real_name());
    command("say I don't have much to say about that topic. I'm"
      + " here to help recruit adventurers for the Mayors quest."
      + " The survival of Greenhollow and Silverdell as a whole"
      + " depends on us finding a way to defeat Baron von Krolock"
      + " before he can unleash his demons on us.");
    return "";
} /* default_answer */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where did they go?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        add_hetzel_asks
 * Description  :        hetzel has a dialogue tree
 *                       which can lead to him giving out
 *                       rewards to players who complete it
 */
public void
add_hetzel_asks()
{
    add_ask( ({ "town", "greenhollow", "village",
                "town of greenhollow", "city" }),
        VBFC_ME("greenhollow_answer"));
	
	add_ask( ({ "silverdell", "area", "land", "region"}),
		VBFC_ME("silverdell_answer"));
		
	add_ask( ({ "conversation", "talk", "speak" }),
		VBFC_ME("conversation_answer"));
		
	add_ask( ({ "call", "cause"}),
		VBFC_ME("call_answer"));
		
	add_ask( ({ "dire", "situation", "dire situation", "danger", "dangerous"}),
		VBFC_ME("dire_answer"));
		
	add_ask( ({ "mountain", "mountains"}),
		VBFC_ME("mountain_answer"));
		
	add_ask( ({ "castle", "fort", "fortress"}),
		VBFC_ME("castle_answer"));
		
	add_ask( ({ "summoning", "circle", "summoning circle",
				"light", "lights", "otherwordly", 
				"otherworldly lights", "otherwordly light"}),
		VBFC_ME("summoning_answer"));
		
	add_ask( ({"pox", "disease"}),
		VBFC_ME("pox_answer"));
		
	add_ask( ({ "mine", "shaft", "mine shaft"}),
		VBFC_ME("mine_answer"));
		
	add_ask( ({ "kobold", "kobolds"}),
		VBFC_ME("kobold_answer"));
		
	add_ask( ({ "baron", "baron von krolock", "krolock"}),
		VBFC_ME("baron_answer"));
		
	add_ask( ({ "demon", "demons", "horde", "demon horde", 
				"army", "demon army"}),
		VBFC_ME("demon_answer"));
		
	add_ask( ({ "mayor"}),
		VBFC_ME("mayor_answer"));
		
	add_ask( ({ "monarchy", "king", "queen", "royal", "royalty"}),
		VBFC_ME("monarchy_answer"));
		
	add_ask( ({ "adventurer", "explorer"}),
		VBFC_ME("adventurer_answer"));
		
	add_ask( ({ "farmer", "farmer brown", "brown"}),
		VBFC_ME("farmer_answer"));
		
	add_ask( ({ "help", "quest", "reward"}),
		VBFC_ME("help_answer"));
	
	add_ask( ({ "pass", "north"}),
		VBFC_ME("pass_answer"));
		
	add_ask( ({ "vampire"}),
		VBFC_ME("vampire_answer"));
	
	add_ask( ({ "evil"}),
		VBFC_ME( "evil_answer"));
	
	add_ask( ({ "forget me"}),
		VBFC_ME("forget_answer"));
		
} /* add_hetzel_asks */

public string
forget_answer()
{
	if (CHECK_TUTORIAL_BIT(BEGINNER_BIT))
    {
        CLEAR_TUTORIAL_BIT(BEGINNER_BIT);
		CLEAR_TUTORIAL_BIT(HETZEL_BIT);
		command("say As you wish!");
    }
	else
	{
		command("say There is nothing to forget.");
	}
}

/*
 * Function name:       silverdell_answer
 * Description  :       response to an add_ask
 */
public string
greenhollow_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Greenhollow? Oh, it's just to the north along"
          + " the road.\n");
        command("point north");
        break;
    case 1:
        command("say Head north, and you'll find it. It has just"
          + " about anything you could need.\n");
        break;
    case 2:
        command("say You can't miss it! Follow the road north, and"
          + " you'll be there in no time. There is a lot to learn"
          + " and do there.\n");
        break;
    }
	check_beginner();
    return "";
} /* silverdell_answer */

/*
 * Function name:       silverdell_answer
 * Description  :       response to an add_ask
 */
public string
silverdell_answer()
{
    command("say Yeah this whole area is called Silverdell."
      + " It encompasses the town of Greenhollow, the island"
      + " forest to the east, the farmlands and meadows to"
	  + " the north, and the rough mountains to the northwest.\n");
	  
	  check_beginner();
	  
    return "";
} /* silverdell_answer */

/*
 * Function name:       conversation_answer
 * Description  :       response to an add_ask
 */
public string
conversation_answer()
{
    command("nod");
    command("say I'd love to talk to you, especially about our"
      + " town and our dire situation. If the Mayor doesn't"
      + " get enough help, our town may be destroyed.\n");
	  
	  check_beginner();
	  
    return "";
} /* conversation_answer */

/*
 * Function name:       call_answer
 * Description  :       response to an add_ask
 */
public string
call_answer()
{
    command("nod vigorously");
    command("say Yes! Our esteemed Mayor has called for help,"
      + " a quest if you will, and has promised a nice"
      + " reward for whoever helps save our town.\n");
	  
	  check_beginner();
	  
    return "";
} /* call_answer */

/*
 * Function name:       dire_answer
 * Description  :       response to an add_ask
 */
public string
dire_answer()
{
    command("grimace");
    command("say It is certainly dire. The last few who"
      + " have gone into the mountains to kill the Baron"
      + " never returned. Either they are dead, or worse.\n");
	command("shudder");
	
	check_beginner();
	
    return "";
} /* dire_answer */

/*
 * Function name:       mountain_answer
 * Description  :       response to an add_ask
 */
public string
mountain_answer()
{
    command("say The Baron has a castle in the mountains"
      + " northwest of town.  Strange, otherworldly lights"
      + " have been seen there. The town sage believes it"
	  + " to be the light from the summoning circles that"
	  + " Baron von Krolock is using to increase his army.\n");
	  
	  check_beginner();
	  
    return "";
} /* mountain_answer */

/*
 * Function name:       castle_answer
 * Description  :       response to an add_ask
 */
public string
castle_answer()
{
    command("say That old castle was long abandoned. A"
      + " nasty pox wiped out the old monarchy. Nobody"
      + " in their right mind would dare go up there"
	  + " and risk getting that disease. Especially"
	  + " with it crawling with demons now.\n");
	  
	  check_beginner();
	  
    return "";
} /* castle_answer */

/*
 * Function name:       pox_answer
 * Description  :       response to an add_ask
 */
public string
pox_answer()
{
    command("wring");
    command("say Oh heavens that was a nasty disease!"
      + " I saw a couple drawings of people with nasty"
      + " purple blisters and bleeding sores. The bodies"
	  + " were thrown down an abandoned mine shaft out"
	  + " of fear\n");
	  
	  check_beginner();
	  
    return "";
} /* pox_answer */

/*
 * Function name:       mine_answer
 * Description  :       response to an add_ask
 */
public string
mine_answer()
{
    command("say Thats why this area is called Silverdell."
      + " The mines weren't too far from the castle. We"
      + " used to export lots of silver, but the vein"
	  + " ended and no more have been found, nor are any"
	  + " likely to be with the shafts full of kobolds.\n");
	  
	  check_beginner();
	  
    return "";
} /* mine_answer */

/*
 * Function name:       kobold_answer
 * Description  :       response to an add_ask
 */
public string
kobold_answer()
{
    command("grimace");
    command("say Rat-like little folks they are. Not too"
      + " tough by themselves, but they tend to travel in"
      + " groups. They'll stick you in a stew-pot if you"
	  + " aren't careful.\n");
	  
	  check_beginner();
	  
    return "";
} /* kobold_answer */

/*
 * Function name:       summoning_answer
 * Description  :       response to an add_ask
 */
public string
summoning_answer()
{
    command("wince");
    command("say Nasty business that! Who knows what the"
      + " Baron has to promise or sacrifice for the"
      + " demons to do his bidding. I try not to think"
	  + " about it too much.\n");
	  
	  check_beginner();
	  
    return "";
} /* summoning_answer */

/*
 * Function name:       mayor_answer
 * Description  :       response to an add_ask
 */
public string
mayor_answer()
{
    command("nod");
    command("say The Mayor lives on the North end of town. He is"
      + " doing his best to keep us safe from the vampire Baron"
      + " von Krolock and his horde of demons. You should go and"
	  + " talk to him to see how you can help out!\n");
	  
	  check_beginner();
	  
    return "";
} /* mayor_answer */

/*
 * Function name:       vampire_answer
 * Description  :       response to an add_ask
 */
public string
vampire_answer()
{
    command("say A frightful state of being, neither fully dead"
      + " nor fully alive. Some say it's the consequence of"
      + " being so evil, but whatever the cause, the Baron"
	  + " is a most grave threat to our town.\n");
	  
	  check_beginner();
	  
    return "";
} /* vampire_answer */

/*
 * Function name:       demon_answer
 * Description  :       response to an add_ask
 */
public string
demon_answer()
{
    command("say Demons are soulless evil creatures with no"
      + " respect for life. Reports say that the castle is"
      + " filling up with them, it is just a matter of time"
	  + " before Baron von Krolock leads them in an attack"
	  + " on the town.\n");
	  
	  check_beginner();
    return "";
} /* demon_answer */

/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public string
help_answer()
{
    command("nod");
    command("say Oh yes! We can most certainly use your help."
      + " The mayor needs strong people like you to fight"
      + " the evil Baron von Krolock and his demons. Go visit"
	  + " the Mayor north of town and take up our cause!\n");
	  
	check_beginner();

    return "";
} /* help_answer */

/*
 * Function name:       monarchy_answer
 * Description  :       response to an add_ask
 */
public string
monarchy_answer()
{
    command("shrug");
    command("say A fat old king and his skinny little queen."
      + " I don't remeber the names exactly, that was before"
      + " my time.\n");
	  
	  check_beginner();
	  
    return "";
} /* monarchy_answer */

/*
 * Function name:       adventurer_answer
 * Description  :       response to an add_ask
 */
public string
adventurer_answer()
{
    command("peer");
    command("say Adventurers are people like yourself who"
      + " explore the realms and hopefully find ways to"
      + " help people at the same time.  You really should"
	  + " go see the Mayor to see how you can help us!\n");
	  
	  check_beginner();
	  
    return "";
} /* adventurer_answer */

/*
 * Function name:       pass_answer
 * Description  :       response to an add_ask
 */
public string
pass_answer()
{
    command("smile hopefully");
    command("say Sure I'll let you pass to the north.\n");
	  
	check_beginner();
	  
    return "";
} /* pass_answer */

/*
 * Function name:       baron_answer
 * Description  :       response to an add_ask
 */
public string
baron_answer()
{
    command("nod");
    command("say Oh yes, that situation is dire! Baron von"
      + " Krolock is building an army of demons in the mountains,"
      + " and the town is in serious danger. The Mayor is"
	  + " recruiting adventurers such as yourself to fight off"
	  + " the evil.\n");
	  
	  check_beginner();
	  
    return "";
} /* baron_answer */

/*
 * Function name:       farmer_answer
 * Description  :       response to an add_ask
 */
public string
farmer_answer()
{
    command("nod");
    command("say It sounds unusual, but it was Farmer Brown, who"
      + " lives a ways north of town, who defeated the Baron the"
      + " last time he threatened the town.  Unfortunately, the"
	  + " Farmer failed to kill the Baron and now he is back"
	  + " even stronger. The Mayor has offered a quest to kill"
	  + " the Baron.\n");
	  
	  check_beginner();
    return "";
} /* farmer_answer */

/*
 * Function name:       evil_answer
 * Description  :       response to an add_ask
 */
public string
evil_answer()
{
    command("sigh");
    command("say I guess it's a bit subjective, but anything"
      + " that exists to cause misery and suffering to others"
      + " and takes enjoyment from it is evil in my book.\n");
	  
	  check_beginner();
    return "";
} /* evil_answer */

/*
 * Function name:       reward_answer
 * Description  :       response to an add_ask
 */
public string
reward_answer()
{
     command("say Oh yes, the Mayor will reward you well for defeating"
      + " the Baron.\n");

    return "";
} /* reward_answer */

/*
 * Function name:       check_begginer
 * Description  :       set beginner bit if at least one quetion is asked
 */
public void
check_beginner()
{
	if (!CHECK_TUTORIAL_BIT(BEGINNER_BIT))
    {
        command("say Make sure you stop and talk to the Mayor.");

        SET_TUTORIAL_BIT(BEGINNER_BIT);
    }
}
/*check_beginner*/



