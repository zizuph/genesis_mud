/*
 *  /d/Sparkle/area/tutorial/npc/mayor.c
 *
 *  The Mayor of Greenhollow. He is the questmaster for the defeat
 *  of Baron von Krolock.
 *
 *  Location: /d/Sparkle/area/tutorial/town/mayors_house.c
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 *
 *  Update August 2015, by Bart Freeman (Tedare)
 *  Changed talking points and information to tie into the new areas.
 *  Updated September 2016, by Tim Breen (Mirandus)
 *  Changed the alignment impact from +600 to +100.
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit NPC_DIR + "silverdell_npc";
inherit LIB_DIR + "quest_reward";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_trainer_asks();
public void    quest_answer();
public void    krolock_answer();
public void    heart_answer();
public void    mayor_answer();
public void    farmer_answer();
public void    pond_answer();
public void    cave_answer();
public void    forest_answer();
public void    spider_answer();
public void    mine_answer();
public void    kobold_answer();
public void    return_object(object obj, object to);


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("berthold");
    set_name("berthold");
    add_name( ({ "berthold sandicutt", "mayor", "_tutorial_mayor" }) );
    set_adj( ({ "authoritative", "finely-dressed" }) );
    set_race_name("hobbit");

    set_title("Sandicutt, Mayor of Greenhollow");
    set_short("authoritative finely-dressed hobbit");
    set_long("This hobbit looks to be a man of importance. Even so, he"
      + " does have quite a big nose to compliment his tiny ears, and"
      + " his cheeks are as puffy as a chipmunk's. As Mayor of Greenhollow,"
      + " he is eager to give out quests to people who <ask> for them.\n");

    default_config_npc(60);  /* more middleish */

    set_act_time(2);
    add_act("emote strides to and fro, puffing on his long pipe.");
    add_act("emote peers out the window and wrings his hands.");
    add_act("emote walks to the map, and frowns at the mountains there.");
    add_act("emote says: You look brave enough to take on the Baron.");
    add_act("emote sighs with deep concern.");


    set_job_response("Why, I am the Mayor of Greenhollow!");

    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0); /* You can give him stuff. */

    add_trainer_asks();
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
    add_ask( ({ "adventure", "task", "tasks", "quest", "quests",
                "help" }),
        VBFC_ME("quest_answer"));
    add_ask( ({ "baron", "krolock", "baron von krolock", "evil",
                "vampire" }),
        VBFC_ME("krolock_answer"));
    add_ask( ({ "heart" }),
        VBFC_ME("heart_answer"));
    add_ask( ({ "mayor", "greenhollow", "town" }),
        VBFC_ME("mayor_answer"));
    add_ask( ({ "farm", "farmer brown", "brown", "farmer" }),
        VBFC_ME("farmer_answer"));
	add_ask( ({ "meadow", "pond", "fish", "frog"}),
		VBFC_ME("pond_answer"));
	add_ask( ({ "cave", "underwater cave"}),
		VBFC_ME("cave_answer"));
	add_ask( ({ "forest", "island", "hunter"}),
		VBFC_ME("forest_answer"));
	add_ask( ({ "spider", "spiders", "black spider", "black spiders"}),
		VBFC_ME("spider_answer"));
	add_ask( ({ "mine", "shaft", "mine shaft", "silver", "silver mine"}),
		VBFC_ME("mine_answer"));
	add_ask( ({ "kobold", "kobolds"}),
		VBFC_ME("kobold_answer"));

} /* add_trainer_asks */


/*
 * Function name:       quest_answer
 * Description  :       response to an add_ask
 */
public string
quest_answer()
{
	object   gem;
	
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        command("say Congratulations, adventurer!");
        command("emote shakes your hand enthusiastically.");
        command("emote says: You really did it!");
        command("say All of Silverdell owes you a debt of gratitude.");
        command("say You will forever be remembered as the savior of"
          + " this land.");

        return "";
    }

    command("introduce myself");
    command("emote looks you up and down.");
    command("emote says: You look to be a brave sort, adventurer.");
    command("emote says: Therefore, I will ask you to save our land!");
    command("emote says: A terrible and evil force has descended upon us.");
    command("emote says: A foul creature by the name of Baron von"
      + " Krolock.");
    command("emote says: He seeks to poison our land, and destroy our"
      + " town.");
    command("emote says: And he is powerful enough to do it!");
    command("emote says: Time is running out ... he must be stopped!");
    command("emote says: The only way to kill him is to cut out his"
      + " heart.");
    command("emote says: He is a Vampire, you see.");
    command("emote says: Therefore, he is beyond mortal harm!");
    command("emote says: But if you travel to the north, find Farmer"
      + " Brown.");
    command("emote says: He has done battle with the Baron before.");
    command("emote says: He will know what to do.");
    command("emote says: Return to me with the heart of Baron von"
      + " Krolock!");
 
	if (!CHECK_TUTORIAL_BIT(HETZEL_BIT))
	{
		command("say Take these gems to help you. In town, there is a"
		  + " general store where you can sell them for money.");

		gem = clone_object(OBJ_DIR + "reward_gem")->move(this_object());
		gem = clone_object(OBJ_DIR + "reward_gem")->move(this_object());
		gem = clone_object(OBJ_DIR + "reward_gem")->move(this_object());
		command("give gems to " + this_player()->query_real_name());

		SET_TUTORIAL_BIT(HETZEL_BIT);
	}

    return "";
} /* quest_answer */


/*
 * Function name:       krolock_answer
 * Description  :       response to an add_ask
 */
public string
krolock_answer()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        command("say Krolock is finished! You have triumphed over"
          + " his evil and saved our land from destruction.");
        return "";
    }

    command("say Krolock is determined to destroy us all!");
    command("say He is the very incarnation of evil ...");
    command("say Talk to Farmer Brown! He will help you defeat him!");
    return "";
} /* krolock_answer */


/*
 * Function name:       heart_answer
 * Description  :       response to an add_ask
 */
public string
heart_answer()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        command("say Seeing his heart destroyed was one of the happiest"
          + " days of my life. Thank you again, adventurer!");

        return "";
    }

    command("say If you have the heart of the Baron, <give> it to me that"
      + " I might destroy it forever!");

    return "";
} /* heart_answer */


/*
 * Function name:       mayor_answer
 * Description  :       response to an add_ask
 */
public string
mayor_answer()
{
    command("say I have been Mayor of Greenhollow for many years now."
      + " It is an honor to serve as I do, and I am very thankful for"
      + " the faith the people here have placed in me.");
    return "";
} /* mayor_answer */


/*
 * Function name:       farmer_answer
 * Description  :       response to an add_ask
 */
public string
farmer_answer()
{
    command("say Farmer Brown lives just north of town near his"
      + " fields. Talk to his wife if you cannot find him.");
    return "";
} /* farmer_answer */

/*
 * Function name:       pond_answer
 * Description  :       response to an add_ask
 */
public string
pond_answer()
{
    command("say As a child I used to fish in the pond north"
      + " of Farmer Brown's fields. We'd catch frogs and scare"
	  + " the girls with them. One friend said he found a hidden"
	  + " cave there, but I never saw it.\n");
    return "";
} /* pond_answer */

/*
 * Function name:       cave_answer
 * Description  :       response to an add_ask
 */
public string
cave_answer()
{
    command("say I don't think it exists, since I never saw it."
      + " If there is a cave, I don't know how to get to it.\n");
    return "";
} /* cave_answer */

/*
 * Function name:       forest_answer
 * Description  :       response to an add_ask
 */
public string
forest_answer()
{
    command("say The forest island is a great place for herbs,"
      + " but I would stay on the ground.  There are enormous"
	  + " spiders in those trees, several reckless advernturers"
	  + " never returned from those tree tops.  Some people"
	  + " hunt the spiders for a living, I think thats insane.");
    return "";
} /* forest_answer */

/*
 * Function name:       spider_answer
 * Description  :       response to an add_ask
 */
public string
spider_answer()
{
    command("say A hunter dragged a dead one into town, it"
      + " was gruesome. It had a dull black body, with hairy"
	  + " legs. Its fangs were almost as long as my arm.");
	command("shudder");
    return "";
} /* spider_answer */

/*
 * Function name:       mine_answer
 * Description  :       response to an add_ask
 */
public string
mine_answer()
{
    command("say Long ago this area was bustling with silver"
      + " miners, but alas, the vein ended. The shafts were"
	  + " abandoned to the kobolds.");
    return "";
} /* mine_answer */

/*
 * Function name:       kobold_answer
 * Description  :       response to an add_ask
 */
public string
kobold_answer()
{
    command("say Kobold is a nice way of saying rat-hobbit."
      + " They usually travel in packs. If you only see one,"
	  + " check behind you!");
    return "";
} /* kobold_answer */


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


/*
 * Function name:        react_items
 * Description  :        have the npc respond to a specific object
 * Arguments    :        object obj - the object that was shown
 *                       object to  - the player who showed it
 */
public void
react_items(object obj, object to)
{
    object  reward;

    set_this_player(to);

    if (obj->id("_krolock_heart"))
    {
        if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
        {
            command("say What strange trick is this? Krolock is already"
              + " dead! Adventurer, you must be having a bit of fun"
              + " at my expense. Please, do not do that ... Krolock is"
              + " ... was ... no joking matter.");
            command("emote snaps his fingers, and the heart disappears"
              + " in a flash!");
            obj->remove_object();
            return;
        }

        command("gasp");
        command("emote shouts: The heart of Baron von Krolock!!");
        command("emote quickly takes the heart and drops it on the floor.");
        command("emote speaks quickly a powerful spell.");
        command("emote waves his hands, and there is a powerful flash of"
          + " pure magic!");
        command("emote steps back, as the heart explodes in a fiery"
          + " blast!");
        command("emote shouts: THE CURSE IS LIFTED AT LONG LAST!");
        write("Far off in the distance, you hear a distant rumbling."
          + " All is still for a moment, and then sunlight streams"
          + " through the window.\n");
        command("emote says: We owe you so much, but take this.");
        reward = MONEY_MAKE_PC(1);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));
        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        give_reward(this_player(), TUTORIAL_KROLOCK_GROUP,
            TUTORIAL_KROLOCK_BIT, TUTORIAL_KROLOCK_EXP,
            "Krolock (good)");  

        SET_TUTORIAL_BIT(SAVIOR_BIT);
        /* Important Note! Normally, one must _NEVER_ use set_alignment() in
         * this way. To have a quest modify alignment, adjust_alignment() is
         * the appropriate function. However, in that this is the defining
         * quest at the beginning of the character's life, we allow this to
         * be a singular exception.
         */
        this_player()->set_alignment(100); /* "agreeable" alignment */
        this_player()->catch_tell("Your good deeds have shifted your"
          + " alignment!\n");
        obj->remove_object();
        return;
    }

    if (obj->id("_tutorial_heart"))
    {
        command("emote looks at the heart with great excitement.");
        write("As he studies the heart, his expression slowly changes.\n");
        command("emote gasps in horror!");
        command("emote yells: Where did you get this! It looks like the"
          + " heart of a child!");
        return;
    }

    command("emote shrugs.");
} /* react_items */


/*
 * function name: show_hook
 * description  : this hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    set_alarm(1.0, 0.0, &react_items(ob, this_player()));
} /* show_hook */
