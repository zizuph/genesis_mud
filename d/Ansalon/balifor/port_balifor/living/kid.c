#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         AM_FILE

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;
    set_name("kid");
    add_name("boy");
    set_adj("young");
    set_race_name("human");
    set_short("young boy");
    set_long("The young boy stares wide eyed at everything around " +
      "him. You wonder what such a young one is doing in " +
      "an Inn.\n");
    set_stats(({10,15,60,5,5,10}));
    set_alignment(400);
    set_knight_prestige(-200);

    set_act_time(0);
    add_act("cough");
    add_act("peer cur");
    add_act("emote says: Another brandy!\n" +
      "Chuckling under his breath, William pours him a water.");
    add_act("emote goes and sits at the bar, but quickly gets up " +
      "after noticing the expression on the face of the " +
      "Innkeeper, William.");
    add_act("emote stares wide-eyed at the kender.");
    add_act("emote pretends to sword fight an invisible enemy, " +
      "wielding a butter knife he found on the ground.");

}
