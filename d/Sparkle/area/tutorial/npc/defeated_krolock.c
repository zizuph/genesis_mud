/*
 *  /d/Sparkle/area/tutorial/npc/defeated_krolock.c
 *
 *  Baron von Krolock. This is his defeated form, in which he offers
 *  his version of the quest to players.
 *
 *  Location: /d/Sparkle/area/tutorial/castle/defeated_lair.c
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 *  Updated September 2016, by Tim Breen (Mirandus)
 *  Changed the alignment impact from -600 to -100.
 */
#pragma strict_types
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit NPC_DIR + "silverdell_npc";
inherit LIB_DIR + "quest_reward";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <money.h>              /* for MONEY_MAKE_PC            */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public string  describe();
public void    make_offer(object player);
public void    react_items(object obj, object to);
public void    show_hook(object ob);
public string  do_search(object pl, string arg);
public void    init_living();
public int     cut_vampire(string arg);


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Krolock");
    set_name("krolock");
    add_name( ({ "baron von krolock", "baron krolock", "baron",
                 "_defeated_krolock", "corpse", "body" }) );
    set_adj( ({ "stately", "pale-skinned", "almost-dead", "dead",
                "almost" }) );
    set_race_name("vampire");

    set_title("the Destroyer, Baron of the Night Realm");

    set_short("nearly-dead vampire");
    set_long(describe);

    default_config_npc(5);    /* Completely humbled */
    set_alignment(-800);      /* Oh, he's evil alright.            */

    set_skill(SS_WEP_SWORD, 30);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_DEFENCE,   30);
    set_skill(SS_PARRY,     25);

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_M_NO_ATTACK, "There seems to be no further point in"
      + " attacking him. You have him at your mercy as it is.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_job_response("Forget about that! You must <listen> to my"
      + " offer! Do not be hasty!");

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
 * Function name:        describe
 * Description  :        provide a state-dependant long description for
 *                       the npc
 * Returns      :        string - the description
 */
public string
describe()
{
    if (!CHECK_TUTORIAL_BIT(OFFER_BIT))
    {
        return "The body of Baron von Krolock lies unmoving on"
          + " the ground. Even in this state, there is a menace lying"
          + " beneath his bones.\n";
    }

    return "Baron von Krolock appears to not be quite as dead"
      + " as he seemed. Perhaps he is not actually killable through"
      + " combat. He looks at you with eager eyes, and will repeat his"
      + " offer to you if you choose to <listen> to him.\n";
} /* describe */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    if (!CHECK_TUTORIAL_BIT(OFFER_BIT))
    {
        command("emote remains still and does not respond.");
        return "";
    }

    command("glare plead "+this_player()->query_real_name());
    command("say Please, <listen> to my offer again!");
    return "";
} /* default_answer */


/*
 * Function name:        make_offer
 * Description  :        Krolock will make an offer to the player,
 *                       giving them the option to do the evil version
 *                       of the quest.
 * Arguments    :        object player - the player getting the offer
 */
public void
make_offer(object player)
{
    set_this_player(player);

    if (!CHECK_TUTORIAL_BIT(OFFER_BIT))
    {
        command("emote suddenly stirs back to life.");

        SET_TUTORIAL_BIT(OFFER_BIT);

        command("emote throws himself at your feet before the altar.");
        command("emote pleads: Wait! Do not be so hasty!");
    }

    command("emote intones: You must listen to me!");
    command("emote intones: I see in you great potential.");
    command("emote intones: Your soul is dark, just like mine ...");
    command("emote intones: I need someone like you to command my armies!");
    command("emote intones: Forget what the Mayor has told you.");
    command("emote intones: I have a better offer for you ... ");
    command("emote intones: My heart is old and withered.");
    command("emote intones: I require a young heart to regain my powers.");
    command("emote intones: Kill Farmer Brown's daughter.");
    command("emote intones: Cut out her heart, and bring it to me!");
    command("emote intones: Do so, and I shall reward you ...");
    command("emote shows you two platinum coins.");
    command("emote intones: You shall command my armies of darkness!"
      + " Together we shall rule the land! Go quickly!");
} /* make_offer */


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
    object  destination;

    set_this_player(to);

    if (obj->id("_tutorial_heart"))
    {
        if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
        {
            command("emote intones: One wasn't enough for you, eh?");
            command("cackle");
            command("emote takes the heart and eats it!");
            obj->remove_object();
            return;
        }

        command("cackle");
        command("emote shouts: The heart of Farmer Brown's daughter!");
        command("emote takes the heart and places it on the altar.");
        command("emote mumbles a demonic incantation.");
        command("emote waves his hands, and there is a powerful flash of"
          + " dark magic!");
        command("emote steps back, as the heart begins to throb.");
        command("emote shouts: THE POWER! THE ABSOLUTE POWER!");
        write("The ground begins to tremble. You hear the howling of"
          + " demons from all around you and the rush of many feet in"
          + " the halls above. You sense that great evil has been"
          + " unleashed into the lands of Silverdell.\n");
        set_short("all-powerful vampire lord");
        command("emote intones: You have done well, Commander!");
        command("emote intones: Welcome to the Legion of Night.");

        reward = MONEY_MAKE_PC(2);
        reward->move(this_object());
        command("give coins to " + OB_NAME(this_player()));
        if (environment(reward) == this_object())
        {
           command("drop coins");
        }

        give_reward(this_player(), TUTORIAL_KROLOCK_GROUP,
            TUTORIAL_KROLOCK_BIT, TUTORIAL_KROLOCK_EXP,
            "Krolock (disagreeable)");  

        SET_TUTORIAL_BIT(DESTROYER_BIT);
        /* Important Note! Normally, one must _NEVER_ use set_alignment() in
         * this way. To have a quest modify alignment, adjust_alignment() is
         * the appropriate function. However, in that this is the defining
         * quest at the beginning of the character's life, we allow this to
         * be a singular exception.
         */
        this_player()->set_alignment(-100); /* "disagreeable" alignment */
        this_player()->catch_tell("Your evil deeds have shifted your"
          + " alignment!\n");
        obj->remove_object();

        destination = clone_object(CASTLE_DIR + "destroyer_lair");
        to->add_prop(LAIR_PROP, destination);
        to->move_living("M",
            to->query_prop(LAIR_PROP)->get_this_object(), 1, 1);
        set_short("nearly-dead vampire");
        return;
    }

    if (obj->id("_krolock_heart"))
    {
        command("emote swipes the heart out of your hand!");
        command("emote places the heart carefully back on the altar.");
        obj->remove_object();
        return;
    }

    command("emote scowls.");
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


/*
 * Function name:        do_search
 * Description  :        allow the player to search the corpse
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (!strlen(arg) || (member_array(arg,
        ({ "corpse", "the corpse", "vampire corpse",
           "body", "vampire", "nearly-dead vampire",
           "nearly dead vampire", "dead vampire", "krolock",
           "baron", "the baron", "baron von krolock" }) ) == -1))
    {
        return "Your search reveals nothing special.\n";
    }

    if (!CHECK_TUTORIAL_BIT(OFFER_BIT))
    {
        return "Looking over the corpse, you notice that there is a"
          + " gaping hole in the chest where the heart should be."
          + " It seems the Baron does not keep his heart in his"
          + " body!\n";
    }

    return "The Baron does not allow you to search him!\n";
} /* do_search */


/*
 * Function name:        init_living
 * Description  :        add some actions to players in the presence of
 *                       the vampire
 */
public void
init_living()
{
    ::init_living();

    add_action(cut_vampire, "cut");
    add_action(cut_vampire, "rip");
    add_action(cut_vampire, "tear");
    add_action(cut_vampire, "get");
    add_action(cut_vampire, "take");
    add_action(cut_vampire, "remove");
} /* init */


/*
 * Function name:        cut_vampire
 * Description  :        allow players to try to get the heart from Krolock
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - we process something, 0 - fail
 */
public int
cut_vampire(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[a] [the] 'heart' 'from' [the] [nearly] [dead] [nearly-dead]"
      + " 'vampire' / 'krolock'"))
    {
        return 0; /* send it on */
    }

    write("As you approach the body of Baron von Krolock, you notice that"
      + " there is a large hole where his heart should be. Apparently he"
      + " keeps it elsewhere.\n");
    return 1;
} /* cut_vampire */


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
        return;
    }

    command("emote looks too weak to respond.");
} /* react_intro */


/*
 * Function name:        add_silverdell_asks
 * Description  :        These are the standard asks defined for the
 *                       people of Greenhollow. They can be redefined in
 *                       inheriting npcs for more specific responses
 */
public void
add_silverdell_asks()
{
    /* empty ... we don't want him responding to things in his state */
} /* add_silverdell_asks */
