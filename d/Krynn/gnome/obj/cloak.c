inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_armour()
{
    seteuid(getuid());
    set_name("cloak");
    set_short("gnomish cloak");
    set_adj("gnomish");
    set_long("Finely woven out of black cloth. A small label is sewn" +
	" into the hem.\n");
    add_item("label", "@@read");
    set_ac(2);
set_am(({-2, -1, 3}));
    set_at(A_ROBE);
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("swirl", "swirl");
    add_action("pose", "cpose");
}

swirl()
{
    if (!query_worn(TO))
    {
    	write("You have to wear the cloak to use the emote!\n");
    	return 1;
    }
    write("You swirl the cloak about you with a flourish.\n");
    say(QCTNAME(TP) + " swirls " + TP->query_possessive() +
	" cloak about in an impressive manner.\n");
    return 1;
}

pose()
{
    if (!query_worn(TO))
    {
    	write("You have to wear the cloak to use the emote!\n");
    	return 1;
    }
    write("You strike a dramatic adventurer pose, cloak fluttering" +
	" behind you in a sudden\ngust of wind.\n");
    say("Taking advantage of a sudden gust of wind, " + QTNAME(TP) +
    	" strikes\na dramatic pose, cloak fluttering behind " +
	TP->query_objective() + ".\n");
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    	"This product can: 'swirl', 'cpose'" +
    	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on cloak")
    {
    	write(read());
	return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
