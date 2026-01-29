/*
 * A lost book of Sauron's, containing forbidden knowledge
 * /d/Gondor/rhovanion/dolguldur/obj/spellbook.c
 *
 * Varian - January, 2021
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
	set_name("_mm_spellbook_");
	add_name("spellbook");
    add_name("book");
	set_adj("midnight");
	add_adj("black");

	set_short("midnight black spellbook");
    set_long("This spellbook is so black that it feels like " +
        "it is sucking the light out of the air around you. " +
        "You can feel the thrum of power eminating from the " +
        "book when it is nearby. You could attempt to read " +
        "the book, but you get the feeling that you would " +
        "do so at your own risk.\n");
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
        write("The black tongue of Mordor burns in your brain as you study " +
            "knowledge not meant for mere mortals! Within these pages " +
            "is the key to unlocking the deepest and darkest secrets " +
            "of how magic can be manipulated to conjure up life beyond " +
            "death - the dreaded skills of a most powerful Necromancy.\n");
        SAYBB(" reads a midnight black spellbook.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You would need to be holding the " +
        	"book in order to read it.\n");
        return 1;
    }

    notify_fail("This book is too damaged for you to read, you should " +
        "contact the wizards of Gondor.\n");
    return 0;
}

public void
init()
{
    ::init();
    add_action("do_read", "read");
    add_action("do_read", "study");
}
