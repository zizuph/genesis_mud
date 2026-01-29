/*
 * gauntlets.c
 * Elven Gauntlets
 * Written by Daneel november 1993
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <formulas.h>
#include "/d/Rhovanion/defs.h"

create_armour()
{
  set_name(({"gauntlets","padded","elven"}));
  set_pname(({"gauntlets","padded","elven"}));
  set_adj("green");
  set_long("@@query_long@@");
  set_ac(14);
  set_at(A_HANDS);
  set_am( ({ 2, 0, -2}) );
  
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,5000);
  add_prop(OBJ_I_VALUE,1000);
}

string query_long()
{
  return(BS("This is a pair of green gauntlets. \n"));
}

init()
{
  ::init();
}

