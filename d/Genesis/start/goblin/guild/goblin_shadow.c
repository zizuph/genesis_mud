/* The goblin shadow */

#pragma save_binary

inherit "/std/guild/guild_race_sh";

#include "../goblins.h"
#include <macros.h>
#include <ss_types.h>

string *titles;
string *power_strings;

#ifdef BUGGY
create()
{
    power_strings = ({ "powerful" });
}
#endif
query_guild_tax_race() { return 15; }

query_guild_not_allow_join_race(player, type, style, name)
{
    if (::query_guild_not_allow_join_race(player, type, style, name))
	return 1;

    return 0;
}

query_guild_keep_player(player)
{
    if (player->query_race_name() != "goblin")
    {
	write("Only goblins can be member of the goblin tribe.\n");
	return 0;
    }

    return 1;
}


/* Function name: query_goblin_title
 * Description:   How far have we progressed in the guild?
 * Returns:       The title
 */
string
query_goblin_title()
{
    int rank;
    titles = ({"Recruit", "Warrior", "Veteran", "Subleader", "Leader", 
        "Sublieutenant", "Lieutenant", "Captain", 
        "Subchief", "Chief", "General"});
    rank = this_player()->query_stat(SS_RACE)/10;
    return titles[MIN(rank, 10)];
}

/* Function name: query_title
 * Description:   We shadow the title function so goblins can have titles of
 *                their own.
 * Returns:       The completet title.
 */
string
query_title()
{
    string title;

    title = shadow_who->query_title();

    if (shadow_who->query_wiz_level())
        return title;
    if (title)
        return title + " and " + query_goblin_title();
    return query_goblin_title();
}

#ifdef BUGGY
/*
 * Function name: desc_stat
 * Returns: 1 if this textgiver describes the given stat
 */
int
desc_stat(int stat)
{
    return (SS_RACE == stat);
}

/*
 * Function name: query_stat_string
 * Description:   Gives text information corresponding to a stat
 * Parameters:    stat: index in stat array
 *                value: stat value (range 1..100)
 * Returns:       string corresponding to stat/value
 */

string
query_stat_string(int stat, int value)
{
    if (stat != SS_RACE && -stat != SS_RACE)
        return "";
    if (value < 0)
    {
        if (value < -sizeof(power_strings))
            value = 0;
        return power_strings[-value];
    }
    if (value > 99)
        value = 99;
    return power_strings[sizeof(power_strings) * value / 100];
}
#endif