/*
 * ~/trash.c
 *
 * A simple trash can to get rid of unwanted items.
 */
#pragma strict_types

inherit "/std/container";
#include <stdproperties.h>

public static int alarm_id;

public void
create_container(void)
{
    set_name("hole"); 
    set_adj("black");
    set_long("This "+ short() +" looks like a good place to dispose "+
        "of all manner of things.\n");

    set_no_show_composite(1);

    add_prop(OBJ_I_VALUE,  1);
    add_prop(OBJ_M_NO_GET, 1);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 90000);  // 90 litres
    add_prop(CONT_I_MAX_WEIGHT, 2500000); // 250 kilos
}

public void
empty_trash(void)
{
    alarm_id = 0;
    all_inventory()->remove_object();
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (alarm_id)
        return;

    /* Five minutes from first item. */
    alarm_id = set_alarm(300.0, 0.0, empty_trash);
}
