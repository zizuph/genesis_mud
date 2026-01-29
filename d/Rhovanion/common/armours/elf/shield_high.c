/*
 * shield.c
 * Elven shield
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
  set_name(({"shield","double","elven"}));
  set_pname(({"shields","doubles","elven"}));
  set_adj("green");
  set_long("@@query_long@@");
  set_ac(25);
  set_at(A_SHIELD);
  set_am( ({ 0, 0, 0 }) );
  
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,5000);
  add_prop(OBJ_I_VALUE,1000);
}

string query_long()
{
  return(BS("This is a green metal shield. \n"));
}

init()
{
  ::init();
}

