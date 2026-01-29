
inherit "/std/scroll";
#include "local.h"
#include <stdproperties.h>

create_scroll()
{
	set_name("note");
	set_adj("secret");
	set_long("A secret note, just for your eyes.\n");
	set_file("/d/Calia/amelia/copies/note_text");

}


