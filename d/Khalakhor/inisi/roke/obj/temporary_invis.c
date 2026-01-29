inherit "/std/object";

#include <stdproperties.h>

#define PATH   ("/d/Khalakhor/inisi/roke/*")

void remove_effect();
void check_path();

void
create_object()
{
    set_name("_temporary_spirit_envis");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);


    set_alarm(5.0, 10.0, &check_path());
    set_alarm(300.0, 0.0, &remove_effect());
}

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);
    ob->inc_prop(OBJ_I_INVIS, 5);
    ob->catch_msg("You feel yourself getting transparent.\n");
}

void
leave_env(object ob, object from)
{
    ::leave_env(ob, from);
    ob->dec_prop(OBJ_I_INVIS, 5);
}

void
remove_effect()
{
    environment()->catch_msg("You are visible again.\n");
    remove_object();
}

void
check_path()
{
    object player = environment();
    
    if (!objectp(player)) {
        remove_effect();
        return;
    }

    if (!environment(player) || !wildmatch(PATH, file_name(environment(player)))) {
        remove_effect();
    }
}
