/*
 * Trackes red fang members and titles
 * Moved from shadow to cut down cpu use.
 *
 * - Cotillion
 */
#pragma no_clone
#pragma strict_types

#include "/d/Kalad/common/guilds/red_fang/default.h"

mapping members;

#define CLAN  "clan"
#define TRIBE "tribe"
#define TOGGLE "toggle"

void
create()
{
    setuid();
    seteuid(getuid());
    
    members = restore_map(FANG_DIR(doc/members));
}

int
save()
{
    save_map(members, FANG_DIR(doc/members));
}

string
query_clan(string member)
{
    if (!members[member])
        return 0;
    
    return members[member][CLAN];
}

string
query_tribe(string member)
{
    if (!members[member])
        return 0;
    
    return members[member][TRIBE];
}

int
query_toggle(string member)
{
    if (!members[member])
        return 0;
    
    return members[member][TOGGLE];
}

int
set_data(string member, string clan, string tribe, int toggle)
{
    members[member] = ([ CLAN: clan, TRIBE: tribe, TOGGLE: toggle ]);
    save();
    return 1;
}

int
set_toggle(string member, int toggle)
{
    if (!members[member])
        return 0;

    toggle = min(max(toggle, 1), 3);
    members[member][TOGGLE] = toggle;
    save();
    return toggle;
}

int
load_old_data()
{
    mapping temp;
    
    members = ([ ]);

    temp = restore_map("/d/Kalad/common/guilds/red_fang/doc/player_tribes");
    foreach (string member, mixed value: temp)
    {
        mixed clan, tribe, toggle;
        sscanf(value, "%s|%s|%d", clan, tribe, toggle);

        members[member] = ([ CLAN : clan, TRIBE : tribe, TOGGLE : toggle ]);
    }    
}
