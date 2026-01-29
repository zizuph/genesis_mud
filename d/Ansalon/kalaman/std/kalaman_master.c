/*
 * Dungeon Master
 *
 * Keeps track of the various states in the
 * dungeon area of Kalaman
 *
 * Lunatari of Krynn
 *
 * OBS WARNING IMPORTANT 
 *
 * Do not reload/update or whatever to this file 
 * during normal gametime, it will reset the status
 * of all grates/ropes and other functions in the
 * dungeon.
 *
 * 2008-01-30: Creation.
 * 2008-02-10: Altered how the master is created.
 */
#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include "../dungeon/local.h";

mapping gStatus;

/*
 * Function: create
 * Info:     Creates the mappings
 */
void
create()
{
    setuid();
    seteuid(getuid());

    gStatus = ([ ]);
}

int
set_status(string what, int arg)
{
    if (gStatus[what]) 
    {
        gStatus[what][0] = arg;
        return 1;
    }
    else
    {
        gStatus[what] = ({ arg, }); 
        return 1;
    }

    return -1;
}

int
query_status(string what)
{
    if (gStatus[what])
    {
        return gStatus[what][0];
    }
    else
    {
        return 0;
    }

    return -1;
}
