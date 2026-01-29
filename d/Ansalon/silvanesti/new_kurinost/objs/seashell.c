/*
 * seashell.c
 *
 * A small worthless seashell, found at the beach.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/object";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_object
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creates the object and sets up descriptions.
 *
 */
public void create_object()
{
    string shellcolour = one_of_list(({ "black", "crimson",
        "indigo", "plum", "turquoise", "olive" }));

    set_name("seashell");
    add_name("shell");
    set_adj(shellcolour);
    add_adj("small");

    set_short("small " + shellcolour + " seashell");
    set_long("Similar to many other small seashells that you " +
        "usually find on beaches, this " + shellcolour +
        " seashell is only a few centimeters in diameter. The " +
        "outside has beautiful patterns, with rough parallel " +
        "lines on the " + shellcolour + " surface and the inside " +
        "of the shell is smooth and clean.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 5 + random(5));
}

