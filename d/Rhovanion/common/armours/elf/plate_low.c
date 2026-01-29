/*
 * plate.c
 * Elven platemail
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
  set_name(({"woven", "cord", "elven"}));
  set_pname(({"woven","cord","elven"}));
  set_adj("green");
  set_long("@@query_long@@");
  set_ac(5);
  set_at(A_BODY);
  set_am( ({ -1, 0, 1 }) );
  
  add_prop(OBJ_I_WEIGHT,4000);
  add_prop(OBJ_I_VOLUME,4000);
  add_prop(OBJ_I_VALUE,3000);
}

string query_long()
{
  return(BS("This is a green woven cord plate. \n"));
}

init()
{
  ::init();
}

