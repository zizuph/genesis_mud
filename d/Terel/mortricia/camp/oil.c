/* Some oil. Mortricia 921002.  */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()

#define OIL_TIME 300

int aid=0;

public void
create_object()
{
    set_name("oil");
    set_short("layer of slippery oil");
    set_pshort("layers of slippery oil");
    set_long("The oil is really slippery. It seems impossible to " +
             "remove, you better wait until it has dried up.\n");
    set_adj("slippery");
    add_prop(OBJ_I_VALUE, 90);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (to && living(to) && !aid)
        aid = set_alarm(itof(OIL_TIME), -1.0, remove_object);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (from && living(from))
        from->catch_msg("The oil disappears.\n");
}

public void
remove_object()
{
    if (aid) aid = 0;

    ::remove_object();
}
