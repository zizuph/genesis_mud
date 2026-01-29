inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* Vision's Armour, by Sarr
 * 2017-05-25 Malus: Set OBJ_M_NO_DROP
 */
void
create_armour()
{
    ::create_armour();
    set_name("fullplate");
    set_adj("ghostly");
    set_short("ghostly fullplate");
    set_long("Seemingly formed of whisps of air, it is nearly transparent!\n");
    set_ac(40);
    set_at(A_BODY | A_HEAD | A_LEGS | A_ARMS);
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,8600);
    add_prop(OBJ_I_VALUE,120);
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

