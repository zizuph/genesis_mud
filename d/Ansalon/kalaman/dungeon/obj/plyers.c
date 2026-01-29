inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("hammer");
    set_adj("gnomish");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("gnomish hammer");
    set_long("A standard hammer for use when making or repairing" +
	" things.  Pretty hefty.\nA label has been stamped on it.\n");
    add_item(({"label","label on hammer","hammer label"}), "@@read");
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(13);
    set_pen(7);
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
    if (str == "label" || str == "label on hammer" || str == "hammer label")
    {
        write(read());
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
