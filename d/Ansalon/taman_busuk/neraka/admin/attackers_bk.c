/* admin.c
 * Ashlar, 2 Sep 97
 * This object handles remembering of attackers
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

// #define DEBUG(x)    (find_player("ashlar")->catch_msg("NATTACK: " + x + "\n"))

#define DELAY 120.0

int gSaveAlarm;
int gAutoAttack;
mapping gNames;
/* gNames is a mapping defined like this:

 name : ({ time of last attack, reputation, last short desc })

 */
#define LAST_ATTACK(x)  (x)[0]
#define REPUTATION(x)   (x)[1]
#define LAST_SHORT(x)   (x)[2]

#define SAVE_FILE   NERAKA + "admin/attackers_save"

/*
 * Function name: save_info
 * Description:   Saves the current attackers info
 */
static void
save_info()
{
    if (mappingp(gNames))
    {
        save_map(gNames, SAVE_FILE);
    }
}

/*
 * Function name: restore_info
 * Description:   Restores saved attackers info (after reboot for instance)
 */
static void
restore_info()
{
    if (file_size(SAVE_FILE + ".o") > 0)
    {
        gNames = restore_map(SAVE_FILE);
    }
}

void
create_room()
{
    set_short("Attackers Admin");
    set_long("This is the administration object for attackers of Neraka.\n");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    gSaveAlarm = set_alarm(DELAY, DELAY, save_info);

    setuid();
    seteuid(getuid());
    restore_info();
}

/*
 * Function name: query_know_person
 * Description:   checks if a guard knows a person (in this case, it means
 *                know that the person is an attacker)
 * Arguments:     object guard - the guard
 *                object person - the person
 * Returns:       1 - The person is recognized as an attacker, 0 otherwise
 */
public int
query_know_person(object guard, object person)
{
    int id_diff;
    mixed *file;

    /* sanity check */
    if (!person || !interactive(person))
        return 0;

    if (person->query_dragonarmy_occ_member())
	return 0;

    if (person->query_pot_member())
        return 0;

    if (mappingp(gNames))
        file = gNames[person->query_real_name()];

    /* We have no file on the person, and can therefore not recognize him */
    if (!pointerp(file))
        return 0;

    /* If we can't see the person, we can't recognize him */
    if (objectp(guard) && (!CAN_SEE(guard, person) || !CAN_SEE_IN_ROOM(guard)))
        return 0;

    /* Calculate the id_diff of the person */
    id_diff = (time() - LAST_ATTACK(file)) - REPUTATION(file);
    if (person->query_nonmet_name() != LAST_SHORT(file))
        id_diff = (id_diff * 3) / 2;

    if (!objectp(guard) && (id_diff < 100000))
    {
        return 1;
    }

    if (objectp(guard) && (guard->query_stat(SS_INT) * 1000) > id_diff)
    {
        /*
        DEBUG(guard->query_name() + " successfully identified " +
        person->query_name() + " as an attacker.");
        */

        gAutoAttack =
        ((REPUTATION(file) / (time() - LAST_ATTACK(file) + 1)) > 10 ? 1 : 0);

        /*
        DEBUG("gAutoAttack = " + gAutoAttack);
        */
        
        return 1;
    }
    else
    {
        gAutoAttack = 0;
        return 0;
    }
}

/*
 * Function name: query_auto_attack
 * Description:   Checks whether a person is someone to attack on sight.
 * Arguments:     object guard - the guard that might do the attacking
 *                object person - the person to autoattack
 *                [if neither of these arguments are specified, it returns
 *                the autoattack consideration based on the last call to
 *                query_know_person]
 * Returns:       1 - By all means, autoattack him. 0 - The defence of the
 *                    city does not require autoattack (the guard might do
 *                    so anyway, depends on the monster I guess)
 */
varargs public int
query_auto_attack(object guard, object person)
{
    if (person->query_dragonarmy_occ_member())
	return 0;

    if (person->query_pot_member())
        return 0;

    if (guard || person)
    {
        gAutoAttack = 0;
        query_know_person(guard,person);
    }

    return gAutoAttack;
}

/*
 * Function name: add_reputation
 * Description:   Adds reputation to a person depending on what he has
 *                done
 * Arguments:     object person - the file to change
 *                int reputation - the reputation units to change, use defines
 *                CRIME_xxx
 */
public void
add_reputation(object person, int reputation)
{
    mixed *file;

    if (!person || !interactive(person))
        return;

    if (mappingp(gNames))
        file = gNames[person->query_real_name()];

    if (pointerp(file))
    {
        int t = time();
        int r;
    
        r = REPUTATION(file) - (t - LAST_ATTACK(file)) + reputation;
        LAST_ATTACK(file) = t;

        if (r < 0)
            r = 0;
            
        REPUTATION(file) = r;

        if ((LAST_SHORT(file) != person->query_nonmet_name()) && !random(3))
            LAST_SHORT(file) = person->query_nonmet_name();

        gNames[person->query_real_name()] = file;
    }
    else
    {
        file = ({ time(), reputation, person->query_nonmet_name() });

        if (mappingp(gNames))
            gNames += ([ person->query_real_name() : file ]);
        else
            gNames = ([ person->query_real_name() : file ]);
    }
}

/*
 * Function name: remove_attacker
 * Description:   remove the file on someone for some reason
 * Arguments:     string name - the name of the file to remove
 *                string reason - the reason for removing the file
 * Returns:       a string with a textual result.
 * Note:          This is intended as an adjustment function called by
 *                a wizard. You must supply a reason why the file is to
 *                be removed, call the function like this:
 *                  Call ! remove_attacker name%%reason
 *                when standing in the room to get it to work.
 */
public nomask string
remove_attacker(string name, string reason)
{
    if (!stringp(name))
        return "Remove whom?\n";
    if (!stringp(reason))
        return "You must specify a reason.\n";

    if (!mappingp(gNames) || !pointerp(gNames[name]))
        return "No such file exists.\n";

    gNames = m_delete(gNames, name);
    return "Ok.\n";
}

/*
 * Function name: clean_registry
 * Description:   Removes old records from the attackers registry.
 */
public void
clean_registry()
{
    string *names;
    int i, sz, t;

    if (!mappingp(gNames))
        return;

    names = m_indexes(gNames);

    sz = sizeof(names);
    t = 0;

    for (i = 0; i < sz; i++)
    {
    	mixed *file;

        file = gNames[names[i]];

        if ((time() - LAST_ATTACK(file)) - REPUTATION(file) > 100000)
        {
            find_player("ashlar")->catch_msg("Removed " + names[i] + " from file.\n");
            t++;
            remove_attacker(names[i], " clean_registry update ");
        }
    }
    find_player("ashlar")->catch_msg("Total " + t + " removed, leaving " + (sz - t) + ".\n");
}
        
    
    
