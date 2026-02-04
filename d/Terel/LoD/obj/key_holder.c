/*
 * key_holder.c
 *
 */
inherit "/std/container";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>

public void
create_container()
{
    set_name("key holder");
    add_name("holder");
    set_adj("circular");
    
    set_long("It's a plain iron ring used as a key holder.\n");
    
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_VOLUME, 28);
    add_prop(CONT_I_MAX_WEIGHT, 1000);
    add_prop(CONT_I_MAX_VOLUME, 280);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_VALUE, 24);
}

public void
move_back(object ob, object from)
{
    if (!ob) return;
    
    if (from)
        ob->move(from, 1);
    else
        ob->move(ETO, 1);
        
    if (from && living(from))
        from->catch_msg("The " + ob->short() + " cannot be hooked to the " +
                        short() + ".\n");
}

public void
enter_inv(object ob, object from)
{
    if (ob && function_exists("create_object", ob) == "/std/key")
    {
        ::enter_inv(ob, from);
        return;
    }
    set_alarm(1.0, 0.0, &move_back(ob, from));
}
