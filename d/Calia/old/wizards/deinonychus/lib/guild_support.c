/*
 * Some support for meditating code
 *
 */

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

string *stat_names;

/*
 * Function name: get_pref
 * Description:   This is the input_to function that is used by set_prefs
 *                You should never call it directly
 */
void
get_pref(string str)
{
    int i, count, *prefs;

    count = this_player()->query_prop(GUILD_I_COUNT);
    prefs = this_player()->query_prop(GUILD_AI_PREFS);
    if (!prefs)
	prefs = allocate(SS_NO_EXP_STATS);

    if (!str || !sscanf(str, "%d", i))
    {
	if (str == "~q")
	{
	    write("Preferences left unchanged.\n");
	    this_player()->remove_prop(GUILD_I_COUNT);
	    this_player()->remove_prop(GUILD_AI_PREFS);
	    return;
	}
        write(stat_names[count] + ": ");
        input_to("get_pref");
        return;
    }
    prefs[count++] = (i >= 0 ? i : 0);
    if (count == SS_NO_EXP_STATS)
    {
        this_player()->set_learn_pref(prefs);
        write("Your learning preferences have been set to: \n");
        prefs = this_player()->query_learn_pref(-1);
        for (i = 0; i < SS_NO_EXP_STATS; i++)
            write(stat_names[i] + ": " + prefs[i] +
                  (i < SS_NO_EXP_STATS -1 ? ", " : "\n"));
	this_player()->remove_prop(GUILD_I_COUNT);
	this_player()->remove_prop(GUILD_AI_PREFS);
        return;
    }

    write(stat_names[count] + ": ");
    this_player()->add_prop(GUILD_I_COUNT, count);
    this_player()->add_prop(GUILD_AI_PREFS, prefs);
    input_to("get_pref");
    return;
}

/*
 * Function name: create_guild_support
 * Description:   Set up the stat_names variable
 */
void
create_guild_support()
{
    stat_names = ({ "STR", "DEX", "CON", "INT", "WIS", "DIS" });
}

/*
 * Function name: set_prefs
 * Description:   An interactive sequence that allows you to set your
 *                learning preferences
 * Returns:       1
 */
int
set_prefs()
{
    int i, *orig_prefs;

    write("Your learning preferences are now: \n");
    orig_prefs = this_player()->query_learn_pref(-1);
    for (i = 0; i < SS_NO_EXP_STATS; i++)
        write(stat_names[i] + ": " + orig_prefs[i] +
              (i < SS_NO_EXP_STATS -1 ? ", " : "\n"));

    write("" +
	"You can set a number indicating how much you want to concentrate\n" +
        "on improving each stat. You can use any positive numbers or 0 for\n" +
        "each stat. The numbers are relative to each other and will be\n" +
        "recalculated so their sum is 100 - your guild tax.\n" +
	"To abort this command, type ~q.\n");

    write(stat_names[0] + ": ");
    input_to("get_pref");

    return 1;
}

/*
 * Function name: assess
 * Description:   Allows a player to estimate how far he is from the next
 *                stat description.
 * Parameters:    stat - one of "STR", "DEX", "CON", "INT", "WIS", "DIS"
 *                lower case is ok as well
 * Returns:       1 - success, 0 - stat not found
 */
int
assess(string stat)
{
    int i, j, k, n, n2, residue;
    string *a_strings;
    mixed stat_strings;
    object tgive;

    notify_fail("Usage: " + query_verb() + " <stat>\n");
    if (!stat)
        return 0;
    
    notify_fail("Possible choices are: " + implode(stat_names, ", ") +  "\n");
    for (i = 0; ; i++)
    {
        if (i >= sizeof(stat_names))
            return 0;
        if (lower_case(stat) == lower_case(stat_names[i]))
            break;
    }

    j = this_player()->query_stat(i);
    if (j >= 160)
    {
        write("You have the " + stat_names[i] + " of an immortal.\n");
        return 1;
    }

    if (j >= 136)
    {
        write("You have reached epic " + stat_names[i] + ".\n");
        return 1;
    }

    if (j >= 100)
	write("If all your stats were this good you would be able " +
	      "to try the wizquest.\n");
    
    /*
     * 8 descriptions / 17 steps each
     */
    a_strings = ({ "very far from", "far from", "halfway to",
                   "close to", "very close to" });

    for (n = 7, n2 = 7 * 17; ; n--, n2 -= 17)
	if (j >= n2)
	{
	    residue = j - n2;
	    break;
	}

    tgive = this_player()->find_stat_describer(i);
    if (objectp(tgive))
	write("You are " + a_strings[residue / sizeof(a_strings)] +
	      " advancing to " +
	      (j >= (7 * 17) ? "epic " + stat_names[i] :
	       tgive->query_stat_string(i, -(n + 1)))
               /* Ugly but working, negative index to query_stat_string
                  will give string with that index. */
	      + "\n");
    else
	write("You are " + a_strings[residue / sizeof(a_strings)] +
	      " advancing.");
    return 1;
}

/*
 * Function name: gs_leave_inv
 * Description:   Should be called if someone leaves the room. if that person
 *		  was meditating, better do something. You should call
 *		  this function from leave_inv() in your room.
 */
void
gs_leave_inv(object ob, object to)
{
    if (ob->query_prop(LIVE_I_MEDITATES))
    {
	ob->remove_prop(LIVE_I_MEDITATES);
	ob->remove_prop(GUILD_I_COUNT);
	ob->remove_prop(GUILD_AI_PREFS);
	ob->remove_prop(LIVE_S_EXTRA_SHORT);
    }
}

/*
 * Function name: init_guild_support
 * Description:   Add the meditate command to the player
 */
void
init_guild_support()
{
    if (!stat_names)
	create_guild_support();
    add_action("gs_meditate", "meditate");
}

/*
 * Function name: gs_hook_already_meditate
 * Description:	  Called when player is already meditating
 * Returns:	  Always 1
 */
int
gs_hook_already_meditate()
{
    write("You are already in deep trance. If you wish to finish your " +
	"meditation\nyou can do so by typing 'rise'.\n");
    return 1;
}

/*
 * Function name: gs_hook_start_meditate
 * Description:   Called when player starts to meditate
 */
void
gs_hook_start_meditate()
{
    write("" +
	"Slowly you sit down on the soft carpet and close your eyes.\n" +
	"A feeling of great ease and self control falls upon you.\n" +
	"You block of your senses and concentrate solely upon your\n" +
	"own mind. You find yourself able to <estimate> your different\n" +
	"preferences and <set> them at you own desire.\n" +
	"Just <rise> when you are done meditating.\n");
    say(QCTNAME(this_player()) + " sits down on the carpet and starts " +
	"to meditate.\n");
}

/*
 * Function name: gs_hook_rise
 * Description:	  Called when player rises from the meditation
 */
void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface of\n" +
	  "your consciousness. You exhale and feel very relaxed as you get\n" +
	  "up and leave the carpet.\n");
    say(QCTNAME(this_player()) + " rises from the carpet.\n");
}

/*
 * Function name: gs_hook_catch_error
 * Description:   Called player tried to do something strange while meditating
 *		  like examin things or leave the room.
 * Arguments:	  str - Argument the player tried to send to his command
 * Returns:	  1 normally.
 */
int
gs_hook_catch_error(string str)
{
    write("You can't do that while meditating.\n");
    return 1;
}

/*
 * Function name: gs_meditate
 * Description:   Player wants to meditate
 */
varargs int
gs_meditate(string str)
{
    string long_str;

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is meditating");
    if (this_player()->query_prop(LIVE_I_MEDITATES))
	return gs_hook_already_meditate();

    this_player()->add_prop(LIVE_I_MEDITATES, 1);

    gs_hook_start_meditate();

    add_action("gs_catch_all", "", 1);
    return 1;
}

/*
 * Function name: gs_rise
 * Description:   Player rises
 */
int
gs_rise()
{
    gs_hook_rise();
    this_player()->remove_prop(LIVE_I_MEDITATES);
    return 1;
}

/*
 * Function name: gs_catch_all
 * Description:	  Catch all commands the player makes while meditating
 */
int
gs_catch_all(string arg)
{
    string action;

    if (!this_player()->query_prop(LIVE_I_MEDITATES))
	return 0;
    action = query_verb();

    switch (action)
    {
    case "estimate":
	return assess(arg);
    case "meditate":
	return gs_meditate();
    case "set":
	set_prefs();
	return 1;
    case "rise":
	this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
	gs_rise();
	return 1;
    case "stats":
    case "quit":
    case "commune":
    case "bug":
    case "typo":
    case "idea":
    case "praise":
    case "sysbug":
	return 0;
    default:
	return gs_hook_catch_error(arg);
    }
}
