/* Knight patrollers for the battlements of the new Vingaard, */
/* by Morrigan 1/11/97. (Taken from Teth's Toede)             */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "../local.h"
#include "../knight/guild.h"

inherit M_FILE
inherit VSTD + "vin_knight_base";
inherit AUTO_TEAM

inherit "/std/act/domove";
inherit "/std/act/action";

void
create_knight_npc()
{
    set_level(3);
    set_act_time(10);
}
