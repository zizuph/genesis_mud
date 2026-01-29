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
  set_name(({"mail","double","elven"}));
  set_pname(({"mails","doubles","elven"}));
  set_adj("green");
  set_long("@@query_long@@");
  set_ac(29);
  set_at(A_BODY);
  set_am( ({ -1, 1, 0 }) );
  
  add_prop(OBJ_I_WEIGHT,21000);
  add_prop(OBJ_I_VOLUME,20000);
  add_prop(OBJ_I_VALUE,3000);
}

string query_long()
{
  return(BS("This is a green double mail made of silver. \n"));
}

init()
{
  ::init();
}

