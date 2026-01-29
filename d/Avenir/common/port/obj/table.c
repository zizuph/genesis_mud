// file name: table.c
// creator(s): Ilyian, taken from Terel Christmas tree by Dust.
// purpose: Just for the fun of it.
/*
 * Revisions:
 *     Lucius, Jul 2017: Re-coded and cleaned up.
 *
 */
inherit "/std/object";

#include <composite.h>
#include <stdproperties.h>

#include "../port.h"

#define FNAME	(PORT +"obj/tablewriting")

public int max_items = 40, max_length = 75;
public string *items, base = "This large, solid oaken table seems to have "+
	"had a very long life here. The top is scarred by countless "+
	"carvings and writings made by patrons of the pub over the "+
	"years. You could probably carve a message into the table "+
	"if you felt like it. ";


public string
decoration(void)
{
    if (!sizeof(items))
    {
	return base +
	    "There is nothing carved in the table right now.\n";
    }

    return base + "The carvings on the table say " +
	COMPOSITE_WORDS(items) + ".\n";
}

public void
add_decoration(string str)
{
    int size = sizeof(items);

    if (++size > max_items)
    {
	int diff = size - max_items;
	items = items[diff..];
    }

    items += ({ str });

    if (file_size(FNAME)) rm(FNAME);
    write_file(FNAME, implode(items, "\n"));
}

public int
do_decorate(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }),
	    "[the] / [this] [message] [into] [the] [table] %s", str))
    {
	notify_fail("Carve what message into the "+ short() +"?\n");
	return 0;
    }

    if (strlen(str) > max_length)
    {
	write("Carving all of that would be too much work!\n");
	return 1;
    }

    add_decoration(str);

    write("You carve \"" + str + "\" into the "+ short() +".\n");
    say(QCTNAME(this_player()) + " carves some words into the tabletop.\n");
    return 1;
}

public void
start_decoration(void)
{
    if (file_size(FNAME) < 10)
	items = ({ "Stormy Haven rules!", "Jarod wuz here", });
    else
	items = explode(read_file(FNAME), "\n");
}

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("table");
    add_adj(({"scarred", "oaken"}));
    set_short("scarred oaken table");
    set_long("@@decoration");

    add_prop(OBJ_I_WEIGHT, 600000);
    start_decoration();
}

public void
init(void)
{
    ::init();
    add_action(do_decorate, "decorate");
    add_action(do_decorate, "carve");
}
