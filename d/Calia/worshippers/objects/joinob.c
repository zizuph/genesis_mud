
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

int count = 0;

string query_auto_load()
{
    return MASTER + ":" + count;
}

int
dest_joinob()
{
    remove_object();
    return 1;
}

/* We'll give them 50 logins to complete the quest   */
/* If they don't finish in 50 logins, they will have */
/* to ask someone to permit them to join again.      */

void
init_arg(string arg)
{
    count = atoi(arg) + 1;
    if (count >= 50)
        set_alarm(5.0, 0.0, dest_joinob);
    
}

create_object()
{
    set_name("Worshippers Joining Object");
    add_name(I_CAN_JOIN);
    set_short("join_object");
    set_long("It's invisible...who cares?\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    set_no_show();
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP,1);
}
