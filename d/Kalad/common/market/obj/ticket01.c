/*                                          */
/*    A ticket to see the fortune teller.   */
/*                                          */
/*                 -Rico 24.01.95           */
/*                                          */

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include <cmdparse.h>

create_object()
{
    set_name("ticket");
    set_pname("tickets");

    set_short("ticket");
    set_pshort("tickets");
    set_long("This ticket will permit you to see "+
       "the fortune teller in the Market.\n");

    add_prop(OBJ_I_VALUE, 10); 
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 1);
}
 
