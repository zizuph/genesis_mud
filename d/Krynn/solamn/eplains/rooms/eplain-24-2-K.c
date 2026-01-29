#include "../local.h"
inherit TDIR+"eplain-K";

public void
create_eplains_room()
{
    ::create_eplains_room();

    add_std_exits();
    add_exit(KALAMAN_LINK,"southeast","@@pass_gate@@");
    add_exit("/d/Ansalon/kalaman/caravan/outside","southwest",0);
    add_invis_exit("/d/Ansalon/kalaman/city/o20","south",0);
}
