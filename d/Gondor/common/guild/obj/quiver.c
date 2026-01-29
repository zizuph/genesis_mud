#pragma strict_types

inherit "/std/receptacle";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

nomask void
create_receptacle()
{
    set_name("quiver");
    set_adj(({"simple", "leather"}));
    set_long("It is a simple quiver made of hardened leather. The quiver " +
	     "has a small cap that can be used to close it, and a strap " +
	     "so you can wear it on your back.\n");
    
    add_prop(CONT_I_WEIGHT, 400);
    add_prop(CONT_I_VOLUME, 400);
    add_prop(CONT_I_MAX_WEIGHT, 25000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_IS_QUIVER, 1);
    add_prop(OBJ_I_VALUE, 144);
    
    set_slots(A_BACK);
    set_layers(4);
    set_looseness(20);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
