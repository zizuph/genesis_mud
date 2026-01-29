
/*
 * rusty_key.c
 *
 * A small key you can find in the draconian camp. Used to open a door
 * inside a small shed.
 * As this is not a normal door with a normal exit, this key is not
 * a standard key. As such it will inherit /std/object and be used
 * as an object to open a locker of sorts. 
 *
 * Copyright (C): Kellon, september 2012
 *
*/
#pragma strict_types


// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/object";


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
    set_name(DC_KEYNAME);
    add_name("key");
    set_adj(({ "small", "rusty", "iron"}));
    set_short("small rusty iron key");
    set_long("Dark and dirty, the surface of the small rusty iron " +
        "key is plain and crude, without markings of any kind. At " +
        "about ten centimeters long, it is a fairly long key and " +
        "the stem seems quite rusty. It seems likely that the " +
        "iron will break if it is used too much.\n");

    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 2);
}
