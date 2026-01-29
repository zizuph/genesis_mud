#include "defs.h"
inherit "/std/weapon";
/* Shade's dagger, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("black");
    add_adj("shadow");
    set_short("black shadow dagger");
    set_long("Its form is made up of nothing but swirling black shadows.\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_KNIFE);
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,300);
}

void
do_destroy()
{
    string message =  "The " + short() + " dissipates into thin air!\n";
    if (living(E(TO)))
        E(TO)->catch_msg(message);
    else
        TELL_CAN_SEE(E(TO), message);
    remove_object();
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if(living(dest) && !dest->query_raumdor_undead())
        set_alarm(0.0, 0.0, "do_destroy");
}

