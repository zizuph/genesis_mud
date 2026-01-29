/*
 * Example Adventurers Guildhall, giving an example of how
 * to use the new functions within /lib/skill_raise.c
 * implemented by me, Lucius.
 */

/*
 * This makes us write proper code.
 */
#pragma strict_types

/*
 * Standard inherits.
 */
inherit "/std/room";
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

/*
 * Include this for the skill type defines.
 */
#include <ss_types.h>

/*
 * This function adds our skills into the adventurer hall.
 */
private void
set_up_skills()
{
/*
 * This sets up the basics for us, from /lib/skill_raise.c
 */
    create_skill_raise();

/*
 * This is how we add skills into the adventurer guild.
 *
 * The strings are blank because we want to use the mud default
 * messages for the skill name and improve messages.
 *
 * The cost factor is only used on special skills, mudlib overrides
 * any setting you place for mudlib skills.
 *
 * The last value set is how high we can train here.
 */
    sk_add_train(SS_WEP_SWORD,	  "", "", 0, 20);
    sk_add_train(SS_WEP_KNIFE,	  "", "", 0, 20);
    sk_add_train(SS_DEFENCE,	  "", "", 0, 20);
    sk_add_train(SS_UNARM_COMBAT, "", "", 0, 20);
}

/*
 * This sets up our room descriptions, and some basic values.
 */
public void
create_room()
{
    ::create_room();

    set_short("Training Hall");
    set_long("This spartan room continues a simple training dummy "+
	"suspended between posts and a few poles erected about "+
	"the room.\n");

    add_item(({"dummy", "training dummy"}), "The training dummy is "+
	"suspended between posts, usefull for all sorts of practice.\n");

    add_item(({"pole", "poles"}), "A few very worn-out appearing poles "+
	"are erected around the room.  Used mainly for weapons practice.\n");

/*
 * Call to the above function so we have some skills to train here.
 */
    set_up_skills();
}

/*
 * Need this here to add the guild commands onto players as they enter
 */
public void
init()
{
    ::init();

/*
 * There are add_actions defined in the two inherit files,
 * /lib/skill_raise.c and /lib/guild_support.c
 * They give us the 'meditate' 'list' 'learn' and 'improve' commands.
 */
    init_skill_raise();
    init_guild_support();
}

/*
 * 1 - can train, 0 - cannot train.
 *
 * Hobbits are prevented from training.
 */
public int
sk_hook_allow_train(object who)
{
    return (who->query_race() != "hobbit");
}

/*
 * You should use notify_fail() and return '0' here, however,
 * it will also work using write() and returning '1'.
 *
 * This is why the hobbits are prevented from training...
 */
public int
sk_hook_not_allow_train()
{
   notify_fail("You take a look at the training devices, and decide to "+
      "back down from their fearful presence.\n");

   return 0;
}

/*
 * 1 - Yes, object 'who' (the player), may train the skill 'skill'
 *     up to the skill level 'level'.
 *
 * 0 - Means go away.
 *
 * Note: If you return '0', they will not even be able to see
 *       the skill listed when they do a 'learn' or 'improve'.
 *
 * This shows we are not an equal opportunity trainer..
 */
public int
sk_hook_allow_train_skill(object who, string skill, int level)
{
    switch (who->query_race())
    {
    case "hobbit":
	return 0; break;
    case "human":
	if ((skill == "unarmed combat") && (level > 15))
	{
	    return 0;
	}
	break;
    case "gnome":
	if ((skill == "sword") && (level > 15))
	{
	    return 0;
	}
	break;
    case "goblin":
	if ((skill == "defence") && (level > 10))
	{
	    return 0;
	}
	break;
    default:
	return 1;
    }

    return 1;
}

/*
 * You should use a write() and return '1' here.
 * However, it will work using notify_fail() and a return of '0'.
 *
 * This is why we are not an equal opportunity trainer...
 */
public int
sk_hook_not_allow_train_skill(string skill)
{
    string race = this_player()->query_race_name();

    write("Members of the race '" + race + "' may not " +
	"train " + (skill ? "the skill '" + skill + "' " : "" ) +
	"any further here.\n");

    return 1;
}

