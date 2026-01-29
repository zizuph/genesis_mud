#include "../defs.h"

inherit (P_UPPERDARK_STD + "arm");

public void
dark_dom_arm(void)
{
}

nomask public void
create_upperdark_armour(void)
{
    set_faerun_region("dark dominion");
    dark_dom_arm();
}
