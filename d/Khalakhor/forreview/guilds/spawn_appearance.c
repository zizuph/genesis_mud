#include "guild.h"
#include "/d/Khalakhor/sys/defs.h"
#include <wa_types.h>

#define IM_AC  A_UARM_AC
#define SH_AC  A_UARM_AC
#define BL_AC  A_UARM_AC

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case W_LEFT:
	return "left claw";
    case W_RIGHT:
	return "right claw";
    case W_BOTH:
	return "joint claws";
    case W_FOOTL:
	return "left rear paw";
    case W_FOOTR:
	return "right rear paw";
    default:
	return "mind";
    }
}

public string
query_gender_string()
{
    return "wolf-shaped";
}

public string
race_sound()
{
    return ONE_OF(({"growls", "snarls", "wails", "grunts", "mutters"}));
}

public void
setup_spawn_looks(object who)
{
    who->set_hitloc_unarmed(TS_HEAD, ({IM_AC, SH_AC, BL_AC}),
      15, "wolf-shaped head");
    who->set_hitloc_unarmed(TS_RARM, ({IM_AC, SH_AC, BL_AC}),
      10, "right forearm");
    who->set_hitloc_unarmed(TS_LARM, ({IM_AC, SH_AC, BL_AC}),
      10, "left forearm");
    who->set_hitloc_unarmed(TS_TORSO, ({IM_AC, SH_AC, BL_AC}),
      45, "fur covered body");
    who->set_hitloc_unarmed(TS_LEGS, ({IM_AC, SH_AC, BL_AC}),
      20, "hind legs");
}
