/*
 * speckled_egg.c
 *
 * The seagull egg that you can collect from birdsnests on the
 * rocky shores of Silvanesti.
 * 'break' it to change it into an edible object.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit "/std/food";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S
public int break_egg(string arg);

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_object
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creating the object with descriptions.
 *
 */
public void
create_food()
{
    set_name("egg");
    add_name(EGGNAME);

    set_adj(({ "grey", "speckled" }));
    set_short("grey speckled egg");

    set_long("Small but tough shelled, this grey speckled egg is " +
        "a nice example of an egg coming from the nest of a " +
        "seagull. Being a little larger in size than the average " +
        "chicken egg, these eggs are usually white, greyish or " +
        "brown in colour and often have dark spots.\n");

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 55);
    add_prop(OBJ_I_VALUE, 5);

    set_amount(1);

    // We need to be able to clone a broken egg from here.
    setuid();
    seteuid(getuid());
}


/*
 *  FUNCTION : init
 *  Arguments: none
 *  Returns  : void
 * 
 *  Adds the action to break the egg.
 *
 */
public void
init()
{
    ::init();

    ADD(break_egg, "break");
}


/*
 *  FUNCTION : command_eat
 *  Arguments: none
 *  Returns  : string - fail message.
 * 
 *  Used when player eats the egg. Fail message is generated.
 *
 */
public mixed
command_eat()
{
    return "The delicious fluids inside the egg is protected by a " +
        "thick shell, making it hard to eat. It would probably be " +
        "possible to break the egg open.\n";
}


/*
 *  FUNCTION : break_egg
 *  Arguments: string - arguments given after the break command.
 *  Returns  : int - 0 if fail, 1 if success.
 * 
 *  Checks if you want to break open the egg so that it can be eaten.
 *
 */
public int
break_egg(string arg)
{
    string break_desc = "Carefully, you give the shell of the egg " +
        "a small hit, breaking it open.";
    string noun;

    if (!stringp(arg) || arg == "")
    {
        NF("Break what?\n");

        return 0;
    }

    if (parse_command(arg, TO, "[open] [the] / [an] %w", noun))
    {
        if (noun == "eggs")
        {
            break_desc = "Being careful not to mess up your eggs, " +
                "you decide to break open one egg at the time. " +
                break_desc;
        }

        if (noun == "egg" || noun == "eggs")
        {
            break_desc = break_desc + "\n";

            write(break_desc);
            say(QCTNAME(TP) + " carefully breaks the shell of " +
                "an egg.\n");

            clone_object(RSOBJS + "speckled_egg_broken")->move(TP, 1);
            reduce_heap_size(1);

            return 1;
        }
    }

    NF("Break what?\n");

    return 0;
}

