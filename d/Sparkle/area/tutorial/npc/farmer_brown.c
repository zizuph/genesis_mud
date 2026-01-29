/*
 *  /d/Sparkle/area/tutorial/npc/farmer_brown.c
 *
 *  This npc is integral to the quests of the area. He hangs out
 *  in the barn north of Greenhollow.
 *
 *  Location: /d/Sparkle/area/tutorial/farm/barn.c
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 *  Updated by Gronkas August 1, 2016 to fix typo about wife's name
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
public void    garlic_answer();
public void    hook_answer();
public void    help_answer();
public void    field_answer();
public void    farmer_answer();
public void    daughter_answer();
public void    intestine_answer();
public void    claw_answer();
public void    return_object(object obj, object to);
public void    react_items(object obj, object to);
public void    show_hook(object ob);


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Benjamin");
    set_name("benjamin");
    add_name( ({ "benjamin brown", "husband", "man", "ben",
                 "_tutorial_farmer_brown", "farmer", "brown" }) );
    set_adj( ({ "stern", "elderly", "old" }) );
    set_race_name("human");

    set_title("Brown, Farmer of Silverdell");
    set_short("stern elderly man");
    set_long("This is Farmer Brown. He is busy tending to things here"
      + " in the barn, and looks as if he has quite a bit on his mind."
      + " You might <ask farmer help> to see if he needs any"
      + " help from you.\n");

    /* this seems to be the only way to allow for "exa farmer brown" */
    add_cmd_item( ({ "farmer brown" }), ({ "exa" }), long);

    default_config_npc(150);  /* a tough old goat */

    set_act_time(2);
    add_act("emote pitches a scoop of hay into the loft.");
    add_act("emote shakes his head and mutters something.");
    add_act("emote calls out: Annie, you be careful up there!");
    add_act("emote says: Would you be able to help me?");
    add_act("emote sighs deeply.");

    set_job_response("My job? I raise crops mostly, but I also do"
      + " what I can to fight against Baron von Krolock.");

    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0); /* You can give him stuff. */

    add_silverdell_asks();
    add_trainer_asks();

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
    add_ask( ({ "garlic", "vampire", "weakness" }),
        VBFC_ME("garlic_answer"));
    add_ask( ({ "hook", "grappling", "climb", "grappling hook",
                "grapling", "grapling hook" }),
        VBFC_ME("hook_answer"));
    add_ask( ({ "help", "task", "assistance", "quest", "tasks",
                "quests", "baron", "krolock", "baron von krolock" }),
        VBFC_ME("help_answer"));
    add_ask( ({ "farm", "fields", "farming", "house", "barn", "farmer" }),
        VBFC_ME("field_answer"));
    add_ask( ({ "matilda", "wife" }),
        VBFC_ME("farmer_answer"));
    add_ask( ({ "daughter", "hayloft", "annie" }),
        VBFC_ME("daughter_answer"));
    add_ask( ({ "intestine", "intestines" }),
        VBFC_ME("intestine_answer"));
    add_ask( ({ "claw", "claws", "animal claw", "animal claws" }),
        VBFC_ME("claw_answer"));

} /* add_trainer_asks */


/*
 * Function name:       garlic_answer
 * Description  :       response to an add_ask
 */
public string
garlic_answer()
{
    command("say Baron von Krolock is an ancient vampire.");
    command("say Therefore, his natural weakness is the garlic plant.");
    command("say Did you notice how those bunnies ate only the garlic?");
    command("say They were sent from him, to destroy the only thing he"
      + " fears!");
    command("say If you are going to defeat him, you'll need to bring"
      + " garlic along.");

    if (CHECK_TUTORIAL_BIT(GARLIC_BIT))
    {
        command("say You can find it growing in the northwest row of the"
          + " field.");
    }
    else
    {
        command("say First, I need a few new starts for the garlic.");
        command("say They grow wild in the Sterling Woods to the east.");
        command("say I went there to get some myself, but lost them.");
        command("say They were washed away when I had to swim across the"
          + " river. I should have brought a backpack!");
        command("say Bring me a clove from the forest!");
    }
    return "";
} /* garlic_answer */


/*
 * Function name:       hook_answer
 * Description  :       response to an add_ask
 */
public string
hook_answer()
{
    command("say Krolock's castle is built on top of steep cliffs.");
    command("say You can find it by traveling west.");
    command("say Train your climbing skill, and you'll be able to scale"
      + " the lower hills.");
    command("say However, you'll need some tools for the steep cliffs.");
    command("say Here is what you'll need to do.");
    command("say There are animals you can kill in the Sterling Woods"
      + " to the east.");
    command("say Once you've killed one, cut out its intestines, and"
      + " bring them to me.");
    command("say Read this tutorial sign to discover how.");
    command("emote points at the tutorial sign.");
    return "";
} /* hook_answer */


/*
 * Function name:       help_answer
 * Description  :       response to an add_ask
 */
public string
help_answer()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        command("say You've done it! You've destroyed the Baron!");
        command("emote hugs you.");
        command("say All of Silverdell owes you a debt of gratitude.");
        command("say You will forever be remembered as the savior of"
          + " this land.");

        return "";
    }

    if (present("_tutorial_grappling_hook", deep_inventory(this_player())))
    {
        command("say Looks like you are ready to go.");
        command("say That grappling hook looks excellent.");
        command("say You'll need to <wield> it in order to climb the steep"
          + " cliffs.");
        command("say Find Baron von Krolock in his castle!");
        command("say Find him and destroy him!");
        command("say And don't forget to bring garlic!");
        return "";
    }

    command("say Baron von Krolock must be destroyed!");
    command("say Were I a younger man, I'd do it myself.");
    command("say But, perhaps you are up to the task.");
    command("say You'll need two things: garlic and a grappling hook.");
    command("say You can <ask> me about either thing, and I'll explain.");

    return "";
} /* help_answer */


/*
 * Function name:       field_answer
 * Description  :       response to an add_ask
 */
public string
field_answer()
{
    command("say Our fields are doing much better, thanks to you.");
    command("say The bunnies are still a nuisance, I suppose.");
    command("say But I've had time to get the garlic"
      + " growing again!");
    return "";
} /* field_answer */



/*
 * Function name:       farmer_answer
 * Description  :       response to an add_ask
 */
public string
farmer_answer()
{
    command("say Matilda is a wonderful woman.");
    command("say I couldn't keep the place running without her.");
    command("say I suppose she's in the house.");
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
    command("say Oh, she's up in the loft, I suppose.");
    command("emote shouts: Annie, you still up there?");
    return "";
} /* daughter_answer */


/*
 * Function name:       intestine_answer
 * Description  :       response to an add_ask
 */
public string
intestine_answer()
{
    command("say Intestines?");
    command("say Most of the forest animals should work for those.");
    command("say Find one, kill it, search it, cut out the intestines.");
    command("say Then, bring one to me and I'll teach you what to do.");
    return "";
} /* intestine_answer */


/*
 * Function name:       claw_answer
 * Description  :       response to an add_ask
 */
public string
claw_answer()
{
    command("say Animal claws?");
    command("say You'll need to go kill a lion for those.");
    command("say Once you do, search it and cut out any claw you find.");
    command("say Then, bring one to me and I'll teach you what to do.");
    return "";
} /* claw_answer */


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
    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
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
    object    rope,
              reward;
    int       num;

    set_this_player(to);

    if (obj->id("_tutorial_clove"))
    {
        if (CHECK_TUTORIAL_BIT(GARLIC_BIT))
        {
            command("say Oh, no thanks. The one you already brought me"
              + " did the trick.");
            return;
        }

        command("say Well done! This is exactly what we needed!");
        command("emote shouts: Wilbur, get in here!");
        write("A tall farmhand wanders in.\n");
        command("say Wilbur, take this clove, and go plant it in the field"
          + " using that instant grow formula that Bibbiss made for us.");
        write("The tall farmhand takes the clove and heads out of the"
          + " barn.\n");
        command("say Excellent. Now you can get some garlic from the field.");
        command("emote says: Here, take this token of our thanks for all"
          + " of your help with our farm.");

        reward = MONEY_MAKE_GC(5);
        reward->move(this_object());
        command("give coins to " + OB_NAME(to));
        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        give_reward(this_player(), TUTORIAL_GARLIC_GROUP, TUTORIAL_GARLIC_BIT,
            TUTORIAL_GARLIC_EXP, "Tutorial Garlic");  

        SET_TUTORIAL_BIT(GARLIC_BIT);
        obj->remove_object();
        return;
    }

    if (obj->id("_tutorial_intestine"))
    {
        if (!CHECK_TUTORIAL_BIT(INSTRUCT_BIT))
        {
            command("say Oh, excellent.");
            command("say Here, I'll show you how to make rope from this.");
            command("emote lays the intestine along the ground.");
            command("emote skillfully works with the intestine.");
            command("emote eventually makes the intestine into a rope.");
            command("emote stands up and hands you the rope.");
            command("say There you go. You'll need to make it longer,"
              + " though.");
            command("say I figure you'll need at least 100 feet of rope.");
            command("say Get more intestines, and <make rope> with them"
              + " yourself.");
            command("say Once you have a long enough rope, come back and"
              + " <show> it to me.");
            command("say Then, I'll tell you what to do next.");

            obj->restore_heap();
            if ((num = obj->num_heap()) <= 1)
            {
                obj->remove_object();
            }
            else
            {
                obj->set_heap_size(num - 1);
            }

            rope = clone_object(OBJ_DIR + "rope")->move(to);
            SET_TUTORIAL_BIT(INSTRUCT_BIT);
            return;
        }

        command("say I already taught you how to do it yourself.");
        command("say Just <make rope> once you have an intestine.");
        command("give " + OB_NAME(obj) + " to " + OB_NAME(to));

        if (environment(obj) == this_object())
        {
            command("drop " + OB_NAME(obj));
        }

        return;
    }

    if (obj->id("_tutorial_garlic"))
    {
        command("say Ah, you've got a garlic bulb!");
        command("say That is what you'll need to defeat the Baron.");
        command("say All you need now is to find a way to get to him.");
        command("say Take that with you ... ");
        command("say And try not to accidentally eat it!");
        return;
    }

    if (obj->id("_tutorial_hook"))
    {
        command("say Oh, excellent!");
        command("say You'll need to <wield> it to climb up the steep"
          + " cliffs.");
        command("say Find Baron von Krolock in his castle!");
        command("say Find him and destroy him!");
        command("say And don't forget to bring garlic!");
        return;
    }

    if (obj->id("_tutorial_claw"))
    {
        command("say That's a nice claw.");
        command("say It would be perfect for a grappling hook.");
        command("say If you had a good rope, you could <attach> it.");
        return;
    }

    if (!obj->id("_tutorial_rope"))
    {
        command("shrug");
        return;
    }

    if (obj->query_length() < 100)
    {
        command("say Hmmm ... you'll need to lengthen that rope a bit.");
        command("say Keep making more lengths out of intestines.");
        command("say Come show it to me when its about one hundred feet"
          + " long.");
        return;
    }

    command("say Looks like you've managed to make a lot of rope there!");
    command("say Yes, that looks to be about one hundred feet long.");
    command("say Good. Here is what to do next.");
    command("say In the hills to the west you can find mountain lions.");
    command("say You'll need to kill a few of those.");
    command("say Cut out their claws just like you did with the"
      + " intestines.");
    command("say You can then <attach> them to the rope.");
    command("say I figure three will do the trick.");
    command("say At that point, you'll have a legitimate grappling hook!");
    return;
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


