/*
 * dc_document.c
 *
 * The strange document.
 *
 * Copyright (C): Kellon, september 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/object";

// P R O T O T Y P E S
public string show_parchment();
public int read_parchment(string arg);

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
    set_name("_kurinost_blank_parchment");
    add_name("parchment");
    set_adj(({ "blank" }));
    set_short("blank parchment");
    set_long(show_parchment);

    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 25);
}


/*
 *  FUNCTION : init
 *  Arguments:
 *  Returns  :
 * 
 *  Add some actions to this object.
 *
 */
public void
init()
{
    ::init();
    ADD(read_parchment, "read");
}


/*
 *  FUNCTION : show_parchment
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Returns a long description of the parchment.
 *
 */
public string
show_parchment()
{

    return "Some kind of thick skin has been used to make this " +
        "parchment although you are not sure what kind of animal " +
        "would produce it. It is blank.\n";
}


/*
 *  FUNCTION : read_parchment
 *  Arguments: string - argument to the command
 *  Returns  : string - the scroll.
 * 
 *  Returns the scroll.
 *
 */
public int
read_parchment(string arg)
{

    if (arg == "document" || arg == "parchment")
    {
        write("The parchment is blank. There is nothing to read.\n");
        say(QCTNAME(TP) + " unfolds a blank piece of parchment " +
            "and briefly looks at it.\n");
        return 1;
    }

    NF("Read what?\n");

    return 0;
}
