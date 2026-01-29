#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Earthsea/lib/intro";
inherit "/d/Earthsea/lib/width_height";
inherit STDCAPTAIN;

public void
create_captain()
{
  ::create_captain();
    set_name("dravid");
    add_name("captain");
    set_adj(({"thin", "ascetic"}));
    add_prop(OBJ_M_NO_ATTACK, "You feel this man is "+
        "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls " +
        "harmlessly on thin air.\n");
    set_chat_time(45);
    set_long("This man is tall and gaunt, having " +
        "hard-calloused hands. While muscular, he is quite thin and " +
        "gives the appearance of one who leads an ascetic life.\n");
    set_living_name("_gont_port_coracle_captain");
    set_race_name("human");
    set_height("very tall");
    set_width("very thin");
    default_config_npc(60);
    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 45);
    set_skill(SS_DEFENCE, 34);
    set_alignment(200);
    add_act("stares quietly into the distance.");
}

public void
intro_hook(object tp)
{
    command("introduce myself");
    command("bow");
}
