
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

create_object()
{
    set_short("meeting summoner");
    set_long("It's a meeting summoner.  Just do 'summon <player>'"+
        "to summon them.\n");
    set_no_show();
    add_prop(OBJ_M_NO_DROP,1);
}

do_respond()
{
    this_player()->move_living("X",environment(find_player("jaacar")));
    remove_object();
    return 1;
}

enter_env(object ob,object from)
{
    ::enter_env(ob,from);
    if (interactive(ob))
        tell_object(ob, "You feel you are being summoned by an "+
            "immortal presence.  You should 'accept' to respond "+
            "to the summons.\n");
    else
        remove_object();
}
  
init()
{
    ::init();
    add_action(do_respond,"accept");
}
