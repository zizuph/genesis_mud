#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/haven/local.h";

inherit "/d/Krynn/std/baaz";
inherit AUTO_TEAM

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/d/Krynn/std/patrol";

object staff;

void
create_baaz()
{
    int i;

    for (i = 0; i < 6; i++)
	set_base_stat(i, 80 + random(40));

    add_name(({"hooded_figure", "figure", "hooded figure"}));
    set_short("hooded figure");
    set_pshort("hooded figures");
    set_long("Long robes shroud these tall figures, and hooded cloaks "+
      "cover the robes. Even their feet and hands are wrapped in cloth. "+
      "They appear to be nervous, and beneath the shadowy hoods, you think "+
      "you can spot two dark glittering eyes.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_act_time(7);

    add_act("@@staff");

    set_pick_up_team(({"hooded_figure"}));
    set_patrol_time(50);
    set_patrol_path(({ "nw", "emote hisses in a foreign tongue.", "nw",
	"nw", "nw", "emote raises a fist in the air, shrieking angrily!",
	"nw", "nw", "w", "nw", "emote hisses: The sstaff, we musst find "+
	"the sstaff!", "w", "w", "e", "scowl", "e", "se", "emote hisses "+
	"something at the other hooded figures.", "e", "se", "emote peers "+
	"intently at the bushes lining the road, apparently looking for "+
	"something.", "se", "se", "emote hisses: If we return the sstaff, "+
	"he will be most pleassed...", "se", "se", "emote hisses: The "+
	"sstaff wass sstolen from our order, and our brother requiress "+
	"itss healing powersss...", "se" }));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_WEP_AXE, 70);
    set_skill(SS_WEP_CLUB, 70);
    
    set_all_hitloc_unarmed(40);

    if (!random(5))
    {
        staff = clone_object(RDIR + "bladed_staff");
        staff->move(TO);
    }
}

public void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
staff()
{
    if (staff)
    {
	command("emote rasps in a thickly accented voice: We musst take "+
	  "thiss sstaff back now...");
	return;
    }

    command("emote rasps in a thickly accented voice: We musst find a "+
      "a sstaff before we return...");
}

