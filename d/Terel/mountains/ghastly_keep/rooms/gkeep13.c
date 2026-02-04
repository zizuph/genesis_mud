/* /d/Terel/mountain/ghastly_keep/ghastly_keep/rooms/gkeep13.c
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

    add_exit(GKEEP + "gkeep10",       "northeast");
    add_exit(GKEEP + "gkeep14",      "east");
    add_exit(GKEEP + "gkeep9",       "northwest");

    add_npc(GKEEP_NPC +"g_sentry", random(3));
    add_npc(GKEEP_NPC +"g_sentinel", random(3));

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
