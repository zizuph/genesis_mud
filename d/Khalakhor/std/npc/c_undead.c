/* File         : /d/Khalakhor/std/npc/c_undead.c
 * Creator      : Teth@Genesis
 * Copyright    : Daniel Mosquin
 * Date         : March 1, 1999
 * Purpose      : This is the base creature undead npc file.
 * Related Files: /std/creature.c
 *              : /d/Khalakhor/std/creature.c
 * Comments     : 
 * Modifications: Improved and updated - Teth, Jan 27 2002
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

inherit STDCREATURE;

#define LIVE_I_NO_DRAGONFEAR    "_live_i_no_dragonfear"

public void
reset_khalakhor_cundead()
{
}

public nomask void
reset_khalakhor_creature()
{
    reset_khalakhor_cundead();
}

/* Function name:  create_khalakhor_cundead
 * Description:    The constructor function
 *                 used to create the undead creature
 */
public void
create_khalakhor_cundead()
{
}

/* Function name:  create_khalakhor_creature (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_c_undead to
 *                 create your undead creature.
 */
public nomask void
create_khalakhor_creature()
{
    set_name("_Khalakhor_cundead");

    add_prop(LIVE_I_NO_DRAGONFEAR, 1);

    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    // Raise this prop number in your undeads.
    add_prop(LIVE_I_UNDEAD, 1);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    create_khalakhor_cundead();
    reset_khalakhor_creature();
}

/*
 * Function name: query_khalakhor_cundead
 * Description  : Check to see if this is a Khalakhor creature
 *                undead.
 * Arguments    : n/a
 * Returns      : 1 - if a creature undead
 */
public int
query_khalakhor_cundead()
{
    return 1;
}
