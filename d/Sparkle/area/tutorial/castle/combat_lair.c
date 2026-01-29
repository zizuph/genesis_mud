/*
 *  /d/Sparkle/area/tutorial/castle/combat_lair.c
 *
 *  The version of the lair where combat takes place.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Prototypes */
public void        create_castle_room();
public void        reset_room();
public int         query_occupied();
public void        init();
public int         get_heart(string arg);


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("within an ominous darkened chamber.");
    set_long("You are within an ominous darkened chamber. The walls"
      + " of this hideous lair are streaked with blood and ashes."
      + " A long aisle bordered by candles leads up to an altar"
      + " which glows with a malevolent and unholy light. A staircase"
      + " winds up into the ceiling.\n\n");

    add_item( ({ "here", "room", "area", "chamber", "lair",
                 "hideous lair" }), long);
    add_item( ({ "wall", "walls" }),
        "The walls of this chamber are long and dark. They appear to"
      + " have been smeared with blood and ashes.\n");
    add_item( ({ "blood", "ashes", "blood and ashes", "ash",
                 "sign", "signs", "demonic sign", "demonic signs" }),
        "Blood and ashes have been smeared along the walls, painting"
      + " demonic signs which are gruesome and horrible to look"
      + " upon.\n");
    add_item( ({ "aisle", "long aisle", "candles", "candle" }),
        "Candles border a long aisle which lead from the center"
      + " of the chamber to the altar.\n");
    add_item( ({ "altar" }),
        "The altar is carved with hideous demonic figures which seem"
      + " to sneer at you with their twisted faces. On top of the"
      + " altar is a pedestal holding a withered, yet beating human"
      + " heart.\n");
    add_item( ({ "heart", "human heart", "withered heart",
                 "beating heart", "beating human heart",
                 "withered human heart" }),
        "This must be the heart of Baron von Krolock! It beats with"
      + " a weak, yet regular pulse. Looking at it, you begin to feel"
      + " ill.\n");
    add_item( ({ "pedestal" }),
        "The pedestal atop the altar holds a beating human heart.\n");

    add_castle_items();
    add_torch_items();

    add_exit("dungeon", "up");

    //This room has its own instancing system.
    instance_entrance = 1;

    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void
reset_room()
{
    object  baron;

    if (!present("_tutorial_krolock"))
    {
        baron = clone_object(NPC_DIR + "krolock");
        baron->move(this_object());
        baron->arm_me();
        return;
    }

    if (!query_occupied())
    {
        /*
         * These rooms are clones. We don't want them piling up. So,
         * if players aren't in them, and we have a reset, lets remove
         * them so they aren't cluttering up memory.
         */
        remove_object();
        return;
    }

} /* reset_room */


/*
 * Function name:        query_occupied
 * Description  :        determine if there is a player in this
 *                       room.
 * Returns      :        int 1 - occupied, 0 - not so
 *
 * This function was copied from /d/Terel/cedric/guild/cubicle.c
 * originally coded, it seems, by Jorl in 1993.
 */
public int
query_occupied()
{
    object  *room_list;
    int     i;
    
    room_list = all_inventory(this_object());
    for (i = 0; i < sizeof(room_list); i++)
    {
        if (interactive(room_list[i]))
            return 1;
    }
    return 0;
} /* query_occupied */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_heart, "get");
    add_action(get_heart, "take");
    add_action(get_heart, "lift");
    add_action(get_heart, "remove");
} /* init */


/*
 * Function name:        get_heart
 * Description  :        allow players to try to get the heart
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - otherwise
 */
public int
get_heart(string arg)
{
    object  destination;

    if (!strlen(arg))
    {
        return 0; /* the mudlib can handle the notify_fail */
    }

    if (!parse_command(arg, ({}),
        "[the] [withered] [beating] [human] 'heart' [from] [the] [altar]"
      + " [pedestal]"))
    {
        return 0; /* bad syntax */
    }

    if (present("_tutorial_krolock"))
    {
        write("The Vampire will not allow you to approach the altar.\n");
        return 1;
    }

    /* this should never happen, but we'd better put it here just in
     * case.
     */
    write("You take a few steps closer to the altar, approaching the"
      + " heart on the pedestal.\n");

    destination = clone_object(CASTLE_DIR + "defeat_lair");
    this_player()->add_prop(LAIR_PROP, destination);
    this_player()->move_living("M",
        this_player()->query_prop(LAIR_PROP)->get_this_object(), 1, 1);
    return 1;
} /* get_heart */
