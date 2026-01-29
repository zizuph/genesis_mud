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

// D E F I N I T I O N S

// G L O B A L   V A R S
int gSeal_broken = 0;

// P R O T O T Y P E S
public string show_parchment();
public int break_seal(string arg);
public int query_seal();
public int read_parchment(string arg);
public string show_seal();

#define PARCHMENT_FILE2    RSTXT + "parchment2.txt"
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
    set_name("_kurinost_camp_fake_secret_document_");
    add_name("parchment");
    set_adj(({ "folded" }));
    set_short("folded parchment");
    set_long(show_parchment);

    add_item("seal", show_seal);

    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 25);

    // We need to read from a file, so we need to set the ID's.
    setuid();
    seteuid(getuid());
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

    ADD(break_seal, "break");
    ADD(read_parchment, "read");
}

public int
query_seal()
{
    return gSeal_broken;
}

/*
 *  FUNCTION : show_seal
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Shows a description of the seal.
 *
 */
public string
show_seal()
{
    if (gSeal_broken)
    {
        return "The seal has been broken off from the parchment " +
            "and all you find is a black stain where it used to " +
            "be.\n";
    }

    return "Some kind of black wax has been stamped onto the " +
        "folded parchment, sealing it effectively. It appears a " +
        "thick finger has made a thumbprint into the wax to make " +
        "it stick.\n";
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
    if (gSeal_broken)
    {
        return "Some kind of thick skin " +
            "has been used to make this parchment although you " +
            "are not sure what kind of animal would produce it. " +
            "As the seal has been broken on the parchment, you " +
            "are able to read it.\n";
    }

    return "Some kind of thick skin has been used to make this " +
        "parchment although you are not sure what kind of animal " +
        "would produce it. You are unable to read the contents " +
        "without breaking the seal on the parchment.\n";
}


/*
 *  FUNCTION : break_seal
 *  Arguments: arg - the arguments given to the command.
 *  Returns  : int 0/1 - success or fail on the command.
 * 
 *  Breaking the seal on the document.
 *
 */
public int
break_seal(string arg)
{
    string noun;

    if (!stringp(arg) || arg == "")
    {
        NF("Break what? You could break the seal on the documents " +
            "if you wanted to.\n");

        return 0;
    }

    if (parse_command(arg, TO,
        "[open] [the] 'seal' [on] [the] [documents] / [document] / [parchment]",
                      noun))
    {
        if (gSeal_broken)
        {
            write("The seal on the parchment has already " +
                "been broken. You can read the parchment.\n");

            return 1;
        }

        write("You break off the wax seal on the parchment.\n");
        say(QCTNAME(TP) + " breaks the seal on a piece of " +
            "parchment.\n");

        gSeal_broken = 1;

        return 1;
    }

    NF("Break what? You could break the seal on the documents if " +
        "you wanted to.\n");

    return 0;
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
    if (!gSeal_broken)
    {
        write("You are unable to read the parchment unless you " +
            "break the seal.\n");

        return 1;
    }

    if (arg == "document" || arg == "parchment")
    {
        say(QCTNAME(TP) + " unfolds a piece of parchment " +
            "and reads it.\n");

        write("You unfold the parchment and read:\n");
        write(read_file(PARCHMENT_FILE2));

        return 1;
    }

    NF("Read what?\n");

    return 0;
}
