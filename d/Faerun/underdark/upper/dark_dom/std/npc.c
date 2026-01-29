#include "../defs.h"

inherit (P_UPPERDARK_STD + "npc");

public void
dark_dom_npc(void)
{
}

nomask public void
create_upperdark_npc(void)
{
    set_faerun_region("dark dominion");
    set_no_unarmed_combat(1);
    dark_dom_npc();
}
