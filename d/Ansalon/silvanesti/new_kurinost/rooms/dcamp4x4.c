/*
 * dcamp4x4.c
 *
 * Draconian camp  -  04 x 04
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit CAMPBASE;

// G L O B A L   V A R S
object wolf_piv, wolf_iv;

// P R O T O T Y P E S
public int mud_path();
public string show_pile();
public string show_shed();
public string show_wall();
public string show_boards();
public string show_window();
public int climb_shed();
public int set_search_time();

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: None
 *  Returns  : None
 * 
 *  Resetting the room.
 *
 */
public void
reset_kurinost_room()
{
    if (!objectp(wolf_piv))
    {
        wolf_piv = clone_object(RSLIVING + "wolf_piv");
        wolf_piv->move(TO);
    }

    if (!objectp(wolf_iv))
    {
        wolf_iv = clone_object(RSLIVING + "wolf_iv");
        wolf_iv->move(TO);
    }

    // Let the two wolves know each other for quick handling of
    // special attacks, etc.
    wolf_piv->set_brother(wolf_iv);
    wolf_iv->set_brother(wolf_piv);
}


/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    // Set up basic camp descriptions.
    generate_camp(DCAMP_MUDDYPIT,
        "Blocking any passage east, south and west of here is an " +
        "especially large and smelly pile of garbage.");

    // Set up descriptions about the paved path.
    generate_path("northwest and northeast, further into the " +
        "mudfilled pit.");

    set_short("muddy refuse pit");
    set_long(show_long_desc);

    remove_item("pile");
    add_item(({ "pile", "piles", "refuse pile", "refuse piles",
        "garbage pile", "garbage piles" }), show_pile);
    add_item(({ "shed", "wooden shed", "dirty shed", "small shed",
        "ramshackle shed" }), show_shed);
    add_item(({ "front wall", "north wall", "wall",
        "northern wall" }), show_wall);
    add_item(({ "boards", "board", "loose boards", "loose board" }),
        show_boards);
    add_item(({ "window" }), show_window);

    add_cmd_parse("[onto] [the] [small] [dirty] [wooden] [ramshackle] 'shed'",
        "climb", climb_shed);

    // Calls to add_search will have stime increased by +5 seconds.
    add_search(({ "pile", "refuse pile", "garbage pile"}),
        set_search_time, "search_pile", 1);

    add_exit(RSROOMS + "dcamp5x3", "northeast", mud_path, 5);
    add_exit(RSROOMS + "dcamp4x3", "northwest", mud_path, 5);

    setup_tells();
    KURINOSTMAP;

    reset_room();
}


/*
 *  FUNCTION : search_pile
 *  Arguments: Who - who did the search?
               What - what did the player search for?
 *  Returns  : String - description of the pile.
 * 
 *  Returns a description of the pile, based on a skill check.
 *
 */
public string
search_pile(object who, string what)
{
    string wolf_desc = "", show_desc = "";

    // If the wolves are here, then we cannot search the pile properly!
    if (objectp(wolf_iv) || objectp(wolf_piv))
    {
        if (objectp(wolf_piv) && objectp(wolf_iv))
        {
            wolf_desc = "a " + wolf_piv->short() + " quickly " +
                "rises, growling deeply, followed moments later " +
                "by an " + wolf_iv->short() + ". Staring " +
                "intensely at you, the two wolves position " +
                "themselves between you and the pile of garbage.";
            show_desc = "a " + wolf_piv->short() + " quickly " +
                "rises, growling deeply, followed moments later " +
                "by an " + wolf_iv->short() + ". Fixing " +
                QTNAME(who) + " with a stare, the two wolves " +
                "position themselves between " + QTNAME(who) +
                " and the garbage pile.";
        }
        else
        if (objectp(wolf_piv))
        {
            wolf_desc = "a " + wolf_piv->short() + " quickly " +
                "rises from next to the garbage pile and places " +
                "itself between you and the pile.";
            show_desc = "a " + wolf_piv->short() + " quickly " +
                "rises from next to the garbage pile and prevents " +
                HIM(who) + "from getting closer.";
        }
        else
        {
            wolf_desc = "an " + wolf_iv->short() + " quickly " +
                "rises from next to the garbage pile and places " +
                "itself between you and the pile.";
            show_desc = "an " + wolf_iv->short() + " quickly " +
                "rises from next to the garbage pile and prevents " +
                HIM(who) + "from getting closer.";
        }

        say(QCTNAME(who) + " tries to get closer to the rubble, " +
            "but " + show_desc + "\n");

        return "As you approach the pile of rubble to take a " +
            "closer look, " + wolf_desc + "\n";
    }

    say("Having climbed boldly up into the middle of the big " +
        "garbage pile, " + QTNAME(who) + " searches around for a " +
        "while and then steps down again.\n");

    // Does the player have awareness over 9? Then allow the search!
    if (who->query_skill(SS_AWARENESS) > 9)
    {
        who->add_prop(PLFOUNDSHED, 1);

        return "Climbing boldly up into the middle of the pile of " +
            "garbage, you start searching around for something of " +
            "value. It does not take long for you to realize that " +
            "it is probably futile to find anything in this pile. " +
            "Just as you are about to step out of the pile, you " +
            "notice a small, very dirty and ramshackle wooden " +
            "shed in the middle of the pile.\n";
    }
    else
    {
        return "Climbing boldly up into the middle of the garbage " +
            "pile, you start searching around for something of " +
            "value. It does not take long for you to realize that " +
            "it is probably futile to find anything in this pile " +
            "and you step down into the mud again. But then " +
            "again, you never were that skilled in finding hidden " +
            "things.\n";
    }
}


/*
 *  FUNCTION : show_window
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  returns the description of the window in the shed.
 *
 */
public string
show_window()
{
    if (PLFOUNDWINDOW)
    {
        return "From down here, it is not possible to see the " +
            "window, but you know it is up there on top of the " +
            "small wooden shed.\n";
    }

    return "Examine what?\n";
}


/*
 *  FUNCTION : show_pile
 *  Arguments: None
 *  Returns  : String - the description.
 * 
 *  Returns a description of the pile, based on a previous search.
 *
 */
public string
show_pile()
{
    string add_desc = " and what appears to be hobgoblin droppings.";
    string wolf_desc = "";

    if (TP->query_prop(PLFOUNDSHED))
    {
        // If the shed has been found, add a description of it here.
        add_desc = ", nasty hobgoblin droppings and in the middle " +
            "of the pile is a small, dirty and ramshackle wooden " +
            "shed.";
    }

    // If either wolf is here, then add a description of them.
    if (objectp(wolf_piv) || objectp(wolf_iv))
    {
        if (objectp(wolf_piv) && objectp(wolf_iv))
        {
            wolf_desc = "As you approach the pile to take a " +
                "closer look, you are met by the stares from a " +
                wolf_piv->short() + " and an " + wolf_iv->short() +
                ". Both wolves lie close to the garbage pile as " +
                "if guarding something. ";
        }
        else
        if (objectp(wolf_piv))
        {
            wolf_desc = "As you approach the pile to take a " +
                "closer look, you cannot help but notice the two " +
                "narrow yellow eyes from a " + wolf_piv->short() +
                " that follow your every move. ";
        }
        else
        {
            wolf_desc = "As you approach the pile to take a " +
                "closer look, you cannot help but notice the two " +
                "narrow red eyes from an " + wolf_iv->short() +
                " that follow your every move. ";
        }
    }

    return "Even the slightest breeze is enough to draw the " +
        "attention to the pile of garbage and refuse you have " +
        "found here. " + wolf_desc + "Everything not used by the " +
        "army is thrown into this pile, it seems. Old broken " +
        "weapons, torn rags, charred lumps of meat, some of them " +
        "half decomposed" + add_desc + " Several meters tall and " +
        "maybe as much as fifteen meters wide, the pile has " +
        "obviously been used for a while.\n";
}


/*
 *  FUNCTION : show_shed
 *  Arguments: None
 *  Returns  : String - the description of the shed.
 * 
 *  Returns a description of the small shed.
 *
 */
public string
show_shed()
{
    if (TP->query_prop(PLFOUNDSHED))
    {
        return "Half askew, the small wooden shed is barely " +
            "standing with half of the garbage pile bearing down " +
            "on it from the south side. Though nearing its " +
            "destruction, it is still standing and the front wall " +
            "seems least damaged.\n";
    }
    else
    {
        return "Examine what?\n";
    }
}


/*
 *  FUNCTION : show_wall
 *  Arguments: None.
 *  Returns  : String - the description of the shed.
 * 
 *  Description of the front wall of the shed.
 *
 */
public string
show_wall()
{
    if (TP->query_prop(PLFOUNDSHED))
    {
        return "Even with half of the garbage pile crushing down " +
            "on the small wooden shed, the front and northernmost " +
            "wall, seems mostly undamaged. Crudely built with " +
            "irregular wooden boards that seems to be nothing " +
            "more than some thick branches split in half down the " +
            "middle, the entire shed looks amateurishly built and " +
            "will surely not last long under the pressure of the " +
            "garbage pile. As you look around, you notice a few " +
            "small loose boards in the front of the shed. You " +
            "might be able to look inside through those.\n";
    }
    else
    {
        return "Examine what?\n";
    }
}


/*
 *  FUNCTION : show_boards
 *  Arguments: None.
 *  Returns  : String - the description of the boards.
 * 
 *  Description of the loose boards in the small shed.
 *
 */
public string
show_boards()
{
    string wolf_desc;

    // If the wolves are here, then no boards will be shown!
    if (objectp(wolf_piv) || objectp(wolf_iv))
    {
        if (objectp(wolf_iv) && objectp(wolf_piv))
        {
            return "As you approach the pile of garbage to " +
                "examine the shed, you are met by a deep angry " +
                "growl from a " + wolf_piv->short() + ". Rising " +
                "from its position next to the garbage pile, it " +
                "is quickly followed by an " + wolf_iv->short() +
                ". The two wolves watch you closely as you back " +
                "away from the pile again.\n";
        }
        else
        if (objectp(wolf_piv))
        {
            wolf_desc = "a " + wolf_piv->short();
        }
        else
        {
            wolf_desc = "an " + wolf_iv->short();
        }

        return "As you approach the pile of garbage to examine " +
            "the shed, you are met by a deep angry growl from " +
            wolf_desc + ". Rising from its position next to " +
            "the garbage pile the wolf steps forward as if " +
            "guarding something. You quickly step back from the " +
            "pile and it seems to calm the wolf down a bit.\n";
    }

    // If player has found the shed!
    if (TP->query_prop(PLFOUNDSHED))
    {
        TP->add_prop(PLFOUNDWINDOW, 1);

        return "Digging your way through the pile of garbage, you " +
            "manage to get close enough to the shed to be able " +
            "to peer through the loose boards. Though it is quite " +
            "dark inside, you manage to see a hole in the ceiling " +
            "that might be a window. You would have to climb up " +
            "onto the half-broken shed in order to enter through " +
            "that window.\n";
    }
    else
    {
        return "Examine what?\n";
    }
}


/*
 *  FUNCTION : climb_shed
 *  Arguments: None.
 *  Returns  : int 0/1 - did we solve the command? 1 = yes.
 * 
 *  Climb into the shed.
 *
 */
public int
climb_shed()
{
    string wolf_desc;

    // Player has not even found the shed!
    if (!TP->query_prop(PLFOUNDSHED))
    {
        NF("Climb what? It does not seem possible to climb onto " +
            "the pile of garbage as it would likely fall apart.\n");

        return 0;
    }

    // Player has not found the window in the shed. Not allowed to climb!
    if (!TP->query_prop(PLFOUNDWINDOW))
    {
        NF("From where you stand, there seems to be nothing " +
            "on top of the shed. It would be quite dangerous " +
            "to climb up there. You decide to stay out of the " +
            "pile of garbage.\n");

        return 0;
    }

    // The wolves are still here. Not allowed to climb!
    if (TP->query_prop(PLFOUNDWINDOW))
    {
        if (objectp(wolf_piv) || objectp(wolf_iv))
        {
            if (objectp(wolf_piv) && objectp(wolf_iv))
            {
                say(QCTNAME(TP) + " approaches the pile of " +
                    "garbage, but is stopped short as two wolves, " +
                    "a " + wolf_piv->short() + " and an " +
                    wolf_iv->short() + " advances on " + HIM(TP) +
                    ", growling deeply, forcing " + HIM(TP) +
                    " back away from the pile.\n");

                write("As you approach the pile of garbage to " +
                    "climb onto the shed, you are met by a deep " +
                    "angry growl from a " + wolf_piv->short() +
                    ". Rising from its position next to the " +
                    "garbage pile, it is quickly followed by an " +
                    wolf_iv->short() + ". The two wolves watch " +
                    "you closely as you back away from the pile " +
                    "again.\n");

                return 1;
            }
            else
            if (objectp(wolf_piv))
            {
                wolf_desc = "a " + wolf_piv->short();
            }
            else
            {
                wolf_desc = "an " + wolf_iv->short();
            }

            say(QCTNAME(TP) + " approaches the pile of garbage, " +
                "but is stopped short as " + wolf_desc +
                " advances on " + HIM(TP) + ", growling deeply, " +
                "forcing " + HIM(TP) + " back away from the pile.\n");

            write("As you approach the pile of garbage to climb " +
                "onto the shed, you are met by a deep angry growl " +
                "from " + wolf_desc + ". You quickly step back " +
                "from the pile and it seems to calm the wolf down " +
                "a bit.\n");

            return 1;
        }

        // Attempt to climb the shed!
        if (TP->resolve_task(TASK_ROUTINE, ({ TS_INT, SS_CLIMB })))
        {
            say(QCTNAME(TP) + " looks long and hard at something, " +
                "deep inside the garbage pile. With a nod of " +
                "determination, " + HE(TP) + " scrambles up " +
                "through the pile and disappears down through a " +
                "hole!\n");

            write("Pausing only briefly, you quickly find the " +
                "best way up onto the top of the shed and start " +
                "climbing. Creaking and groaning under your " +
                "weight, the shed seems to hold just barely. You " +
                "quickly scamper through the window in the top.\n");

            TP->move_living("M", RSROOMS + "dcshed", 1, 0);

            return 1;
        }
        else
        {
            // Failed the climb check, not allowed to climb!
            say(QCTNAME(TP) + " looks long and hard at " +
                "something, deep inside the garbage pile. With a " +
                "nod of determination, " + HE(TO) + " scrambles " +
                "up through the pile, but seems to have chosen a " +
                "bad path up. Stumbling down through the pile, " +
                QTNAME(TP) + " ends up in the thick mud again.\n");

            write("Pausing only briefly, you quickly find the " +
                "best way up onto the top of the shed and start " +
                "climbing. You quickly learn that you have picked " +
                "the wrong spot to start and you stumble through " +
                "the pile of garbage. Moments later you have to " +
                "give up and climb back down.\n");

            return 1;
        }
    }
}


/*
 *  FUNCTION : set_search_time
 *  Arguments: none.
 *  Returns  : int - Searchtime for searching the pile of rubble
 * 
 *  If the wolves are present, searchtime is cut short to one second,
 *  otherwise searchtime is 7 seconds.
 *
 */
public int
set_search_time()
{
    if (objectp(wolf_piv))
    {
        return -4;
    }
    else
    {
        return 2;
    }
}


/*
 *  FUNCTION : descend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you walk through the mud of the pit. Show
 *  additional description of the path.
 *
 */
public int
mud_path()
{
    write("Slosh! Slosh! Tearing your feet out of the wet sucking " +
        "mud with each step, you walk through the pit.\n");

    return 0;
}

