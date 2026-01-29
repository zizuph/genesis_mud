
#pragma save_binary
#pragma strict_types

inherit "/std/message";

#include "/d/Khalakhor/sys/basic.h"
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <macros.h>

public varargs void
hook_message_destroyed(object room, object player)
{
    tell_room(room, "The dragonscroll mysteriously bursts into "+
      "flames and disappears.\n");
}

public void
create_message()
{
    set_name("dragonscroll");
    set_pname("dragonscrolls");
    set_short("dragonscroll");
    set_pshort("dragonscrolls");
    set_long("A dragonscroll, borne by elven nymph dragons.\n");
    set_adj("paper");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

public string
message_description()
{
    return "The message in the dragonscroll is:\n" + EXPAND_LINE("~", 60) +
        "\n\n"+ query_message() + "\n"+ EXPAND_LINE("~", 60) + "\n\n";
}

