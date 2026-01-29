
inherit "/std/object";

#include <stdproperties.h>

create_object()
{
set_short("obsidian coin");
set_name("coin");
set_adj("obsidian");
add_name("_sw_ent_quest_coin");
set_long(break_string(
    "This is an odd obsidian coin.  It is quite shiny, and totally"
    +" black in color, smooth all over.  You marvel at what"
    +" a treasure such a coin must be.\n",75));

}
