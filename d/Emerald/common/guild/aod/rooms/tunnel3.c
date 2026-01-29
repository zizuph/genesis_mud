/*
 *  /d/Emerald/common/guild/aod/rooms/tunnel3.c
 *
 *  This is a connecting tunnel in the Army of Darkness guildhall.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";

/* prototypes */
public void        create_cave_room();


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("at the southern end of a long tunnel");
    set_em_long("The massive tunnel rounds a corner here, heading"
      + " both northwest and northeast. A dull roaring sound, broken"
      + " by loud strikes of metal on metal issues from a corridor"
      + " which travels east.\n");

    add_item( ({ "tunnel", "long tunnel", "massive tunnel" }),
        "The tunnel is enormous, and could easily allow ten men"
      + " walking abreast to pass by. It rounds a bend here.\n");
    add_item( ({ "bend", "corner" }),
        "The tunnel rounds it.\n");
    add_item( ({ "sound", "roaring", "roaring sound", "strikes",
                 "loud strikes" }),
        "Sound isn't particularly visible. Try listening instead.\n");
    add_item( ({ "corridor" }),
        "The corridor to the east is lit by a menacing red glow.\n");
    add_item( ({ "glow", "menacing glow", "red glow",
                 "menacing red glow" }),
        "It flickers like something near a campfire.\n");
    add_item( ({ "fire", "campfire" }),
        "Hard to be sure from here. Travel east and see for yourself.\n");
    add_cmd_item( ({ "sound" }),
                  ({ "listen", "hear" }),
        "You hear two sounds - a dull roar and loud strikes.\n");
    add_cmd_item( ({ "roar", "dull roar" }),
                  ({ "listen", "hear" }),
        "The roar is constant and somewhat menacing.\n");
    add_cmd_item( ({ "strike", "strikes", "loud strike",
                     "loud strikes" }),
                  ({ "listen", "hear" }),
        "The strikes sound like the clash of metal.\n");

    add_cave_items();
    add_spike("tunnel3");

    add_exit("tunnel2", "northwest");
    add_exit("tunnel4", "northeast");
    add_exit("forge", "east");
} /* create_cave_room */