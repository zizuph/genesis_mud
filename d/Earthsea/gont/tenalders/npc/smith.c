#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/intro";

#include <ss_types.h>

public void
create_earthsea_monster()
{
    set_name("pelle");
    set_living_name("_pelle_");
    add_name(({"man", "human", "smith", "blacksmith"}));
    add_adj(({"middle-aged", "muscular"}));
    set_long("By his soot-stained face and "+
        "clothes, you can tell his profession is that of a "+
        "blacksmith.\n");
    set_stats(({ 200, 150, 250, 70, 70, 150 }));
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_title("blacksmith");
    set_act_time(60);
    set_chat_time(30);
    add_chat("Where is that boy when I need him? Always out "+
        "roaming when there's work to be done!");
    add_chat("The Kargs are coming! We must forge weapons to "+
        "defeat them!");
    add_act("emote brings his great hammer down hard "+
        "onto a piece of metal on the anvil.");
    add_act("emote stokes the fire, until it is red hot.");
    add_ask(({"work", "job", "task", "quest", "need"}),
        "The smith grunts out: I ain't got no work right now, but I might " +
        "some day soon!\n");
    add_equipment(({ "/d/Earthsea/gont/tenalders/wep/hammer",
        "/d/Earthsea/gont/tenalders/arm/smith_overalls" }));
}
