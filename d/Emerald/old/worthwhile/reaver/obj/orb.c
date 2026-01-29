inherit "/std/object";

static object guardian;

void
create_object()
{
    set_name("orb");
    set_adj("black");

    set_long("A black orb about eight centimeters in diameter.  " +
        "It is extremely cold to the touch and very heavy.\n");

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 270);
    add_prop(OBJ_I_VALUE,  10000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public void
set_guardian(object ob)
{
    guardian = ob;
}

public void
call_guardian()
{
    if (!guardian)
    {
        remove_alarm(guardian_alarm);
        guardian_alarm = 0;
        return;
    }
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (!guardian_alarm && guardian && !env->id("reaver_chest"))
    {
        guardian_alarm = set_alarm(3.0, 300.0, call_guardian);
    }
}
