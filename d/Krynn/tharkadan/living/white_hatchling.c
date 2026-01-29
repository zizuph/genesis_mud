
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
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
    set_age("hatchling");
    set_gender(random(2));
    set_colour("white");
    set_long("A hungry dragon hatchling, covered with white scales.\n");
    set_aggressive(1);
    set_base_stat(5, 150);

    remove_prop(OBJ_I_RES_FIRE);

    set_act_time(11);
    add_act("emote shrieks hungrily.");
    add_act("emote beats its juvenile wings.");
    add_act("emote flexes its juvenile wings.");
    add_act("emote clears its throat, emitting as it does a " +
      "small puff of frost.");
    add_act("emote stares at you with intensely cold and hungry eyes.");

    set_cact_time(11);
    add_act("emote shrieks hungrily.");
    add_act("emote beats its juvenile wings.");
    add_act("emote flexes its juvenile wings.");
    add_act("emote clears its throat, emitting as it does a " +
      "small puff of frost.");
    add_act("emote stares at you with intensely cold and hungry eyes.");

}

