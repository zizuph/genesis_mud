/*
 * A black robe for the WoHS
 */

#include "/d/Krynn/common/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "../local.h"

inherit ROBEBASE;

void
create_robe()
{
   set_name("robe");
   set_adj("dark");
   add_adj("black");

   set_short("dark velvet robe");

   set_long("It is a soft dark velvet robe. It has long sleeves and " +
	    "a large hood. The robe has some magical symbols " +
	    "written in silvery color on it, they are probably runes " +
	    "of protection.\n");
}

public nomask int
query_wohs_change_order(int align)
{
    if (align > 0) return 1;

    return 0;
}

public string
query_robe_color() { return "black"; }
