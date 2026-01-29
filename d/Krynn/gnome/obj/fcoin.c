inherit "/std/object";
 
#include <stdproperties.h> 	/* All prop definitions */
#include <macros.h>		/* QCTNAME and QTNAME macro */
#include "/d/Krynn/common/defs.h"

create_object()
{
    seteuid(getuid());
    set_name("coin");
    set_adj("unusual");
    set_adj("gold");
    set_short("unusual gold coin");
    set_long(BS("The light piece of metal gleams in the sun and somehow "
	+ "looks special. Then you realize to your dismay that this is not "
	+ "a real coin at all, but a cheap fake. A label is stamped in the "
	+ "back of the coin.", 70));
    add_item("label", "@@read");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_VALUE, 0);
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("walk", "cwalk");
    add_action("toss", "ctoss");
}

toss(str)
{
    write("You toss the coin up into the air and catch it again.\n");
    say(QCTNAME(TP) + " tosses a coin into the air and catches it.\n");
    return 1;
}

walk()
{
    write("You walk the coin across your knuckles, a dazzling" +
	" display of manual dexterity.\n");
    say(QCTNAME(TP) + " walks a coin across " + TP->query_possessive() +
	" knuckles.\nNeat trick...\n");
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
	"This product can: 'cwalk', 'ctoss'" +
	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on coin")
    {
        write(read());
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}

