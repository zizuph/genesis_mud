inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_armour()
{
    seteuid(getuid());
    set_name("chainmail");
    set_short("gnomish chainmail");
    set_adj("gnomish");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_long("A suit of chainmail made of several layers of very " +
	"small links.  It is quite\nflexible, and looks well kept.\n");
    add_item("label", "@@read");
    set_ac(22);
    set_am(({-2, 3, -1}));
    set_at(A_BODY);
}

init()
{
    ::init();
    add_action("do_read", "read");
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    "\n";
}

do_read(str)
{
    if (str == "label" || str == "label on chainmail")
    {
    	write(read());
	return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
