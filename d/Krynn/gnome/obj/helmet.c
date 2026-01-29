inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_armour()
{
    seteuid(getuid());
    set_name("helmet");
    set_short("gnomish helmet");
    set_adj("gnomish");
    set_long(BS(""+
      "A helmet made of boiled leather and metal.  A label is stamped "+
      "into the rim."+
      "", 70));
    add_item(({"label","label on helmet","helmet label"}), "@@read");
    set_ac(10);
set_am(({1, 1, -2}));
    set_at(A_HEAD);
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("rap", "rap");
}

rap()
{
    if (!query_worn(TO))
    {
    	write("You have to wear the helmet to use the emote!\n");
    	return 1;
    }
    write("You rap yourself on the head.  Your ears ring a bit," +
	" but the helmet \nprotects you.\n");
    say(QCTNAME(TP) + " raps " + TP->query_objective() +
	"self on the head.\n");
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    	"This product can: 'rap'" +
    	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on helmet")
    {
        write(read());
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
