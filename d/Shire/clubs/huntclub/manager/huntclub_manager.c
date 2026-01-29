/*
 * Data store for the hunt-club
 *
 * This club has many players and thus needs to store data in way which is 
 * somewhat efficient. 
 *
 * - Cotillion
 */

#include "../huntclub.h"

#include <files.h>
#define TALLY_FILE(player)      (HUNTCLUB_MANAGER + "data/" + (player))
#define FLUSH_DELAY             (60.0)

/* Global Variables, when adding a global variable that is
   kept track of through reboots, don't forget to add it to
   restore_manager(). */
static string *dirty = ({ });   /* Players which need to be flushed to disk */
static mapping tallies = ([ ]);

/* Prototypes */
void save(string player);
void purge();

void
create()
{
    setuid();
    seteuid(getuid());

    set_alarm(120.0, 0.0, &purge());

    /* Migration */
    //mapping old = restore_map(HUNTCLUB_MANAGER + "tally");
    //if (old["m_options"]) {
    //    foreach (string name, mapping val: old["m_options"]["kills"]) {
    //        tallies[name] = val;
    //        save(name);
    //    }
    //}
}

void
purge()
{
    foreach (string file: get_dir(TALLY_FILE("*.o")))
    {
        string player = file[..-3];
        
        if (!SECURITY->exist_player(player))
        {
            log_file("huntclub", ctime() + ": Purged " + player + "\n");
            m_delkey(tallies, player);
            rm(TALLY_FILE(file));
        }
    }
}


static mapping
get_tally(string player)
{
    /* Cached? */
    if (!tallies[player]) {
        /* Load? If file is missing restore_map returns an empty mapping */
        mapping map = restore_map(TALLY_FILE(player));
        if (m_sizeof(map)) 
            tallies[player] = map["tally"];
        else
            tallies[player] = ([ ]);
    }

    return tallies[player];
}


void
flush()
{
    foreach (string player: dirty) {
        save_map(([ "tally": tallies[player] ]), TALLY_FILE(player));
    }
    dirty = ({ });
}

int flush_alarm = 0;

void
remove_object()
{
    flush();
    destruct();
}

/* 
 * Saves are deferred as they can cause latency
 */
void
save(string player)
{
    dirty |= ({ player });
    if (!get_alarm(flush_alarm))
        flush_alarm = set_alarm(FLUSH_DELAY, 0.0, &flush());
}


/* Called from domain link to flush now */
void
armageddon()
{
    flush();
}

/* Called from domain_link when a player is renamed */
void
rename_player(string old_name, string new_name)
{
    /* Not a member */
    if (!tallies[old_name] && file_size(TALLY_FILE(old_name) + ".o") < 0)
        return;
    
    mapping tally = get_tally(old_name);
    tallies[new_name] = tally;
    tallies[old_name] = ([ ]);

    save(new_name);
    save(old_name);
}


/*
 * Function name:   query_killed_category
 * Description:     Returns the category to which the specified object belongs.
 * Arguments:       (object) killed - The living object being killed.
 * Returns:         (string) - the category to which the object belongs.
 *                  (int) -2: Not a living object
 *                  (int) -1: No category found for object
 */
public mixed
query_killed_category(object killed)
{
    string race;
    
    if (!living(killed))
        return -2;
    
    if (interactive(killed))
        return "player";
    
    /* Example code, can do it other ways */
    switch(killed->query_race_name())
    {
        /* Example of how you can categorize it */
        case "hobgoblin":
        race = "goblin";
            break;
            
        default:
        race = killed->query_race_name();
            break;
    }
    
    if (!strlen(race) && !strlen(race = killed->query_race()))
        return "other";
    
    return race;
} /* query_killed_category */

/*
 * Function name:   query_hunter_kills
 * Description:     Returns the amount of kills the player has achieved, either
 *                  from the specified category, or total tally.
 * Arguments:       (mixed) player - Either the player object or the player name
 *                  (string) category - The category to query, unspecified will
 *                                      return total tally of all categories.
 * Returns:         (int) -1: No player specified.
 *                  (int)  0: No tally was found.
 *                  (int) >0: The kill tally in the specified category.
 */
public varargs int
query_hunter_kills(mixed player, string category)
{
    int     total_tally;
    
    if (objectp(player))
        player = player->query_real_name();
    
    if (!stringp(player))
        return -1;
    
    mapping tally_list = get_tally(player);
    
    if (!m_sizeof(tally_list))
        return 0;
    
    if (strlen(category))
    {
        if (member_array(category, m_indexes(tally_list)) < 0)
            return 0;
        
        return tally_list[category];
    }
    
    foreach(int tally: m_values(tally_list))
    {
        total_tally += tally;
    }
    
    return total_tally;
} /* query_hunter_kills */


/*
 * query_hunter_categorgies
 */
public string *
query_hunter_categories(mixed player)
{
    if (objectp(player))
        player = player->query_real_name();

    if (!stringp(player))
        return ({ });
 
    return m_indexes(get_tally(player));
}

/*
 * Function name:   add_hunter_kills
 * Description:     The amount of kills the player has achieved, either on the
 *                  specified category, or total tally.
 * Arguments:       (mixed) player - Either the player object or the player name
 *                  (object) killed - The to be added to the tally.
 *                  (int) tally - Amount with which we increment the tally.
 * Returns:         (status)  0: Failure.
 *                  (status)  1: Success.
 */
public varargs status
add_hunter_kills(mixed player, object killed, int tally = 1)
{
    string  category;
    
    if (objectp(player))
        player = player->query_real_name();
    
    if (!stringp(player) || !objectp(killed))
        return 0;
    
    if (!stringp(category = query_killed_category(killed)))
        return 0;
    
    mapping kills = get_tally(player);
    
    if (!mappingp(kills))
        kills = ([]);
    
    kills[category] += tally;
    
    save(player); 
    return 1;
} /* add_hunter_kills */

mixed
query_alarms()
{
    return get_all_alarms();    
}

