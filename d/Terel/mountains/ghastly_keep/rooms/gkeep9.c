/* /d/Terel/mountain/ghastly_keep/ghastly_keep/gkeep9.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

#include "defs.h";

inherit GKEEP_STD_ROOM;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    set_area(GKEEP_LVL1);
    update_longdesc();

    add_exit(GKEEP + "gkeep6",       "north");
    add_exit(GKEEP + "gkeep13",      "southeast");

    add_npc(GKEEP_NPC +"g_sentry", random(2));
    add_npc(GKEEP_NPC +"g_sentinel", random(2));

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    
}
