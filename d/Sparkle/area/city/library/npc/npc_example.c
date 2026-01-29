/*
 *  /w/petros/sparkle/library/npc/nikolon.c
 *
 *  Nikolon is the head librarian of the Library of Sparkle
 *  
 *  Created by Petros, March 2008
 */
#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <ss_types.h>
#include "../../defs.h"

// Inheritance 
inherit SPARKLE_NPC_BASE;

// Prototypes
public void             create_monster();
public void             react_hook_fart(object player);
public void             react_hook_cough(object player);
public void             speech_hook(string verb, object actor, 
                                    string adverb, object *oblist,
                                    string text, int target);
public string           help_answer();

/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int is_valid_room(string str)
{
    if (wildmatch("/w/petros/sparkle/library/room/*", str))
    {
        return 1;
    }
    
    return 0;
}

/* 
 * Function name:       create_monster
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_monster()
{
    set_name("nikolon");
    set_living_name("nikolon");
    set_race_name("human");
    set_adj("lanky");
    set_adj("light-haired");
    set_short("lanky light-haired librarian");
    set_gender(G_MALE);
    set_long("He looks like the head librarian.\n");

    set_stats(({ 60, 60, 60, 80, 40, 80 }));
    set_hp(100);
    
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120);

    add_ask( ({ "help", "task", "assistance", "carrot", "potion",
                "letter", "quest", "tasks", "quests" }),
        &help_answer());    
}

/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public string
help_answer()
{
    command("say Hello there!");
    return "";
}

/*
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this living, or when
 *                it is performed on in the room in general, this function
 *                is called to let the living know about the emotion. This
 *                way we can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used w/ the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the 
 *                    used emotion, preceded by a " " (space). This way you
 *                    can use the adverb in your reaction if you please 
 *                    without having to parse it further.
 *                object *oblist - the targets of the emotion, if any.
 *                int cmd_attr - the command attributes, if any.
 *                int target - if true, this object was a target of the 
 *                             emote.
 */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,
    int cmd_attr, int target)
{
    /*
    int asksize = sizeof(ask_arr);
    foreach (mixed askitem : ask_arr)
    {
        if (member_array("help", askitem[0]) >= 0)
        {
            this_object()->check_call(askitem[1], this_object());
            command("say I found help!");
            break;
        }
    }
    */
    float delay = 0.3;
    switch (emote)
    {
    case "cough":
        set_alarm(delay, 0.0, &react_hook_cough(actor));
        break;
    case "fart":
        set_alarm(delay, 0.0, &react_hook_fart(actor));
        break;
    }
}

/*
 * Function name: react_hook_fart
 * Description  : This is defined for npcs to react to a fart action
 * Arguments    : player - Player who farted
 * Returns      : nothing
 */
public void
react_hook_fart(object player)
{
    string player_name = player->query_name();
    if (!CAN_SEE(this_object(), player))
    {
        command("say Whoever just farted, it's just plain rude. "
              + "Please go outside or use the restroom.");
    }
    else
    {
        command("say to " + player_name 
              + " It's pretty rude to fart in the Library.");
    }}

/*
 * Function name: react_hook_cough
 * Description  : This is defined for npcs to react to a cough action
 * Arguments    : player - Player who coughed
 * Returns      : nothing
 */
public void
react_hook_cough(object player)
{
    string player_name = player->query_name();
    if (!CAN_SEE(this_object(), player))
    {
        command("say Whoever just coughed, please try and keep quiet. "
              + "People are trying to study around here.");
    }
    else
    {
        command("say to " + player_name 
              + " Shhhhh! People are trying to study around here!\n");
    }
}

/*
 * Function name: speech_hook
 * Description  : This is defined for npcs to process speech actions
 * Arguments    : actor         - Player who spoke
 *                verb          - passed by the room. first word entered 
 *                                by players this is assumed to be the verb,
 *                                except for speech commands like ' and a'
 *                adverb        - adverb if there was one used
 *                oblist        - list of objects that were targetted
 *                text          - text of the speech
 *                target        - -1/0/1 - targeted at others/
 *                                       - targeted at no one
 *                                       - directed targeted
 * Returns      : nothing
 */
public void
speech_hook(string verb, object actor, string adverb, object *oblist,
            string text, int target)
{
    string *cues = ({ "novak",
                      "petros",
					  "styles",
					  "aeg",
					  "gorboth",
					  "you",
					  "he",
					  "him",
					  "a",
					  "to",
					  "is"
                   });
    
    string lc_arguments = " " + lower_case(text) + " ";
    int already_processed = 0; // boolean ensures that only one cue is 
                               // spoken at the same time. put the cue 
                               // priority as the order in the switch 
                               // statement
    foreach (string cue: cues)
    {
        if (already_processed != 0)
        {
            break;
        }
        
        if (sizeof(regexp( ({ lc_arguments }), " [! ?\\.,]*" + cue + "[! ?\\.,]* ")) > 0)
        {
            switch (cue)
            {
            case "novak":
                command("whisper to "+ actor->query_real_name() +
						" Did you say Novak? Be careful speaking that name in public.");
                already_processed = 1;
                continue;

            case "petros":
                command("say Petros is the most awesome wizard "
                      + "in the world!");
                already_processed = 1;
                continue;

			case "styles":
				command("sigh");
                command("say Styles? Well, there's a troubeled soul I'd say.");
                already_processed = 1;
                continue;

			case "aeg":
                command("say to "+ actor->query_real_name() +
						" Yes, Aeg. He's one cute little gnome.");
				command("smile");
                already_processed = 1;
				continue;

			case "gorboth":
                command("say to "+ actor->query_real_name() +
						" Be carefull around Gorboth. He might start singing for us.");
                already_processed = 1;
				continue;

			case "you":
			case "is":
			case "to":
                command("say I just looove the sound of your voice!");
				command("hug "+ actor->query_real_name());
                already_processed = 1;
                continue;

			case "a":
			case "he":
			case "him":
                command("say Please, talk more! It makes me so happy.");
				command("kiss "+ actor->query_real_name());
                already_processed = 1;
                continue;

            }
        }
    }
}
