inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_short("pair of gnomish boots");
    set_pshort("pairs of gnomish boots");
    set_adj("gnomish");
    set_long(BS(""+
      	"A pair of hard-soled boots.  Not very comfortable, really, " +
      	"but they do a good job of protecting your feet in tunnels.  " +
      	"A label is sewn into the rim of each boot." +
      	"", 70));
    add_item("label", "@@read");
    set_ac(6);
set_am(({-2, 0, 2}));
    set_at(A_FEET);
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("clomp", "clomp");
}

clomp()
{
    if (!query_worn(TO))
    {
    	write("You have to wear the boots to use the emote!\n");
    	return 1;
    }
    write("You clomp about in your gnomish boots, making quite a racket.\n");
    say(QCTNAME(TP) + " clomps about noisily in " + TP->query_possessive() +
	" hard-soled boots.\n");
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    	"This product can: 'clomp'" +
    	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on boots")
    {
    	write(read());
	return 1;
    }
    notify_fail("Read what?\n");
    return 1;
}
