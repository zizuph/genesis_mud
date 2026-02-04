/* /d/Terel/mountains/ghastly_keep/rooms/gkeep4.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 * Znagsnuf
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  28/04-17                   Added ROOM_I_INSIDE                     Znagsnuf
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
    update_longdesc();

    set_short("Beneath the fallen castle");
    set_long("Beneath the fallen castle lies a narrow, humid room. "
    +"It is covered in rubble, roots and dead vermin. The blackness "
    +"engulfing the room seems to seep from the very pores of what "
    +"surrounds you. The blackness is formed from some primeval hatred, and "
    +"the collective despair of all those it has taken before. The air "
    +"smells as if it hasn't moved for years, festering like a "
    +"stagnant pool of water. You can feel the wind shifting as the "
    +"spirits roam and wander the soulless ruins. You can sense the "
    +"evil presence within it.\n");

    add_item( ("rubble"), "Rubble made out of "
               +"rough fragments of broken stone covers the area.\n");

    add_item( ({"roots", "vermin"}), "Roots, and dead vermin lay in heaps "
               +"at unnatural angles around the area..\n");

    add_item( ({"black", "blackness", "darkness"}), "The blackness "
               +"is formed from some primeval hatred, and the collective "
               +"despair of all those it has taken before.\n");

    add_item( ({"water", "air", "smell", "pool"}), "The air smells as if "
               +"it hasn't moved for years, festering like a stagnant pool "
               +"of water.\n");

    add_item( ({"wind", "spirit", "spirits", "ruin", "ruins"}), "You "
               +"can feel the wind shifts as the spirits roam and wonder "
               +"the soulless ruins. You can sense the evil presence "
               +"within it.\n");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

    set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    add_exit(GKEEP + "gkeep2",      "east");
    add_exit(GKEEP + "gkeep7",      "southeast");
    add_exit(GKEEP + "gkeep6",      "southwest");
    add_exit(GKEEP + "gkeep5",      "west");

    add_npc(GKEEP_NPC +"g_sentry",   2);
    add_npc(GKEEP_NPC +"g_sentinel", 2);
    add_npc(GKEEP_NPC +"g_ghost",    1);

    add_prop(ROOM_I_INSIDE,         1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
}
