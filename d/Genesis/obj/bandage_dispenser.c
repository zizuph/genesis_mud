/*
 * Neverending container for bandages
 */
inherit "/std/container";

#include <stdproperties.h>

void load_box();

void
create_container()
{
    set_name("box");
    add_name("_bandage_dispenser");
    set_adj(({ "medical", "supply" }));

    set_long("It is a simple wooden box with a sign reading 'medical supplies' on it.\n");

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_M_NO_INS, 1);
    add_prop(OBJ_M_NO_GET, 1);

    
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);

    setuid();
    seteuid(getuid());
    
    load_box();
}

void
load_box()
{
    object ob;

    add_prop(CONT_M_NO_INS, 0);
    
    if (!(ob = present("bandage", this_object())))
    {
        ob = clone_object("/d/Genesis/obj/bandage");
        ob->set_heap_size(30);
        ob->move(this_object());        
    }

    ob->set_heap_size(100);
    
    add_prop(CONT_M_NO_INS, 1);
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    set_alarm(0.1, 0.0, load_box);
}
