/*
 *  /d/Sparkle/area/city/npc/dog.c
 *
 *  This is Pookie, the Town Crier's Dog. He's definitely the brains
 *  behind the operation.
 *
 *  Created March 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"


/* Prototypes */
public void        create_monster();
public void        bark();
public void        map_msg(object who);
public void        give_map(object who);
public void        check_map(object who);
public string      default_answer();
public void        unseen_hook();

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_race_name("dog");
    set_name("pookie");
    add_name( ({ "pet", "hound", "animal", "pooch", CRIER_DOG }) );
    add_adj( ({ "fluffy", "brown" }) );

    set_short("fluffy brown dog");
    set_long("There is a strange intelligence in this dog's eyes, almost"
      + " as if she were fully in charge of the situation here. She seems"
      + " to be monitoring everything happening to and around the town"
      + " crier and his table.\n");

    set_gender(G_FEMALE);
    set_default_answer(VBFC_ME("default_answer"));

    set_alignment(0); /* no alignment */
    set_stats( ({ 40, 150, 60, 200, 200, 200 }) ); /* Quite a dog! */
                  
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_DEFENCE,      80);
    set_skill(SS_UNARM_COMBAT, 80);

    set_act_time(10);
    add_act("emote whines inquisitively.");
    add_act("emote sits on her hind legs, panting as she looks around.");
    add_act("emote hops up on the table and tidies up the clutter a bit.");
    add_act("emote gnaws quietly on a bone, peering alertly around.");

    set_no_show_composite(1); /* He isn't obviously in the room. */
    set_dont_answer_unseen(1);

    add_prop(OBJ_M_NO_ATTACK, "Just as you begin to make your move,"
      + " the fluffy brown dog bares her teeth and"
      + " produces an uncanny growl. Whether there are some odd magicks"
      + " at work with this beast you cannot be sure, but you find your"
      + " willpower faltering completely.\n");

    setuid();
    seteuid(getuid());
} /* create_monster */


/*
 * Function name:   query_gender
 * Description:     Returns the gender code of the living.
 * Returns:         The code. (0 - male, 1 - female, 2 - netrum)
 */
public int
query_gender()
{
    return G_FEMALE;
}


/*
 * Function name:     bark
 * Description:       Have the dog bark to wake up the Town Crier
 */
public void
bark()
{
    command("emote " + one_of_list( ({
        "barks loudly!",
        "quickly barks at the town crier!",
        "sits up and issues a loud bark!",
        "jumps up on the table and barks loudly!",
        "suddenly barks loudly!", }) ));

    return;
} /* bark */


/*
 * Function name:        give_map
 * Description  :        Pookie will give a magic map to any player
 *                       who does not have one.
 * Arguments    :        object who - the player to give it to
 */
public void
give_map(object who)
{
    set_alarm(1.0, 0.0, &map_msg(who));
}


/*
 * Function name:        map_msg
 * Description  :        print a message letting people know that
 *                       the player has been given a map
 * Arguments    :        object who - the player given the map
 */
public void
map_msg(object who)
{
    object   who_env = environment(who);
    object   dog_env = environment(this_object());

    clone_object("/d/Sparkle/std/obj/magic_map")->move(who);
    TELL_G("\n\n\n     A Map was given to "
          + capitalize(who->query_real_name()) + "!\n\n");

    who->catch_msg("A fluffy brown dog runs up to you with something"
      + " in her mouth. You feel a magic map shoved into your hand. The"
      + " dog barks and then runs back to her owner in front of the"
      + " church.\n");

    if (who_env != dog_env)
    {
        tell_room(who_env, "A fluffy brown dog runs into the area and"
          + " shoves something from her mouth into " + QTNAME(who)
          + "'s hand. The dog barks and then runs back down the"
          + " street toward the church.\n", who);
        tell_room(dog_env, "The fluffy brown dog grabs a magic map"
          + " from the table and runs off down the street after "
          + QTNAME(who) + ". In a moment, she returns and lies down"
          + " beside her owner.\n");
        return;
    }

    tell_room(who_env, "The fluffy brown dog grabs a magic map from the"
      + " table, and runs over to " + QTNAME(who) + ", dropping it from"
      + " her mouth into the latter's hands. With a happy bark, the"
      + " dog returns to lie beside the table.\n", who);

    return;
} /* map_msg */


/*
 * Function name:        init_living
 * Description  :        Have the dog give players who don't already
 *                       have one a magic map.
 */
public void
init_living()
{
    ::init_living();

    check_map(this_player());
} /* init_living */


/*
 * Function name:        check_map
 * Description  :        See if a player needs a magic map
 * Arguments    :        Object who - the player
 */
public void
check_map(object who)
{
    if (!present("_sparkle_magic_map", who))
    {
        if (!interactive(who))
        {
            return;
        }

        set_alarm(0.0, 0.0, &give_map(who));
    }
} /* check_map */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("emote " + one_of_list( ({
        "seems to consider the question, and then barks loudly.",
        "barks loudly a few times.",
        "offers a few short woofs in response.",
        "points at the poster with her nose and barks!",
        "peers incredulously around at having been asked a question.",
            }) ));
    return "";
} /* default_answer */


/*
 * Function name: unseen_hook
 * Description:   This function gets called if this mobile couldn't see
 *		  who asked the question and is not supposed to answer
 *		  in that case.
 */
public void
unseen_hook()
{
    command("emote cocks its head, and looks around in confusion.");
    command("emote can't seem to see whoever made that noise.");
} /* unseen_hook */
