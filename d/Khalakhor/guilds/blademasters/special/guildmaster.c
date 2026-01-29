/*
 * guildmaster.c
 *
 * This is a manager type object that keeps track of
 * some different things in teh blademasters, such
 * as their sword skill & guildstat.
 *
 * Khail - January 25/98.
 */
#pragma strict_types
#pragma no_clone

#include "defs.h"

#define GUILDSTAT  0
#define SWORDSKILL 1
#define READNEWS   2

mapping masters;

public void
reset_euid()
{
    seteuid(getuid());
}

public void
create()
{
    masters = ([]);
    setuid();
    reset_euid();
    masters = restore_map(SPECIAL + "master_map");
    if (!mappingp(masters))
    {
        masters = ([ ]);
    }
}

/*
 * Function name: update_list
 * Description  : Called when a player joins or enters the game,
 *                and updates the masters map with their
 *                current stat and sword skill.
 * Arguments    : name - Name of the blademaster.
 *                skill - Player's sword skill.
 *                stat - Player's lay guild stat.
 * returns      : n/a
 */
public void
update_list(string name, int skill, int stat)
{
    if (!strlen(name))
    {
        return;
    }
    if (!masters[name])
        masters[name] = ({skill, stat, 0});
    else
    {
        masters[name][SWORDSKILL] = skill;
        masters[name][GUILDSTAT] = stat;
    }
    reset_euid();
    save_map(masters, SPECIAL + "master_map");
}

public void
remove_master(string name)
{
    if (!strlen(name))
    {
        return;
    }
    if (!masters[name])
    {
        return;
    }
    masters = m_delete(masters, name);
    save_map(masters, SPECIAL + "master_map");
}

public int
query_news(string name)
{
    if (!masters[name])
    {
        return 0;
    }
    return !masters[name][READNEWS];
}

public int
update_news(string name)
{
    if (!strlen(name))
    {
        return 0;
    }
    if (!masters[name])
    {
        return 0;
    }
    masters[name][READNEWS] = 1;
    save_map(masters, SPECIAL + "master_map");
}

/*
 * Function name: add_news
 * Description  : Removes the 'news' toggle in the masters
 *                save map so when they next log in, they'll
 *                know there's something new.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
add_news()
{
    int i;
    string *indexes = m_indexes(masters);

    if (!sizeof(indexes))
        return;

    for (i = 0; i < sizeof(indexes); i++)
        masters[indexes[i]][READNEWS] = 0;
    reset_euid();
    save_map(masters, SPECIAL + "master_map");
}

public mapping
query_masters()
{
    return masters + ([]);
}

public void
remove_object()
{
    reset_euid();
    if (!masters)
        return;
    save_map(masters, SPECIAL + "master_map");
}

