/**********************************************************************
 * - tbarrel.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 10/2004                             - *
 * - Modified by Valen 10/2004                                      - *         
 **********************************************************************/
#pragma strict_types

#include "../default.h"
#include <composite.h>
inherit "/std/container";

#define TIMEOUT	10.0

int alarm_active = 0;
int recycling = 0;
int alarm_id;

void
create_container()
{
    set_name("barrel");
    set_adj(({"large", "round" }));
    add_name(({"trashcan", "can"}));
    set_short("large round barrel");
    set_long("This is a large round barrel that has been made from "+
      "heavy oak wood. A spell has been cast upon this barrel so that "+
      "what ever is placed within it will be recycled. It has been "+
      "placed here for broken or unwanted items that need to be "+
      "disposed of. Beware!! If you place a non-intended item within "+
      "it too will be lost. You will not be able to retrieve the item. "+
      "So please be careful in what you place inside.\n");
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_IN, 1);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    
}   

void
recycle_all(void)
{
    object *all;

    all = all_inventory(TO);
    if(sizeof(all))
    {
        tell_room(environment(TO), "You notice " + COMPOSITE_DEAD(all) +
            " contained in the " + TO->short() + " dissolve" +
            (sizeof(all) > 1 ? "" : "s") + ".\n");
        recycling = 1;
        all->remove_object();
        recycling = 0;
    }
    alarm_active = 0;
}

void prepare_alarm(void)
{
    if(alarm_active)
    {
        remove_alarm(alarm_id);
    }
    alarm_id = set_alarm(TIMEOUT, 0.0, recycle_all); 
    alarm_active = 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    prepare_alarm();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if(!recycling) prepare_alarm();
}
