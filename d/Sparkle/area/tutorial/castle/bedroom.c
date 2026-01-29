/*
 *  /d/Sparkle/area/tutorial/castle/bedroom.c
 *
 *  The Bedchambers of Baron von Krolock.
 *
 *  Created October 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

#include <stdproperties.h>

/* Global Variables */
public int         Open = 0;  /* is the drawer open? */

/* Prototypes */
public void        create_castle_room();
public void        enter_inv(object ob, object from);
public string      describe(string arg);
public void        init();
public int         get_key(string arg);
public int         mess_with_drawer(string arg);

/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("in a splendid bedchamber");
    set_long("You have entered a splendid bedchamber. Tapestries"
      + " line the stone walls, and a lush carpet is spread along"
      + " the floor. A small nightstand rests beside a luxurious"
      + " coffin which lies on a raised dais. An archway leads"
      + " south to a hallway.\n\n");

    add_item( ({ "here", "area", "room", "chamber", "bedchamber" }),
        long);
    add_item( ({ "coffin", "bed", "casket", "luxurious coffin" }),
        "The coffin rests on a raised dais exactly where one would"
      + " expect a bed to be. It seems that the occupant does not"
      + " sleep in the manner of mortal men. A small nightstand rests"
      + " beside the dais upon which the coffin lies.\n");
    add_item( ({ "dais", "raised dais" }),
        "A coffin rests atop the dais. Beside it, a small nightstand"
      + " has been positioned.\n");
    add_item( ({ "nightstand", "stand", "small stand",
                 "small nightstand" }), &describe("stand"));
    add_item( ({ "key", "large key" }), &describe("key"));
    add_item( ({ "drawer" }), &describe("drawer"));
    add_item( ({ "south", "arch", "archway", "hall", "hallway" }),
        "The hallway is visible through an archway to the south.\n");

    add_castle_items();
    add_torch_items();

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit("hallway_6n", "south");

    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        make sure the drawer is closed
 */
public void
reset_room()
{
    Open = 0;
} /* reset_room */


/* 
 * Function name: enter_inv
 * Description:   Broadcast the Baron's voice to players who enter
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    string    txt = "";

    ::enter_inv(ob, from);

    if (!strlen(from->query_trigger_room()) ||
        !interactive(ob))
    {
        return;
    }

    set_this_player(ob);

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        txt = "WELCOME, FAITHFUL SERVANT.";
    }
    else
    {
        txt = one_of_list( ({
            "LEAVE MY PERSONAL CHAMBERS AT ONCE!",
            "COMING HERE, YOU HAVE SENTENCED YOURSELF TO DEATH, FOOL!",
            "TOUCH ONE THING IN MY BEDROOM, AND YOU SHALL DIE!" }) );
    }

    set_alarm(0.5, 0.0, &broadcast(txt, ob));
} /* enter_inv */


/*
 * Function name:        describe
 * Description  :        provide a status dependant descriptions
 * Arguments    :        string arg - what are we describing?
 * Returns      :        string - various descriptions of things
 */
public string
describe(string arg)
{
    switch(arg)
    {
        case "stand":
            if (Open)
            {
                return "The stand rests next to the dais. A drawer"
                  + " near to the top of the stand has been"
                  + " opened. Perhaps you could examine it?\n";
            }

            return "The stand rests beside the dais. You notice a"
              + " closed drawer near to the top of the stand.\n";
            break;
        case "key":
            if (present("_tutorial_castle_key", this_player()) ||
                !Open)
            {
                return "You find no key.\n";
            }

            return "You see a large key inside the drawer.\n";
            break;
        case "drawer":
            if (!Open)
            {
                return "The drawer is closed.\n";
            }

            if (!present("_tutorial_castle_key", this_player()))
            {
                return "You see a large key inside the drawer.\n";
            }

            Open = 0;
            return "The drawer is empty, so you close it.\n";
            break;
    } /* switch(arg) */
} /* describe */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_key, "get");
    add_action(get_key, "take");
    add_action(get_key, "remove");
    add_action(get_key, "pick");
    add_action(get_key, "put");
    add_action(get_key, "return");
    add_action(mess_with_drawer, "open");
    add_action(mess_with_drawer, "pull");
    add_action(mess_with_drawer, "push");
    add_action(mess_with_drawer, "close");
    add_action(mess_with_drawer, "lock");
    add_action(mess_with_drawer, "unlock");
} /* init */


/*
 * Function name:        get_key
 * Description  :        allow players to take the key from the drawer
 * Arguments    :        string arg - what the player typed after the
 *                                    verb.
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
get_key(string arg)
{
    object  key;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle it */
    }

    if (present("_tutorial_castle_key", this_player()))
    {
        if (parse_command(arg, ({}),
            "[the] [large] 'key' 'in' / 'into' [to] 'drawer'"
          + " / 'nightstand' / 'stand'"))
        {
            write("Realizing the key might be important, you decide"
              + " against it.\n");
            return 1;
        }
    }

    if (!Open)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [a] [large] 'key' / 'all' 'from' [the] [small] "
      + "'stand' / 'nightstand' / 'drawer'"))
    {
        if (parse_command(arg, ({}),
            "[a] [the] [small] 'key' / 'keys'"))
        {
            write("The key is inside the drawer.\n");
            return 1;
        }

        if (parse_command(arg, ({}),
            "[a] [the] 'key' / 'keys' 'in' [the] [small] 'drawer'"
          + " / 'stand' / 'nightstand'"))
        {
            write("Use syntax: <get [item] from [place]>\n");
            return 1;
        }

        return 0; /* give it to the mudlib */
    }

    if (present("_tutorial_castle_key", this_player()))
    {
        write("You have already taken it.\n");
        return 1;
    }

    key = clone_object(OBJ_DIR + "castle_key");
    write("You take the large key from the drawer, shutting the"
      + " drawer afterwards.\n");
    Open = 0;

    if (key->move(this_player()))
    {
        write("You can't carry the key so you drop it on the floor.\n");
        key->move(this_object(), 1);
    }

    set_alarm(1.0, 0.0, &write("A voice booms: WRETCHED FOOL!"
      + " RETURN WHAT YOU HAVE STOLEN!\n"));

    return 1;
} /* get_key */


/*
 * Function name:        mess_with_drawer
 * Description  :        let the player open and close the drawer
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
mess_with_drawer(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [small] 'drawer' / 'stand' / 'nightstand'"))
    {
        if (parse_command(arg, ({}),
            "[the] 'coffin'"))
        {
            write("A strange force prevents you from getting near the"
              + " coffin.\n");
            return 1;
        }

        return 0; /* bad syntax */
    }

    switch(query_verb())
    {
        case "open":
        case "pull":
            if (Open)
            {
                write("The drawer is already open.\n");
                return 1;
            }

            write("You pull the drawer in the nightstand open.\n");
            Open = 1;
            return 1;
            break;
        case "push":
        case "close":
            if (Open)
            {
                write("You push the drawer in the nightstand"
                  + " closed.\n");
                Open = 0;
                return 1;
            }

            write("The drawer is already closed.\n");
            return 1;
        case "lock":
        case "unlock":
            write("There doesn't seem to be any lock on the drawer.\n");
            return 1;
    } /* switch(query_verb()) */

    return 0; /* shouldn't ever happen. */
} /* mess_with_drawer */


/*
 * Function name:        do_search
 * Description  :        allow the player to search things in the room
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (!strlen(arg) || (member_array(arg,
        ({ "stand", "nightstand", "small stand",
           "small nightstand", "small drawer", "drawer",
           "coffin" }) ) == -1))
    {
        return "Your search reveals nothing special.\n";
    }

    switch(arg)
    {
        case "stand":
        case "nightstand":
        case "small stand":
        case "small nightstand":
            return "After searching, you notice that the nightstand"
              + " has a small drawer near the top.\n";
            break;
        case "drawer":
        case "small drawer":
            if (!Open)
            {
                return "It seems like you could open the drawer.\n";
            }

            if (!present("_tutorial_castle_key", this_player()))
            {
                return "You notice nothing special about the drawer,"
                  + " but it does contain a large key.\n";
            }

            return "You notice nothing special about the drawer. It"
              + " is empty.\n";
            break;
        case "coffin":
            return "You can't get near the coffin because of some"
              + " strange force surrounding it.\n";
            break;
        default:
            return "You search around the area, but don't find anything"
              + " of interest.\n";
    }

    return "Your search does not reveal anything at all.\n";
} /* do_search */
