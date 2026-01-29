/*
 *  /d/Sparkle/area/tutorial/npc/priest.c
 *
 *
 *  Created August 2015, by Bart Freeman (Tedare)
 *  Done using the syle of Cooper Sherry (Gorboth)
 *  New NPC to allow newbies to change their race
 *  either because they dislike their initial choice
 *  or they just want to compare different races.
 */
#pragma strict_types
#include "../defs.h"
#include <login.h>

inherit NPC_DIR + "silverdell_npc2";

inherit "/d/Genesis/lib/intro";


#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>
#include <time.h>
#include <state_desc.h>

#define change_ready         (0)


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_priest_asks();
public void    change_answer();
public void    race_answer();
public void    human_answer();
public void    elf_answer();
public void    dwarf_answer();
public void    goblin_answer();
public void    hobbit_answer();
public void    gnome_answer();
public void    other_answer();
public void    best_answer();
public void    regrow_answer();
public void    regrow_answer2();
public void    regrow_answer3();
public void    regrow_me();
public void	   regrow_me2();
public void    regrow_me3();
public void    regrowth_answer();
public void    quest_answer();
public void    return_object(object obj, object to);
public void    emote_hook(string emote, object actor, string adverb, object *oblist, string cmd_attr, int target);


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("brek");
    set_name("brek");
    add_name( ({ "brek enphix", "priest", "_tutorial_priest" }) );
    set_adj( ({ "wizened", "humble" }) );
    set_race_name("half-elf");

    set_title("Enphix, Priest of Regrowth");
    set_short("humble wizened half-elf");
    set_long("This half-elf has seen a lot to look this old. The wisdom"
      + " in his eyes kindle instant trust.\n");

    default_config_npc(40);  /* more middleish */

    set_act_time(10);
    add_act("emote says: Not everyone is happy with their body."
			+ " I can help those who feel their soul doesn't match"
			+ " their exterior.\n");
    add_act("emote sizes you up with a look that sees right through you.\n");
	add_act("emote says: If you are unsure if you like your race, I can help you change.\n");


    set_job_response("Priest of Regrowth, at your service.");

    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1); /* You can not give him stuff. */

    add_priest_asks();
    add_silverdell_asks();

    set_skill(SS_AWARENESS, 15);
    set_skill(SS_UNARM_COMBAT, 75);

    setuid();
    seteuid(getuid());
} /* create_silverdell_npc */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(3)), 0.0, &react_intro(who));
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
        command("say Where'd they go now?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        add_priest_asks
 * Description  :        answers questions about race change
 *                      
 */
public void
add_priest_asks()
{
    add_ask( ({ "change", "race change", "changing race",
			"race change", "changing", "change body", 
			"changing body", "body", "change my body", 
			"change my race", "body change", "change race"}),
        VBFC_ME("change_answer"));
		
    add_ask( ({ "race", "races"}),
		VBFC_ME("race_answer"));

	add_ask( ({ "human", "humans"}),
		VBFC_ME("human_answer"));
	
	add_ask( ({ "elf", "elfs", "elves"}),
		VBFC_ME("elf_answer"));
		
	add_ask( ({ "dwarf", "dwarfs", "dwarves"}),
		VBFC_ME("dwarf_answer"));
		
	add_ask( ({ "goblin", "goblins"}),
		VBFC_ME("goblin_answer"));
		
	add_ask( ({ "gnome", "gnomes"}),
		VBFC_ME("gnome_answer"));
		
	add_ask( ({ "hobbit", "hobbits", "hobbitses"}),
		VBFC_ME("hobbit_answer"));
		
	add_ask( ({ "orc","orcs", "minotaur", "minotaurs", "drow",
				"drows", "drowes", "grunt", "grunts", "amazon",
				"amazons", "orc", "orcs", "half-elf", "halfelf",
				"half-elves", "halfelves", "half-orc", "halforc"}),
		VBFC_ME("other_answer"));
	
	add_ask( ({ "best", "best race"}),
		VBFC_ME("best_answer"));
		
	add_ask( ({ "regrow", "regrowth"}),
		VBFC_ME("regrowth_answer"));
	
	add_ask( ({ "quest", "help"}),
		VBFC_ME("quest_answer"));	
} /* add_priest_asks */


/*
 * Function name:       change_answer
 * Description  :       response to an add_ask
 */
public string
change_answer()
{
	if(SD_IS_NEWBIE(this_player()))
	{
    command("say I have the power of Regrowth, and can help"
      + " you fundamentally change who you are. If you do not like"
	  + " your race, I can help you regrow as something else."
	  + " <nod priest> if you want to change your body in any way.\n");
	  SET_TUTORIAL_BIT(RACE_BIT);
	}
	else
	{
	command("say Regrowing someone is a difficult task. I'm afraid"
      + " you have outgrown my abilities and will have to seek other"
	  + " ways to change who you are.\n");
	}
	
    return "";
} /* quest_answer */


/*
 * Function name:       race_answer
 * Description  :       response to an add_ask
 */
public string
race_answer()
{
     command("say There are six races you can choose. Each race"
	   + " has its strengths and weakness. You can choose from"
	   + " human, elf, dwarf, goblin, gnome, and hobbit.\n");
 
    return "";
} /* race_answer */


/*
 * Function name:       human_answer
 * Description  :       response to an add_ask
 */
public string
human_answer()
{
    command("say This is a human, examine it well.\n");
	command("gesture slowly great human statue");
    return "";
} /* human_answer */


/*
 * Function name:       elf_answer
 * Description  :       response to an add_ask
 */
public string
elf_answer()
{
    command("say This is an elf, examine it well.\n");
		command("gesture slowly great elf statue");
    return "";
} /* elf_answer */


/*
 * Function name:       dwarf_answer
 * Description  :       response to an add_ask
 */
public string
dwarf_answer()
{
    command("say This is a dwarf, examine it well.\n");
	command("gesture slowly great dwarf statue");	
    return "";
} /* dwarf_answer */

/*
 * Function name:       goblin_answer
 * Description  :       response to an add_ask
 */
public string
goblin_answer()
{
    command("say This is a goblin, examine it well.\n");
	command("gesture slowly great goblin statue");
    return "";
} /* goblin_answer */

/*
 * Function name:       hobbit_answer
 * Description  :       response to an add_ask
 */
public string
hobbit_answer()
{
    command("say This is a hobbit, examine it well.\n");
	command("gesture slowly great hobbit statue");
    return "";
} /* hobbit_answer */

/*
 * Function name:       other_answer
 * Description  :       response to an add_ask
 */
public string
other_answer()
{
    command("say There may be other races out there, but they"
      + " are all variations on the six main races.\n");
    return "";
} /* other_answer */

/*
 * Function name:       gnome_answer
 * Description  :       response to an add_ask
 */
public string
gnome_answer()
{
    command("say This is a gnome.\n");
	command("gesture slowly gnome statue");
    return "";
} /* gnome_answer */

/*
 * Function name:       best_answer
 * Description  :       response to an add_ask
 */
public string
best_answer()
{
    command("say There is no such thing as a best race."
      + " The best you can hope for is a race that fits"
	  + " you and your goals.");
    return "";
} /* best_answer 

/*
 * Function name:       regrowth_answer
 * Description  :       response to an add_ask
 */
public void
regrowth_answer()
{
    command("say As a priest of regrowth, I can help you escape"
	  + " our current body and regrow one of another race, gender"
	  + ", size, or description.\n");
} /* regrowth_answer */

/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public void
quest_answer()
{
    command("say My ability to help is limited to assisting"
	  + " you in changing your body. The mayor, however, is"
	  + " looking for help.\n");
} /* help_answer */

/*
 * Function name:       regrow_answer
 * Description  :       response to an add_ask
 */
public void
regrow_answer()
{
    command("say May you find happiness in your new form.\n");
	set_alarm(itof(2), 0.0, &regrow_answer2());
} /* regrow_answer */

/*
 * Function name:        regrow_answer2
 * Description  :        delay for cinematics for race change
 */
public void
regrow_answer2()
{
	command("emote ages visibly as he gets a light blue aura"
		+ " around his head and hands.\n");
	set_alarm(itof(2), 0.0, &regrow_answer3());
} /* regrow_answer2 */

/*
 * Function name:        regrow_answer3
 * Description  :        delay for cinematics for race change
 */
public void
regrow_answer3()
{
	command("emote spreads his arms and the blue light begins to"
		+ " gather in front him into a large sphere.\n");
	set_alarm(itof(2), 0.0, &regrow_me());
} /* regrow_answer2 */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    set_this_player(to);

    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }

    return;
} /* return_object */


/* Function name:        regrow_me
 * Description  :        will start a no cost race change
 */
public void
regrow_me()
{
	tell_room(environment(this_player()), QCTNAME(this_player())
	  + " is consumed by the warm blue light.\n", this_player());
	write("Your vision blurs as you are enveloped in a warm"
	  + " blue light.\n\n");
	
	
	this_player()->set_ghost(GP_BODY);
	this_player()->reincarnate();
	this_player()->set_ghost(GP_BODY);
	set_alarm(itof(2), 0.0, &regrow_me2());

} /* regrow_me */

/* Function name:		regrow_me2
 * Description:			continuation of regrow_me
 */
 
public void
regrow_me2()
{
	write("\nThe shimmering blue portal begins to pulse and you feel"
	  + " yourself being incontrollably drawn into it.\n\n");
	set_alarm(itof(2), 0.0, &regrow_me3());
}
/* regrow_me2 */

/* Function name:		regrow_me3
 * Description:			continuation of regrow_me
 */
public void
regrow_me3()
{
	this_player()->move_living("M", "/d/Genesis/login/creation", 1,1);		
}
/* regrow_me3 */

/*
 * Function name: emote_hook
 * Description  : Used to trigger Race Change sequence
 */
 
public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    string cmd_attr, int target)
{
	if (emote=="nod")
	{
		if(target)
		{
			if(CHECK_TUTORIAL_BIT(RACE_BIT))
			{	
				set_alarm(itof(2), 0.0, &regrow_answer());
				CLEAR_TUTORIAL_BIT(RACE_BIT);
			}
		}
	}
}

