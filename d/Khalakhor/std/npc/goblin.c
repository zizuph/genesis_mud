/* File         : /d/Khalakhor/std/npc/goblin.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 1, 1999         
 * Purpose      : Khalakhor standard goblin npc.   
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

public void
reset_khalakhor_goblin()
{
}

public nomask void
reset_khalakhor_monster()
{
    reset_khalakhor_goblin();
}

/* Function name:  create_khalakhor_goblin
 * Description:    The constructor function
 *                 used to create the goblin
 */
public void
create_khalakhor_goblin()
{
}

/* Function name:  create_khalakhor_monster (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_goblin to
 *                 create your monster.
 */
public nomask void
create_khalakhor_monster()
{
    set_name("_Khalakhor_goblin");
    set_race_name("goblin");

    add_prop(LIVE_I_QUICKNESS, 10);
    add_prop(LIVE_I_SEE_DARK, 10);

    add_prop(OBJ_I_RES_ACID, 5);
    add_prop(OBJ_I_RES_COLD, 10);
    add_prop(OBJ_I_RES_DEATH, 5);
    add_prop(OBJ_I_RES_EARTH, 40);
    add_prop(OBJ_I_RES_LIFE, 20);
    add_prop(OBJ_I_RES_MAGIC, 10);
    add_prop(OBJ_I_RES_POISON, 5);

    create_khalakhor_goblin();
    reset_khalakhor_monster();
}

/*
 * Function name: query_khalakhor_goblin
 * Description  : Check to see if this is a Khalakhor goblin.
 * Arguments    : n/a
 * Returns      : 1 - if a goblin
 */
public int
query_khalakhor_goblin()
{
    return 1;
}
