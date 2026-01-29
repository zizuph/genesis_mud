/*
 *
 */
#pragma strict_types
#include "imbuement.h"

#include <macros.h>
#include <files.h>
#include <time.h>

inherit "/std/object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Prototypes */
public string   count();
public int      resetcount();

/* Global Variables */
int             weapons = 0, armours = 0, count_time = time();

/*
 * Function name:        create
 * Description  :        set up
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());
    
    LISTENER_ADD(this_object());
    set_name("counter");
    set_long(count);
} /* create */

public void
init()
{
    add_action(resetcount, "resetcount");
}

/*
 * Function name:        notify_new_object
 * Description  :        called when something is cloned
 */
public void
notify_new_object(object obj)
{
    if (!obj)
        return;
    if (!environment(obj))
        return;

    if (!environment(obj)->query_npc())
        return;

    if (!environment(environment(obj)))
        return;

    if (!wildmatch("/d/*", MASTER_OB(environment(environment(obj)))))
        return;

    if (IS_WEAPON_OBJECT(obj))
    {
        weapons++;
        return;
    }

    if (IS_ARMOUR_OBJECT(obj))
    {
        armours++;
        return;
    }
}

public string
count()
{
    return("Weapons: " + weapons + "  Armours: " + armours + "  Total: " + 
    (weapons + armours) + "\n<resetcount> to reset\n"
    + "Time since last reset: " + CONVTIME(time() - count_time) + "\n");
}

public int
resetcount()
{
    weapons = 0;
    armours = 0;
    count_time = time();
    write("Counts reset.\n");
    return 1;
}
