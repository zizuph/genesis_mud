/*
 *  /d/Sparkle/area/tutorial/npc/farmers_wife.c
 *
 *  This npc is integral to the quests of the area. She resides in
 *  the farmhouse north of Greenhollow.
 *
 *  Location: /d/Sparkle/area/tutorial/farm/farmhouse.c
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit NPC_DIR + "silverdell_npc";
inherit LIB_DIR + "quest_reward";
inherit "/d/Genesis/lib/intro";

#include <const.h>              /* for G_FEMALE                 */
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_trainer_asks();
public void    help_answer();
public void    field_answer();
public void    farmer_answer();
public void    daughter_answer();
public void    return_object(object obj, object to);
public void    react_carrot(object obj, object to);
public void    react_potion(object obj, object to);



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Matilda");
    set_name("matilda");
    add_name( ({ "matilda brown", "wife", "woman",
                 "_tutorial_farmers_wife", "farmers wife",
                 "farmer's wife", "farmer brown's wife",
                 "farmer browns wife" }) );
    set_adj( ({ "sturdy", "elderly", "old" }) );
    set_race_name("human");
    set_gender(G_FEMALE);

    set_title("Brown, the Farmer's Wife");
    set_short("sturdy old woman");
    set_long("This is Farmer Brown's wife. She looks concerned about"
      + " something. You can <ask wife help> to see if she needs any"
      + " help from you.\n");

    default_config_npc(120);  /* Too strong for these players */

    set_act_time(2);
    add_act("emote busies herself around the farmhouse.");
    add_act("emote looks out the window in the direction of the fields.");
    add_act("emote shakes her head as if troubled.");
    add_act("emote says: Would you be able to help me?");
    add_act("emote sighs deeply.");

    set_job_response("It is my job to help Farmer Brown tend the"
      + " farm.");

    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0); /* You can give her stuff. */

    add_silverdell_asks();
    add_trainer_asks();

    set_skill(SS_AWARENESS, 30);
    set_skill(SS_UNARM_COMBAT, 20);

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
        command("say Where'd they go now?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        add_trainer_asks
 * Description  :        hardel responds to questions about
 *                       the skills he trains.
 */
public void
add_trainer_asks()
{
    add_ask( ({ "help", "task", "assistance", "carrot", "potion",
                "letter", "quest", "tasks", "quests" }),
        VBFC_ME("help_answer"));
    add_ask( ({ "farm", "fields", "farming", "house", "barn" }),
        VBFC_ME("field_answer"));
    add_ask( ({ "farmer brown", "husband", "brown", "farmer" }),
        VBFC_ME("farmer_answer"));
    add_ask( ({ "daughter", "hayloft" }),
        VBFC_ME("daughter_answer"));

} /* add_trainer_asks */


/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public string
help_answer()
{
    object  note;
    object  carrot;

    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say Who said that? Where are you??");
        return "";
    }

    if (!CHECK_TUTORIAL_BIT(POTION2_BIT))
    {
        if (CHECK_TUTORIAL_BIT(NOTE_BIT))
        {
            if (present("_tutorial_letter", this_player()))
            {
                command("say Please, take the letter I gave you to"
                  + " Bibbiss.");
                command("say She is on the second floor of the"
                  + " Adventurers guild in town.");
                command("say When you find her, you can <give letter to"
                  + " bibbiss>.");
                return "";
            }

            if (present("_tutorial_potion", this_player()))
            {
                command("say Did you give the letter to Bibbiss?");
                command("say Did she give you something for me?");
                return "";
            }

            command("say Did you lose the letter I gave you?");
            command("say Here's another one.");
            command("say Please, take it to Bibbiss right away!");
            command("say She is on the second floor of the"
              + " Adventurers guild in town.");

            note = clone_object(OBJ_DIR + "farmers_letter");
            note->move(this_object());
            command("give letter to " + this_player()->query_real_name());
            return "";
        }

        command("say Baron von Krolock has sent a plague against us!");
        command("say Rabbits are always a nuisance, of course.");
        command("say But the foul beasts which are in our fields ...");
        command("say They can only be the product of his evil ways.");
        command("say Please, take this letter to Bibbiss.");
        command("say She is the Magic Trainer in Greenhollow.");
        command("say I believe she'll know what to do.");

        note = clone_object(OBJ_DIR + "farmers_letter");
        note->move(this_object());
        command("give letter to " + this_player()->query_real_name());

        SET_TUTORIAL_BIT(NOTE_BIT);
        return "";
    }

    if (!CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        if (!CHECK_TUTORIAL_BIT(CARROT2_BIT))
        {
            command("say I think I know what to do.");
            command("say Please bring me a carrot from the fields.");
            return "";
        }

        if (!(carrot = present("_tutorial_enchanted_carrot", 
            this_player())))
        {
            command("say Did you lose the enchanted carrot?");
            command("say I've still got the potion broth right here.");
            command("say Give me another carrot, and I'll enchant it.");
            return "";
        }

        command("say Find the mother rabbit!");
        command("say She's probably in a big rabbit hole somewhere.");
        command("say Look for where the rabbits are thickest in the"
          + " fields.\n");
        command("say You've got to find a way to get her to eat that"
          + " enchanted carrot!");
        return "";
    }

    if (!CHECK_TUTORIAL_BIT(GARLIC_BIT))
    {
        command("say Farmer Brown has returned from the Sterling Woods.");
        command("say Unfortunately, it looks like he had a hard time.");
        command("say He's pretty upset about it.");
        command("say He could probably use your help.");
        command("say You can usually find him in the barn.");
        command("emote points out the window across the barnyard to the"
          + " west.");
    }

    if (!CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        command("say You should talk to Farmer Brown.");
        command("say He is probably in the barn.");
        return "";
    }

    command("say You've helped us more than we ever could have hoped"
      + " for. I'd go so far as to call you a real hero. We never thought"
      + " we'd see the end of Baron von Krolock.");
    return "";
} /* help_answer */


/*
 * Function name:       field_answer
 * Description  :       response to an add_ask
 */
public string
field_answer()
{
    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        command("say Our fields are doing much better, thanks to you.");
        command("say The bunnies are still a nuisance, I suppose.");

        if (CHECK_TUTORIAL_BIT(GARLIC_BIT))
        {
            command("say But thanks to you, garlic is growing again.");
            return "";
        }

        command("say Its too bad Farmer Brown lost his garlic starts.");
        command("say You ought to go talk to him. He's in the barn.");
        return "";
    }

    command("say Farming has been hopeless since these bunnies came!");
    command("say If only there was someone to help us!");
    return "";
} /* field_answer */


/*
 * Function name:       farmer_answer
 * Description  :       response to an add_ask
 */
public string
farmer_answer()
{
    if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        command("say Farmer Brown has returned home.");
        command("say I'm glad, because I was beginning to worry.");
        command("say He's usually in the barn, if you're looking for him.");
        return "";
    }

    command("say Farmer Brown went across the river into the forest.");
    command("say He's looking for wild garlic to plant in the field.");
    command("say He's been gone a while. I'm beginning to worry!");
    return "";
} /* farmer_answer */


/*
 * Function name:       daughter_answer
 * Description  :       response to an add_ask
 */
public string
daughter_answer()
{
    command("say Our daughter?");
    command("say I'm not sure where she's got off to.");
    command("say She often plays in the hayloft in the barn.");
    return "";
} /* daughter_answer */


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
    if (obj->id("_tutorial_potion"))
    {
        set_alarm(0.5, 0.0, &react_potion(obj, to));
        return;
    }

    if (obj->id("_tutorial_carrot"))
    {
        set_alarm(0.5, 0.0, &react_carrot(obj, to));
        return;
    }

    if (obj->id("_tutorial_clove"))
    {
        command("say Hmmm ... that looks like one of the cloves that"
          + " Farmer Brown has been looking for. You should give it to"
          + " him.\n");
    }
    else
    {
        command("say Thanks, but I don't think I need that.");
    }
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name:        react_carrot
 * Description  :        have the npc respond to a specific object
 */
public void
react_carrot(object obj, object to)
{
    set_this_player(to);

    if (!CHECK_TUTORIAL_BIT(CARROT_BIT))
    {
        command("say Whats this? Why are you pulling up my carrots?");
        //return;
	}
    else if (CHECK_TUTORIAL_BIT(BUNNY_BIT))
    {
        command("say Ooo ... thats a nice one!");
        command("say Please, take it, you've earned it!");
    }
    else if (obj->query_enchanted())
    {
        command("say I can't fight my way through all those things!");
        command("say Take this and find a way to feed it to the"
          + " mother bunny. Her hole is somewhere in the field.");
    }
    else
    {
        if (CHECK_TUTORIAL_BIT(CARROT2_BIT))
        {
            command("say What happened, did you lose the other one?");
        }
        else
        {
            command("say Ah, excellent. That's a nice big carrot.");
        }

        command("emote drops the carrot into the bubbling potion broth.");
        command("emote allows the carrot to stew for a minute or two.");
        command("emote fishes the carrot out with a ladle.");
        command("say Oooo ... look how this thing is glowing.");
        command("say Please, take this enchanted carrot!");
        command("say Find a way to feed it to the mother bunny.");
        obj->set_enchanted(1);

        set_this_player(to);
        SET_TUTORIAL_BIT(CARROT2_BIT);

        if (obj->query_picked_by() == to->query_real_name())
        {
            give_reward(this_player(), TUTORIAL_CARROT_GROUP,
                TUTORIAL_CARROT_BIT, TUTORIAL_CARROT_EXP,
                "Tutorial Carrot");
        }
        else
        {
            to->catch_tell("If you'd picked it yourself, you'd probably"
              + " feel more experienced. Oh, well.\n");
        }

        /*command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
        if (environment(obj) == this_object())
        {
            command("drop " + OB_NAME(obj));
        }

        return;*/
    }

    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
        //command("drop " + OB_NAME(obj));
		obj->remove_object();
    }
} /* react_carrot */


/*
 * Function name:        react_potion
 * Description  :        have the npc respond to a specific object
 */
public void
react_potion(object obj, object to)
{
    set_this_player(to);

    if (CHECK_TUTORIAL_BIT(POTION2_BIT))
    {
        command("say Another potion? That's strange. One was enough.");
        obj->remove_object();
        return;
    }

    if (!CHECK_TUTORIAL_BIT(NOTE_BIT))
    {
        command("say Whats this potion for? Why'd you give it to me?");
        command("drop " + OB_NAME(obj));
        return;
    }

    obj->remove_object();

    command("emote reads the note attached to the potion.");
    command("emote fills a pot with water.");
    command("emote begins boiling the water on the stove.");
    command("emote pours the potion into the pot.");
    command("emote stirs the water, creating a bubbling broth.");
    command("say Thank you! I know just what to do now.");
    command("say Please bring me a carrot from the fields.");

    give_reward(this_player(), TUTORIAL_POTION_GROUP, TUTORIAL_POTION_BIT,
        TUTORIAL_POTION_EXP, "Tutorial Potion");  

    SET_TUTORIAL_BIT(POTION2_BIT);
    SET_TUTORIAL_BIT(CARROT_BIT);
} /* react_potion */



