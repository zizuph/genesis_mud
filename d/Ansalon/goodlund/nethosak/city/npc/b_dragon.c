#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_age("ancient");
    set_colour("black");
    add_name("onyx");
    set_gender(G_FEMALE);
    set_long("This is one of the many black dragons that " +
      "has taken up residence far away from the city of " +
      "Neraka. This majestic creature almost completely fills " +
      "this dark cave, it emits a strong stench of sulphur " +
      "from it's mouth and nostrils. Its entire body is covered "+
      "with thick dark scales and it's long tail and immense wings "+
      "looks extremely dangerous.\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

