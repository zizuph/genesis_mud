
inherit "/std/object";

#include <stdproperties.h>

create_object()
{
set_short("funny green moss");
set_name("moss");
set_adj("funny");
add_adj("green");
add_name("_rhosgobel_quest_moss");
set_long(break_string(
    "This is a funny green moss.  You wonder what it's purpose might "+
    "be.\n",75));

}
