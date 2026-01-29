/*
 * Copy of the Scroll of Isildur in Cair Andros
 * /d/Gondor/anorien/cairandros/obj/oldbook.c
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
	set_name("book");
	set_name("_scroll_of_isildur_");
	set_adj("old");
	add_adj("musty");

	set_short("musty old book");
    set_long("This book appears to be in very bad condition, " +
    	"and many parts of it are illegible. It appears to " +
    	"be a diary or an account of some sort. You could " +
    	"try to read it.\n");
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
        write("The early parts of the book are completely illegible, " +
        	"but you are able to make out the following passage:\n\n" +
        	"The Great Ri-- --all go now to be an heirl--- -- -he " +
        	"North Kin---- -ut records of i- --all be left in " +
        	"Gond-- where also dwell t-- --irs of Elen--- lest a " +
        	"tim- ---- -hen the memory of t---- -reat matters shall " +
        	"grow dim.\n\nThis is followed by another passage which " +
        	"is in much better condition:\n\n-- -as hot when I first " +
        	"took it, hot as a glede, and my hand was scorched, so " +
        	"that I doubt if ever again I shall be free of the pain " + 
        	"of it. Yet even as I write it is cooled, and it seemeth " +
        	"to shrink, though it loseth neither its beauty nor its " +
        	"shape. Already the writing upon it, which at first was " +
        	"as clear as red flame, fadeth and is now only barely " +
        	"to be read. It is fashioned in an elven-script of " +
        	"Eregion, for they have no letters in Mordor for such " +
        	"subtle work; but the language is unknown to me. I deem " +
        	"it to be a tongue of the Black Land, since it is foul " +
        	"and uncouth. What evil it saith I do not kno- ---\n\n" +
        	"There is more written, yet unfortunately the words " +
        	"have been totally ruined by the passage of time.\n");
        SAYBB(" studies a musty old book.");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You would need to be holding the " +
        	"book in order to read it.\n");
        return 1;
    }

    notify_fail("This book is too damaged for you to read.\n");
    return 0;
}

public void
init()
{
    ::init();
    add_action("do_read", "read");
    add_action("do_read", "study");
}
