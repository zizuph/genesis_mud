/*
 *  /d/Sparkle/area/orc_temple/npc/prisoner.c
 *
 *  These are the poor prisoners in the jail cells who have been
 *  driven insane by their torment at the hands of the orcs and the
 *  demon.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";

#include <cmdparse.h>
#include <const.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_temple_npc();
public int         query_gender();
public void        intro_responses(object tp);
public int         not_here_func();
public void        init_living();
public int         try_rescue(string arg);
public void        return_object(object obj, object to);
public void        react_key(object key);
public void        escape1();
public void        escape2();
public void        escape3();
public void        escape4();
public void        escape5();

/* Global Variables */
public int         Escaping = 0; /* is the prisoner currently escaping? */
public mixed       Gender = G_MALE;
public string     *Busy_Msgs = ({
        "say What?! You ... NO!!! Get away from me!!!",
        "say The ... the ... the pit knows all names!",
        "say If ... if ... when ... where ... all to die!",
        "say Not ... forward ... not ... under ...",
        "say STOP EATING MY EARS!",
        "say MY HEAD HATES YOUR WORDS!" });

/*
 * Function name:        create_temple_npc  
 * Description  :        The constructor for the monster
 */
public void
create_temple_npc()
{
    mapping race_type  = ([ "elf"   : "elven",
                            "dwarf"  : "dwarven",
                            "gnome" : "gnomish",
                            "human" : "human" ]);
    string  race =   one_of_list( ({ "elf", "dwarf", "gnome", "human" }) ),
            aspect = one_of_list( ({ "starved", "deranged", "mindless",
                                     "wild-eyed", "haggard" }) ),
            racial = race_type[race];

    set_name(race);
    set_race_name(race);
    add_name( ({ "prisoner" }) );
    add_adj( ({ aspect, racial }) );

    set_short(aspect + " " + racial + " " + "prisoner");
    set_long(capitalize(aspect) + " and looking hideously abused and"
      + " insane, this once-happy person has been reduced to a"
      + " wretched creature of woe.\n");

    if (random(2))
    {
        set_gender(G_FEMALE);
        Gender = G_FEMALE;
    }

    set_alignment(0); /* no alignment - a mindless creature */
    set_stats( ({ 4, 13, 9, 1, 1, 20 }) );
                  
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      20);
    set_skill(SS_UNARM_COMBAT, 30);

    set_act_time(4);
    add_act("emote sucks in a ragged breath.");
    add_act("scream");
    add_act("shout Y-y-you!! You m-m-must die!");
    add_act("shout Down to the demon with YOU this time!");
    add_act("shout Keys, give me the keys!");
    add_act("shout Don't look it in the eyes! Not the eyes!");
    add_act("whimper slight");
    add_act("cackle");
    add_act("shout All of you! You all are damned!");
    add_act("shout You will be eaten! I know!");

    add_cact("emote sucks in a ragged breath.");
    add_cact("scream");
    add_cact("shout Y-y-you!! You m-m-must die!");
    add_cact("shout Down to the demon with YOU this time!");
    add_cact("shout Keys, give me the keys!");
    add_cact("shout Don't look it in the eyes! Not the eyes!");
    add_cact("whimper slight");
    add_cact("cackle");
    add_cact("shout All of you! You all are damned!");
    add_cact("shout You will be eaten! I know!");

    set_default_answer(VBFC_ME("default_answer"));
    set_give_response("This is useless! The keys! Give me the keys!!");

    set_aggressive(1, 100); /* insane, fearless, attacks anyone */
} /* create_temple_npc   */


/*
 * Function name:   query_gender
 * Description:     Returns the gender code of the living.
 * Returns:         The code. (0 - male, 1 - female, 2 - netrum)
 */
public int
query_gender()
{
    return Gender;
}


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command(one_of_list(Busy_Msgs));

    return "";
} /* default_answer */


/*
 * Function name:        intro_responses
 * Description  :        provide responses to an introduction
 * Arguments    :        object tp - this_player()
 *
 * This should be redefined in inheriting npcs for flavor variation.
 */
public void
intro_responses(object tp)
{
    command(one_of_list(Busy_Msgs));
} /* intro_responses */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("emote weeps angrily.");
     return 0;
} /* not_here_func */


/*
 * Function name:        init living
 * Description  :        set up some actions for the players who
 *                       enter the room
 */
public void
init_living()
{
    ::init_living();

    add_action(try_rescue, "rescue");
    add_action(try_rescue, "free");
    add_action(try_rescue, "invite");
} /* init_living */


/*
 * Function name:        try_rescue
 * Description  :        allow players to try to rescue the prisoner
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success (though one cannot rescue him)
 *                       int 0 - failure
 */
public int
try_rescue(string arg)
{
    object *obj;
    string *responses = ({
                "GO WITH YOU?! NEVER! YOU ARE ONE OF THEM!!",
                "I SHALL NEVER GO WITH YOU TO THE PIT! YOU WILL DIE!!",
                "I CAN SEE THROUGH YOUR LIES! DEATH TO YOU AND ALL YOUR"
              + " KIND!!",
                "RESCUE?! I'LL KILL YOU LIKE YOU KILLED MY CHILDREN! GIVE"
              + " ME THE KEYS!!",
                "IT IS A TRICK! YOU WANT TO TAKE ME TO THE PIT LIKE ALL"
              + " THE OTHERS! DIE!!"
                        });

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(environment(this_object())),
        "[the] %i", obj) ||
        !sizeof(obj = NORMAL_ACCESS(obj, 0, 0)))
    {
        notify_fail("Did you want to try to " + query_verb() + " the"
          + " prisoner?\n");
        return 0;
    }

    if (obj[0] != this_object())
    {
        notify_fail("Huh? You cannot " + query_verb() + " that!\n");
        return 0;
    }

    write("You try to convince the " + short() + " that you will" 
      + " help " + query_objective() + " escape.\n");
    tell_room(environment(this_object()), QCTNAME(this_player())
      + " tries to convince the " + short() + " to follow "
      + this_player()->query_objective() + " to freedom.\n", this_player());

    if (Escaping)
    {
        command("shout I'm getting out of here, you can be sure of that!");
        return 1;
    }

    command("shout " + one_of_list(responses));

    return 1;
} /* try_rescue */


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
    if (Escaping)
    {
        command("say No time! No time!");
        return;
    }

    if (obj->id("coin"))
    {
        command("say I don't need money! Give me the keys!!");
        return;
    }

    if (obj->id("key"))
    {
        command("gasp");

        set_alarm(2.0, 0.0, &react_key(obj));
        return;
    }

    command("say " + Give_Response);
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name:        react_key
 * Description  :        The prisoner reacts to being given a key.
 * Arguments    :        object key - the key object
 */
public void
react_key(object key)
{
    command("peer swift key");

    if (!key->id(JAILERS_KEYS))
    {
        command("shout Useless! I need the jailer's key ring!");
        command("emote gnaws on the key with a deranged grimmace.");
        command("drop key");
        return;
    }

    command("cheer");
    command("say I must be swift!");

    Escaping = 1;
    set_aggressive(0, 0);

    set_alarm(1.0, 0.0, escape1);
} /* react_key */


/*
 * Function name:        escape1
 * Description  :        part of the escaping sequence
 */
public void
escape1()
{
    command("unlock door with key");

    set_alarm(1.0, 0.0, escape2);
} /* escape1 */


/*
 * Function name:        escape2
 * Description  :        part of the escaping sequence
 */
public void
escape2()
{
    command("open door");

    set_alarm(1.0, 0.0, escape3);
} /* escape2 */


/*
 * Function name:        escape3
 * Description  :        part of the escaping sequence
 */
public void
escape3()
{
    command(environment(this_object())->query_door_direction());

    set_alarm(2.0, 0.0, escape4);
} /* escape3 */


/*
 * Function name:        escape4
 * Description  :        part of the escaping sequence
 */
public void
escape4()
{
    command("cackle");
    command("shout FREE!! I'M FREE!!!");

    set_alarm(3.0, 0.0, escape5);
} /* escape4 */


/*
 * Function name:        escape5
 * Description  :        part of the escaping sequence
 */
public void
escape5()
{
    object  guard;
    object *guards = filter(
                       FILTER_LIVE(all_inventory(environment(this_object()))),
                       &->id(ORC_TEMPLE_NPC));

    if (sizeof(guards))
    {
        guard = guards[0];
        guard->command("shout Look! Prisoner escaping! KILL KILL!");
    }
    else
    {
        guard = clone_object(NPC_DIR + "goblin_warrior");
        tell_room(environment(this_object()), "A guard runs in, looking"
          + " for the source of the noise.\n");
        guard->arm_me();
        guard->move(environment(this_object()));
    }

    guard->command("shout Look! Prisoner escaping! KILL KILL!");
    heal_hp(-100000);
    guard->command("kill prisoner");
    do_die(guard);
} /* escape5 */