#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/haven/local.h"
#include <ss_types.h>

inherit STD + "dwarf_base";
inherit AUTO_TEAM

object weapon;

create_dwarf_npc()
{
    int i;

    set_level(10);
    set_gender(0);
    set_name("colin");
    set_living_name("colin");
    set_adj(({"tall", "noble"}));
    set_title("Ironfist");
    set_long("Tall and noble, this dwarf is quite obviously in "+
      "charge of the camp here. A long flowing beard hangs down "+
      "to almost his waist, silvery grey. Two charcoal coloured "+
      "eyes look around with the wisdom that comes with age, "+
      "something this dwarf definitely has.\n");

    set_stats(({ 150, 140, 155, 120, 125, 140 }));
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    
    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(LIVE_I_QUICKNESS, 100);
    set_introduce(1);
    set_short(0);
    set_pick_up_team(({"dwarf"}));
}

public void
init_living()
{
    init_team_pickup();
    ::init_living();
}

