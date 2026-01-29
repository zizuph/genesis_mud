/*
 *  /d/Emerald/common/guild/aod/rooms/chaos_area.c
 *
 *  This is the room right outside both the Repository of Skulls and
 *  the Darkling Tower at the Army of Darkness Headquarters.
 *
 *  Copyright (c) May 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
inherit AOD_ROOM_DIR + "blackwall_room";

/* Prototypes */
public void        create_blackwall_room();
public int         climb_steps(string arg);
public void        init();


/*
 * Function name:        create_blackwall_room
 * Description  :        set up the room
 */
public void
create_blackwall_room()
{
    set_short("upon a high cliff near a massive structure");
    set_em_long("You stand upon a high cliff which has been leveled"
      + " flat by some unnatural process. Here, at the top of a"
      + " long series of stairs leading down the cliff, a massive"
      + " structure looms, radiating its penetrating orange glow"
      + " on all nearby surfaces.\n");

    add_item( ({ "cliff", "high cliff", "cliffs" }), 
        "This area appears to have once risen higher than its current"
      + " elevation. It has been shorn off, though, and a perfectly"
      + " flat plateau extends in a wide area all around, its surface"
      + " as smooth and polished as glass.\n");
    add_item( ({ "plateau", "flat plateau", "perfectly flat plateau" }),
        "No force of nature could have accomplished this. The"
      + " surface is a thing of wonder.\n");
    add_item( ({ "surface", "process", "unnatural process",
                 "ground", "floor" }),
        "The surface of the ground here is smooth as polished glass,"
      + " almost as if some extreme searing heat had cut it to a"
      + " perfect level and then melted it smooth.\n");
    add_item( ({ "stair", "stairs", "step", "steps", "stairway",
                 "series", "series of stairs", "series of steps", }),
        "The steps travel down the cliff to the west.\n");
    add_item( ({ "cliff to the west", "western cliff", "west" }),
        "The western cliff provides passage via a series of"
      + " steps.\n");
    add_item( ({ "glow", "orange glow", "penetrating glow",
                 "penetrating orange glow" }),
        "The glow from the vortex pulsates off all nearby surfaces"
      + " so much that the entire area almost feels alive.\n");

    add_outdoor_items();
    room_add_object(AOD_OBJ_DIR + "chaos_gate");

    add_exit("middle_ground", "down", 0, 3, 0);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest" }),
        "You walk along the edge of the plateau, but find no means"
      + " of travel in that direction.\n");
} /* create_blackwall_room */


/*
 * Function name:       climb_steps
 * Description  :       allow players to climb up the steps
 * Arguments    :       what the player typed after the verb
 * Returns      :       int 1 - success
 *                          0 - failure
 */
public int
climb_steps(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [series] [of] [stone] 'step' / 'steps' / 'stair'"
      + " / 'stairs' / 'stairway'"))
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player <down> here using"
          + " command(). Since you are a wizard, you'll have to do it"
          + " manually by just typing it yourself.\n");
        return 1;
    }

    this_player()->command("$down");
    return 1;
} /* climb_steps */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action("climb_steps", "climb");
} /* init */