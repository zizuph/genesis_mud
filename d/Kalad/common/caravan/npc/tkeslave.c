#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("slave");
    set_race_name("elf");
    set_adj("pitiful");
    set_short("pitiful elf");
    set_pshort("pitiful elves");
    set_long("This must be the most pitiful elf you have ever laid eyes "+
      "upon. Gone is the elfs joyous countenance, gone is his love of life "+
      "and gone is his freedom. He is a total slave of the Knights of Thanar.\n");
    set_stats(({10, 20, 5, 30, 15, 10}));
    set_alignment(500);
    set_skill(SS_UNARM_COMBAT, 15);
    set_act_time(6);
    add_act("groan");
    add_act("moan");
    add_act("cry");
    add_act("sob");
    add_act("sniff");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_knight_prestige(-3);
}
