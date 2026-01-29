inherit "/d/Emerald/std/clone_handler";
#include "/d/Emerald/defs.h"
#define PRIV "/d/Emerald/triana/private/"
#define KAR "/d/Wiz/karath/workroom.c"

void create_clone_handler()
{
	set_default_area("/d/Wiz/karath/workroom.c");
	add_clone(PRIV + "elmo1.c", 8, 1, KAR);
	add_clone(PRIV + "elmo2.c", 8, 1, KAR);
	add_clone(PRIV + "elmo3.c", 9, 1, KAR);
	set_clone_handler_id("Elmo Clone Handler");
}
