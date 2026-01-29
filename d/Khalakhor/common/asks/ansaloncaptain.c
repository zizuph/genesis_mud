/* This is an ask module for the Ansalon - Khalakhor ship
 * captain, Doyle.
 */

#include <math.h>
#include <std.h>
#include "/d/Khalakhor/sys/defs.h"
  

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
        my_communicate("Blimey, you're right here!");
        return;
    }

  /* What to do if the player's a wizard. */
    if (player->query_wiz_level())
    {
        command("panic");
        my_communicate("Donnae say tha' name aloud! " +
            capitalize(HE_SHE(player)) +
            " might hear you! I can tell you nae!");
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
            "'s right here beside you!");
        return;
    }

  /* Some npc's will have a memory, so we'll see if */
  /* the npc has the player remembered. */
    if (query_remembered(str))
    {
        resp += "Actually, I was chatting with " +
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
        resp += "'Course I heard of " + 
            HIM_HER(player) + ", who " +
            "hasn't? ";
        do_align = 1;
    }
    else if (age > 5184000)      /* 60 days */
    {
        resp += "I believe I do know who that is, " +
            "if the sea-shanties be true. ";
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
        resp += capitalize(str) + ", the name is " +
            "like the wind in me memory. One day here, " +
            "one day not. ";
    else
        resp += "Sorry, I have nae the vaguest " +
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
            " was somewhere up north. ";
    else if (info == 1)
        resp += "Rumour has it " + HE_SHE(player) +
            " is somewhere in " + ({"Ansalon", "Avenir" ,"Calia",
            "Raumdor", "Gondor", "the Shire", "Terel", "Krynn",
            "Emerald"})[NAME_TO_RANDOM(TO->query_real_name(),
            12345678, 9)] + ", though I cannae say for sure. ";
    else if (info == 2)
        resp += "Rumour has it that " + HE_SHE(player) +
            "'s been explorin' the islands for the past " +
            "while. ";
    else if (info == 3)
        resp += "I had a trader on here the other day " +
            "who claimed to hae seen " + HIM_HER(player) +
            " in a village down the coast, but he could nae " +
            "remember the name of the place. ";
    else if (info == 4)
        resp += "I think " + HE_SHE(player) + " was on the " +
            "Bonnie Lass earlier today, actually, " +
            "but I hae no idea where " + HE_SHE(player) +
            " could be now. ";
   /* As finger_player.c doesn't define alignments, we */
  /* will generate a completely random alignment. */
    if (player->query_finger_player())
        align = random(2401) - 1200;
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
            "'s a good customer.";
    else if (align < -600)
        resp += "The miserable " + 
            (gender ? "harlot" : "fiend") + " can bloody " +
            "well stay away from my ship too, for all I " +
            "care.";
    my_communicate(resp);
    return;
}

public void
new_answer_question(string question)
{
	if (parse_command(question, TP, "[the] 'human' / 'humans'"))
	{
		my_communicate("Humans? I hae no problem with humans.");
		return;
	}
	else if (parse_command(question, TP, "[the] 'dwarf' / 'dwarves'"))
	{
		my_communicate("Well, I'm a dwarf if I ever did " +
		    "see one! True, not many are cap'ns of ships, but they " +
			"donnae know what they are missing!");
		return;
	}
	else if (parse_command(question, TP, "[the] 'elf' / 'elves'"))
	{
		my_communicate("Elves? I donnae see many elves on my ship " +
		   "that are from Khalakhor proper. Most were wiped out a "+
		   "long time ago, and they hae never recovered.");
		return;
	}
	else if (parse_command(question, TP, "[the] 'goblin' / 'goblins'"))
	{
	    command("spit");
		my_communicate("Bah! Most goblins o' Khalakhor are filthy, " +
		    "stinking creatures out of the north. Sure, some " +
		    "travelling goblins are well-mannered. I know enough " +
		    "that appearances can be deceiving. Still, I hear rumours " +
		    "that some goblins out of the far north have been " +
		    "prowling about the piers in Port Macdunn!");
		return;
	}
	else if (parse_command(question, TP, "[the] 'hobbit' / 'hobbits'"))
	{
		my_communicate("I cannae say much about hobbits, there " +
			"are none where dwarves hang their hats in Khalakhor.");
		return;
	}
	else if (parse_command(question, TP, "[the] 'gnome' / 'gnomes'"))
	{
		command("scratch chin");
		my_communicate("The few gnomes I've chanced to meet are nice " +
		    "enough folk. I cannae say I've ever seen any on Khalakhor " +
		    "proper, and I'm fairly well-travelled.");
		return;
	}
	else if (parse_command(question, TP, "[the] 'khalakhor'"))
    {
        command("strut");
        my_communicate("Khalakhor! A land o' rugged beauty!");
		return;
    }
	else if (parse_command(question, TP, "[the] [rugged] 'beauty'"))
    {
        my_communicate("Foothills an' alpine meadows of heather! An " +
            "unforgiving sea, an' rich forested islands!");
		return;
    }
	else if (parse_command(question, TP, "[the] [rich] [forested] 'islands'"))
    {
        my_communicate("They circle th' main continent!");
		return;
    }
	else if (parse_command(question, TP, "[the] [main] 'continent'"))
    {
        my_communicate("Tis the bulk o' the lands o' Khalakhor!");
		return;
    }
	else if (parse_command(question, TP,
	        "[the] [alpine] [meadows] [of] 'heather'"))
    {
        command("sniff reminiscently");
        my_communicate("The beauty mine eyes have seen almost brings " +
            "a tear!");
		return;
    }
	else if (parse_command(question, TP,
	        "[the] [unforgiving] 'ocean' / 'sea'"))
    {
        my_communicate("Cuan Siorriudh, of course!");
		return;
    }
	else if (parse_command(question, TP, "[the] [ship] 'route'"))
    {
        my_communicate("I sail 'tween the ports o' Port Macdunn, " +
            "an' Kalaman!");
		return;
    }
	else if (parse_command(question, TP, "[the] 'kalaman'"))
    {
        my_communicate("I donnae know much about it, I only " +
            "hear strange rumours of lizard men!");
		return;
    }
	else if (parse_command(question, TP, "[the] [strange] 'rumours'"))
    {
        command("cough quietly");
        my_communicate("I'll not be revealin' my sources!");
		return;
    }
	else if (parse_command(question, TP,
	        "[the] [lizard] 'men' / 'lizardmen'"))
    {
        my_communicate("Tis only rumours.");
		return;
    }
	else if (parse_command(question, TP, "[the] [port] 'macdunn'"))
    {
        my_communicate("Aye, a nice enough place to visit, it's " +
            "undergoin' a bit o' a religious revival.");
		return;
    }
	else if (parse_command(question, TP, "[the] 'religion'"))
    {
        my_communicate("I'm no one to be asking that of!");
		return;
    }
	else if (parse_command(question, TP, "[the] [religious] 'revival'"))
    {
        my_communicate("A passel of monastics 'ave taken a likin' " +
            "to the town!");
		return;
    }
	else if (parse_command(question, TP, "[the] 'monastics'"))
    {
        my_communicate("I donnae associate wi' them!");
		return;
    }
	else if (parse_command(question, TP, "[the] 'quest' / 'task'"))
    {
        my_communicate("Nay, I've not any for tha'! Ask " +
            "the folk of Port Macdunn, tho'!");
		return;
    }
    
    if (default_answer)
    {
        set_alarm(rnd() * 4.0, 0.0, &answer_question(default_answer, 1));
    }
    else
        my_communicate("I cannae help thee with that!");
}

