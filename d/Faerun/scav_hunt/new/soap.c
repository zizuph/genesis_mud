/*
 * Scavenger Hunt item
 * Finwe, October 2015
*/

inherit "/std/object";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_object()
{

   set_name("soap");

   set_short("bar of soap");
   add_adj(({"fragrant"}));

   set_long("This is a fragrant bar of soap. It is oval shaped and a  white colored. It smells of roses and wildflowers and a favorite of wealthy people.\n");

   add_prop(OBJ_I_WEIGHT, 227);
   add_prop(OBJ_I_VALUE, 0);
}
