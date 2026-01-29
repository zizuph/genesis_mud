
inherit "/std/object";

#include "/d/Rhovanion/farlong.h"
#include <stdproperties.h>

create_object()
{
set_short("funny blue weed");
set_name("weed");
set_adj("funny");
set_adj("blue");
add_name("_rhosgobel_quest_weed");
set_long(break_string("This is a funny blue weed."
	+"  It seems rather unique; you wonder if it"
	+" might have some magical properties.\n",75));

}
