#include "defs.h"
inherit "/std/weapon";
/* Vision's sword, Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    set_adj("ghostly");
    set_short("ghostly sword");
    set_long("Seemingly formed of whisps of air, it is nearly transparent!\n");
    set_dt(W_SLASH | W_IMPALE);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_hit(50);
    set_pen(45);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_DROP,1);
}

void
do_destroy()
{
    string message =  "The " + short() + " disappers!\n";
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

