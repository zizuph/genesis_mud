inherit "/std/monster";

#include <macros.h>

void create_monster()
{
    set_act_time(7);
    add_act("@@sing@@");
}

string
sing()
{
    tell_room(environment(), QCTNAME(this_object()) + " sings a song: ....\n", this_object());
    return "";
}
