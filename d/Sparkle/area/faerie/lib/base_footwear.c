/* Base footwear file for shoes and sandals
 * Finwe, September 2002
 */
inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"

int alarm_id;

void create_shoes() {}

void
create_armour()
{
  
    set_ac(1);
    set_at(A_FEET);

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 275);
    add_prop(OBJ_I_VOLUME, 500);
    create_shoes();

}

void
leave_env(object from, object to)
{
    ::leave_env();
    remove_alarm(alarm_id);
}

int
remove()
{
   remove_alarm(alarm_id);
   return 1;

}
