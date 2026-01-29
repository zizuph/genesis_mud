
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

object from;

create_object()
{
    set_name("orb");
    add_name("_walkers_returning_object_");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_no_show();
}

init()
{
    ::init();
    add_action("go_back","back");
}

go_back()
{
    write("You close your eyes and concentrate.\n");
    say(QCTNAME(this_player())+" closes "+this_player()->query_possessive()+
        " eyes in concentration, then disappears in a flash of light!\n");
    tell_room(from,QCTNAME(this_player())+" appears in a flash of light!\n");
    this_player()->move_living("M",from,1,0);
    remove_object();
    return 1;
}

void
set_return_location(object obj)
{
    from = obj;
}

object
query_return_location()
{
    return from;
}
