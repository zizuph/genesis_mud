/*
 *  /d/Emerald/blackwall/delrimmon/npc/catapult_orc.c
 *
 *  These orcs will be guarding the boss npc in the caves. If they
 *  are present, the player may not climb the ledge to attack the
 *  boss.
 *
 *  Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/npc/del_rimmon_orc.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon_orc();

/*
 * Function name:        create_del_rimmon_orc
 * Description  :        set up the npc
 */
public void
create_del_rimmon_orc()
{
    Chief = 1;

    add_name("_guardian_orc");

} /* create_del_rimmon_orc */


