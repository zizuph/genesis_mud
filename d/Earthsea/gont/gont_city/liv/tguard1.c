/*
* Tower guard , changed from standard gont guard by Ged 5/10/2001
*/

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/gont/gont_city/liv/basic_guard.c";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "basic_guard.h"
#include "/sys/money.h"

inherit "/d/Earthsea/gont/tenalders/npc/auto_teaming.c";

void
create_earthsea_monster()
{
    ::create_guard();
    set_gender(random(1));
    set_levels(0);
    add_name("_guard1_");
    set_long(TO->query_long() + capitalize(TO->query_pronoun()) +
      " appears to be a raw recruit.\n");
    (MONEY_MAKE_GC(random(5)))->move(TO);
    add_equipment(({WEAPONS[random(sizeof(WEAPONS))],
	HELM }));

set_pick_up("guard");
}

void init_living()
{
 ::init_living();
 init_team_pickup();
}

