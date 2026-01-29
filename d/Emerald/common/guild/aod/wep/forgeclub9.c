/*
 *  /d/Emerald/common/guild/aod/wep/forgeclub9.c
 *
 *  One of the 10 club types that can be forged at the Army of Darkness
 *  Headquarters. The club's quality is on a scale of 0-9 with 9
 *  being highest. Look at the filename to see what level this one
 *  is. For complete information on the details of each club,
 *  refer to the inherited file.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 *
 *  2019-01-15: Carnak
 *      These items will now break from item expiration
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"

inherit AOD_WEP_DIR + "forged_weapon";


/* Prototypes */
public void        create_forged_weapon();


/*
 * Function name:        create_forged_weapon
 * Description  :        set up the weapon
 */
public void
create_forged_weapon()
{
    set_wep_level(9); /* sledgehammer of the colossus */

    setuid();
    seteuid(getuid());
} /* create_forged_weapon */


/*
 * Function name:        exa_this_weapon
 * Description  :        Yes, it is strange to mask the functionality
 *                       of exa/look, but here it is necessary to deal
 *                       with this unorthodox weapon name.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - we dealt with it in this function
 *                       0 - pass it on to the mudlib
 */
public int
exa_this_weapon(string arg)
{
    if (arg != "sledgehammer of the colossus" &&
        arg != "at sledgehammer of the colossus")
    {
        return 0;
    }

    write(long());
    return 1;
} /* exa_this_weapon */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(exa_this_weapon, "exa");
    add_action(exa_this_weapon, "look");
} /* init */

varargs void
remove_broken(int silent = 0)
{
    /* This was added so it can break from item expiration */
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);
    
    return;
}


int
set_dull(int du)
{
    return 0;
}


void
enter_env(object dest, object old)
{
    string  from = old->query_name();
    string  to = dest->query_name();

    ::enter_env(dest, old);

    if (!old)
    {
        from = "(none)";
    }
    else if (!interactive(old))
    {
        from = MASTER_OB(old);
    }
    else if (interactive(old))
    {
        from = upper_case(from);
    }

    if (!interactive(dest))
    {
        to = MASTER_OB(dest);
    }
    else if (interactive(dest))
    {
        to = upper_case(to);
    }

    write_file(AOD_LOG_DIR + "hammer",
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ")"
      + "\n\tObject: #" + OB_NUM(this_object())
      + "\n\tMoved From: " + from
      + "\n\tMoved To: " + to + "\n");
}
