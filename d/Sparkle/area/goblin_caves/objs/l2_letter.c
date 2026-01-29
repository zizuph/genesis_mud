/*
 * letter from boy in love
 * Boreaulam, Oct 2013
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/std/object";

string name;

void
create_object()
{
    set_name("letter");
	add_name("envelope");
    add_name(LEVEL2_QUEST_LETTER);
    set_adj("closed");
    set_short("closed letter");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

/*
 * Function name: init
 * Description:   Init all commands suplied by the letter.
 */
public void
init()
{
    ::init();

    add_action("open_letter", "open");
}

public string
get_letter_name()
{
	return name;
}

public int
open_letter(string what)
{
    if (!id(what))
    {
		notify_fail("Open what?\n");
		return 0;
    }
	notify_fail("This letter is not for you and you decide to leave " +
        "the envelope closed.\n");
	return 0;
}

public void 
set_letter_name(string arg)
{
	name = arg;
    set_long("This closed envelope has some crudely drawn letters " +
        "scrawled across the front. With some work, you are able to " +
        "decipher the name of the person this letter has been " +
        "addressed to: " + name + ".\n");
}

