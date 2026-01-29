
#pragma save_binary

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/language.h"

int count, *prefs;
string *stat_names;

/*
 * Function name: get_pref
 * Description:   This is the input_to function that is used by set_prefs
 *                You should never call it directly
 */
void
get_pref(string str)
{
    int i;

    if (!str || !sscanf(str, "%d", i))
    {
	if (str == "~q")
	{
	    write("Preferences left unchanged.\n");
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
        for(i = 0; i < SS_NO_EXP_STATS; i++)
            write(stat_names[i] + ": " + prefs[i] +
                  (i < SS_NO_EXP_STATS -1 ? ", " : "\n"));
        return;
    }
    write(stat_names[count] + ": ");
    input_to("get_pref");
    return;
}

/*
 * Function name: set_prefs
 * Description:   An interactive sequence that allows you to set your
 *                learning preferences
 * CAUTION:       This function uses global variables and input_to
 *                You must make sure that only one person at a time
 *                can use it.
 *                The code to check this can lok something like:
 *                if(!stat_names || count == SS_NO_EXP_STATS)
 *                    set_prefs();
 * Returns:       1
 */
int
set_prefs()
{
    int i;

    prefs = allocate(SS_NO_EXP_STATS);
    stat_names = ({ "STR", "DEX", "CON", "INT", "WIS", "DIS" });

    write("Your learning preferences are now: \n");
    prefs = this_player()->query_learn_pref(-1);
    for(i = 0; i < SS_NO_EXP_STATS; i++)
        write(stat_names[i] + ": " + prefs[i] +
              (i < SS_NO_EXP_STATS -1 ? ", " : "\n"));

    write("You can set a number indicating how much you want to concentrate\n" +
          "on improving each stat. You can use any positive numbers or 0 for\n"
+
          "each stat. The numbers are relative to each other and will be\n" +
          "recalculated so their sum is 100.\n" +
	  "To abort this command, type ~q.\n");

    count = 0;
    write(stat_names[count] + ": ");
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
    int i, j, k, n;
    string *stat_names, *a_strings;
    mixed stat_strings;
    object tgive;

    notify_fail("Usage: " + query_verb() + " <stat>\n");
    if (!stat)
        return 0;
    stat_names = ({ "STR", "DEX", "CON", "INT", "WIS", "DIS" });
    
    notify_fail("Possible choices are: " + implode(stat_names, ", ") +  "\n");
    for (i = 0; ; i++)
    {
        if (i >= sizeof(stat_names))
            return 0;
        if (lower_case(stat) == lower_case(stat_names[i]))
            break;
    }
    j = this_player()->query_stat(i);
    if (j >= 150)
    {
        write("You have the " + stat_names[i] + " of an immortal.\n");
        return 1;
    }

    if (j > 100)
    {
        write("You have reached epic " + stat_names[i] + ".\n");
        return 1;
    }
    
    a_strings = ({ "very far from", "far from", "halfway to",
                   "close to", "very close to" });

    n = (j % 16) * sizeof(a_strings) / 16;
    /* Hardcoded, based on 6 decriptions / 100 statpoints */

    tgive = this_player()->find_stat_describer(i);
    if (objectp(tgive))
	write("You are " + a_strings[n] + " advancing to " +
	      (j >= 80 ? "epic " + stat_names[i] :
	       tgive->query_stat_string(i, j + 20 ))
	      + "\n");
    else
	write("You are " + a_strings[n] + " advancing.");
    return 1;
}