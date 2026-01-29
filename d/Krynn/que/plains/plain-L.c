#include "local.h"
inherit TDIR+"plain_base";

void
create_plains_room()
{
    set_short("Outside Que Shu");
    set_special_short("Outside of Que Shu");
    set_long("You are standing just outside the entrance of Que Shu. " +
	     "Towards your west, a path continues into the wilderness " +
	     "in the direction of Que Teh and Que Kiri, " +
	     "east is the small village of Que Shu.\n");

    add_std_exits();
}
