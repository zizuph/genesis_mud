#include "/d/Raumdor/defs.h"
#include <stdproperties.h>
inherit "/std/monster";
inherit "/d/Raumdor/common/lib/pathways";

void
create_monster()
{
    add_name("wayfarer");
    set_short("wayfarer");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    autopath("beach", 10.0);
}

void
do_autopath_stopped()
{
    command("emote hikes out of view.");
    remove_object();
}

