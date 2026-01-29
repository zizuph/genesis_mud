/* Ticket for the task for applicants for the Calian guild.


*/


inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/domain.h"
#include "/d/Calia/glykron/palace/specials/orange_task.h"

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    set_adj("strange");
    set_long("It is a strange ticket. It has "+
        "the words \"shout Praise Caliana\" written on it.\n");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_NO_DROP,0);
    add_prop(OBJ_I_NO_STEAL,1);
    add_prop(OBJ_M_NO_SELL,1);
}

