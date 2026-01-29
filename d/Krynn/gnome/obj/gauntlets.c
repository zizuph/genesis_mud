inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_armour()
{
    seteuid(getuid());
    set_name("gauntlets");
    set_pname("gauntlets");
    set_short("set of gnomish gauntlets");
    set_pshort("sets of gnomish gauntlets");
    set_adj("gnomish");
    set_long("A sturdy pair of thick leather gloves with metal" +
	" platelets over the back.\nProbably used for working on" +
	" machinery rather than in combat, by the look\nof them." +
	"  A label has been sewn into each.\n");
    add_item(({"label","label on gloves","gloves label","gauntlet label",
		 "gauntlets label","label on gauntlets"}), "@@read");
    set_ac(7);
set_am(({-2, -1, 3}));
    set_at(A_HANDS);
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("clench", "clench");
}

clench()
{
    if (!query_worn(TO))
    {
    	write("You have to wear the gauntlets to use the emote!\n");
    	return 1;
    }
    write("You clench your fists in frustration.\n");
    say(QCTNAME(TP) + " clenches " + TP->query_possessive() +
	" fists in frustration.\n");
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    	"This product can: 'clench'" +
    	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on gauntlets" || 
	str == "gauntlet label" || str == "label on gloves" ||
	str == "gloves label" || str == "gauntlets label")
    {
        write(read());
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
