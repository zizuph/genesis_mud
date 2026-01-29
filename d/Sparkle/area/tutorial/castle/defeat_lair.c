/*
 *  /d/Sparkle/area/tutorial/castle/defeat_lair.c
 *
 *  The version of the lair where one has defeated Krolock.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Definitions */
#define  TUTORIAL_CHAPTER    44  /* the chapter for the sign */

/* Prototypes */
public void        create_castle_room();
public string      describe(string arg);
public void        reset_room();
public int         query_occupied();
public void        init();
public int         get_heart(string arg);
public int         do_listen(string arg);



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
    add_item( ({ "altar" }), &describe("altar"));
    add_item( ({ "heart", "human heart", "withered heart",
                 "beating heart", "beating human heart",
                 "withered human heart" }), &describe("heart"));
    add_item( ({ "pedestal" }), &describe("pedestal"));

    add_castle_items();
    add_torch_items();

    add_exit("dungeon", "up");

    reset_room();
} /* create_castle_room */


/*
 * Function name:        describe
 * Description  :        provide state-dependant descriptions of a few
 *                       things.
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - the description
 */
public string
describe(string arg)
{
    switch (arg)
    {
        case "altar":
            if (present("_krolock_heart", this_player()))
            {
                return "The altar is carved with hideous demonic figures"
                 + " which seem to sneer at you with their twisted faces."
                 + " On top of the altar is an empty pedestal.\n";
            }

            return "The altar is carved with hideous demonic figures"
                 + " which seem to sneer at you with their twisted faces."
                 + " On top of the altar is a pedestal holding a withered,"
                 + " yet beating human heart.\n";
            break;
        case "pedestal":
            if (present("_krolock_heart", this_player()))
            {
                return "The pedestal upon the altar is empty.\n";
            }

            return "The pedestal upon the altar holds a beating human"
              + " heart.\n";
            break;
        case "heart":
            if (present("_krolock_heart", this_player()))
            {
                return "Upon the altar, you find no heart.\n";
            }

            return "This must be the heart of Baron von Krolock! It beats"
             + " with a weak, yet regular pulse. Looking at it, you begin"
             + " to feel ill.\n";
            break;
    }

    return ""; /* should never happen, but just in case */
} /* describe */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void
reset_room()
{
    object  baron;

    if (!query_occupied)
    {
        /*
         * These rooms are clones. We don't want them piling up. So,
         * if players aren't in them, and we have a reset, lets remove
         * them so they aren't cluttering up memory.
         */
        remove_object();
    }

    if (!present("_defeated_krolock"))
    {
        baron = clone_object(NPC_DIR + "defeated_krolock");
        baron->move(this_object());
    }

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/*
 * Function name:        query_occupied
 * Description  :        determine if there is a player in this
 *                       room. We only allow one at a time.
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
    add_action(do_listen, "listen");
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
    object  krolock;
    object  heart;

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

    if (present("_krolock_heart", this_player()))
    {
        write("You already have the Baron's heart.\n");
        return 1;
    }

    if (objectp(krolock = present("_defeated_krolock")))
    {
        if (!CHECK_TUTORIAL_BIT(OFFER_BIT))
        {
            krolock->make_offer(this_player());
            return 1;
        }

        krolock->command("emote wails in agony!");
        krolock->command("emote intones: I beg you! Reconsider my"
          + " offer!");
    }

    write("You step up to the altar, and take the heart from the"
      + " pedestal.\n");

    heart = clone_object(OBJ_DIR + "krolock_heart")->move(this_player());

    return 1;
} /* get_heart */


/*
 * Function name:        do_listen
 * Description  :        Allow the player to listen to krolock's offer
 *                       once again.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_listen(string arg)
{
    object  krolock;

    if (!strlen(arg))
    {
        write("Listen to whom or what?\n");
        return 1; /* to avoid the mudlib response */
    }

    if (!parse_command(arg, ({}),
        "[to] [the] [stately] [old] [nearly] [nearly-dead] [dead]"
      + " 'baron' / 'krolock' / 'vampire' / 'offer'"))
    {
        write("What?\n");
        return 1; /* bad syntax - still want to avoid mudlib response */
    }

    if (!objectp(krolock = present("_defeated_krolock", this_object())))
    {
        notify_fail("Aparently, there is no one here to listen to.\n");
        return 1;
    }

    write("You decide to listen to the Baron's offer once again.\n");
    krolock->make_offer(this_player());

    return 1;
} /* do_listen */
