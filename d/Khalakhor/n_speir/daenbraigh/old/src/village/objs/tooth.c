/*
 * Elven tooth
 * TAPAKAH 10/2005
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>
#include "../../daenbraigh.h"
#include "../../village/village.h"

void
create_food()
{
  ::create_food();
  
  set_name(V_OBJID + "tooth");
  add_name("tooth");
  set_adj("elven");
  set_pname("teeth");
  set_short("elven tooth");
  set_pshort("elven teeth");
  set_long("A tooth. It looks elven and it seems to very very old.\n");
  add_prop(OBJ_I_VOLUME,1);
  add_prop(OBJ_I_WEIGHT,1);
  set_amount(1);
}
