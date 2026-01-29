/* File         : /d/Khalakhor/std/npc/human.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 1, 1999         
 * Purpose      : Khalakhor standard human npc.   
 * Related Files: /std/monster.c
 *                /d/Khalakhor/std/monster.c
 * Comments     :
 * Modifications: Improved and updated - Teth, Jan 27 2002
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <math.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

inherit STDMONSTER;

public void
reset_khalakhor_human()
{
}

public nomask void
reset_khalakhor_monster()
{
    reset_khalakhor_human();
}


/* Function name:  create_khalakhor_human
 * Description:    The constructor function
 *                 used to create the human
 */
public void create_khalakhor_human()
{
}

/* Function name:  create_khalakhor_monster (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_human to
 *                 create your human.
 */
public nomask void
create_khalakhor_monster()
{
    set_name("_Khalakhor_human");
    add_name("human");
    set_race_name("human");

    add_prop(LIVE_I_QUICKNESS, 10);

    add_prop(OBJ_I_RES_AIR, 5);
    add_prop(OBJ_I_RES_COLD, 5);
    add_prop(OBJ_I_RES_EARTH, 5);    
    add_prop(OBJ_I_RES_WATER, 5);

    create_khalakhor_human();
    reset_khalakhor_monster();
}

/*
 * Function name: query_khalakhor_human
 * Description  : Check to see if this is a Khalakhor human.
 * Arguments    : n/a
 * Returns      : 1 - if a human
 */
public int
query_khalakhor_human()
{
    return 1;
}

public void
assist_me(object *myteam, object ob)
{
    myteam = filter(myteam, &operator(!=)(ob) @
        &->query_attack());
    myteam = filter(myteam, &->query_autoassist());
    if (myteam->query_enemy() != ob)
    {
//    if ((random(5) - 3) > 0)
//     {
     myteam->command("say Stand fast!");
//     }
    myteam->command("$assist " + OB_NAME(TO));
    }
}

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
            HIM_HER(player) + " on this very spot ";
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
    if (age > 8640000)           /* 100 days */
    {
        resp += "'Course I've heard of " + 
            HIM_HER(player) + ", who " +
            "hasn't? ";
        do_align = 1;
    }
    else if (age > 5184000)      /* 60 days */
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
         
    info = NAME_TO_RANDOM(player->query_real_name(), 87654321, 5);

    if (!info)
        resp += "I last heard " + HE_SHE(player) +
            " was somewhere in the far north. ";
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
            " could be now. ";
  /* The name_to_random doesn't like a 0 as a range, */
  /* so if align = 0, set it to 1. */
    align = (!align ? 1 : align);
  /* Now for a comment about alignment. */
    negative = (align >= 0 ? 0 : 1);
    align = NAME_TO_RANDOM(player->query_real_name(), 12345678,
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
		   "are still few and far between.");
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
    if (default_answer)
    {
        set_alarm(rnd() * 4.0, 0.0, &answer_question(default_answer, 1));
    }
    else
        my_communicate("Afraid I can't help you much there.");
}

