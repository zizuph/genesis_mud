/* The anti magic object that belongs to the anti magic scroll. */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("_anti_magic_scroll_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_NO_GET, 1);
}

void
remove_antimagic(object me)
{
    environment(me)->remove_prop(ROOM_M_NO_MAGIC);
    me->remove_object();
}

void
apply_no_magic(int duration)
{
    environment(this_object())->add_prop(ROOM_M_NO_MAGIC, "This area is under " +
                    "the effect of strong abjuration magic.\n");
    set_alarm(itof(duration), 0.0, &remove_antimagic(this_object()));
}

