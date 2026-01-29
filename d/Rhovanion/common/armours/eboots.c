/*
 * eboots.c
 * Elven boots
 * Written by Daneel november 1993
 *
 */

#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <formulas.h>
#include "/d/Rhovanion/defs.h"

create_armour()
{
  set_name(({"boots","double","elven"}));
  set_pname(({"boots","doubles","elven"}));
  set_adj("green");
  set_long("@@query_long@@");
  set_ac(15);
  set_at(A_FEET);
  set_am( ({ -1, 1, 0 }) );
  
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,5000);
  add_prop(OBJ_I_VALUE,1000);
}

string query_long()
{
  return(BS("This is a green boots made of metal. \n"));
}

init()
{
  ::init();
}
