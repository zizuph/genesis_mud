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

   set_name("poo");

   set_short("stinky pile of orc poo");
   add_adj(({"stinky","pile", "orc"}));

   set_long("This is a stinky pile of orc poo. It is green colored an smells rancid and of half rotted food.\n");

   add_prop(OBJ_I_WEIGHT, 1400);
   add_prop(OBJ_I_VOLUME, 14000);
   add_prop(OBJ_I_VALUE, 0);
}
