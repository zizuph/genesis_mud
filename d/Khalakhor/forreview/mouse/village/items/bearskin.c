/* bear pelt coded by Elizabeth Cook/Mouse, January 1997 */

inherit "/std/object";
#include <stdproperties.h>
#include "../../mouse.h"

void create_object()
{
   set_name("bear skin");
   add_name(({"fur","pelt","skin","hide"}));
   set_short("bear skin");
   set_long("This shaggy brown hide comes from a bear.\n");
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 4000);
}

int query_fur()
{
   return 1;
}

int query_fur_value()
{
   return 1500; 
}

