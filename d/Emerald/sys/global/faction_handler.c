/*
 * /d/Emerald/sys/global/faction_handler.c
 *
 * Handles the storage and retrieval of faction information
 * concerning players and NPCs.
 * 
 * Faction groups are defined and then when players perform
 * certain actions, their faction changes based on the action,
 * and secondly based on the relations of faction groups.
 *
 * For example, assume that the faction relation between
 * the "TelberinGuards" and "AvularCitizens" is -40.
 * This means that any action on the "TelberinGuards" receiving 
 * a faction award (positive * or negative) will be duplicated, at 40% value, 
 * in opposite direction, on the "AvularCitizens"
 */

#pragma strict_types
#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#include "/d/Emerald/sys/faction.h"
#include "/d/Emerald/sys/faction_groups.h"

#include "/d/Emerald/sys/domain.h"

/*
 * Functions available to calling objects
 */
void add_faction(mixed player, string factiongroup, int amount);
int query_faction(mixed player, string factiongroup);

/*
 * Internal Functions
 */
void load_player_map(string pname);
void save_player_map(string pname);
string getpfilename(string pname);
void clean_cache();

private mapping player_map;
private int clean_alarm;
private mapping faction_groups = FACTION_GROUPS;

void
create()
{
    /* Perform 1-time initializations here */
    player_map = ([]);
    clean_alarm = set_alarm(14400.0, 0.0, clean_cache);
}

void
load_player_map(string pname)
{
    setuid();
    seteuid(getuid());
    player_map[pname] = restore_map(getpfilename(pname));
}

void
save_player_map(string pname)
{
    setuid();
    seteuid(getuid());
    save_map(player_map[pname], getpfilename(pname));
}

string
getpfilename(string pname)
{
    return sprintf("/d/Emerald/log/faction/%c/%s", pname[0], pname); 
}

void
add_faction(mixed player, string factiongroup, int amount)
{
    mapping pinfo;
    string *names;
    int pct;
    int i;
    int newamt;

    if (objectp(player))
    {
        player = player->query_real_name();
    }

    /* Check and see if the player's faction is cached. */
    if (!(pinfo = player_map[player]))
    {
        /* since its not in there, put it in there */
        load_player_map(player);
        pinfo = player_map[player];
    }

    /* At this point we're assured player's mapping is in memory,
     * even if it is empty
     */
    pinfo[factiongroup] += amount;     

    /*
     * Now iterate through all related factions, adding faction
     * for this player accordingly
     */

    names = m_indices(faction_groups[factiongroup]); /* All those w/relations */
    for (i = 0; i < sizeof(names); i++)
    {
        pct = faction_groups[factiongroup][names[i]];
        
        /* newamt = ftoi((abs(itof(amount)) * itof(pct)) / 100.0); */
        newamt = (amount * pct) / 100;
        pinfo[names[i]] += newamt;
    }

    save_player_map(player);
}

int
query_faction(mixed player, string factiongroup)
{
    mapping pinfo;

    if (objectp(player))
    {
        player = player->query_real_name();
    }

    if (!(pinfo = player_map[player]))
    {
        load_player_map(player);
        pinfo = player_map[player];
    }

    return pinfo[factiongroup];    
}

void
clean_cache()
{
    int i;
    string *names;
    object player, env;

    /* This is slightly better than a repeating alarm for our purposes.  If
     * we get an eval-cost error while executing this function, it still
     * gets called next interval.  With a repeating alarm, it would be shut
     * off.
     */
    clean_alarm = set_alarm(14400.0, 0.0, clean_cache);

    names = m_indices(player_map);
    for (i = 0; i < sizeof(names); i++)
    {
        player = find_player(names[i]);

	if (!player || !interactive(player) || !(env = environment(player)) ||
            (env->query_domain() != DOMAIN_NAME))
        {
            /* Flush that boy out of the cache */
	    player_map = m_delete(player_map, names[i]);
        }      
    }
}
