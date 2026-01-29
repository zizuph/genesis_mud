/*
 * /d/Gondor/anorien/cairandros/obj/letter.c
 *
 * A letter of requisition for some pipeweed
 *
 * Varian - February, 2020
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "../../defs.h"

int do_read(string str);

public void
create_object()
{
	set_name("letter");
	set_name("_letter_of_requisition_");
	set_adj("small");
	add_adj("folded");

	set_short("small folded letter");
    set_long("This small letter is folded, but you could " +
        "still read it.\n");
}

int
do_read(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        write("Letter of Requisition\n\nThis letter entitles the " +
            "bearer to one crate of 'Old Toby' pipeweed from the " +
            "stores of Farmer Reginard Longhole of Waymeet as " +
            "purchased by the Army of Gondor.\n\nArdain, " +
            "Quartermaster of Cair Andros.\n");
        SAYBB(" reads a small letter.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You need to pick up the letter " +
            "first!\n");
        return 1;
    }

    notify_fail("You can't seem to read the letter for some strange " +
        "reason. Contact a wizard for help.\n");
    return 0;
}

public void
init()
{
    ::init();
    add_action("do_read", "read");
}
