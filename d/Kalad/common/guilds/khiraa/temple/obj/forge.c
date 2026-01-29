inherit "/std/container";
#include "/d/Kalad/defs.h"

void
create_container()
{
    set_name("furnace");
    set_adj("blazing");
    set_short("blazing furnace");
    set_long("The furnace is large and resembles a well. Bright red "+
    "light glows from within. You could probably put something in it "+
    "to get rid of it.\n");
    add_prop(OBJ_M_NO_GET,1);
    add_prop(CONT_I_MAX_WEIGHT,100000);
    add_prop(CONT_I_MAX_VOLUME,1000000);
}

void
burn_it(object ob)
{
    tell_room(E(TO),"The "+ob->short()+" melts away into the "+
    "molten substance within.\n");
    ob->remove_object();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    set_alarm(1.0,0.0,&burn_it(ob));
}

