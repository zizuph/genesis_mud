/* File         : /d/Khalakhor/std/npc/elf.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : March 1, 1999         
 * Purpose      : Khalakhor standard elf npc.   
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
reset_khalakhor_elf()
{
}

public nomask void
reset_khalakhor_monster()
{
    reset_khalakhor_elf();
}

/* Function name:  create_khalakhor_elf
 * Description:    The constructor function
 *                 used to create the elf
 */
public void create_khalakhor_elf()
{
}

/* Function name:  create_khalakhor_monster (MASKED)
 * Description:    The Khal standard constructor function set
 *                 as nomask so DO NOT define this function
 *                 in anything that inherits this file.
 *                 You must use create_khalakhor_elf to
 *                 create your elf.
 */
public nomask void
create_khalakhor_monster()
{
    set_name("_Khalakhor_elf");
    set_race_name("elf");

    add_prop(LIVE_I_QUICKNESS, 60);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(LIVE_I_SEE_INVIS, 1);

    add_prop(OBJ_I_RES_AIR, 10);
    add_prop(OBJ_I_RES_DEATH, 60);
    add_prop(OBJ_I_RES_ELECTRICITY, 5);
    add_prop(OBJ_I_RES_MAGIC, 20);
    add_prop(OBJ_I_RES_POISON, 5);

    create_khalakhor_elf();
    reset_khalakhor_monster();
}

/*
 * Function name: query_khalakhor_elf
 * Description  : Check to see if this is a Khalakhor elf.
 * Arguments    : n/a
 * Returns      : 1 - if a elf
 */
public int
query_khalakhor_elf()
{
    return 1;
}
