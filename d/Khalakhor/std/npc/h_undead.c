/* File         : /d/Khalakhor/std/npc/h_undead.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 1, 1999         
 * Purpose      : Khalakhor standard undead humanoid npc.   
 * Related Files: /std/monster.c
 *                /d/Khalakhor/std/monster.c
 * Comments     :
 * Modifications: Improved and updated - Teth, Jan 27 2002
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

inherit STDMONSTER;

#define LIVE_I_NO_DRAGONFEAR   "_live_i_no_dragonfear"

public void
reset_khalakhor_hundead()
{
}

public nomask void
reset_khalakhor_monster()
{
    reset_khalakhor_hundead();
}

/* Function name:  create_khalakhor_hundead
 * Description:    The constructor function
 *                 used to create the undead humanoid
 */
public void create_khalakhor_hundead()
{
}

/* Function name:  create_khalakhor_monster (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_hundead
 *                 to create your monster.
 */
public nomask void
create_khalakhor_monster()
{
    set_name("_Khalakhor_hundead");

    add_prop(LIVE_I_NO_DRAGONFEAR, 1);

    // Raise this prop number in your undeads.
    add_prop(LIVE_I_UNDEAD, 1);
    
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    create_khalakhor_hundead();
    reset_khalakhor_monster();
}

/*
 * Function name: query_khalakhor_hundead
 * Description  : Check to see if this is a Khalakhor humanoid
 *                undead.
 * Arguments    : n/a
 * Returns      : 1 - if a humanoid undead
 */
public int
query_khalakhor_hundead()
{
    return 1;
}
