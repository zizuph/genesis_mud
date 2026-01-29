/* The drawer under the desk in the mages laboratory.
 *
 * Aridor, 09/95 
 */

#include "local.h"

inherit "/std/receptacle";


void
create_receptacle()
{
    set_name("drawer");
    set_long("This is a fairly large drawer under the desk.\n");
    set_key(DRAWER_KEY);
    set_pick(80);
    set_no_show_composite(1);
    add_prop(CONT_I_LOCK,1);
    add_prop(CONT_I_CLOSED,1);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 96000);
    add_prop(CONT_I_MAX_WEIGHT,10000000);
    add_prop(CONT_I_RIGID,1);
}


void
reset_it()
{
    if (P("horn",TO))
      return;
    seteuid(getuid(TO));
    clone_object(HORN)->move(TO,1);
}
