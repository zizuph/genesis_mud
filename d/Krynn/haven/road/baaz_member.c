/* Modified - Karath March 13th, 1997 - added figure and hooded figure names
 *
 * 2004-12-30 - Cotillion
 * - Fixed 'mind' attacks.
 * 
 */
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

void
create_baaz()
{
    int i;

    for (i = 0; i < 6; i++)
	set_base_stat(i, 100 + random(40));

    add_name( ({"hooded_figure", "figure", "hooded figure"}));
    set_short("hooded figure");
    set_pshort("hooded figures");
    set_long("Long robes shroud these tall figures, and hooded cloaks "+
      "cover the robes. Even their feet and hands are wrapped in cloth. "+
      "They appear to be nervous, and beneath the shadowy hoods, you think "+
      "you can spot two dark glittering eyes.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_act_time(7);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_WEP_AXE, 70);
    set_skill(SS_WEP_CLUB, 70);
    
    set_all_hitloc_unarmed(40);
}


void init_team_pickup() { }
