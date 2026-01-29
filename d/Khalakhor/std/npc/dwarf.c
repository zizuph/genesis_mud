/* File         : /d/Khalakhor/std/npc/dwarf.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 1, 1999         
 * Purpose      : Khalakhor standard dwarf npc,   
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
reset_khalakhor_dwarf()
{
}

public nomask void
reset_khalakhor_monster()
{
    reset_khalakhor_dwarf();
}

/* Function name:  create_khalakhor_dwarf
 * Description:    The constructor function
 *                 used to create the dwarf
 */
public void create_khalakhor_dwarf()
{
}

/* Function name:  create_khalakhor_monster (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_dwarf to
 *                 create your monster.
 */
public nomask void
create_khalakhor_monster()
{
    set_name("_Khalakhor_dwarf");
    set_race_name("dwarf");

    add_prop(LIVE_I_QUICKNESS, -5);
    add_prop(LIVE_I_SEE_DARK, 5);

    add_prop(OBJ_I_RES_DEATH, 5);
    add_prop(OBJ_I_RES_EARTH, 20);
    add_prop(OBJ_I_RES_MAGIC, 40);
    add_prop(OBJ_I_RES_POISON, 50);

    create_khalakhor_dwarf();
    reset_khalakhor_monster();
}

/*
 * Function name: query_khalakhor_dwarf
 * Description  : Check to see if this is a Khalakhor dwarf.
 * Arguments    : n/a
 * Returns      : 1 - if a dwarf
 */
public int
query_khalakhor_dwarf()
{
    return 1;
}
