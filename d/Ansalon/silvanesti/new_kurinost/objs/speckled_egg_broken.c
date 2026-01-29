/*
 * speckled_egg_broken.c
 *
 * The seagull egg that you can collect from birdsnests on the
 * rocky shores of Silvanesti.
 * This object can be eaten, as it has been 'broken'.
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
 *  FUNCTION : create_food
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
        "brown in colour and often have dark spots. " +
        "This egg has had its shell broken, making it easy to " +
        "open and eat.\n");

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 55);
    add_prop(OBJ_I_VALUE, 5);

    set_amount(15);
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
 *  Returns  : 1 - success.
 * 
 *  Used when player eats the egg. Adds a description and returns 1.
 *
 */
public mixed
command_eat()
{
    write("Quickly removing the broken parts of the shell, you " +
        "eat the egg.\n");

    return 1;
}


/*
 *  FUNCTION : break_egg
 *  Arguments: string - arguments given after the break command.
 *  Returns  : int - 0 if fail.
 * 
 *  The eggshell is already broken, so this will fail.
 *
 */
public int
break_egg(string arg)
{
    NF("The eggshell is already broken, exposing the fluids " +
        "inside.\n");

    return 0;
}

