#pragma strict_types

inherit "/d/Gondor/common/npc/mosquito";
inherit "/std/act/action";

#include <stdproperties.h>

public void
create_mosquito()
{
    set_name("bee");
    set_adj(({"angry", "golden", "honey"}));
    set_race_name("bee");
    set_long("A golden honey bee. These fierce little insects "+
        "are very protective of their hive.\n");
    set_poison_file("/d/Gondor/common/poison/weak_bee_sting");
    set_act_time(30);
    add_act("emote buzzes loudly.");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able "+
        "to carry something.\n");
}
