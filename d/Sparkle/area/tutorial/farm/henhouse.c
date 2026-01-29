/*
 *  /d/Sparkle/area/tutorial/farm/henhouse.c
 *
 *  This henhouse is meant to function as an endless source of combat
 *  experience. Basically, my fear is that there could be times when
 *  there are too many people in the tutorial for the area to keep up
 *  with demand in terms of combat exp. These sorts of rooms should never
 *  exist in the regular game.
 *
 *  Created February 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit FARM_DIR + "crop_room";

#include <stdproperties.h>

/* prototypes */
public void        create_crop_room();
public void        reset_room();
public void        init();
public void        henhouse_cmd(string arg);


/*
 * Function name:        create_crop_room
 * Description  :        set up the room
 */
public void
create_crop_room()
{
    add_name("_tutorial_henhouse");
    set_short("a simple henhouse");
    set_long("This henhouse looks to have been nearly overrun by vermin!"
      + " Rabbit droppings are everywhere, and the hens have evacuated to"
      + " the yard leaving the roosts empty. A door leads southeast out"
      + " to the fields.\n\n");

    add_item( ({ "here", "area", "room", "henhouse", "house" }), long);
    add_item( ({ "floor", "ground", "floorboards", "board", "boards",
                 "floor board", "floor boards", "dropping", "droppings",
                 "rabbit droppings", "rabbit dropping", "filth", "down" }),
        "Ugh! The filth! The floorboards of the henhouse are covered"
      + " with rabbit droppings. Someone really ought to take care of"
      + " these vermin.\n");
    add_item( ({ "roost", "roosts" }),
        "It appears as if rabbits and hens do not get along. The roosts"
      + " have been evacuated.\n");
    add_item( ({ "ceiling", "rafters", "up", "roof" }),
        "In the rafters you spy a lone chicken, bukking nervously. It"
      + " appears as if she is too scared to come down.\n");
    add_item( ({ "chicken", "hen", "lone chicken", "lone hen" }),
        "She pleads at you: Buk buk ... bkaaaawk?\nShe probably wants you"
      + " to get rid of all these rabbits so she can come down.\n");
    add_item( ({ "chickens", "hens" }),
        "The hens all seem to have given the place over to the rabbit"
      + " population. They all have left!\n");
    add_item( ({ "wall", "walls" }),
        "The walls of the henhouse are rather dirty.\n");
    add_item( ({ "sky" }),
        "The sky is visible through the door to the southeast.\n");
    add_item( ({ "door", "doorway", "southeast", "field",
                 "fields" }),
        "Southeast, the fields are visible through the doorway.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("garlic_patch3", "southeast");

    clone_bunny(7, (one_of_list(
        ({ "baby", "bunny", "rabbit", "large", "jack"}))));
} /* create_silverdell */


/*
 * Function name:        reset_room
 * Description  :        fill the room with many bunnies!
 */
public void
reset_room()
{
    set_alarm(300.0, 0.0, &clone_bunny(7, (one_of_list(
        ({ "baby", "bunny", "rabbit", "large", "jack"})))));
} /* reset_room */


/*
 * Function name:        init
 * Description  :        disable the crop picking here
 */
public void
init()
{
    ::init();

    add_action(henhouse_cmd, "pick");
    add_action(henhouse_cmd, "get");
    add_action(henhouse_cmd, "dig");
    add_action(henhouse_cmd, "pull");
    add_action(henhouse_cmd, "reap");
    add_action(henhouse_cmd, "harvest");
} /* init */


/*
 * Function name:        henhouse_cmd
 * Description  :        Because we are inheriting the crop room,
 *                       we want to disable the ability to pick crops
 *                       here.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        0 - we send it to the mudlib
 */
public int
henhouse_cmd(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[a] [the] 'carrot' / 'carrots' / 'potato' / 'potatos'"
      + " / 'garlic' / 'garlics' / 'bulb' / 'bulbs' / 'radish'"
      + " / 'radishes' / 'turnip' / 'turnips' / 'crop' / 'crops'"))
    {
        return 0; /* let the mudlib handle it */
    }

    write("There is nothing planted here.\n");
    return 1;
} /* henhouse_cmd */
