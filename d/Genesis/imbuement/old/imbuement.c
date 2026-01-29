/*
 *  /d/Genesis/imbuement/imbuement.c
 *
 *  This is a library module that can be inherited by items in the game
 *  that are meant to get a roll at cloning for random magic mods being
 *  attached.
 *
 *  Created November 2009, by Cooper Sherry (Gorboth)
 */

#include "imbuement.h"
#include <macros.h>

/* Prototypes */
public void        initialize_imbuement();
public void        perform_mod();



/*
 * Function name:        init_imbuement
 * Description  :        At creation, we want this object, following
 *                       a brief delay, to try to roll for mods.
 */
public void
initialize_imbuement()
{
TELL_G("Okay ... lets do this.");
TELL_G("trying to init object");
    /* If the item is already modded, we do not re-roll! */
    if (this_object()->query_prop(IMBUE_TRY))  
    {
TELL_G("Already got the roll - from initialize_imbuement");
        return;
    }

TELL_G("okay ... lets try to call perform_mod");
    set_alarm(1.0, 0.0, &perform_mod());
} /* initialize_imbuement */


/*
 * Function name:        perform_mod
 * Descripton   :        Check to see where this item is. If it is
 *                       in the possession of an npc, we roll for
 *                       mods.
 */
public void
perform_mod()
{
    object    loc = environment(this_object());

TELL_G("perform_mod called");
    /* Lets check this one more time, just to be safe. */
    /* If the item is already modded, we do not re-roll! */
    if (this_object()->query_prop(IMBUE_TRY))  
    {
TELL_G("oops, already imbued, so we drop.");
        return;
    }

    setuid();
    seteuid(getuid());

    if (loc)
    {
        TELL_G("Looks like there is a location.");
    }
    else
    {
        TELL_G("No location!");
    }

TELL_G("not imbued yet, so continue");
TELL_G("loc = " + MASTER_OB(loc));
    if (living(loc) && !interactive(loc))
    {
TELL_G("Okay, calling the master!");
        IMBUE_MASTER->imbue_item(this_object());
    }

    return;
} /* perform_mod */
