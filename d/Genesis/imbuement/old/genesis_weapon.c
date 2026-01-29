/*
 *  /d/Genesis/imbuement/genesis_weapon.c
 *
 *  This object is used to allow imbuement to take place in objects
 *  that inherit it.
 *
 *  Created November 2009, by Cooper Sherry (Gorboth)
 */

#include "imbuement.h"

inherit "/std/weapon";
inherit IMBUE_DIR + "imbuement.c";


/* Prototypes */
nomask void        create_weapon();
public void        create_genesis_weapon();
public void        enter_env(object dest, object old);

/* Global Variables */
public int         Imbue_Check = 0;


/*
 * Function name:        create_weapon
 * Description  :        The base constructor function
 */
nomask void
create_weapon()
{
    create_genesis_weapon();
} /* create_weapon */


/*
 * Function name:        create_genesis_weapon
 * Description  :        A dummy constructor to be redefined in inheriting
 *                       code.
 */
public void
create_genesis_weapon()
{
} /* create_genesis_weapon */


/*
 * Function name:        enter_env
 * Description  :        when the weapon enters a new environment,
 *                       if the environment is an npc and this is the
 *                       first locaton we've entered, we try to mod
 *                       the item.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (this_object()->query_prop(IMBUE_TRY) || Imbue_Check)
    {
        return;
    }

    if (dest->query_npc())
    {
        initialize_imbuement();
    }

    /* This tells us not to try to imbue this item again from the
     * enter_env function. It might be possible to imbue it some other
     * way, still, so we do not add the IMBUE_TRY prop.
     */
    Imbue_Check = 1;
} /* enter_env */