/*   
 *	/d/Gondor/common/guild/outlaw.c
 *
 *   Modified from the Minas Tirith outlaw-system,
 *   by Elessar, May 1995.
 *   Original code by Olorin.
 *   Quick hack to only restore once. There is no need to do
 *   so more than once per armageddon.
 */
#pragma save_binary
#pragma strict_types

#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

#define SAVE  "/d/Gondor/common/guild/outlaws"

string *outlaw = ({});
static int restored = 0;

void
restore_outlaws()
{
    if (!restored)
        restore_object(SAVE);
}

int
add_outlaw(mixed e)
{
    int     i,
            is_finger = 0;
    object  e_ob;
    string  n, r;

    seteuid(getuid());
    if (stringp(e)) 
    {
        n = lower_case(e);
        if (!(e_ob = find_player(n))) 
	{
            is_finger = 1;
            e_ob = SECURITY->finger_player(n);
	}
        if (!objectp(e_ob)) return -1;
        r = e_ob->query_race_name();
        if (is_finger)
            e_ob->remove_object();
    }
    else if (objectp(e)) 
    {
        if (e->query_npc())
            return -1;
        n = e->query_real_name();
        r = e->query_race_name();
        if (!stringp(n))
            return -1;
    }

    restore_outlaws();

    if ((i = member_array(n, outlaw)) >= 0)
    {
        if (r != outlaw[i+1])
        {
            outlaw[i+1] = r;
            save_object(SAVE);
        }
        return 0;
    }

    outlaw += ({ n, r });
    log_file("r_outlaw", CAP(n) + " ("+ r + ") declared to be Enemy of the Rangers, "
      + ctime(time()) + ".\n");
    save_object(SAVE);
    return 1;
}

int
remove_outlaw(string name)
{
    int     i;

    seteuid(getuid());
    restore_outlaws();
    name = LOW(name);
    if ((i = member_array(name, outlaw)) < 0)
        return 0;
    outlaw = exclude_array(outlaw, i, i+1);
    log_file("r_outlaw", CAP(name) + " is no longer an Enemy of the Rangers, "
      + ctime(time()) + ".\n");
    save_object(SAVE);
    return 1;
}

varargs mixed
query_outlaw(string name, string race)
{
    int     i;

    seteuid(getuid());
    restore_outlaws();
    if (!stringp(name))
        return outlaw;

    name = LOW(name);
    if ((i = member_array(name, outlaw)) < 0)
        return 0;

    if (!stringp(race))
        race = find_living(name)->query_race_name();
    if (!stringp(race))
        return 1;
    if (outlaw[i+1] != race)
    {
        outlaw[i+1] = race;
        save_object(SAVE);
    }
    return 1;
}
