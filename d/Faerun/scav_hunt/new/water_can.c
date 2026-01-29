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

   set_name("can");

   set_short("watering can");
   add_adj(({"metal", "watering"}));

   set_long("This is a watering can. It is a round container with a spout on one side and a handle on the other. The spout has multiple small holes. Water pours through the spout to water plants and flowers.\n");

   add_prop(OBJ_I_WEIGHT, 907);
   add_prop(OBJ_I_VALUE, 0);
}
