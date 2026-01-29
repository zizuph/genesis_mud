/*
 * local_npc.c
 *
 * This file is a new, more intelligent npc base. Npc's which inherit
 * this file will be able to respond to 'general-knowledge' questions
 * such as asking about different places or players. It also has a
 * self-contained introduction and memory for remembering players
 * that it's met (not beyond armageddon though).
 *
 * Khail - July 5/97
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include "gks.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <math.h>

inherit "/std/monster";

mapping Gremembered;
int *global_coords,
    *local_coords;
string info_module;

/*
 * Function name: my_communicate
 * Description  : A stripped down version of communicate() to cut down
 *                on cpu cost, since a lot of the checks made in
 *                communicate() are redundant for most npc's.
 * Arguments    : str - The strign we're about to say.
 * Returns      : 1 - success
 *                0 - failure
 */
public int
my_communicate(string str)
{
    string temp;

    if (temp = TO->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(temp) ? temp : "You are gagged and cannot " +
            "speak.\n");
    }

    tell_room(environment(), QCTNAME(TO) + " " + VBFC_ME("race_sound") +
        ": " + str + "\n");
}

/*
 * Remembered routines.
 */
public void
add_introduced(string str)
{
    object player;

    if (!str || !strlen(str) || !find_player(str))
        return;

    player = present(str, environment());
    if (!TO->hook_return_intro(str))
        command("introduce myself to " + OB_NAME(player));

    if (!Gremembered)
        Gremembered = ([]);

    Gremembered[str] = time();

}

public varargs mixed
query_remembered(string str)    
{
    if (!str)
        return Gremembered;

    str = lower_case(str);
    if (!Gremembered || !Gremembered[str])
        return 0;

    return Gremembered[str];
}

/*
 * Function name: init_living (MASK)
 * Description  : Called when we meet another object. We
 *                mask it here so that the npcs can remember
 *                the last time they saw a player they have
 *                been introduced to.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init_living()
{
    ::init_living();

  /* Ignore non-interactives. */
    if (!interactive(TP))
        return;

  /* Can't recognize someone we can't see. */
    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
        return;

  /* If a player we know just arrived in the room, then */
  /* update his 'timestamp' in the remembered map. */
    if (Gremembered && Gremembered[TP->query_real_name()])
        Gremembered[TP->query_real_name()] = time();
}

/*
 * Special routines for locations of landmarks using the
 * master information modules.
 */

/*
 * Function name: enter_env (MASK)
 * Description  : Called whenever we enter a new environment.
 * Arguments    : to - Object pointer to our new environment.
 *                from - Object pointer to our old environment.
 * Returns      : n/a
 */
public void
enter_env(object to, object from)
{
    int *temp;
    ::enter_env(to, from);

    if (!to)
        return;

    if (!(local_coords = to->query_local_coords()))
        local_coords = ({});

    if (!(temp = to->query_global_coords()))
        global_coords = ({});
    else if (!sizeof(global_coords) && sizeof(temp))
        global_coords = temp;
    else if (global_coords[0] != temp[0] &&
        global_coords[1] != temp[1])
        global_coords = temp;
    else
        return;

    if (sizeof(global_coords))
        info_module = INFO_MASTER->resolve_my_location(global_coords);
    else
        info_module = "";
}

public int *
query_global_coords()
{
    return global_coords;
}

public int *
query_local_coords()
{
    return local_coords;
}

public string
query_info_module()
{
    return info_module;
}

/*
 * Routines for answering 'asks'
 */

/*
 * Function name: resolve_player_location
 * Description  : Called from resolve_location once we've determined
 *                that a player is looking for another player.
 * Arguments    : str - Name of the player being looked for.
 * Returns      : n/a
 */
public void
resolve_player_location(string str)
{
    object player;
    int align,
        gender,
        age,
        t,
        do_align,
        info,
        negative;
    string resp;

    if (!(player = find_player(str)))
        player = SECURITY->finger_player(str);

    align = player->query_alignment();
    gender = player->query_gender();
    age = player->query_age() * 2;
    resp = capitalize(str) + "? ";

  /* What to do if a player asks about himself. */
    if (player == TP &&
        query_remembered(player->query_real_name()) &&
        player->check_seen(TO))
    {
        my_communicate("Why, you're right here, of course!");
        return;
    }

  /* What to do if the player's a wizard. */
    if (player->query_wiz_level())
    {
        command("panic");
        my_communicate("Don't say that name out loud! " +
            capitalize(HE_SHE(player)) +
            " might hear you! I can tell you nothing!");
        if (player->query_finger_player())
            player->remove_object();
        return;
    }

  /* What to do if the player is in the room. */
    if (present(player, environment(TO)) &&
        player->check_seen(TO) &&
        query_remembered(str))
    {
        my_communicate("Why, " + HE_SHE(player) +
            "'s standing right beside you, as a matter " +
            "of fact!");
        return;
    }

  /* Some npc's will have a memory, so we'll see if */
  /* the npc has the player remembered. */
    if (query_remembered(str))
    {
        resp += "Actually, I was talking to " +
            HE_SHE(player) + " on this very spot ";
        t = time() - Gremembered[lower_case(str)];
        if (t < 60)      /* 1 min. */
            resp += "just a moment ago. ";
        else if (t < 300)     /* 5 mins. */
            resp += "just a few minutes ago. ";
        else if (t < 1200)    /* 20 mins. */
            resp += "a short while ago. ";
        else if (t < 3600)    /* 1 hr */
            resp += "not long ago. ";
        else if (t < 21600)   /* 6 hrs */
            resp += "a few hours ago. ";
        else if (t < 43200)   /* 12 hrs */
            resp += "several hours ago. ";
        else
            resp += "many hours ago. ";

        resp += "I've no idea where " +
            HE_SHE(player) + " went though. ";
        my_communicate(resp);
        if (player->query_finger_player())
            player->remove_object();
        return;
    }
     
  /* Get a general opinion based on size. */
  /* So we don't give away exact info on a player's */
  /* exp, we take a random value of it, seeded off */
  /* the name of the npc, so the random will always */
  /* be the same value for the same range. */
    age = NAME_TO_RANDOM(TO->query_real_name(), 12345678, age);
    if (age > 4320000)           /* 50 days */
    {
        resp += "'Course I've heard of " + 
            HIM_HER(player) + ", who " +
            "hasn't? ";
        do_align = 1;
    }
    else if (age > 3456000)      /* 40 days */
    {
        resp += "I believe I know who that is, " +
            "if the stories are true. ";
        do_align = 1;
    }
    else if (age > 2592000)      /* 30 days */
    {
        resp += "Hmm, " + capitalize(str) + "... " +
            "I think I know who you're talking " +
            "about. ";
        do_align = 1;
    }
    else if (age > 1728000)       /* 20 days. */
        resp += capitalize(str) + ", the name rings " +
            "a bell but I can't put a face to it. ";
    else
        resp += "Sorry, I haven't got the vaguest " +
            "idea who that might be. ";
  /* End it here if we aren't going to pad with an align */
  /* string. */ 
    if (!do_align)
    {
        my_communicate(resp);
        if (player->query_finger_player())
            player->remove_object();
        return;
    }
         
    info = NAME_TO_RANDOM(TO->query_real_name(), 87654321, 5);

    if (!info)
        resp += "I last heard " + HE_SHE(player) +
            "was somewhere in the far north. ";
    else if (info == 1)
        resp += "I believe rumour has it " + HE_SHE(player) +
            " is somewhere in " + ({"Ansalon", "Avenir" ,"Calia",
            "Cirath", "Gondor", "The Shire", "Terel", "Krynn",
            "Emerald"})[NAME_TO_RANDOM(TO->query_real_name(),
            12345678, 9)] + ", though I can't say for sure. ";
    else if (info == 2)
        resp += "Rumour has it that " + HE_SHE(player) +
            "'s been exploring the islands for the past " +
            "few months. ";
    else if (info == 3)
        resp += "I had a trader in here the other day " +
            "who claimed to have seen " + HIM_HER(player) +
            " in a village down the coast, but he couldn't " +
            "remember the name of the place. ";
    else if (info == 4)
        resp += "I think " + HE_SHE(player) + " passed " +
            "through here earlier today, actually, " +
            "but I've got no idea where " + HE_SHE(player) +
            "could be now. ";
   /* As finger_player.c doesn't define alignments, we */
  /* will generate a completely random alignment. */
    if (player->query_finger_player())
        align = random(2401) - 1200;
  /* The name_to_random doesn't like a 0 as a range, */
  /* so if align = 0, set it to 1. */
    align = (!align ? 1 : align);
  /* Now for a comment about alignment. */
    negative = (align >= 0 ? 0 : 1);
    align = NAME_TO_RANDOM(TO->query_real_name(), 12345678,
            align);
    align = (negative ? -align : align);

    if (align > 600)
        resp += "Hopefully " + HE_SHE(player) +
            "'ll return soon, " + HE_SHE(player) +
            "'s missed by many.";
    else if (align < -600)
        resp += "The miserable " + 
            (gender ? "bitch" : "bastard") + " can bloody " +
            "well stay there too, for all anyone here " +
            "cares.";
    my_communicate(resp);
    return;
}

/*
 * Function name: resolve_location
 * Description  : Attempts to respond to 'where is' type
 *                questions, for players, npcs, and locations
 *                in the game.
 * Arguments    : str - String argument to the 'where is <str>'
 *                      syntax.
 * Returns      : n/a
 */
public varargs void
resolve_location(string str = "")
{
    string resp;

  /* Fail if the player didn't specify who or what */
  /* they were looking for. */
    if (!strlen(str))
    {
        my_communicate("Where is? Where is what?");
        return;
    }

  /* If the player is looking for another player. */
    if (SECURITY->exist_player(str))
    {
        resolve_player_location(str);
        return;
    }

    if (strlen(resp = INFO_MASTER->get_response(str, TO,
        global_coords, local_coords, info_module)))
    {
        my_communicate(resp);
        return;
    }

    my_communicate("I don't understand the question.");
    return;
}

public void
new_answer_question(string question)
{
    if (parse_command(question, TP, "[the] 'human' / 'humans'"))
    {
        my_communicate("Humans? Not much to tell, except they're " +
            "the dominant race in these parts.");
    }
    else if (parse_command(question, TP, "[the] 'dwarf' / 'dwarves'"))
    {
        my_communicate("Dwarves? Well, we don't see many of them " +
            "this far south, but in the Highlands they're a " +
            "force to be reckoned with.");
    }
    else if (parse_command(question, TP, "[the] 'elf' / 'elves'"))
    {
        my_communicate("Elves? Don't see many of them, something "+
           "wiped most of the elves out a long time ago, and they "+
           "are still few and far between. However I hear stories "+
           "of this Sanctuary tower, which has risen on the isle of "+
           "Galaith. Some big mystery.");
    }
    else if (parse_command(question, TP, "[the] 'goblin' / 'goblins'"))
    {
        my_communicate("Goblins? Filthy creatures out of the " +
            "Great Waste in the north. Rumours have it a few " +
            "have actually been seen prowling around the " +
            "piers here in town. Can you believe it?");
    }
    else if (parse_command(question, TP, "[the] 'hobbit' / 'hobbits'"))
    {
        my_communicate("Not much to say about hobbits, they " +
            "sure as blazes aren't from around here though.");
    }
    else if (parse_command(question, TP, "[the] 'gnome' / 'gnomes'"))
    {
        command("shiver");
        my_communicate("Blasted gnomes always tinkering with " +
            "things. They aren't from Khalakhor, but as the story " +
            "goes, they arrived here in a boat about a hundred " +
            "years back. The bloody thing exploded not ten " +
            "minutes after they came ashore and it flattened " +
            "every home within a mile!");
    }
    else if (default_answer)
    {
        command("say " + default_answer);
    }
    else
        my_communicate("Afraid I can't help you much there.");
}

public nomask void
catch_question(string question)
{
    int i;

  /* If the npc isn't supposed to respond to invis, fail if */
  /* the npc can't see the player. */
    if (query_dont_answer_unseen() && (!TP->check_seen(TO) ||
        !CAN_SEE_IN_ROOM(TO)))
    {
        set_alarm(rnd() * 3.0 + 1.0, 0.0, unseen_hook);
        return;
    }

  /* Extract possible punctuation from the question asked. */
    i = strlen(question);
    if (question[i - 1] == "."[0] || question[i - 1] == "?"[0])
        question = extract(question, 0, i - 2);

  /* Lowercase whatever the current string is. */
    question = lower_case(question);

  /* Extract possible 'about' for the question. */
    parse_command(question, TP, "[about] %s", question);

  /* Next, we duplicate the remaining code from the normal */
  /* catch_question so that we can have normal add_ask */
  /* functionality as well as global. Only rather than fail */
  /* here if there is no specified response to the question, */
  /* then we check globals. The globals will produce a default */
  /* fail if they too cannot match the question to an anser. */
    if (ask_arr)
    {
        for (i = 0; i < sizeof(ask_arr); i++)
        {
            if (member_array(question, ask_arr[i][0]) >= 0)
            {
                set_alarm(rnd() * 4.0, 0.0, 
                    &answer_question(ask_arr[i][1], ask_arr[i][2]));
                return;
            }
        }
    }

  /* Check if they're wondering 'where is' something. */
    if (parse_command(question, TP, "'where' 'is' / 'are' %s", question))
        set_alarm(rnd() * 4.0, 0.0, &resolve_location(question));
    else
        set_alarm(rnd() * 4.0, 0.0, &new_answer_question(question));
}
