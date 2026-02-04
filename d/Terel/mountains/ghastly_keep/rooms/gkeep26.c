/* /d/Terel/mountain/ghastly_keep/rooms/gkeep26.c
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

    set_area(GKEEP_LVL2);
    update_longdesc();

    add_exit(GKEEP + "gkeep23",       "northeast");
    add_exit(GKEEP + "gkeep27",       "east");
    add_exit(GKEEP + "gkeep30",       "southeast");
    add_exit(GKEEP + "gkeep29",       "southwest");
    add_exit(GKEEP + "gkeep25",       "west");
    add_exit(GKEEP + "gkeep22",       "northwest");

    add_npc(GKEEP_NPC +"g_sentinel", random(3));
    add_npc(GKEEP_NPC +"g_guardian", random(3));

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
