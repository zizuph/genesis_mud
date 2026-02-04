/* /d/Terel/mountain/ghastly_keep/ghastly_keep/rooms/gkeep3.c
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

#include <stdproperties.h>

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("Beneath the fallen temple");
    set_long("Beneath the fallen temple lies a narrow, humid room. "
          + "It is covered in rubble, roots and dead vermin. A small strip "
          + "of light from a crack in the ceiling allows you to see the "
          + "remnants of a pillaged burial chamber, nearly absorbed "
          + "by time itself. There is only one path out of here. An "
          + "enormous beastly skeleton is chained to the walls.\n");

    add_item( ("rubble"), "Rubble made out of "
               + "rough fragments of broken stone covers the area.\n");

    add_item( ({"roots", "vermin"}), "Old roots and dead vermin lay in heaps "
               + "at unnatural angle around the area.\n");

    add_item( ({"crack", "cracks"}), "Small cracks in the "
               + "ceiling allows pillars of light into the room.\n");

    add_item( ({"strip", "light", "ceiling"}), "A small crack in the "
               + "ceiling lets in a beam of light.\n");

    add_item( ({"chamber", "remnants"}), "Only the remnants are "
               + "left behind, pillaged and absorbed by time itself.\n");

    add_item( ({"beastly", "skeleton", "chain"}), "The skeleton "
              + "is chained to the wall, possibly for a crime committed a long "
              + "time ago?\n");

    add_item( ({"wall", "wall", "chain"}), "You find nothing of interest "
               + "besides the skeleton chained to it.\n");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

    set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    add_npc(GKEEP_NPC + "g_sentry",   2);
    add_npc(GKEEP_NPC + "g_sentinel", 2);

    add_exit(GKEEP + "gkeep2",   "west");

    add_prop(ROOM_I_INSIDE,         1);
    add_prop(ROOM_I_LIGHT,          1);
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
