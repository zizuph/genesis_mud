/*
 *  /d/Emerald/common/guild/aod/rooms/middle_ground.c
 *
 *  A connecting room leading toward the Army of Darkness guild.
 *
 *  Created May 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Emerald/std/room";


/* Prototypes */
public void        create_emerald_room();
public int         climb_steps(string arg);
public void        init();


/* 
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("on a steep slope heading up into the mountains");
    set_em_long("The incline of this slope is rather daunting as it"
      + " travels between the mountains to the north and lower"
      + " ground to the south. To the east and west, sheer cliffs"
      + " rise to form high walls on either side of this extremely"
      + " wide path. To the north, a black tower rises in the"
      + " distance. Just to the east, stone steps lead up into"
      + " the heights.\n");

    add_item( ({ "incline" }),
        "It is a rather severe angle. One needs sure footing on"
      + " such a slope.\n");
    add_item( ({ "angle" }),
        "Severe. Rather.\n");
    add_item( ({ "severe angle" }),
        "Yes, it is. Rather.\n");
    add_item( ({ "rather severe angle" }),
        "Oh, its as rather severe as angles get!\n");
    add_item( ({ "slope", "wide slope" }),
        "The slope travels between the lower ground to the south and"
      + " the dark mountains to the north.\n");
    add_item( ({ "mountain", "mountains", "blackwall mountains",
                 "dark mountains" }),
        "The Blackwall Mountains rise directly to the north, framing"
      + " a distant tower.\n");
    add_item( ({ "tower", "distant tower", "black tower" }),
        "The tower is yet too distant to make out much detail. It"
      + " is clearly quite massive.\n");
    add_item( ({ "lower ground", "south" }),
        "A ways to the south, at the base of the slope, lower ground"
      + " is indeed visible from here.\n");
    add_item( ({ "base", "base of the slope" }),
        "It is a ways to the south.\n");
    add_item( ({ "cliff", "cliffs", "sheer cliff", "sheer cliffs" }),
        "They form an aisle with this slope, leading north and"
      + " south. The eastern cliff opens upon stone steps leading"
      + " up.\n");
    add_item( ({ "wall", "walls", "high wall", "high walls" }),
        "The cliffs appear impervious.\n");
    add_item( ({ "path", "wide path", "extremely wide path" }),
        "The path has clearly been trod by massive feet.\n");
    add_item( ({ "footprint", "footprints", "print", "prints" }),
        "Only something horrifyingly huge could make such"
      + " prints!\n");
    add_item( ({ "steps", "stone steps", "step", "stone step",
                 "stair", "stairs", "stairway" }),
        "They lead directly up into the eastern cliffs.\n");
    add_item( ({ "eastern cliff", "east cliff", "eastern cliffs",
                 "east cliffs" }),
        "Embedded within them are stone steps leading up.\n");
    add_item( ({ "heights" }),
        "One can only guess what lies up there.\n");

    add_exit("courtyard", "north");
    add_exit("lower_ground", "south");
    add_exit("chaos_area", "up", 0, 3, 0);

    add_npc(AOD_NPC_DIR + "aod_ogre", 2);

    set_no_exit_msg( ({ "northeast", "east", "southeast", "southwest",
                        "west", "northwest" }),
        "The sheer cliff walls prevent movement in that direction.\n");
} /* create_emerald_room */


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
        "[up] [the] [stone] 'step' / 'steps' / 'stair' / 'stairs'"
      + " / 'stairway'"))
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player <up> here using"
          + " command(). Since you are a wizard, you'll have to do it"
          + " manually by just typing it yourself.\n");
        return 1;
    }

    this_player()->command("$up");
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
