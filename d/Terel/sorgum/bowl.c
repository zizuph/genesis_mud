inherit "/std/container";

#pragma strict_types

#include <stdproperties.h>

int heat(string str);
int crush(string str);
int pulverize(string str);
int herb_filter(object ob);
int mix(string str);
object ro = find_player("rohim");

void
create_container()
{
    set_short("small bowl");
    add_name("bowl");
    add_adj("small");
    set_long("This a simple cheramic bowl.\n");
    add_prop(CONT_I_VOLUME, 150);
    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 6000);
    add_prop(CONT_I_TRANSP, 1);
}

void
init()
{
    ::init();
    add_action(heat, "heat");
    add_action(crush, "crush");
    add_action(pulverize, "pulverize");
    add_action(mix, "mix");
}

int
heat(string str)
{
    int i;
    object fire;
    object *items;
    notify_fail("Heat what?\n");
    if (!str)
        return 0;
    notify_fail("Heat what over what?\n");
    if (!parse_command(str, environment(environment()), " 'bowl' [over] [at] [in] [the] %o ", fire))
        return 0;
    if (!fire->query_prop(OBJ_I_HAS_FIRE))
    {
        write("You can't heat the bowl over that.\n");
        return 1;
    }
    items = deep_inventory();
    dump_array(items);
    items = filter(items, &herb_filter(this_object());
    dump_array(items);
    write("You heat the bowl.\n");
    
    return 1;
}

int
herb_filter(object ob)
{
    int n;
    ro->catch_msg(file_name(ob));
    return sscanf(file_name(ob), "/std/herb#%d", n);
}

int crush(string str) 
{
    return 0;
}

int pulverize(string str)
{
    return 0;
}

int mix(string str)
{
    return 0;
}

                      


    
