/*
 * dcamp5x3.c
 *
 * Draconian camp  -  05 x 03
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit CAMPBASE;

public int mud_path();
public string show_pile();
public int set_search_time();

object wolf_piv, wolf_iv;
int key_found = 0;

public void
reset_kurinost_room()
{
    key_found = 0;

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
        "Blocking any passage east and south of here is an " +
        "especially large and smelly pile of refuse.");

    // Set up descriptions about the paved path.
    generate_path("west and southwest, further into the mudfilled " +
        "pit.");

    set_short("muddy refuse pit");
    set_long(show_long_desc);

    remove_item("pile");
    add_item(({ "pile", "piles", "refuse pile", "refuse piles",
        "garbage pile", "garbage piles" }), show_pile);

    // Calls to add_search will have stime increased by +5 seconds.
    add_search(({ "pile", "refuse pile", "garbage pile"}),
        set_search_time, "search_pile", 1);

    add_exit(RSROOMS + "dcamp4x3", "west", mud_path, 5);
    add_exit(RSROOMS + "dcamp4x4", "southwest", mud_path, 5);

    setup_tells();
    KURINOSTMAP;

    reset_room();
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

    say(QCTNAME(who) + " searches around a pile of garbage for a " +
        "while, reminding you disturbingly of a gully dwarf.\n");

    // Does the player have awareness over 9? Then allow the search!
    if (!key_found)
    {
        object key = clone_object(RSOBJS + "rusty_key");
        key->move(who, 1);
        key_found = 1;

        return "You search around the pile of rubbish for a while, " +
            "finding only a small rusty iron key for your troubles.\n";
    }
    else
    {
        return "You search around the pile of rubbish for a while, " +
            "finding nothing of interest and questioning your sanity.\n";
    }
}

public string
show_pile()
{
    string add_desc = " and what appears to be hobgoblin droppings.";
    string wolf_desc = "";

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
