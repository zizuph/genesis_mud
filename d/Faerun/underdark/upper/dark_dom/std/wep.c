#include "../defs.h"

inherit (P_UPPERDARK_STD + "wep");

public void
dark_dom_wep(void)
{
}

nomask public void
create_upperdark_weapon(void)
{
    set_faerun_region("dark dominion");
    dark_dom_wep();
}
