inherit "/std/receptacle";
#include "/d/Kalad/defs.h".
#include "/sys/stdproperties.h"
int turns;

/* by korat */
/* 2017-06-04 Malus: Set short and pshort */ 
    
void
create_receptacle()
{
    set_name("cylinder");
    set_pname("cylinders");
    set_adj("metal");
    set_short("metal cylinder");
    set_pshort("metal cylinders");
    set_long("A small metal cylinder with a small lid on the top. It looks " +
           " like the kind tied to a pigeon's leg to deliver messages.\n");
    add_prop(CONT_I_WEIGHT, 10);
    add_prop(CONT_I_MAX_WEIGHT, 20);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_VOLUME, 150);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_M_NO_SELL,1);
    set_alarm(0.0,0.0,"add_message");
}

add_message()
{
    object message;

    seteuid(getuid(this_object()));
    message = clone_object("/d/Kalad/common/central/obj/message");
    message->move(TO);
    change_prop(CONT_I_CLOSED, 1);
}
