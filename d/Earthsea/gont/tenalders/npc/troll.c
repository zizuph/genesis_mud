#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include <ss_types.h>
#include <macros.h>

public void
create_earthsea_monster()
{
    set_name("ophotee");
    add_name("_ophotee_");
    set_race_name("troll");
    set_adj(({"red-haired", "green-skinned"}));
    add_adj("bridge");
    set_long("A red-haired, green-skinned bridge troll. "+
        "These creatures are known to live under bridges. At night "+
        "they creep into people's houses and steal prized "+
        "possessions.\n");
    set_stats(({ 14 + random(20), 10 + random(30),
        35 + random(30), 5, 5, 100 }));
    set_gender(G_NEUTER);
    set_act_time(60);
    add_act("emote snarfles.");
    add_act("emote drools excessively.");
    add_act("emote scratches its behind.");
    add_act("emote gnaws on a fish head.");
    add_act("emote eyes you hungrily.");
    set_all_hitloc_unarmed(1);
    set_default_answer(QCTNAME(this_object()) + " snarfles.\n");
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_POLEARM, 25 + random(10));
    set_skill(SS_PARRY, 20+ random(15));
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);
    add_equipment(({ "/d/Earthsea/gont/tenalders/wep/trident" }));
}
