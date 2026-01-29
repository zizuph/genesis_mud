#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

public void
create_object()
{
    set_name("harmonica");
    set_adj(({"small", "old"}));
    set_short("small harmonica");
    set_long("This is a harmonica, which is about as long as your "+
        "hand and is flat and narrow. It is made from wood, and "+
        "you can see some metallic parts on it as well. There are holes "+
        "on either side for blowing into, and the reeds inside it "+
        "produce a sound which sometimes resembles music.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 25);
    add_cmd_item("harmonica", ({"play", "blow"}), "@@play_me");
}

public string
play_me()
{
    object tp = this_player();

    if (tp == environment(this_object()))
    {
        tp->catch_msg("You blow into the harmonica and play a lively "+
            "tune.\n");
        tell_room(environment(tp), QCTNAME(tp) + " blows into "+
            tp->query_possessive() + " harmonica and plays a lively tune.\n",
            ({tp}));
        return "";
    }

    return "You don't have the harmonica.\n";
}
