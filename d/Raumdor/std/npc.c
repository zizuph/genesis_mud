#pragma strict_types
#pragma save_binary
#include "defs.h"
inherit "/std/npc";
inherit "/std/combat/humunarmed";
inherit "/std/act/action";
inherit "/std/act/add_things";
inherit "/std/act/asking";

public void
create_npc()
{
    ::create_npc();
}

public int
query_raumdor_npc()
{
    return 1;
}

void
seen_emote(string text)
{
    TELL_SEEN(TO, QCTNAME(TO) + " " + text + "\n");
}

public void
test_special()
{
    object enemy;
    if (enemy = query_attack())
        special_attack(enemy);
}

public int
wiz_join(object wiz)
{
    if (my_leader)
        return 0;

    if (!wiz->set_leader(this_object()))
        return 0;

    if (IN_ARRAY(wiz, query_team()))
        return 1;

    if (!my_team)
        my_team = ({});

    my_team += ({ wiz });
    return 1;
}

public string
query_combat_file()
{
    return "/std/combat/chumanoid";
}

