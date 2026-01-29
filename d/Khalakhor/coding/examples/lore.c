inherit "/d/Khalakhor/std/scroll";
inherit "/d/Khalakhor/lib/lore";

#include <macros.h>
#include "/d/Khalakhor/sys/lore_bit1.h"
#include "/d/Khalakhor/sys/skills.h"

public void
create_khalakhor_scroll()
{
    set_name("scroll");
    set_adj(({"yellowed", "ancient"}));
    set_short("ancient yellowed scroll");
    set_long("This scroll contains various writings of "+
      "Khalakhorian Lore.\n");

    set_scroll_file("/d/Khalakhor/atlas/global/history");

    set_lore_skill(SS_KHALAKHOR_LORE_BIT1);
    set_lore_bits(LORE_BIT1_A);
}

public mixed
command_read(int more_flag)
{
    mixed result;

    result = ::command_read(more_flag);

    /// If the result is 1 then we were able to read the scroll
    //  So we test to see if the player learned any lore from the reading.
    if (result == 1)
	test_lore(this_player());

    return result;
}
